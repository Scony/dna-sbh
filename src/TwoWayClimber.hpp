#ifndef TWO_WAY_CLIMBER_HPP
#define TWO_WAY_CLIMBER_HPP

#include <iostream>
#include <utility>

#include "LineGraph.hpp"

class TwoWayClimber
{
  LineGraph * graph;

  std::pair<std::string,int> startFrom(int a);
public:
  TwoWayClimber(LineGraph * graph);
  ~TwoWayClimber();
  std::pair<std::string,int> run();
};

#endif
