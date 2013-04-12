#ifndef LINE_GRAPH_HPP
#define LINE_GRAPH_HPP

#include <iostream>

class LineGraph
{
  int n;
  int l;
  std::string * vLabel;
  int ** vMatrix;

  void readGraph(std::istream & in);
  int nShifted(const char *a, const char *b);
public:
  LineGraph(std::istream & in);
  LineGraph(std::string fName);
  ~LineGraph();

  int getN();
  int getDistance(int a, int b);
  std::string getLabel(int a);

  void print();
};

#endif
