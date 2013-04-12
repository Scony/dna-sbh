#include "HillClimber.hpp"

#include <list>

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
  while(0 <= visit && visit < n)
    {
      visited++;
      hash[visit] = true;
      list<pair<int,int> > lst;
      for(int i = 0; i < n; i++)
	{
	  int dst = graph->getDistance(visit,i);
	  if(dst > 0)
	    lst.push_back(pair<int,int>(dst,i));
	}
      lst.sort();

      visit = -1;
      for(list<pair<int,int> >::iterator i = lst.begin(); i != lst.end(); i++)
	if(!hash[i->second])
	  {
	    if(result.length() + i->first > p)
	      continue;
	    result += graph->getLabel(i->second).substr(l-i->first);
	    visit = i->second;
	    break;
	  }
    }

  return pair<string,int>(result,visited);
}

pair<string,int> HillClimber::run()
{
  list<pair<int,pair<int,string> > > results;
  for(int i = 0; i < graph->getN(); i++)
    {
      pair<string,int> tmp = startFrom(i);
      pair<int,string> str = pair<int,string>(graph->getP()-tmp.first.length(),tmp.first);
      pair<int,pair<int,string> > result = pair<int,pair<int,string> >(-tmp.second,str);

      results.push_back(result);
    }
  results.sort();

  pair<string,int> re = pair<string,int>(results.front().second.second,-results.front().first);
  return re;
}
