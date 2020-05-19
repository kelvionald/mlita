/*
20.13. Арифметическая прогрессия (4)
	Заданo N натуральных (целых положительных) чисел из диапазона [1; 10000]. 
Необходимо определить, можно ли из этих чисел в каком-либо порядке их следования 
составить арифметическую прогрессию. 
	Ввод. Первая строка файла INPUT.TXT содержит число тестовых блоков L (L ≤ 10). 
Каждый тестовый блок состоит из двух строк. В первой указывается количество чисел N (N ≤ 10^5), 
во второй - N чисел через пробел. 
	Вывод. Результат в файле OUTPUT.TXT. Для каждого тестового блока выводится единственная 
строка со значением Yes или No – можно или нет составить арифметическую прогрессию.
Пример
	Ввод
		2
		3
		5 9 1
		4
		11 13 15 13
	Вывод
		Yes
		No

*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2019

#include <cassert>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

#define DEV 0

int compare(const void* x1, const void* x2)
{
	return (*(int*)x1 - *(int*)x2);
}

bool checkSequence(vector<int>& nums)
{
	int len = nums.size();
	if (len == 1 || len == 2)
	{
		return true;
	}
	int d = nums[1] - nums[0];
	for (int i = 2; i < len; i++)
	{
		if (nums[i - 1] + d != nums[i])
		{
			return false;
		}
	}
	return true;
}

void show(vector<int>  nums)
{
	if (DEV && nums.size() < 20)
	{
		for (size_t i = 0; i < nums.size(); i++)
		{
			cout << nums[i] << " ";
		}
		cout << endl;
	}
}

void prepareBlock(ifstream& in, ofstream& out)
{
	int numCount;
	in >> numCount;
	vector<int> nums;
	for (int i = 0; i < numCount; i++)
	{
		int num;
		in >> num;
		nums.push_back(num);
	}
	qsort(&nums[0], numCount, sizeof(int), compare);
	show(nums);
	out << (checkSequence(nums) ? "Yes" : "No") << endl;
}

void program(ifstream& in, ofstream& out)
{
	int blocksCount;
	in >> blocksCount;
	for (int i = 0; i < blocksCount; i++)
	{
		prepareBlock(in, out);
	}
}

void tests()
{
	vector<int> a = { 1, 2, 3, 4 };
	assert(checkSequence(a));

	a = { 1, 2, 3, 5 };
	assert(!checkSequence(a));
}

int main()
{
	tests();
	string line;
	ifstream in("input.txt");
	ofstream out("output.txt");
	unsigned int start_time = clock();
	program(in, out);
	unsigned int end_time = clock();
	if (DEV) cout << end_time - start_time;
	in.close();
	out.close();
	return 0;
}