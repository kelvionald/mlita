/*
10.12. Последовательность 4 (6)
Имеется последовательность целых чисел x1, x2, ..., xn. 
Найти количество троек чисел, в каждой из которых одно 
из чисел равно сумме двух других.
Ввод из файла INPUT.TXT. В первой строке содержится 
значение n (3 <= n <= 5000). Во второй строке заданы 
через пробел значения x1, x2, ..., xn  (1 <= xi <= 10^5).
Вывод в файл OUTPUT.TXT. В единственной строке выводится 
количество указанных троек чисел (xi, xj, xk).
Примеры
Ввод 1          Ввод 2
5               5
2 4 1 3 6       5 7 3 5 9
Вывод 1         Вывод 2
3               0

*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2017

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <map>

using namespace std;

#define DEV 1
#define MAX_IN 105

#define ALG_STUPID 1
#define ALG_SMART 2

#define ALG ALG_SMART

typedef int t_num;
typedef vector<t_num> Numbers;
typedef map<t_num, int> NumbersMap;

Numbers numbers;
NumbersMap stats;

void addNumberIfNotEmpty(string& tmp, const int& count) {
	if (tmp.size() && numbers.size() < count) {
		int val = atoi(tmp.c_str());
		stats[val]++;
		numbers.push_back(val);
		//cout << atoi(tmp.c_str()) << endl;
		tmp = "";
	}
}

void parse(int count, string rawNumbers) {
	numbers.reserve(count);
	string tmp;
	for (int i = 0; i < rawNumbers.size(); i++)
	{
		char ch = rawNumbers[i];
		if (ch == ' ') {
			addNumberIfNotEmpty(tmp, count);
			continue;
		}
		tmp += ch;
	}
	addNumberIfNotEmpty(tmp, count);
}

int compare(const void *i, const void *j)
{
	return *(int *)i - *(int *)j;
}

void sort() {
	qsort(&numbers[0], numbers.size(), sizeof(int), compare);
}

void calc(ofstream& out) {
	register int counter = 0;
	int length = numbers.size();
	if (ALG == ALG_STUPID) {
		for (int i = 0; i < length; i++) {
			for (int j = i + 1; j < length; j++) {
				for (int k = j + 1; k < length; k++) {
					int ni = numbers[i];
					int nj = numbers[j];
					int nk = numbers[k];
					if (ni + nj == nk) {
						counter++;
					}
					if (ni + nk == nj) {
						counter++;
					}
					if (nk + nj == ni) {
						counter++;
					}
				}
			}
		}
	}
	else if (ALG == ALG_SMART) {
		for (int i = 0; i < length; i++) {
			for (int j = i + 1; j < length; j++) {
				int ni = numbers[i];
				int nj = numbers[j];
				int s = ni + nj;
				if (stats.find(s) != stats.end())
				{
					counter += stats[s];
				}
			}
		}
	}

	if (DEV) cout << counter << endl;
	out << counter;
}

void program(int count, string rawNumbers, ofstream& out) {
	clock_t start;
	if (DEV) start = clock();
	parse(count, rawNumbers);
	sort();
	calc(out);
	if (DEV) cout << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	if (in.is_open())
	{
		string count;
		string rawNumbers;
		getline(in, count);
		getline(in, rawNumbers);
		//if (DEV) cout << count  << endl;
		try {
			program(atoi(count.c_str()), rawNumbers, out);
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