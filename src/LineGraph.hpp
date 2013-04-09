#ifndef LINE_GRAPH_HPP
#define LINE_GRAPH_HPP

#include <iostream>

class LineGraph
{
  int n;
  std::string * vLabel;
  int ** vMatrix;

  void readGraph(std::istream & in);
public:
  LineGraph(std::istream & in);
  LineGraph(std::string fName);
  ~LineGraph();

  void print();
};

#endif
