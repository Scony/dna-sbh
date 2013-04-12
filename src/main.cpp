#include <iostream>
#include <utility>

#include "LineGraph.hpp"
#include "Graph.hpp"
#include "HillClimber.hpp"

using namespace std;

int main()
{
  ios_base::sync_with_stdio(0);

  LineGraph g(cin);
  //g.print();
  HillClimber hc(&g);
  pair<string,int> result= hc.run();
  cout << result.first << " " << result.first.length() << " " << g.rate(result.first)
       << " " << result.second << " of " << g.getN() << endl;

  return 0;
}
