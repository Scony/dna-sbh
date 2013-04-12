#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Graph
{
  int nEdges;
  int n;
  int l;
  int perfect;
  std::vector<std::string> vLabel;
  std::map<std::string, int> vLabelMap;
  int ** vMatrix;

  void readGraph(std::istream & in);
public:
  Graph(std::istream & in);
  Graph(std::string fName);
  ~Graph();

  int getN();
  int getL();
  int getP();
  int getDistance(int a, int b);
  std::string getLabel(int a);
  int addVLabel(std::string label);

  void print();
};

#endif
