objects = BPlusTree.o file.o

test: $(objects) test.cpp data.h
	g++ $(objects) test.cpp -o test
BPlusTree.o: BPlusTree.cpp BPlusTree.h data.h
	g++ -c BPlusTree.cpp -o BPlusTree.o
file.o: newfile.cpp data.h base.cpp
	g++ -c newfile.cpp -o file.o
clean:
	rm -rf $(objects) test
