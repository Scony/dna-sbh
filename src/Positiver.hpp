#ifndef POSITIVER_HPP
#define POSITIVER_HPP

#include <iostream>
#include <utility>

#include "Graph.hpp"

class Positiver
{
  Graph * graph;
public:
  Positiver(Graph * graph);
  ~Positiver();
  std::pair<std::string,int> run();
  int countDisjoints();
  void printInOut();
};

#endif
