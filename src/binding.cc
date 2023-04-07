#include <cstdint>
#include <functional>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdint.h>

#include "eqDiffSolver.h"

solution vdp_euler(double x0, double y0, double mu, float dt, double max_t) {
  eulerSolver solver([mu](double x, double) { return -mu * (1 - x * x); }, [](double x, double) { return x; });
  solver.solve(x0, y0, 0., dt, max_t);

  return solver.sol();
}

solution vdp_rk2(double x0, double y0, double mu, float dt, double max_t) {
  rk2Solver solver([mu](double x) { return -mu * (1 - x * x); }, [](double x) { return x; });
  solver.solve(x0, y0, dt, max_t);

  return solver.sol();
}

PYBIND11_MODULE(VanDerPol, m) {
  m.doc() = "Numerical solver of the VanDerPol equation";

  pybind11::class_<solution>(m, "solution")
      .def(pybind11::init<>())
      .def(pybind11::init<int>())
      .def(pybind11::init<int, int>())
      .def("setCapacity", &solution::setCapacity)
      .def("getVariable_i", &solution::getVariable_i)
      .def("getTime", &solution::getTime);

  m.def("vdp_euler", &vdp_euler);
  m.def("vdp_rk2", &vdp_rk2);
}
