objects =  BPlusTree.o f_heap.o file.o
flags = -g

all: $(objects) main.cpp
	g++ $(flags) $(objects) main.cpp -o main
test: $(objects) test.cpp
	g++ $(flags) $(objects) test.cpp -o test
BPlusTree.o: BPlusTree.cpp BPlusTree.h data.h
	g++ -c BPlusTree.cpp -o BPlusTree.o
f_heap.o: data.h fibonacci_heap.h fibonacci_heap.cpp
	g++ $(flags) -c fibonacci_heap.cpp -o f_heap.o
file.o: newfile.cpp data.h base.cpp timeoffset.h
	g++ $(flags) -c newfile.cpp -o file.o
appoint.o: fibonacci_heap.h data.h
	g++ $(flags) -c appoint.cpp -o appoint.o
clean:
	rm -rf $(objects) main
