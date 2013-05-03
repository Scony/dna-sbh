#include "Negativer.hpp"

// #include <list>
#include <stack>

using namespace std;

Negativer::Negativer(Graph * graph)
{
  this->graph = graph;
}

Negativer::~Negativer()
{
}

// pair<string,int> Negativer::run()
// {
// }

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

void Negativer::printInOut()
{
  int n = graph->getCurrentN();

  for(int i = 0; i < n; i++)
    {
      int in = 0;
      int out = 0;
      for(int j = 0; j < n; j++)
	if((graph->getDistance(i,j) && ++out) ||
	   (graph->getDistance(j,i) && ++in));
      if(in!=out)
	cout << i << " :: " << in << " / " << out << endl;
    }
}
