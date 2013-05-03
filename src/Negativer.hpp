#ifndef NEGATIVER_HPP
#define NEGATIVER_HPP

#include <iostream>
#include <utility>

#include "Graph.hpp"

class Negativer
{
  Graph * graph;

public:
  Negativer(Graph * graph);
  ~Negativer();
  // std::pair<std::string,int> run();
  int countDisjoints();
  void printInOut();
};

#endif
