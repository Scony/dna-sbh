#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

class Graph
{
  int nEdges;
  int n;
  int currentN;
  int l;
  int perfect;
  int errors;

  std::vector<std::string> vLabel;
  std::map<std::string, int> vLabelMap;
  int ** vMatrix;
  std::set< std::pair<int, int> > edges;

  void readGraph(std::istream & in);
public:
  Graph(std::istream & in);
  Graph(std::string fName);
  ~Graph();

  int getN();
  int getCurrentN();
  int getL();
  int getP();
  int getDistance(int a, int b);
  void setDistance(int a, int b, int d);
  std::string getLabel(int a);
  int getIndex(std::string label);
  int addVertex(std::string label); // also returns index of vertex
  void removeVertex(int index);
  void addEdge(int a, int b, int weight);
  bool inOriginal(int a, int b);
  void originalPop(int a, int b);

  void print();
};

#endif
