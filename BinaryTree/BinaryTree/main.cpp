#include <iostream>
#include "BinarySearchTree.h"

int main() {
	BinarySearchTree<int> tree;
	tree.insert(70);
	tree.insert(65);
	tree.insert(64);
	tree.insert(66);

	tree.deleteKey(70);

	return 0;
}