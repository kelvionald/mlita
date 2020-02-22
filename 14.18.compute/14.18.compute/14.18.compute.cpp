/*
14.18. Вычисление выражения (7)
Во входной строке записано арифметическое выражение, состоящее из 
целых чисел и знаков операций «+», «-», «*», «/», «(», «)», «^». 
Пробелы в выражении отсутствуют. Требуется написать программу, 
которая вычислит значение данного выражения.
Ввод. Входной файл INPUT.TXT содержит одну строку, состоящую не 
более чем из 255 символов. Числа в выражении не превышают по модулю 
2х10^9. Гарантируется, что в процессе вычислений получаемые значения 
не превышают по модулю 2х10^9.
Вывод. В единственной строке файла OUTPUT.TXT требуется вывести 
значение выражения с точностью 4 знака после запятой.
Примеры
Ввод 1            Ввод 2
1+2*3^(1-2/3^4)  (1/2+2/3)*(3/4-4/5)*1000
Вывод 1           Вывод 2
6.8394            -58.3333
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2017

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define DEV 0

#define and &&
#define or ||

struct Token
{
	string value;
	double numVal;
	bool isNum = false;
};

typedef vector<Token> Tokens;

Tokens tokens;

void prtTokens(Tokens tokens) {
	for (int i = 0; i < tokens.size(); i++)
	{
		cout << tokens[i].value << " ";
	}
	cout << endl;
}

Token createToken(char ch) {
	string val;
	val = ch;
	Token t{ val };
	return t;
}

Token createToken(string tmp) {
	double numVal = atof(tmp.c_str());
	Token t{ tmp, numVal, true };
	return t;
}

Token createToken(double numVal) {
	Token t{ "", numVal, true };
	return t;
}

void addToken(Token t) {
	tokens.push_back(t);
}

void addTokenIfFilled(string& tmp) {
	if (tmp.length()) {
		addToken(createToken(tmp));
		tmp = "";
	}
}

void tokenize(string line)
{
	string tmp;
	bool isNumber = false;
	char prevCh = '\0';
	for (int i = 0; i < line.length(); i++)
	{
		char ch = line[i];
		isNumber = isdigit(ch);
		if (isNumber) {
			tmp += ch;
		}
		else if ((ch == '-' or ch == '+') and prevCh == '(') {
			addToken(createToken("0"));
			addToken(createToken(ch));
		}
		else if ((ch == '-' or ch == '+') and i == 0) {
			addToken(createToken("0"));
			addToken(createToken(ch));
		}
		else {
			addTokenIfFilled(tmp);
			addToken(createToken(ch));
		}
		prevCh = ch;
	}
	addTokenIfFilled(tmp);
}

bool isSimpleOperator(Token t) {
	char ch = t.value[0];
	if (ch == '+') return true;
	if (ch == '-') return true;
	if (ch == '*') return true;
	if (ch == '/') return true;
	return false;
}

int priority(Token t) {
	char ch = t.value[0];
	if (ch == '+') return 1;
	if (ch == '-') return 1;
	if (ch == '*') return 2;
	if (ch == '/') return 2;
	return 0;
}

void pushing(Tokens& stack, Tokens& result) {
	int len = stack.size();
	for (int i = 0; i < len; i++)
	{
		Token t = stack[stack.size() - 1];
		stack.pop_back();
		if (t.value == "(") {
			break;
		}
		result.push_back(t);
	}
}

Tokens result;

void postfixier() {
	Tokens stack;
	for (int i = 0; i < tokens.size(); i++)
	{
		Token t = tokens[i];
		if (t.isNum) {
			result.push_back(t);
		}
		else if (stack.size() == 0 or stack[stack.size() - 1].value == "(") {
			stack.push_back(t);
		}
		else if (stack.size() != 0 and isSimpleOperator(t) and isSimpleOperator(stack[stack.size() - 1]) and priority(t) > priority(stack[stack.size() - 1])) {
			stack.push_back(t);
		}
		else if (stack.size() != 0 and isSimpleOperator(t) and isSimpleOperator(stack[stack.size() - 1]) and priority(t) == priority(stack[stack.size() - 1])) {
			Token t2 = stack[stack.size() - 1];
			stack.pop_back();
			result.push_back(t2);
			stack.push_back(t);
		}
		else if (isSimpleOperator(t)) {
			pushing(stack, result);
			stack.push_back(t);
		}
		else if (t.value == "^") {
			stack.push_back(t);
		}
		else if (t.value == "(") {
			stack.push_back(t);
		}
		else if (t.value == ")") {
			pushing(stack, result);
		}
	}
	pushing(stack, result);
	if (DEV) {
		cout << "rpn ";
		prtTokens(result);
	}
}

double calculate() {
	Tokens stack;
	for (int i = 0; i < result.size(); i++)
	{
		Token t = result[i];
		if (t.isNum) {
			stack.push_back(t);
		}
		else if (isSimpleOperator(t) or t.value == "^") {
			double a = stack[stack.size() - 2].numVal;
			double b = stack[stack.size() - 1].numVal;
			stack.pop_back();
			stack.pop_back();
			double result;
			char ch = t.value[0];
			if (DEV) cout << a << " " << ch << " " << b << endl;
			if (ch == '-') {
				result = a - b;
			}
			else if (ch == '+') {
				result = a + b;
			}
			else if (ch == '*') {
				result = a * b;
			}
			else if (ch == '/') {
				result = a / b;
			}
			else if (ch == '^') {
				result = pow(a, b);
			}
			stack.push_back(createToken(result));
		}
	}
	if (DEV) cout << stack[0].numVal << endl;
	return stack[0].numVal;
}

double compute(string line) {
	tokenize(line);
	postfixier();
	return calculate();
}

int main()
{
	string line;
	ifstream in("input.txt");
	ofstream out("output.txt");
	out.precision(4);
	out.setf(ios::fixed);
	cout.precision(4);
	cout.setf(ios::fixed);
	if (in.is_open())
	{
		getline(in, line);
		if (DEV) cout << "input ";
		if (DEV) cout << line << endl;
		try {
			out << compute(line);
		}
		catch (string s) {
			cout << "Error: " << s << endl;
		}
		catch (char* s) {
			cout << "Error: " << s << endl;
		}
		in.close();
	}
	else {
		cout << "Error open input.txt\n";
	}
	out.close();
	if (DEV) system("pause");
	return 0;
}