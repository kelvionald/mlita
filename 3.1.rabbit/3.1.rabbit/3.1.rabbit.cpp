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

struct bigint
{
	static const long long BASE = 1e9;
	static const long long SIZE = 4;

	long long digits[SIZE];

	bigint(long long val)
	{
		memset(digits, 0, sizeof(long long) * SIZE);
		int i = 0;
		while (val)
		{
			digits[i++] = val % BASE;
			val /= BASE;
		}
	}

	void operator+=(const bigint& other)
	{
		for (int i = 0; i < SIZE; i++)
		{ //сначала сложим числа поразрядно,
			digits[i] += other.digits[i]; //игнорируя переполнения
		}

		for (int i = 0; i < SIZE - 1; i++)
		{ //а затем поочередно выполним переносы
			if (digits[i] >= BASE)
			{ //для каждого разряда
				digits[i] -= BASE;
				digits[i + 1]++;
			}
		}
	}

	friend ostream& operator<<(ostream& out, const bigint& num)
	{
		string result;

		char buffer[10];

		for (int i = bigint::SIZE - 1; i >= 0; i--)
		{
			sprintf(buffer, "%09d", num.digits[i]);
			result += buffer;
		}

		int first_idx = result.find_first_not_of('0');
		if (first_idx == string::npos)
		{
			out << "0";
		}
		else
		{
			out << result.substr(first_idx);
		}

		return out;
	}

	bool operator==(long long val)
	{
		int i = 0;
		while (val)
		{
			if (digits[i++] != val % BASE)
			{
				return false;
			}
			val /= BASE;
		}
		return true;
	}
};

typedef bigint int64;

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
		int64 s = 0;
		for (int i = offset; i < arr.size(); i++)
		{
			s += arr[i];
		}
		arr.push_back(s);
	}
	return arr[N];
}

void tests()
{
	cout << rabbit(30, 2) << " " << (rabbit(30, 2) == 1346269) << endl;
	cout << rabbit(10, 10) << " " << (rabbit(10, 10) == 512) << endl;
	cout << rabbit(100, 100) << endl; //633825300114114700748351602688
}

void program(ifstream& in, ofstream& out)
{
	int N;
	int K;
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