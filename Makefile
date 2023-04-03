CXX=g++
CXXFLAGS=-std=c++11 

bind: ./src/binding.cc ./src/eqDiffSolver.h
	cd ./src ; $(CXX) $(CXXFLAGS) -O3 -Wall -shared -fPIC -I/usr/include/python3.10 -I/home/simone/.local/lib/python3.10/site-packages/pybind11/include ./binding.cc -o VanDerPol.cpython-310-x86_64-linux-gnu.so

test: ./test/test_solution.cc
	cd ./test ; \
	$(CXX) $(CXXFLAGS) ./test_solution.cc -o test_solution
	touch test.sh ; chmod +x test.sh
	echo "./test_solution" >> test.sh

clean:
	rm -f ./test/test_solution
	rm -f ./test.sh
	rm -f ./*a.out
	clear
