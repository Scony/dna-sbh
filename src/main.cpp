#include <iostream>
#include <fstream>
#include <utility>

#include "LineGraph.hpp"
#include "Graph.hpp"
#include "HillClimber.hpp"
#include "TwoWayClimber.hpp"
#include "TopSort.hpp"
#include "Negativer.hpp"
#include "Positiver.hpp"

using namespace std;

int main(int argc, char ** argv)
{
  ios_base::sync_with_stdio(0);

  if(argc < 2)
    {
      cout << "Type file name\n";
      return 0;
    }


  ifstream in1(argv[1]);
  ifstream in2(argv[1]);

  LineGraph lg(in1);
  //Graph g(in2);

  in1.close();
  in2.close();

  TwoWayClimber twc(&lg);
  //Negativer n(&g);

  pair<string,int> result;
  result = twc.run();
  //cout << result.first << " " << result.first.length() << " " << lg.rate(result.first)
  //     << " " << result.second << " of " << lg.getN() << endl;
  //result = n.run();
  //cout << result.first << " " << result.first.length() << " " << lg.rate(result.first)
  //     << " " << result.second << " of " << lg.getN() << endl;
  //cout << "---------------------------------------------------------\n";

  return 0;
}
