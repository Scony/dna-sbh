#ifndef POSITIVER_HPP
#define POSITIVER_HPP

#include <iostream>
#include <utility>
#include <list>

#include "Graph.hpp"

class Positiver
{
  Graph * graph;
public:
  Positiver(Graph * graph);
  ~Positiver();
  std::pair<std::string,int> run();
  std::list<std::list<int> > getDisjoints();
  std::list<std::pair<int,int> > dfs(int v, int left, std::list<std::pair<int,int> > hash);
};

#endif
