/*
2.8.Калькулятор(7)
	Одна фирма выпускает в продажу странные калькуляторы.Они могут выполнять лишь три операции :
	- ввести число 1;
	- удвоить текущее число;
	- поменять в текущем числе первую и последнюю цифры.
	Калькулятор умеет работать лишь с целыми числами от 1 до L(1 ≤ L ≤ 10^5).Незначащие нули в 
начале числа отбрасываются.Написать программу, которая проверяет, можно ли на данном калькуляторе 
получить число N(1 ≤ N ≤ 10^5).Если это возможно, выдать самую короткую последовательность преобразований.
	Ввод.В единственной строке находятся через пробел значения число L и N.
	Вывод.В первой строке вывести Yes или No.Если значение N достижимо, во второй строке выдать 
количество значений в цепочке преобразований от 1 до N, а в третьей строке через пробел сами эти значения.
Примеры
	Ввод 1       Ввод 2
	 100 61       100 3
	Вывод 1      Вывод 2
	 Yes          No
	 6
	 1 2 4 8 16 61
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2017

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define DEV 1

bool isPossible = false;

struct row {
	int num;
	bool swapped = false;
	row* parent = nullptr;
	int deep;
};

queue<row*> q;
row* curr;
set<int> nums;
int L;
int N;

int swapExtremeDigits(int a) {
	int p = 10;
	while (a / p > 10) {
		p *= 10;
	}
	int unit = a % 10;
	int div = a / p;
	return a + unit * (p - 1) + div * (1 - p);
}

void addQ(int num, row* parent, bool swapped = false, int deep = 1) {
	if (num < L && nums.find(num) == nums.end()) {
		nums.insert(num);
		row* local = new row{ num, swapped, parent, deep };
		q.push(local);
	}
}

void calc() {
	isPossible = false;
	addQ(N, nullptr);
	while (q.size())
	{
		curr = q.front();
		q.pop();
		if (DEV) for (int i = 1; i < curr->deep; i++) cout << ' ';
		if (DEV) cout << curr->num << " " << curr->swapped << endl;
		if (curr->num == 1) {
			isPossible = true;
			return;
		}
		if (curr->num % 2 == 0) {
			addQ(curr->num / 2, curr, false, curr->deep + 1);
		}
		//if (curr->num % 10 != 0) {
			addQ(swapExtremeDigits(curr->num), curr, true, curr->deep + 1);
		//}
	}
}

void showPath(ofstream& out) {
	cout << curr->deep << endl;
	out << curr->deep << endl;
	while (true) {
		cout << curr->num << " ";
		out << curr->num << " ";
		if (curr->parent == nullptr) {
			break;
		}
		curr = curr->parent;
	}
	cout << endl;
	out << endl;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	in >> L;
	in >> N;
	calc();
	if (isPossible) {
		cout << "Yes" << endl;
		out << "Yes" << endl;
		showPath(out);
	} else {
		cout << "No" << endl;
		out << "No" << endl;
	}
	in.close();
	out.close();
	if (DEV) system("pause");
}