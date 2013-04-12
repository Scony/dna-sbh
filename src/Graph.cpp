#include "Graph.hpp"

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;

Graph::Graph(istream & in)
{
  readGraph(in);
}

Graph::Graph(string fName)
{
  ifstream file(fName.c_str());
  if(file)
    readGraph(file);
  else
    throw "I/O error";
}

Graph::~Graph()
{
  for(int i = 0; i < n; i++)
    delete [] vMatrix[i];
  delete [] vMatrix;
}

void Graph::readGraph(istream & in)
{
  int ignore;
  string line;
  list<string> lst;
  in >> perfect >> l >> ignore;
  while(in >> line)
    lst.push_back(line);

  nEdges = lst.size();
  vector< pair<int, int> > edges;

  for (list<string>::iterator i = lst.begin(); i != lst.end(); i++) {
    string vLabel1 = i->substr(0, l - 1);
    string vLabel2 = i->substr(1, l);
    int vIndex1 = addVLabel(vLabel1);
    int vIndex2 = addVLabel(vLabel2);
    edges.push_back(make_pair(vIndex1, vIndex2));
  }

  n = vLabel.size();
  vMatrix = new int * [n];
  for(int i = 0; i < n; i++)
    vMatrix[i] = new int[n](); // 0-initialized

  for (int i = 0; i < nEdges; i++) {
    int a = edges[i].first;
    int b = edges[i].second;
    vMatrix[a][b] = 1;
  }
}

int Graph::addVLabel(string label)
{
  map<string, int>::iterator it = vLabelMap.find(label);
  if (it != vLabelMap.end()) {
    return it->second;
  }
  int newIndex = vLabel.size();
  vLabelMap.insert(make_pair(label, newIndex));
  vLabel.push_back(label);
  return newIndex;
}

int Graph::getN()
{
  return n;
}

int LineGraph::getL()
{
  return l;
}

int LineGraph::getP()
{
  return perfect;
}

int Graph::getDistance(int a, int b)
{
  if(0 <= a && a < n && 0 <= b && b < n)
    return vMatrix[a][b];
  throw "Vertex out of bounds";
}

string Graph::getLabel(int a)
{
  if(0 <= a && a < n)
    return vLabel[a];
  throw "Vertex out of bounds";
}

void Graph::print()
{
  for(int i = 0; i < n; i++)
    cout << vLabel[i] << endl;

  for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
	cout << vMatrix[i][j] << " ";
      cout << endl;
    }
}
