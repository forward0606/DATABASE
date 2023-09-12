

a.out:  main.cpp KeyNode.o Node.o LeafNode.o BPTree.o
	g++ -g -fsanitize=address -fsanitize=leak main.cpp KeyNode.o Node.o LeafNode.o BPTree.o

example.out: example.cpp KeyNode.o Node.o LeafNode.o BPTree.o
	g++ -g -fsanitize=address -fsanitize=leak -o example.out example.cpp KeyNode.o Node.o LeafNode.o BPTree.o

Node.o: Node.h Node.cpp
	g++ -c -g -fsanitize=address -fsanitize=leak Node.h Node.cpp

KeyNode.o: Node.o KeyNode.h KeyNode.cpp
	g++ -c -g -fsanitize=address -fsanitize=leak KeyNode.h KeyNode.cpp

LeafNode.o:	Node.o LeafNode.h LeafNode.cpp
	g++ -c -g -fsanitize=address -fsanitize=leak LeafNode.h LeafNode.cpp

BPTree.o: Node.o KeyNode.o LeafNode.o BPtree.h BPtree.cpp
	g++ -c -g -fsanitize=address -fsanitize=leak BPtree.h BPtree.cpp

run:	testcase
	./a.out < testcase
clean: 
	-rm *.out
	-rm *.o
	-rm *.gch
