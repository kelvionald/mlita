/*
3.1. Заяц (5)
	Имеется лестница, состоящая из N ступенек. При подъеме по лестнице 
заяц может прыгать на любое количество ступенек от 1 до K. Сколько 
у зайца способов подъема по лестнице? 
	Ввод из файла INPUT.TXT. Единственная строка содержит целые 
положительные числа N и K.
	Вывод  в файл OUTPUT.TXT. Выводится единственное число - количество 
способов подъема по лестнице.
	Ограничения: 1 <= K <= N <= 100.
Пример
	Ввод
	3 2
	Вывод
	3
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2017

#include "pch.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

#define DEV true

typedef long long int64;

template <typename T>
T min(T a, T b)
{
	return a < b ? a : b;
}

int64 rabbit(int N, int K, string s = "")
{
	vector<int64> arr {1, 1};
	for (int i = 2; i <= N; i++)
	{
		int lenArr = arr.size();
		int offset = lenArr - min(K, lenArr);
		int64 s = accumulate(arr.begin() + offset, arr.end(), 0);
		arr.push_back(s);
	}
	return arr[N];
}

void tests()
{
	cout << (rabbit(30, 2) == 1346269) << endl;
}

void program(ifstream& in, ofstream& out)
{
	int64 N;
	int64 K;
	in >> N;
	in >> K;
	out << rabbit(N, K);
}

int main()
{
	if (DEV)
	{
		tests();
	}
	else
	{
		string line;
		ifstream in("input.txt");
		ofstream out("output.txt");
		if (in.is_open())
		{
			program(in, out);
			in.close();
		}
		else
		{
			cout << "Error open input.txt\n";
		}
		out.close();
	}
	if (DEV)
		system("pause");
	return 0;
}