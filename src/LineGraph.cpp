#include "LineGraph.hpp"

#include <fstream>
#include <list>
#include <string.h>

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
  list<string> lst;
  in >> ignore >> l >> ignore;
  while(in >> line)
    lst.push_back(line);

  n = lst.size();
  vLabel = new string[n];
  vMatrix = new int * [n];
  for(int i = 0; i < n; i++)
    vMatrix[i] = new int[n];

  int j = 0;
  for(list<string>::iterator i = lst.begin(); i != lst.end(); i++)
    vLabel[j++] = *i;

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      {
	int shift = nShifted(vLabel[i].c_str(),vLabel[j].c_str());
	if(shift >= l)
	  shift = 0;

	vMatrix[i][j] = shift;
      }
}

int LineGraph::nShifted(const char *a, const char *b)
{
    int n_common = 0;
    int i;

    for (i = 0; i < l; i++) {
        if (strncmp(a + i, b, l - i) == 0) {
            return i;
        }
    }
    return l;
}

int LineGraph::getN()
{
  return n;
}

int LineGraph::getDistance(int a, int b)
{
  if(0 <= a && a < n && 0 <= b && b < n)
    return vMatrix[a][b];
  throw "Vertex out of bounds";
}

string LineGraph::getLabel(int a)
{
  if(0 <= a && a < n)
    return vLabel[a];
  throw "Vertex out of bounds";
}

void LineGraph::print()
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
