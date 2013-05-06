#include "Positiver.hpp"

// #include <list>
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

  // get disjoints
  list<list<int> > djs = getDisjoints();
  list<int> biggest = djs.front(); // fix to use iter
  for(list<list<int> >::iterator i = djs.begin(); i != djs.end(); i++)
    if(i->size() > biggest.size())
      biggest = *i;		// =||=

  cout << biggest.size() << endl;

  cout << graph->getP() - graph->getL() + 1 << endl;

  // count path len
  int pathLen = graph->getP() - graph->getL() + 1;

  // foreach big disjoint find entrys and try dfs 'em
  // for now: biggest
  int n = graph->getCurrentN();
  int in[n];
  int out[n];
  for(int i = 0; i < n; i++)
    {
      in[i] = 0;
      out[i] = 0;
      for(int j = 0; j < n; j++)
	{
	  if(graph->getDistance(i,j) && ++out[i]);
	  if(graph->getDistance(j,i) && ++in[i]);
	}
    }

  stack<int> tryIt;
  for(list<int>::iterator i = biggest.begin(); i != biggest.end(); i++)
    if(in[*i] < out[*i])
      tryIt.push(*i);

  if(tryIt.size() > 0)
    {
      while(!tryIt.empty())
	{
	  int visit = tryIt.top();
	  tryIt.pop();
	  // list<pair<int,int> > Positiver::dfs(int v, int left, list<pair<int,int> > hash)
	  list<pair<int,int> > re = dfs(visit,pathLen,list<pair<int,int> >());
	  if(re.front().first != -1)
	    {
	      cout << "OK !!!" << re.size() << endl;
	      string seq = "";
	      int edges = re.size();
	      for(list<pair<int,int> >::iterator i = re.begin(); i != re.end(); i++)
		if(seq == "")
		  seq = graph->getLabel(i->first) + graph->getLabel(i->second).substr(graph->getLabel(i->second).length()-1);
		else
		  seq += graph->getLabel(i->second).substr(graph->getLabel(i->second).length()-1);

	      return pair<string,int>(seq,edges);
	    }
	}
    }

  return fail;
}

list<list<int> > Positiver::getDisjoints()
{
  int n = graph->getCurrentN();
  bool hash[n];
  for(int i = 0; i < n; i++)
    hash[i] = false;
  list<list<int> > result;

  for(int i = 0; i < n; i++)
    if(!hash[i])
      {
	list<int> vs;
	stack<int> s;
	s.push(i);

	while(!s.empty())
	  {
	    int visit = s.top();
	    hash[visit] = true;
	    vs.push_front(visit);
	    s.pop();

	    for(int j = 0; j < n; j++)
	      if((graph->getDistance(visit,j) ||
		  graph->getDistance(j,visit)) && !hash[j])
		s.push(j);
	  }

	result.push_back(vs);
      }

  return result;
}

list<pair<int,int> > Positiver::dfs(int v, int left, list<pair<int,int> > hash)
{
  if(left <= 0)
    {
      return hash;
    }
  else
    {
      int n = graph->getCurrentN();
      for(int i = 0; i < n; i++)
	if(graph->getDistance(v,i))
	  {
	    bool cnt = false;
	    for(list<pair<int,int> >::iterator j = hash.begin(); j != hash.end(); j++)
	      if(j->first == v && j->second == i)
		{
		  cnt = true;
		  break;
		}
	    if(cnt)
	      continue;
	    list<pair<int,int> > tmp = hash;
	    tmp.push_back(pair<int,int>(v,i));
	    list<pair<int,int> > re = dfs(i,left-1,tmp);
	    if(re.front().first != -1)
	      return re;
	  }
      hash.push_front(pair<int,int>(-1,-1));

      return hash;
    }
}
