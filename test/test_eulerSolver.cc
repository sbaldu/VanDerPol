#include <cmath>
#include "eqDiffSolver.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./doctest.h"

TEST_CASE("Solve y'(x) = y(x)") {
  eulerSolver solver([](double, double) { return 1; }, 
					 [](double y, double) { return -y; });
  solver.solve(1., 0., 0.01, 10.);
  solution sol{solver.sol()};
  std::vector<double> x_t{sol.getVariable_i(0)};
  std::vector<double> t{sol.getTime()};

  for (int i{}; i < t.size(); ++i) {
    CHECK( (x_t[i] - exp(t[i])) / exp(t[i]) < 0.01 );
  }
}

TEST_CASE("Solve y'(x) = x") {
  eulerSolver solver([](double, double) { return 1; }, 
					 [](double, double x) { return -x; });
  solver.solve(0., 0., 0.01, 10.);
  solution sol{solver.sol()};
  std::vector<double> x_t{sol.getVariable_i(0)};
  std::vector<double> t{sol.getTime()};

  CHECK( x_t[0] == pow(t[0], 2) / 2 );
  for (int i{1}; i < t.size(); ++i) {
    CHECK( (x_t[i] - pow(t[i], 2) / 2) / pow(t[i], 2) / 2 < 0.01 );
  }
}

TEST_CASE("Solve y''(x) = 2") {
  eulerSolver solver([](double, double) { return 1; }, 
					 [](double, double x) { return -2; });
  solver.solve(0., 0., 0., 0.01, 10.);
  solution sol{solver.sol()};
  std::vector<double> x_t{sol.getVariable_i(0)};
  std::vector<double> t{sol.getTime()};

  CHECK( x_t[0] == pow(t[0], 2) );
  for (int i{1}; i < t.size(); ++i) {
    CHECK( (x_t[i] - pow(t[i], 2)) / pow(t[i], 2) < 0.01 );
  }
}

TEST_CASE("Solve y''(x) + y(x) = 0") {
  eulerSolver solver([](double, double) { return 0; }, 
					 [](double y, double) { return y; });
  solver.solve(0., 1., 0., 0.001, 10.);
  solution sol{solver.sol()};
  std::vector<double> x_t{sol.getVariable_i(0)};
  std::vector<double> t{sol.getTime()};

  CHECK( x_t[0] == sin(t[0]) );
  for (int i{1}; i < t.size(); ++i) {
    CHECK( (x_t[i] - sin(t[i])) / sin(t[i]) < 0.015 );
  }
}

TEST_CASE("Solve y''(x) + y'(x) = 0") {
  eulerSolver solver([](double y, double) { return y; }, 
					 [](double, double) { return 0; });
  solver.solve(0., 1., 0., 0.001, 10.);
  solution sol{solver.sol()};
  std::vector<double> x_t{sol.getVariable_i(0)};
  std::vector<double> t{sol.getTime()};

  CHECK( x_t[0] == (1 - exp(t[0])) );
  for (int i{1}; i < t.size(); ++i) {
    CHECK((x_t[i] - (1 - exp(t[i]))) / (1 - exp(t[i])) < 0.015);
  }
}
