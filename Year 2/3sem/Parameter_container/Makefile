all:
	g++ par.cpp test.cpp -lm
	./a.out
gr:
	g++ par.cpp test.cpp -g
	valgrind ./a.out --quiet --kcachegrind
