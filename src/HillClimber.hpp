#ifndef HILL_CLIMBER_HPP
#define HILL_CLIMBER_HPP

#include <iostream>
#include <utility>

#include "LineGraph.hpp"

class HillClimber
{
  LineGraph * graph;

  std::pair<std::string,int> startFrom(int a);
public:
  HillClimber(LineGraph * graph);
  ~HillClimber();
  std::pair<std::string,int> run();
};

#endif
