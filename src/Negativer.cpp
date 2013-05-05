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

  int nDisjoints = countDisjoints();
  cout << "nDisjoints = " << nDisjoints << endl;
  if(nDisjoints == 1)	// easy way
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
      int newNDisjoints = merge(in, out);
      cout << "nDisjoints before/after: " << nDisjoints  << "/" << newNDisjoints << endl;
      cout << "currentN = " << graph->getCurrentN() << endl;
    }

  // printInOut();

  // finally find euler path

  n = graph->getCurrentN();
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

  int perfect = graph->getP();

  string seq = "";
  int usage = 0;
  int prev;
  while(!backtrack.empty())
    {
      if(seq == "") {
	seq = graph->getLabel(backtrack.top());
      } else {
	seq += graph->getLabel(backtrack.top()).substr(graph->getLabel(backtrack.top()).length()-1);
      	if (graph->inOriginal(prev, backtrack.top())) {
      	  usage++;
      	  graph->originalPop(prev, backtrack.top());
      	}
      }
      prev = backtrack.top();
      backtrack.pop();
      if (seq.size() == perfect)
      	break;
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

int Negativer::merge(int in[], int out[])
{
  int l = graph->getL();
  int n = graph->getCurrentN();
  int nDisjoints = countDisjoints();

  vector<int> heads;
  vector<int> tails;
  for (int i = 0; i < n; i++) {
    if (in[i] == 0 && out[i] == 1) {
      heads.push_back(i);
    } else if (in[i] == 1 && out[i] == 0) {
      tails.push_back(i);
    }
  }

  for (int shift = 1; shift <= 6; shift++) {
    for (int t = 0; t < tails.size(); t++) {
      int i = tails[t];
      for (int h = 0; h < heads.size(); h++) {
      	int j = heads[h];

      	if (i == j || graph->getDistance(i, j)) {
      	  continue;
      	}

      	if (graph->getLabel(i).compare(shift, l - shift - 1,
      	      graph->getLabel(j), 0, l - shift - 1) == 0) {

      	  vector<int> newVertexes;
      	  int prev = i;
      	  for (int m = 1; m <= shift - 2; m++) { // only for shift >= 3
      	    // add "imaginary" vertex
      	    string newLabel = graph->getLabel(i).substr(m, l - m) +
      	      graph->getLabel(j).substr(shift - 1, m);
      	    //cout << graph->getLabel(i) << " " << graph->getLabel(j) << " " << newLabel << endl;
      	    int newV = graph->addVertex(newLabel);
      	    if (newV == graph->getCurrentN() - 1) { // new vertex
      	      newVertexes.push_back(newV);
      	    }
	    // connect with edge
	    graph->setDistance(prev, newV, 1); 
	    prev = newV;
      	  }
	  graph->setDistance(prev, j, 1);

	  int newNDisjoints = countDisjoints();
	  if (nDisjoints <= newNDisjoints) {
	    //remove
      	    int prev = i;
      	    for (int v = 0; v < newVertexes.size(); v++) {
      	      int newV = newVertexes[v];
	      graph->setDistance(prev, newV, 0); // remove edge
	      prev = newV;
      	    }
	    graph->setDistance(prev, j, 0);
      	    for (int v = newVertexes.size() - 1; v >= 0; v--) {
      	      int newV = newVertexes[v];
      	      graph->removeVertex(newV);
      	    }
      	    newVertexes.clear();

	  } else {
	    out[i]++;
	    in[j]++;
	    heads.erase(heads.begin() + h);
	    tails.erase(tails.begin() + t);
	    h--;
	    t--;

	    nDisjoints = newNDisjoints;
	    if (nDisjoints == 1) {
	      return 1;
	    }
	  }

      	}

      }
    }

  }
  return nDisjoints;
}

int Negativer::naiveMerge()
{
  int l = graph->getL();
  int n = graph->getCurrentN();
  for (int k = 2; k <= 5; k++) {
    //n = graph->getCurrentN();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
      	if (i == j || graph->getDistance(i, j)) {
      	  continue;
      	}
      	if (graph->getLabel(i).compare(k, l - k - 1,
      	           graph->getLabel(j), 0, l - k - 1) == 0) {
      	  // add "imaginary" vertex
      	  for (int m = 1; m <= k - 2; m++) {
      	    string newLabel = graph->getLabel(i).substr(m, l - m) +
      	      graph->getLabel(j).substr(k - 1, m);
      	    //cout << graph->getLabel(i) << " " << graph->getLabel(j) << " " << newLabel << endl;
      	    graph->addVertex(newLabel);
      	  }
      	}
      }
    }
  }
  n = graph->getCurrentN();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j || graph->getDistance(i, j)) {
      	continue;
      }
      if (graph->getLabel(i).compare(1, l - 2, graph->getLabel(j), 0, l - 2) == 0) {
      	// add "imaginary" edge
      	graph->setDistance(i, j, 1);
      }
    }
  }
  //for (int k = 2; k <= 5; k++) {
  //	for (int i = 0; i < n; i++) {
  //    for (int j = 0; j < n; j++) {
  //	    if (i == j || graph->getDistance(i, j)) {
  //	      continue;
  //	    }
  //	    if (graph->getLabel(i).compare(k, l - 1 - k, graph->getLabel(j), 0, l - 1 - k) == 0) {
  //	      // add "imaginary" edge
  //	      graph->setDistance(i, j, 1);
  //	    }
  //    }
  //	}
  //}
  int newNDisjoints = countDisjoints();
  return newNDisjoints;
  //return fail;
  //return run();
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
