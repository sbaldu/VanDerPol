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
  solution(int n_, int capacity_) : n{n_}, Capacity{capacity_} {
	data.resize(n * Capacity);
  }

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

  std::vector<double>::iterator it_to_variable(int i) {
	return data.begin() + Capacity * i;
  }

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
  double m_x0;
  double m_y0;
  solution m_sol;

public:
  eulerSolver(double x0, double y0) : m_x0{x0}, m_y0{y0} {}

  // x'' + a(x)x' + b(x) = 0, y = x'
  void solve(coeff_t a_x, coeff_t b_x, float dt, double max_t) {
    double x{m_x0};
    double y{m_y0};
    double t{};
    double steps{max_t / dt};
    double z;

	m_sol.n = 2;
    m_sol.setCapacity(steps);
    m_sol.add(0, m_x0, m_y0, 0.);

    for (int i{1}; i <= steps; ++i) {
      z = x + y * dt;
      y = a_x(x) * y * dt + y;
      x = z;
      t += dt;

	  m_sol.add(i, x, y, t);
    }
  }
};
