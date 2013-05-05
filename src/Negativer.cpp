#include "Negativer.hpp"

#include <list>
#include <stack>
#include <cmath>

using namespace std;

Negativer::Negativer(Graph * graph)
{
  this->graph = graph;
}

Negativer::~Negativer()
{
}

pair<string,int> Negativer::run()
{
  pair<string,int> fail = pair<string,int>("FAIL",-1);

  int n = graph->getCurrentN();
  int in[n];
  int out[n];
  for(int i = 0; i < n; i++)
    {
      in[i] = 0;
      out[i] = 0;
    }
  list<int> anomalies;

  for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
	{
	  out[i] += graph->getDistance(i,j);
	  in[i] += graph->getDistance(j,i);
	}
      if(in[i] != out[i] && in[i] != 0 && out[i] != 0)
	anomalies.push_back(i);
    }

  // for(list<int>::iterator i = anomalies.begin(); i != anomalies.end(); i++)
  //   cout << *i << endl;

  if(countDisjoints() == 1)	// easy way
    {
      while(!anomalies.empty())
	{
	  int visit = anomalies.front();
	  anomalies.pop_front();

	  int diff = abs(in[visit] - out[visit]);
	  while(diff--/*in[visit] != out[visit]*/)
	    {
	      // cout << ":(" << endl;	 // TODO: prevent infinite loop
	      if(in[visit] > out[visit]) // endouble out(s)
		{
		  list<pair<int,list<int> > > bfs;
		  bfs.push_back(pair<int,list<int> >(visit,list<int>()));

		  while(!bfs.empty())
		    {
		      pair<int,list<int> > v = bfs.front();
		      bfs.pop_front();

		      if(in[v.first] < out[v.first] && out[v.first] != 0 && in[v.first] != 0) // recover
			{
			  int next = v.first;
			  while(!v.second.empty())
			    {
			      int present = v.second.back();
			      v.second.pop_back();

			      graph->setDistance(present,next,graph->getDistance(present,next)+1);
			      out[present]++;
			      in[next]++;

			      next = present;
			    }
			  break;
			}
		      else	// explore
			{
			  v.second.push_back(v.first);

			  for(int i = 0; i < n; i++)
			    if(graph->getDistance(v.first,i))
			      {
				bool skip = false;
				for(list<int>::iterator j = v.second.begin(); j != v.second.end(); j++)
				  if(*j == i)
				    {
				      skip = true;
				      break;
				    }
				if(!skip)
				  bfs.push_back(pair<int,list<int> >(i,v.second));
			      }
			}
		    }
		}
	      else		// in[visit] < out[visit] // endouble in(s)
		{
		  list<pair<int,list<int> > > bfs;
		  bfs.push_back(pair<int,list<int> >(visit,list<int>()));

		  while(!bfs.empty())
		    {
		      pair<int,list<int> > v = bfs.front();
		      bfs.pop_front();

		      if(in[v.first] > out[v.first] && out[v.first] != 0 && in[v.first] != 0) // recover
			{
			  int prev = v.first;
			  while(!v.second.empty())
			    {
			      int present = v.second.back();
			      v.second.pop_back();

			      graph->setDistance(prev,present,graph->getDistance(prev,present)+1);
			      out[prev]++;
			      in[present]++;

			      prev = present;
			    }
			  break;
			}
		      else	// explore
			{
			  v.second.push_back(v.first);

			  for(int i = 0; i < n; i++)
			    if(graph->getDistance(i,v.first))
			      {
				bool skip = false;
				for(list<int>::iterator j = v.second.begin(); j != v.second.end(); j++)
				  if(*j == i)
				    {
				      skip = true;
				      break;
				    }
				if(!skip)
				  bfs.push_back(pair<int,list<int> >(i,v.second));
			      }
			}
		    }
		}
	    }
	  if(in[visit] != out[visit]) // still wrong
	    return fail;
	}
    }
  else				// merging way
    {
      // dozens of evil code lines
      return fail;
    }

  // printInOut();

  // finally find euler path

  int start = -1;
  for(int i = 0; i < n; i++)	// look for entry point IN/OUT = 0/1
    if(in[i] == 0 && out[i] == 1)
      {
	start = i;
	break;
      }

  if(start == -1)		// no entry point found
    return fail;

  stack<int> exploration;
  stack<int> backtrack;

  exploration.push(start);

  while(!exploration.empty())
    {
      int visit = exploration.top();
      int neighbour = -1;

      for(int i = 0; i < n; i++)
	if(graph->getDistance(visit,i))
	  {
	    neighbour = i;
	    break;
	  }

      if(neighbour != -1)	// new visit
	{
	  graph->setDistance(visit,neighbour,graph->getDistance(visit,neighbour)-1);
	  exploration.push(neighbour);
	}
      else			// backtrack
	{
	  backtrack.push(exploration.top());
	  exploration.pop();
	}
    }

  string seq = "";
  int usage = backtrack.size() - 1;
  while(!backtrack.empty())
    {
      if(seq == "")
	seq = graph->getLabel(backtrack.top());
      else
	seq += graph->getLabel(backtrack.top()).substr(graph->getLabel(backtrack.top()).length()-1);
      backtrack.pop();
    }

  pair<string,int> result = pair<string,int>(seq,usage);

  return result;
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

void Negativer::printInOut()
{
  int n = graph->getCurrentN();

  for(int i = 0; i < n; i++)
    {
      int in = 0;
      int out = 0;
      for(int j = 0; j < n; j++)
	{
	  out += graph->getDistance(i,j);
	  in += graph->getDistance(j,i);
	}
      if(in != out)
	cout << i << " :: " << in << " / " << out << endl;
    }
}
