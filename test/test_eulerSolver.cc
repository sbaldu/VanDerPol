#include <cmath>
#include "../src/eqDiffSolver.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./doctest.h"

TEST_CASE("Solve y(x) = y'(x)") {
  eulerSolver solver([](double, double) { return 1; }, [](double y, double) { return -y; });
  solver.solve(1., 0., 0.01, 10.);
  solution sol{ solver.sol() };
  std::vector<double> x_t{ sol.getVariable_i(0) };
  std::vector<double> t{ sol.getTime() };

  for(int i{}; i < t.size(); ++i) {
	CHECK( (x_t[i] - exp(t[i]))/exp(t[i]) < 0.01 );
  }
}
