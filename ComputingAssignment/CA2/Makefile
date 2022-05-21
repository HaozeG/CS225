objects =  BPlusTree.o fibonacci_heap.o report.o base.o file.o appoint.o btree.o
flags = -g

all: $(objects) main.cpp
	g++ $(flags) $(objects) main.cpp -o main
# test: $(objects) main.cpp
# 	g++ $(flags) $(objects) main.cpp -o test
report.o: report.h report.cpp data.h
	g++ $(flags) -c report.cpp -o report.o
BPlusTree.o: BPlusTree.cpp BPlusTree.h data.h
	g++ $(flags) -c BPlusTree.cpp -o BPlusTree.o
fibonacci_heap.o: data.h fibonacci_heap.h fibonacci_heap.cpp
	g++ $(flags) -c fibonacci_heap.cpp -o fibonacci_heap.o
file.o: file.cpp data.h timeoffset.h
	g++ $(flags) -c file.cpp -o file.o
base.o: base.cpp data.h
	g++ $(flags) -c base.cpp -o base.o
appoint.o: fibonacci_heap.h data.h
	g++ $(flags) -c appoint.cpp -o appoint.o
btree.o: btree.cpp btree.h data.h
	g++ $(flags) -c btree.cpp -o btree.o
# %.o: %.cpp %.h data.h
# 	g++ $(flags) -c $<

clean:
	rm -rf $(objects) main
