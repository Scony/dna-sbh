#include "LineGraph.hpp"

#include <fstream>
#include <list>

using namespace std;

LineGraph::LineGraph(istream & in)
{
  readGraph(in);
}

LineGraph::LineGraph(string fName)
{
  ifstream file(fName.c_str());
  if(file)
    readGraph(file);
  else
    throw "I/O error";
}

LineGraph::~LineGraph()
{
  delete [] vLabel;
  for(int i = 0; i < n; i++)
    delete [] vMatrix[i];
  delete [] vMatrix;
}

void LineGraph::readGraph(istream & in)
{
  int ignore;
  string line;
  list<string> l;
  in >> ignore >> ignore >> ignore;
  while(in >> line)
    l.push_back(line);

  n = l.size();
  vLabel = new string[n];
  vMatrix = new int * [n];
  for(int i = 0; i < n; i++)
    vMatrix[i] = new int[n];

  int j = 0;
  for(list<string>::iterator i = l.begin(); i != l.end(); i++)
    vLabel[j++] = *i;

  //build assoc's
}

void LineGraph::print()
{
  for(int i = 0; i < n; i++)
    cout << vLabel[i] << endl;
}
