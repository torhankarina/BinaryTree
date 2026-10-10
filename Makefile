CXX = g++
CXXFLAGS = -Wall -std=c++11 -O3

binarytree: binarytree.cc btree.h node.h
	$(CXX) $(CXXFLAGS) binarytree.cc -o binarytree

clean:
	rm -f binarytree