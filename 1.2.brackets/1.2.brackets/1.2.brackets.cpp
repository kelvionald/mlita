/*
1.2. Скобки (5)
При заданном четном N (N <= 18) перечислить все правильные скобочные
 формы длины N из скобок ‘(‘, ‘)’, ’[‘, ’]’.
Ввод из файла INPUT.TXT. В единственной строке задается число N.
Вывод  в файл OUTPUT.TXT всех правильных скобочных форм.
Пример
Ввод
5
Вывод
(())
([])
()()
()[]
[()]
[[]]
[]()
[][]
Подсказка. Поиском в глубину организовать  ограниченный  перебор
по  позициям строки. Нужно учитывать число вложенных открывающих
скобок, поскольку  потребуется такое же количество закрывающих.
Возможность добавления закрывающей скобки без нарушения синтаксиса
проверяется с помощью стека.
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2017

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef char byte;

struct Line {
	char str[19];
	byte c1 = 0;
	byte c2 = 0;
	byte c3 = 0;
	byte c4 = 0;
	byte openers = 0;
};

inline Line createLine(char ch) {
	Line l;
	l.str[0] = ch;
	l.str[1] = '\0';
	if (ch == '(') {
		l.c1 = 1;
		l.openers = 1;
	}
	else if (ch == '[') {
		l.c3 = 1;
		l.openers = 1;
	}
	return l;
}

inline void appendLine(Line &l, char ch, int pos) {
	l.str[pos] = ch;
	l.str[pos + 1] = '\0';
	if (ch == '(') { l.c1++; l.openers++; }
	else if (ch == ')') l.c2++;
	else if (ch == '[') { l.c3++; l.openers++; }
	else if (ch == ']') l.c4++;
}

inline int countChar(string str, char ch) {
	char* start = const_cast<char*>(str.c_str());
	return count(start, start + str.size(), ch);
}

int assoc[19] = {
	0,
	6,
	16,
	48,
	140,
	432,
	1316,
	4144,
	12944,
	40304,
	118900,
	333916,
	858044,
	2031132,
	4202268,
	7598700,
	10465804,
	10465804
};

inline int getMaxLen(int n) {
	return assoc[n];
}

inline void charHit(char ch, int i, int n, Line& line, Line* tmpstack, int& tcounter, bool& changed) {
	if (i == n - 1 && false) {
		//fout << line.str << ch << endl;
	}
	else {
		appendLine(line, ch, i);
		tmpstack[tcounter] = line;
		tcounter++;
		//cout << line.str << endl;
	}
	changed = true;
}

void calc(const int n) {
	int statDrop1 = 0;
	int statDrop2 = 0;
	int statDrop3 = 0;

	ofstream fout("output.txt");

	char chars[5] = "([)]";
	const int half = n / 2;
	const int strLen = n + 1;
	Line* fstack = new Line[getMaxLen(n - 1)]{
		createLine('('), createLine('[')
	};
	Line* tmpstack = new Line[getMaxLen(n - 1)];
	int fcounter = 2;
	int tcounter = 0;
	for (int i = 1; i < n; i++)
	{
		bool smaller = i < half;
		for (int j = 0; j < fcounter; j++)
		{
			// (
			bool changed = false;
			Line line = fstack[j];
			if (smaller || !(line.openers == half || line.c1 == half)) {
				charHit('(', i, n, line, tmpstack, tcounter, changed);
			}
			// [
			if (changed) {
				changed = false;
				line = fstack[j];
			}
			if (smaller || !(line.openers == half || line.c3 == half)) {
				charHit('[', i, n, line, tmpstack, tcounter, changed);
			}
			// )
			if (changed) {
				changed = false;
				line = fstack[j];
			}
			char lastCh = line.str[i - 1];
			if (!(lastCh == '[' || line.c1 - line.c2 == 0)) {
				charHit(')', i, n, line, tmpstack, tcounter, changed);
			}
			// ]
			if (changed) {
				line = fstack[j];
				lastCh = line.str[i - 1];
			}
			if (!(lastCh == '(' || line.c3 - line.c4 == 0)) {
				charHit(']', i, n, line, tmpstack, tcounter, changed);
			}
		}
		Line* swap = fstack;
		fstack = tmpstack;
		tmpstack = swap;
		fcounter = tcounter;
		tcounter = 0;
		cout << "" << fcounter << ", " << endl;
	}
	if (fcounter < 10) {
		for (int i = 0; i < fcounter; i++)
		{
			cout << fstack[i].str << endl;
		}
	}
	fout.close();
}

int main()
{
	string line;
	ifstream in("input.txt");
	if (in.is_open())
	{
		getline(in, line);
		int n;
		n = atoi(line.c_str());
		if (n % 2 == 1) {
			n = n - 1;
		}
		clock_t start;
		start = clock();
		calc(n);
		cout << (std::clock() - start) / (double)CLOCKS_PER_SEC << endl;
	}
	in.close();
	system("pause");
	return 0;
}