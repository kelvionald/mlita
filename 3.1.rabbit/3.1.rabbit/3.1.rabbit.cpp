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
// Копирайт: https://www.cyberforum.ru/post9400862.html

#include "pch.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

#define DEV false

typedef long long int64_;

const int64_ MAX_SIZE = 4;
const int64_ BASE = 1000000000;

struct int256
{
	int64_ nums[MAX_SIZE];

	int256(int64_ val)
	{
		memset(nums, 0, sizeof(int64_) * MAX_SIZE);
		int i = 0;
		while (true)
		{
			nums[i++] = val % BASE;
			val /= BASE;
			if (!val)
				break;
		}
	}

	void operator+=(const int256& other)
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			nums[i] += other.nums[i];
			if (nums[i] >= BASE && i < MAX_SIZE - 1)
			{
				nums[i] -= BASE;
				nums[i + 1]++;
			}
		}
	}

	friend ostream& operator<<(ostream& out, const int256& num)
	{
		string result;
		char buffer[10];
		for (size_t i = 1; i <= MAX_SIZE; i++)
		{
			sprintf(buffer, "%09d", num.nums[MAX_SIZE - i]);
			result += buffer;
		}
		string result2;
		bool isNulls = true;
		for (size_t i = 0; i < result.size(); i++)
		{
			if (isNulls)
			{
				if (result[i] != '0')
				{
					isNulls = false;
					result2 += result[i];
				}			
			}
			else
			{
				result2 += result[i];
			}
		}
		out << result2;
		return out;
	}

	bool operator==(long long val)
	{
		int i = 0;
		while (true)
		{
			if (nums[i++] != val % BASE)
			{
				return false;
			}
			val /= BASE;
			if (!val)
			{
				break;
			}
		}
		return true;
	}
};

typedef int256 int64;

int64 rabbit(int N, int K, string s = "")
{
	vector<int64> arr {1, 1};
	for (int i = 2; i <= N; i++)
	{
		int lenArr = arr.size();
		int min = K < lenArr ? K : lenArr;
		int offset = lenArr - min;
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