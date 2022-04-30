objects =  f_heap.o

test: $(objects) test.cpp
	g++ -g $(objects) test.cpp -o test
b_tree.o: b_tree.h b_tree.cpp
	g++ -g -c b_tree.cpp -o b_tree.o
f_heap.o: data.h fibonacci_heap.h fibonacci_heap.cpp
	g++ -g -c data.h fibonacci_heap.h fibonacci_heap.cpp -o f_heap.o
clean:
	rm -rf $(objects) test
