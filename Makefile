export CXX := g++
CXXFLAGS = -std=c++11 -O3

PYTHON_VERS := $(shell python3 -V | awk -F '' '{print $$8$$9$$10$$11}' | sed 's/\.//g'  )
PYTHON_VERS_DOT := $(shell python3 -V | awk -F '' '{print $$8$$9$$10$$11}')
PYTHON_PATH := /usr/include/python$(PYTHON_VERS_DOT)
PYBIND_PATH := ${HOME}/.local/lib/python$(PYTHON_VERS_DOT)/site-packages/pybind11/include
BIND_FLAGS := -Wall -shared -fPIC -I$(PYTHON_PATH) -I$(PYBIND_PATH)
MODULE_NAME := VanDerPol.cpython-$(PYTHON_VERS)-x86_64-linux-gnu.so

bind: ./src/binding.cc ./src/eqDiffSolver.h
	cd ./src ; $(CXX) $(CXXFLAGS) $(BIND_FLAGS) ./binding.cc -o $(MODULE_NAME)

test: ./test/test_solution.cc ./test/test_eulerSolver.cc ./test/test_rk2Solver.cc
	cd ./test ; \
	$(CXX) $(CXXFLAGS) ./test_solution.cc -o test_solution ;
	cd ./test ; \
	$(CXX) $(CXXFLAGS) ./test_eulerSolver.cc -o test_eulersolver
	cd ./test ; \
	$(CXX) $(CXXFLAGS) ./test_rk2Solver.cc -o test_rk2solver
	touch test.sh ; chmod +x test.sh
	echo "./test/test_solution" > test.sh
	echo "./test/test_eulersolver" >> test.sh
	echo "./test/test_rk2solver" >> test.sh

clean:
	rm -f ./test/test_solution
	rm -f ./test/test_eulersolver
	rm -f ./test/test_solver
	rm -f ./test.sh
	rm -f ./*a.out
	clear
