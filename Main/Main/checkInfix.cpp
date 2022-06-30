#include"Functions.h"
#include<iostream>
#include<stack>
using namespace std;

bool checkInfix(string infix) {
	stack<char>s;
	bool isoperator = 0; //The loop is not for operator, loop for operand
	for (int i = 0; i < infix.length();) {
		if (infix[i] == '(' || infix[i] == '[' || infix[i] == '{') {
			s.push(infix[i]);
			i++;
			continue;
		}
		//Number
		else if (isdigit(infix[i])) {
			if (isoperator == 1)
				return 0;
			isoperator = 1;
			bool isfloat = 0;
			int numdedigit = 0;
			while (isdigit(infix[i]) || infix[i] == '.') {
				if (isfloat == 1)
					numdedigit++;
				if (infix[i] == '.')
					isfloat = 1;
				if (numdedigit > 2)
					return 0;
				i++;
			}
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
			if (isoperator == 0)
				return 0;
			isoperator = 0;
			i++;
		}
		else
			return 0;
		//Check synthesis
		if (i >= infix.length())
			break;
		while (i < infix.length() && infix[i] != ' ') {
			if (infix[i] != ')' && infix[i] != ']' && infix[i] != '}')
				return 0;
			else {
				if (s.empty())
					return 0;
				if (infix[i] == ')' && s.top() != '(')
					return 0;
				else if (infix[i] == ']' && s.top() != '[')
					return 0;
				else if (infix[i] == '}' && s.top() != '{')
					return 0;
				s.pop();
				i++;
			}
		}
		i++;
	}
	if (!s.empty())
		return 0;
	return 1;
}