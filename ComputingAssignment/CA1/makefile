test: main.cpp heap.o appoint.o report.o
	g++ heap.o file.cpp appoint.o report.o main.cpp -o test
heap.o: fibonacii_heap.cpp fibonacii_heap.h data.h
	g++ -c fibonacii_heap.cpp -o heap.o
heap_test: heap.o fibonacii_heap_test.cpp
	g++ -c heap.o fibonacii_heap_test.cpp -o heap_test
report.o: report.cpp report.h
	g++ -c report.cpp -o report.o

appoint.o: appoint.cpp appoint.h
	g++ -c appoint.cpp -o appoint.o
clean:
	rm -rf ./test ./heap.o ./report.o

# test: maintest.cpp heap.o appoint.o
# 	g++ heap.o appoint.o maintest.cpp file.cpp -o test2
# heap.o: fibonacii_heap.cpp fibonacii_heap.h data.h
# 	g++ -c fibonacii_heap.cpp -o heap.o
# heap_test: heap.o fibonacii_heap_test.cpp
# 	g++ -c heap.o fibonacii_heap_test.cpp -o heap_test
# appoint.o: appoint.cpp appoint.h
# 	g++ -c appoint.cpp -o appoint.o
# clean:
# 	rm -rf ./test2 ./heap.o ./appoint.o
