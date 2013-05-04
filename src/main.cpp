#include <iostream>
#include <utility>

#include "LineGraph.hpp"
#include "Graph.hpp"
#include "HillClimber.hpp"
#include "TwoWayClimber.hpp"
#include "TopSort.hpp"
#include "Negativer.hpp"

using namespace std;

int main()
{
  ios_base::sync_with_stdio(0);

  LineGraph lg(cin);
  Graph g(cin);

  TwoWayClimber twc(&lg);
  Negativer n(&g);

  pair<string,int> result = twc.run();
  cout << result.first << " " << result.first.length() << " " << lg.rate(result.first)
       << " " << result.second << " of " << lg.getN() << endl;
  result = n.run();
  cout << result.first << " " << result.first.length() << " " << lg.rate(result.first)
       << " " << result.second << " of " << lg.getN() << endl;
  cout << "---------------------------------------------------------\n";

  return 0;
}
