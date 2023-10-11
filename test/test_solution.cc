#include "eqDiffSolver.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./doctest.h"

bool equal(std::vector<double> const& v1, std::vector<double>&& v2) {
  return v1 == v2;
}

TEST_CASE("Testing the internal structure of the solution data vector and the add function") {
  // Define a solution object characterized by three variables (ex. x, y and time t)
  // and whose calculated points are 2
  solution sol(3, 2);
  // Add the two points inside the object
  sol.add(0, 1.5, 2., 0.);
  sol.add(1, 2.5, 3., 0.5);

  // Now check that the content of the vector is what it should be
  CHECK(sol.data[0] == 1.5);
  CHECK(sol.data[1] == 2.5);
  CHECK(sol.data[sol.Capacity] == 2.);
  CHECK(sol.data[sol.Capacity + 1] == 3.);
  CHECK(sol.data[2*sol.Capacity] == 0.);
  CHECK(sol.data[2*sol.Capacity + 1] == 0.5);
}
 
TEST_CASE("Testing the slicing methods for the data") {
  // Define a solution object characterized by three variables (ex. x, y and time t)
  // and whose calculated points are 2
  solution sol(3, 2);
  // Add the two points inside the object
  sol.add(0, 1.5, 2., 0.);
  sol.add(1, 2.5, 3., 0.5);

  // Test the getVariable_i and getTime functions
  std::vector<double> var_0 { sol.getVariable_i(0) };
  std::vector<double> var_1 { sol.getVariable_i(1) };
  std::vector<double> var_2 { sol.getVariable_i(2) };
  std::vector<double> time { sol.getTime() };

  CHECK(equal(var_0, {1.5, 2.5}));
  CHECK(equal(var_1, {2., 3.}));
  CHECK(equal(var_2, {0., 0.5}));
  CHECK(equal(time, {0., 0.5}));
  CHECK(var_2 == time);	// We also want to check that the vector of the last variable is the same of getTime
}
