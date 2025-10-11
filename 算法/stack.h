#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename E>
class Stack {
private:
	E* data;
	int top;
	int capacity;
	
public:
	Stack(int size) {
		capacity = size;
		data = new E[capacity];
		top = -1;
	}
	
	~Stack() {
		delete[] data;
	}
	
	void push(E value) {
		if (top == capacity - 1) {
			cout << "Stack overflow!" << endl;
			return;
		}
		data[++top] = value;
	}
	
	E pop() {
		if (isEmpty()) {
			cout << "Stack underflow!" << endl;
			return E(); // 返回默认值
		}
		return data[top--];
	}
	
	E topvalue() const {
		if (isEmpty()) throw out_of_range("Stack is empty!");
		return data[top];
	}
	
	bool isEmpty() const {
		return top == -1;
	}
	
	void clear() {
		top = -1;
	}
};

#endif

