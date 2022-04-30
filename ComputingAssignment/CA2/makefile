objects = b_tree.o

test: $(objects) test.cpp
	g++ -g $(objects) test.cpp -o test
b_tree.o: b_tree.h b_tree.cpp
	g++ -g -c b_tree.cpp -o b_tree.o
