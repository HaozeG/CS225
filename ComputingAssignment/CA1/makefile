test: main.cpp heap.o
	g++ heap.o main.cpp -o test
heap.o: fibonacii_heap.cpp fibonacii_heap.h data.h
	g++ -c fibonacii_heap.cpp -o heap.o
clean: test heap.o
	rm -rf test heap.o
