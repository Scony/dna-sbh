#include "Graph.hpp"

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stdexcept>

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
    throw runtime_error("I/O error");
}

Graph::~Graph()
{
  for(int i = 0; i < n; i++)
    delete [] vMatrix[i];
  delete [] vMatrix;
}

void Graph::readGraph(istream & in)
{
  string line;
  list<string> lst;
  in >> perfect >> l >> errors;
  while(in >> line)
    lst.push_back(line);

  nEdges = lst.size();
  vector< pair<int, int> > edges;

  currentN = 0;
  for (list<string>::iterator i = lst.begin(); i != lst.end(); i++) {
    string vLabel1 = i->substr(0, l - 1);
    string vLabel2 = i->substr(1, l);
    int vIndex1 = addVertex(vLabel1);
    int vIndex2 = addVertex(vLabel2);
    edges.push_back(make_pair(vIndex1, vIndex2));
  }

  n = vLabel.size();

  int vMatrixSize = n;
  if (errors < 0) {
    vMatrixSize -= errors;
  }

  vMatrix = new int * [vMatrixSize];
  for(int i = 0; i < vMatrixSize; i++)
    vMatrix[i] = new int[vMatrixSize](); // 0-initialized

  for (int i = 0; i < nEdges; i++) {
    int a = edges[i].first;
    int b = edges[i].second;
    addEdge(a, b, 1);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (vMatrix[i][j] != 0 || i == j) {
      	continue;
      }
      //if (vLabel[i].compare(1, l - 2, vLabel[j], 0, l - 2) == 0) {
      //	// add "imaginary" edge
      //	vMatrix[i][j] = 2;
      //}
    }
  }
}

int Graph::addVertex(string label)
{
  int index = getIndex(label);
  if (index >= 0) {
    return index;
  }
  int newIndex = vLabel.size();
  vLabelMap.insert(make_pair(label, newIndex));
  vLabel.push_back(label);
  currentN++;
  return newIndex;
}

void Graph::addEdge(int a, int b, int weight)
{
  if (0 <= a && a < currentN && 0 <= b && b < currentN) {
    vMatrix[a][b] = weight;
  } else {
    throw runtime_error("Vertex out of bounds in addEdge");
  }
}

int Graph::getN()
{
  return n;
}

int Graph::getCurrentN()
{
  return currentN;
}

int Graph::getL()
{
  return l;
}

int Graph::getP()
{
  return perfect;
}

int Graph::getDistance(int a, int b)
{
  if(0 <= a && a < currentN && 0 <= b && b < currentN)
    return vMatrix[a][b];
  throw runtime_error("Vertex out of bounds in getDistance");
}

void Graph::setDistance(int a, int b, int d)
{
  if(0 <= a && a < currentN && 0 <= b && b < currentN)
    vMatrix[a][b] = d;
  else
    throw runtime_error("Vertex out of bounds in setDistance");
}

string Graph::getLabel(int a)
{
  if(0 <= a && a < currentN)
    return vLabel[a];
  throw runtime_error("Vertex out of bounds in getLabel");
}

int Graph::getIndex(string label)
{
  map<string, int>::iterator it = vLabelMap.find(label);
  if (it != vLabelMap.end()) {
    return it->second;
  }
  return -1;
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
