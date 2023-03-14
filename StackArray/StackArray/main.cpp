#include <iostream>
#include "StackArray.h"


int main() {
	
	StackArray<int> stack;
	std::cout << (stack.isEmpty() ? "YEA\n" : "NO\n");

	std::cout << (stack.isFull() ? "YE\n" : "NO\n");

	stack.Print();

	stack.push(5);
	stack.push(4);
	stack.push(7);
	stack.Print();
	std::cout << stack.top() << "\n";

	stack.pop();
	stack.Print();
	std::cout << stack.top() << "\n";

}