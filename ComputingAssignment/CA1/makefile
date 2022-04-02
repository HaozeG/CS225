test: main.cpp heap.o
	g++ heap.o file.cpp main.cpp -o test
heap.o: fibonacii_heap.cpp fibonacii_heap.h data.h
	g++ -c fibonacii_heap.cpp -o heap.o
heap_test: heap.o fibonacii_heap_test.cpp
	g++ -c heap.o fibonacii_heap_test.cpp -o heap_test
clean:
	rm -rf ./test ./heap.o
