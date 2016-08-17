#include <iostream>
#include <string>
#include "stack.h"
#include <queue>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

struct error {
	error(string x, string y) : name(x), description(y) {}
	string name;
	string description;
};

struct token {
	token(string x, char y) : value(x), type(y) {}
	string value;
	char type;
};

long double power(long double x, long double y);
string ctos(char);
long double calculate(long double, long double, char);
void initPriority();
void tokenize(const string &, vector<token> &);
void verify(vector<token> &);
int checkParentesis(vector<char> &);
void toPostfix(queue<string> &, stack<char> &, vector<token> &);
long double resolve(queue<string> &);
long double parse(const string &);
int pVerify(string);

int pVerify(string x) {
	if (x == "")
		return 1;
	bool ok = false;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] != ' ')
			ok = true;
	}
	if (ok == false)
		return 1;
	return 0;
}

map<char, int> pTable;

int main() {
	cout.precision(15);
	initPriority();
	string exp = "";
	while (1) {
		if (exp == "q" || exp == "quit" || exp == "exit")
			break;
		cout << ">>";
		getline(cin, exp);
		if (!pVerify(exp))
			cout << parse(exp) << endl;
	}
	return 0;
}

long double power(long double x, long double y) {
	if (y <= 0)
		return 1;
	return x * power(x, y - 1);
}

string ctos(char x) {
	stringstream c;
	c << x;
	return c.str();
}

long double calculate(long double x, long double y, char type) {
	switch (type) {
	case '+':
		return x + y;
		break;
	case '-':
		return x - y;
		break;
	case '*':
		return x * y;
		break;
	case '/':
		if (y == 0)
			throw error("Division error", "Division by 0 isn't possible");
		return x / y;
		break;
	case '%':
		return fmod(x, y);
		break;
	case '^':
		return power(x, y);
		break;
	default:
		return -1;
	}
}

void initPriority() {
	pTable['+'] = 1;
	pTable['-'] = 1;
	pTable['*'] = 2;
	pTable['/'] = 2;
	pTable['^'] = 3;
	pTable['%'] = 2;
	pTable['('] = NULL;
	pTable[')'] = NULL;
}

void tokenize(const string &exp, vector<token> &tokens) {
	string number = "";
	for (int i = 0; i < exp.size(); i++) {
		char curr = exp[i];
		if (pTable.find(curr) != pTable.end()) {
			if (number.size() != 0) {
				tokens.push_back(token(number, 'n'));
				number = "";
			}
			tokens.push_back(token(ctos(curr), 'o'));
		}
		else if (curr == ' ') {
			if (number.size() != 0) {
				tokens.push_back(token(number, 'n'));
				number = "";
			}
		}
		else if (isdigit(curr) || curr == '.' || curr == '_') {
			if (curr == '_') {
				if (number.size() != 0) {
					tokens.push_back(token(number, 'n'));
					number = "";
				}
				number += '-';
			}
			else
				number += curr;
		}
		else {
			throw error("Tokenization error", "An unknown character was found while tokenizing the expression.");
		}
	}
	if (number.size() != 0)
		tokens.push_back(token(number, 'n'));
}

void verify(vector<token> &tokens) {
	string front = tokens.front().value, back = tokens.back().value;
	if (pTable.find(front[0]) != pTable.end() && pTable[front[0]] != NULL && !isdigit(front[1])) {
		throw error("Verification error", "You can not begin an expression with an operator");
	}
	if (pTable.find(back[0]) != pTable.end() && pTable[back[0]] != NULL && !isdigit(back[1])) {
		throw error("Verification error", "You can not end an expression with an operator");
	}
	vector<char> parentesis;
	bool lwo = false, lwn = false;
	for (vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		if (it->type == 'n') {
			if (lwn)
				throw error("Verification error", "You can not have a number following another number");
			lwn = true;
			lwo = false;
		}
		else {
			if (it->value == "(") {
				parentesis.push_back('(');
				lwn = false;
				lwo = false;
			}
			else if (it->value == ")") {
				parentesis.push_back(')');
				lwn = false;
				lwo = false;
			}
			else {
				if (lwo)
					throw error("Verification error", "You can not have an operator following another operator");
				lwo = true;
				lwn = false;
			}
		}
	}
	if (parentesis.size() != 0) {
		cout << "Parentesis: ";
		for (vector<char>::iterator it = parentesis.begin(); it != parentesis.end(); it++)
			cout << *it << " ";
		cout << endl;
		if (checkParentesis(parentesis))
			throw error("Verification error", "There was some parentesis dismatch");
	}
}

int checkParentesis(vector<char> &parentesis) {
	if (parentesis.front() == ')')
		return 1;
	stack<char> s;
	for (vector<char>::iterator it = parentesis.begin(); it != parentesis.end(); it++) {
		if (*it == '(')
			s.push('(');
		else
			s.pop();
	}
	
	if (s.size() != 0)
		return 1;
	return 0;
}

void toPostfix(queue<string> &output, stack<char> &operators, vector<token> &tokens) {
	for (vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		if (it->type == 'n')
			output.push(it->value);
		else {
			if (it->value == "(")
				operators.push('(');
			else if (it->value == ")") {
				while (1) {
					char curr = operators.top();
					operators.pop();
					if (curr == '(')
						break;
					output.push(ctos(curr));
				}
			}
			else {
				if (operators.size() != 0) {
					while (1) {
						if (operators.size() != 0) {
							char curr = operators.top();
							if (curr == '(')
								break;
							if (pTable[curr] > pTable[it->value[0]]) {
								operators.pop();
								output.push(ctos(curr));
							}
							else
								break;
						}
						else
							break;
					}
				}
				operators.push(it->value[0]);
			}
		}
	}
	while (operators.size() != 0) {
		output.push(ctos(operators.top()));
		operators.pop();
	}
}

long double resolve(queue<string> &output) {
	stack<string> operands;
	while (output.size() != 0) {
		string curr = output.front();
		if (pTable.find(curr[0]) == pTable.end() || isdigit(curr[1]))
			operands.push(curr);
		else {
			double x, y;
			y = stold(operands.top());
			operands.pop();
			x = stold(operands.top());
			operands.pop();
			stringstream add;
			add << calculate(x, y, curr[0]);
			operands.push(add.str());
		}
		output.pop();
	}
	return stold(operands.top());
}

void show(queue<string> output) {
	cout << "Postfix: ";
	while (output.size() != 0) {
		cout << output.front() << " ";
		output.pop();
	}
	cout << endl;
}

long double parse(const string &exp) {
	vector<token> tokens;
	stack<char> operators;
	queue<string> output;
	try {
		tokenize(exp, tokens);
		cout << "Tokens: ";
		for (vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++)
			cout << it->value << " ";
		cout << endl;
		verify(tokens);
		toPostfix(output, operators, tokens);
		show(output);
		return resolve(output);
	}
	catch (error err) {
		cout << err.name << ": " << err.description << endl;
		return -1;
	}
}