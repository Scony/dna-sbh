#include "HillClimber.hpp"

#include <list>
#include <climits>

using namespace std;

HillClimber::HillClimber(LineGraph * graph)
{
  this->graph = graph;
}

HillClimber::~HillClimber()
{
}

pair<string,int> HillClimber::startFrom(int a)
{
  int n = graph->getN();
  int l = graph->getL();
  int p = graph->getP();

  bool hash[n];
  for(int i = 0; i < n; i++)
    hash[i] = false;

  int visited = 0;
  int visit = a;
  string result = graph->getLabel(visit);
  while(true)
    {
      visited++;
      hash[visit] = true;

      int nxt = -1;
      int dst = INT_MAX;
      for(int i = 0; i < n; i++)
	{
	  int d = graph->getDistance(visit,i);
	  if(d > 0 && !hash[i] && d < dst)
	    {
	      nxt = i;
	      dst = d;
	      if(d == 1)	// better d is not possible
		break;
	    }
	}

      if(nxt < 0)			// all hashed
	break;

      if(result.length() + dst > p) // len(out) > perfect len(out)
	break;

      visit = nxt;
      result += graph->getLabel(nxt).substr(l-dst);
    }

  return pair<string,int>(result,visited);
}

pair<string,int> HillClimber::run()
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
