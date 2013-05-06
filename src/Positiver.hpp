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
  std::list<int> getLargestDisjoint();
  std::list<pair<int,int> > dfs(int left,std::list<pair<int,int> > hash);
};

#endif
