export CXX := g++
CXXFLAGS = -std=c++11

PYTHON_PATH := /usr/include/python3.10
PYBIND_PATH := ${HOME}/.local/lib/python3.10/site-packages/pybind11/include
BIND_FLAGS :=-O3 -Wall -shared -fPIC -I$(PYTHON_PATH) -I$(PYBIND_PATH)
PYTHON_VERS := $(python3 -V | awk -F '' '{print $8$9$10$11}' | sed 's/\.//g'  )
MODULE_NAME := VanDerPol.cpython-$(PYTHON_VERS)-x86_64-linux-gnu.so

bind: ./src/binding.cc ./src/eqDiffSolver.h
	cd ./src ; $(CXX) $(CXXFLAGS) $(BIND_FLAGS) ./binding.cc -o $(MODULE_NAME)

test: ./test/test_solution.cc ./test/test_eulerSolver.cc
	cd ./test ; \
	$(CXX) $(CXXFLAGS) ./test_solution.cc -o test_solution ;
	cd ./test ; \
	$(CXX) $(CXXFLAGS) ./test_eulerSolver.cc -o test_eulersolver
	touch test.sh ; chmod +x test.sh
	echo "./test/test_solution" > test.sh
	echo "./test/test_eulersolver" >> test.sh

clean:
	rm -f ./test/test_solution
	rm -f ./test/test_eulersolver
	rm -f ./test.sh
	rm -f ./*a.out
	clear
