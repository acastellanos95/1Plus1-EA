#include <iostream>
#include "rand.h"
#include "(1+1)-EE.h"

int main() {
  int Gmax = 20000;
  // (1.0,1.5) => x=(-0.089842,0.712656 ), f(x)=-1.031628 20000
  // (-3.0,2.0) => x=(0.089842,-0.712656 ), f(x)=-1.031628, ps=0.000000
  std::vector<double> x{1.0,1.0};
  const std::vector<std::pair<double, double>> constraints{std::make_pair(-3.0,3.0), std::make_pair(-2.0,2.0)};
  onePOneEE(Gmax, x, constraints);
  return 0;
}
