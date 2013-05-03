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

  // LineGraph g(cin);
  // HillClimber hc(&g);
  // TwoWayClimber twc(&g);
  // pair<string,int> result= hc.run();
  // cout << result.first << " " << result.first.length() << " " << g.rate(result.first)
  //      << " " << result.second << " of " << g.getN() << endl;
  // result= twc.run();
  // cout << result.first << " " << result.first.length() << " " << g.rate(result.first)
  //      << " " << result.second << " of " << g.getN() << endl;
  // TopSort ts(&g);
  // result= ts.run();
  // cout << result.first << " " << result.first.length() << " " << g.rate(result.first)
  //      << " " << result.second << " of " << g.getN() << endl;
  // cout << "---------------------------------------------------------\n";

  Graph g(cin);
  // g.print();
  Negativer n(&g);
  cout << n.countDisjoints() << endl;
  n.printInOut();
  return 0;
}
