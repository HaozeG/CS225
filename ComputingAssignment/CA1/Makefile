objects = heap.o report.o file.o appoint.o

test: $(objects) main.cpp
	g++ -g $(objects) main.cpp -o test
heap.o: fibonacci_heap.cpp timeoffset.h fibonacci_heap.h data.h
	g++ -g -c fibonacci_heap.cpp -o heap.o
report.o: report.cpp report.h timeoffset.h data.h
	g++ -g -c report.cpp -o report.o
file.o: file.cpp data.h timeoffset.h
	g++ -g -c file.cpp -o file.o
appoint.o: appoint.cpp appoint.h data.h timeoffset.h
	g++ -g -c appoint.cpp -o appoint.o
clean:
	rm -rf $(objects) ./test

