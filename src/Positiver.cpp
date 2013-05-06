#include "Positiver.hpp"

#include <list>
#include <stack>
#include <cmath>

using namespace std;

Positiver::Positiver(Graph * graph)
{
  this->graph = graph;
}

Positiver::~Positiver()
{
}

pair<string,int> Positiver::run()
{
  pair<string,int> fail = pair<string,int>("FAIL",-1);

  return fail;
}

int Negativer::countDisjoints()
{
  int n = graph->getCurrentN();
  bool hash[n];
  for(int i = 0; i < n; i++)
    hash[i] = false;
  int djs = 0;

  for(int i = 0; i < n; i++)
    if(!hash[i])
      {
	stack<int> s;
	s.push(i);

	while(!s.empty())
	  {
	    int visit = s.top();
	    hash[visit] = true;
	    s.pop();

	    for(int j = 0; j < n; j++)
	      if((graph->getDistance(visit,j) ||
		  graph->getDistance(j,visit)) && !hash[j])
		s.push(j);
	  }

	djs++;
      }

  return djs;
}

list<int> Positiver::getLargestDisjoint()
{
  //
}

list<pair<int,int> > dfs(int left,list<pair<int,int> > hash)
{
  //
}
