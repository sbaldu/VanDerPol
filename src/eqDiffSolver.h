#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

using coeff_t = std::function<double(double)>;

struct solution {
  std::vector<double> data;
  // number of functions in the system of differential equations
  int n;
  int Capacity;

  // Constructors
  solution() = default;
  solution(int n_) : n{n_} {}
  solution(int n_, int capacity_) : n{n_}, Capacity{capacity_} { data.resize(n * Capacity); }

  void setCapacity(int capacity) {
    data.resize(n * capacity);
    Capacity = capacity;
  }

  template <typename T1, typename... Tn>
  void add(int i, T1 arg1, Tn... args) {
    data[i] = arg1;
    add(i + Capacity, args...);
  }

  void add(int i) {}

  std::vector<double>::iterator it_to_variable(int i) { return data.begin() + Capacity * i; }

  std::vector<double> getVariable_i(int i) {
    std::vector<double> slice;
    std::copy(it_to_variable(i), it_to_variable(i) + Capacity, std::back_inserter(slice));

    return slice;
  }
  std::vector<double> getTime() {
    std::vector<double> slice;
    std::copy(it_to_variable(n - 1), it_to_variable(n - 1) + Capacity, std::back_inserter(slice));

    return slice;
  }
};

class eulerSolver {
private:
  coeff_t m_ax;
  coeff_t m_bx;
  solution m_sol;

public:
  eulerSolver() = default;
  eulerSolver(coeff_t ax, coeff_t bx) : m_ax{std::move(ax)}, m_bx{std::move(bx)} {}

  solution sol() const { return m_sol; }

  // x'' + a(x)x' + b(x) = 0, y = x'
  void solve(double x0, double y0, float dt, double max_t) {
    double x{x0};
    double y{y0};
    double t{};
    double steps{max_t / dt};
    double z;

    m_sol.n = 3;
    m_sol.setCapacity(steps + 1);
    m_sol.add(0, x0, y0, 0.);

    for (int i{1}; i <= steps; ++i) {
      z = x + y * dt;
      y = -(m_ax(x) * y + m_bx(x)) * dt + y;
      x = z;

      t += dt;
      m_sol.add(i, x, y, t);
    }
  }
};

class rk2Solver {
private:
  coeff_t m_ax;
  coeff_t m_bx;
  solution m_sol;

public:
  rk2Solver() = default;
  rk2Solver(coeff_t ax, coeff_t bx) : m_ax{std::move(ax)}, m_bx{std::move(bx)} {}

  solution sol() const { return m_sol; }

  void solve(double x0, double y0, double dt, double max_t) {
    double x{x0};
    double y{y0};
    double t{};
    double steps{max_t / dt};
    // Coefficients for the Runge-Kutta method
    double k1, k2, l1, l2;
    double z;

    m_sol.n = 3;
    m_sol.setCapacity(steps + 1);
    m_sol.add(0, x0, y0, 0.);

    for (int i{}; i <= steps; ++i) {
      k1 = dt * y;
      l1 = -dt * (m_ax(x) * y + m_bx(x));
      k2 = dt * (y + l1);
      z = x + (k1 + k2) / 2;
      l2 = -dt * (m_ax(x + k1) * (y + l1 * dt / 2) + m_bx(x + k1));
      y = y + (l1 + l2) / 2;
      x = z;

      t += dt;
      m_sol.add(i, x, y, t);
    }
  }
};
