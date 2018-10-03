BinarySearchTree: BinarySearchTree.cpp
	g++ -std=c++11 BinarySearchTree.cpp -o BinarySearchTree

clean:
	rm -f *.o
	rm -f BinarySearchTree

run: BinarySearchTree
	./BinarySearchTree
