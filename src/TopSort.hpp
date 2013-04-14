#ifndef TOP_SORT_HPP
#define TOP_SORT_HPP

#include <iostream>
#include <utility>

#include "LineGraph.hpp"

class TopSort
{
  LineGraph * graph;

public:
  TopSort(LineGraph * graph);
  ~TopSort();
  std::pair<std::string,int> run();
};

#endif
