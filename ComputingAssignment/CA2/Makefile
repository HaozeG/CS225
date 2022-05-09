objects = btree.o file.o

test:$(objects) test.cpp
	g++ -g $(objects) test.cpp -o test

file.o: data.h newfile.cpp base.cpp
	g++ -g -c newfile.cpp -o file.o
btree.o: btree.cpp btree.h data.h
	g++ -g -c btree.cpp -o btree.o
clean:
	rm -rf $(objects) test
