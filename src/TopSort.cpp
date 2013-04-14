#include "TopSort.hpp"

#include <list>

using namespace std;

TopSort::TopSort(LineGraph * graph)
{
  this->graph = graph;
}

TopSort::~TopSort()
{
}

pair<string,int> TopSort::run()
{
  int n = graph->getN();
  int l = graph->getL();
  int p = graph->getP();

  bool hash[n];
  for(int i = 0; i < n; i++)
    hash[i] = false;

  int visited = 0;
  int prev = -1;
  int prevV[n];
  string result;

  list<pair<double,int> > sack;
  for(int i = 0; i < n; i++)
    sack.push_back(pair<double,int>(0,i));
  while(!sack.empty())
    {
      for(list<pair<double,int> >::iterator i = sack.begin(); i != sack.end(); i++)
	{
	  int count = 0;
	  int sum = 0;
	  for(int j = 0; j < n; j++)
	    if(graph->getDistance(j,i->second) > 0)
	      {
		sum += graph->getDistance(j,i->second);
		count++;
	      }
	  i->first = - (double)sum/count;
	}

      sack.sort();

      int visit = sack.front().second;
      if(prev != -1)
	{
	  if(result.length() + prevV[visit] > p)
	    break;
	  result += graph->getLabel(visit).substr(l-prevV[visit]);
	}
      else
	result = graph->getLabel(visit);
      hash[visit] = true;
      visited++;
      prev = visit;

      sack.clear();

      for(int i = 0; i < n; i++)
	if(graph->getDistance(visit,i) > 0 && !hash[i])
	  sack.push_back(pair<double,int>(0,i));

      for(int i = 0; i < n; i++)
	{
	  prevV[i] = graph->getDistance(visit,i);
	  graph->setDistance(visit,i,0);
	  graph->setDistance(i,visit,0);
	}
    }

  return pair<string,int>(result,visited);
}
