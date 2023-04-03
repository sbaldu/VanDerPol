test:
	g++ test/test_solution.cc -o testsol
	(./testsol && clear) || exit
	rm testsol ; clear

bind:
	cd ./src ; ./compile.sh && clear
