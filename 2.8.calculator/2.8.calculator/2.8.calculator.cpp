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
};

struct row2 {
	int num;
	bool swapped = false;
	row2* parent = nullptr;
};

queue<row> q;
queue<row2> q2;
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

void addQ(int num, bool swapped = false) {
	if (num < L) {
		q.push({ num, swapped });
	}
}

void addQ2(int num, row2* parent, bool swapped = false) {
	if (num < L && nums.find(num) == nums.end()) {
		nums.insert(num);
		q2.push({ num, swapped, parent });
	}
}

void calc(int need) {
	q.push({ 1 });
	for (int i = 0; i < 10 && q.size(); i++)
	{
		row curr = q.front();
		cout << " " << curr.num << " " << curr.swapped << endl;
		if (curr.num == need) {
			isPossible = true;
			return;
		}
		q.pop();
		if (curr.num > 9) {
			addQ(curr.num * 2);
			if (!curr.swapped) {
				addQ(swapExtremeDigits(curr.num), true);
			}
		} else {
			addQ(curr.num * 2);
		}
	}
}

void calc2() {
	if (N > L) {
		return;
	}
	q2.push({ N });
	for (int i = 0; q2.size(); i++)
	{
		row2 curr = q2.front();
		q2.pop();
		cout << curr.num << " " << curr.swapped << endl;
		if (curr.num == 1) {
			isPossible = true;
			return;
		}
		if (curr.num % 2 == 0) {
			addQ2(curr.num / 2, &curr);
		}
		if (!curr.swapped) {
			addQ2(swapExtremeDigits(curr.num), &curr, true);
		}
		//swap ?= swap swap
	}
}

int main()
{
	ifstream in("input.txt");
	in >> L;
	in >> N;
	//calc(N);
	calc2();
	cout << (isPossible ? "Yes" : "No") << endl;
	if (DEV) system("pause");
}