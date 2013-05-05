#ifndef NEGATIVER_HPP
#define NEGATIVER_HPP

#include <iostream>
#include <utility>

#include "Graph.hpp"

class Negativer
{
  Graph * graph;
  int merge(int in[], int out[]);
  int naiveMerge();

public:
  Negativer(Graph * graph);
  ~Negativer();
  std::pair<std::string,int> run();
  int countDisjoints();
  void printInOut();
};

#endif
