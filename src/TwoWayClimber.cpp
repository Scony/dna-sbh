#include "TwoWayClimber.hpp"

#include <list>
#include <climits>

using namespace std;

TwoWayClimber::TwoWayClimber(LineGraph * graph)
{
  this->graph = graph;
}

TwoWayClimber::~TwoWayClimber()
{
}

pair<string,int> TwoWayClimber::startFrom(int a)
{
  int n = graph->getN();
  int l = graph->getL();
  int p = graph->getP();

  bool hash[n];
  for(int i = 0; i < n; i++)
    hash[i] = false;

  int visited = 0;
  int first = a;
  int last = a;
  string result = graph->getLabel(first);
  while(true)
    {
      visited++;
      hash[first] = hash[last] = true;

      int dst = INT_MAX;
      int nxt = -1;
      bool back;
      for(int i = 0; i < n; i++)
	{
	  // forward
	  int d = graph->getDistance(last,i);
	  if(d > 0 && !hash[i] && d < dst)
	    {
	      dst = d;
	      nxt = i;
	      back = false;
	    }
	  // backward
	  d = graph->getDistance(i,first);
	  if(d > 0 && !hash[i] && d < dst)
	    {
	      dst = d;
	      nxt = i;
	      back = true;
	    }
	}

      if(nxt < 0)			// all hashed
	break;

      if(result.length() + dst > p) // len(out) > perfect len(out)
	break;

      if(back)
	{
	  first = nxt;
	  result = graph->getLabel(nxt).substr(0,dst) + result;
	}
      else
	{
	  last = nxt;
	  result += graph->getLabel(nxt).substr(l-dst);
	}
    }

  return pair<string,int>(result,visited);
}

pair<string,int> TwoWayClimber::run()
{
  string result = "";
  pair<int,int> best = pair<int,int>(1,INT_MAX);
  for(int i = 0; i < graph->getN(); i++)
    {
      pair<string,int> tmp = startFrom(i);
      pair<int,int> cmp = pair<int,int>(-tmp.second,graph->getP()-tmp.first.length());
      if(cmp < best)
  	{
  	  best = cmp;
  	  result = tmp.first;
  	}
    }

  return pair<string,int>(result,-best.first);
}
