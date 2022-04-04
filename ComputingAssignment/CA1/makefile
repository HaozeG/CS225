objects = heap.o report.o file.o appoint.o main.cpp

test: $(objects)
	g++ $(objects) -o test
heap.o: fibonacii_heap.cpp timeoffset.h fibonacii_heap.h data.h
	g++ -c fibonacii_heap.cpp -o heap.o
report.o: report.cpp report.h timeoffset.h data.h
	g++ -c report.cpp -o report.o
file.o: file.cpp data.h timeoffset.h
	g++ -c file.cpp -o file.o
appoint.o: appoint.cpp appoint.h data.h timeoffset.h
	g++ -c appoint.cpp -o appoint.o
clean:
	rm -rf ./test ./heap.o ./report.o ./file.o ./appoint.o

