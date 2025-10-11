#include <iostream>
#include <vector>
#include <string>
#include "stack.h"
using namespace std;

// 判断字符串是否是正整数
bool isInteger(const string &s) {
	if (s.empty()) return false;
	for (char c : s)
		if (!isdigit(c)) return false;
	return true;
}

// 返回运算符优先级
int precedence(const string &op) {
	if (op == "+" || op == "-") return 1;
	if (op == "*" || op == "/") return 2;
	return 0;
}

int main() {
	string line;
	getline(cin, line); // 读取整行输入
	
	vector<string> infix;   // 中缀表达式
	string token = "";
	
	// 解析输入，将数字和运算符分开
	for (char c : line) {
		if (isdigit(c)) {
			token += c; // 拼接多位数字
		} else {
			if (!token.empty()) {
				infix.push_back(token);
				token.clear();
			}
			
			if (c == ' ') continue; // 忽略空格
			
			if (c == '=') { // 遇到等号结束
				break;
			}
			
			string op(1, c); //将字符转化为一位字符串
			infix.push_back(op);
		}
	}
	
	if (!token.empty()) infix.push_back(token); // 最后数字入栈
	
	vector<string> afterfix;            // 后缀表达式
	Stack<string> opStack(infix.size()); // 运算符栈
	
	// 中缀转后缀
	for (const string &t : infix) {
		if (isInteger(t)) { //数字直接加入后缀表达式
			afterfix.push_back(t);
		} 
		
		else if (t == "(") { //前括号直接入栈
			opStack.push(t);
		} 
		
		else if (t == ")") {
			bool foundLeftParen = false;
			while (!opStack.isEmpty()) {
				string top = opStack.topvalue();
				if (top == "(") {
					opStack.pop(); // 弹出 '('
					foundLeftParen = true;
					break;
				} else {
					afterfix.push_back(opStack.pop());
				}
			}
			if (!foundLeftParen) {
				throw out_of_range("错误格式：括号不匹配");
			}
		}
		
		
		else { // 运算符 + - * /
			while (!opStack.isEmpty() && opStack.topvalue() != "(" &&
				precedence(opStack.topvalue()) >= precedence(t)) { 
				afterfix.push_back(opStack.pop()); //根据优先级决定栈顶符号是否加入后缀表达式
			}
			opStack.push(t); //入栈
		}
	}
	
	while (!opStack.isEmpty()) { //弹出栈中剩余元素
		if (opStack.topvalue() == "(") throw out_of_range("错误格式：括号不匹配");
		afterfix.push_back(opStack.pop());
	}
	
	afterfix.push_back("="); // 等号标记结束 
	
	// 计算后缀表达式
	Stack<double> numStack(afterfix.size());
	for (const string &t : afterfix) {
		if (isInteger(t)) { //数字入栈
			numStack.push(stod(t));
		} else if (t == "+") { //符号弹出两个数进行相应计算
			double b = numStack.pop();
			double a = numStack.pop();
			numStack.push(a + b);
		} else if (t == "-") {
			double b = numStack.pop();
			double a = numStack.pop();
			numStack.push(a - b);
		} else if (t == "*") {
			double b = numStack.pop();
			double a = numStack.pop();
			numStack.push(a * b);
		} else if (t == "/") {
			double b = numStack.pop();
			double a = numStack.pop();
			if (b == 0) throw runtime_error("除零错误");
			numStack.push(a / b);
		} else if (t == "=") { //遇到等号结束计算，弹出结果
			cout << "Result: " << numStack.topvalue() << endl;
		}
	}
	
	return 0;
}
