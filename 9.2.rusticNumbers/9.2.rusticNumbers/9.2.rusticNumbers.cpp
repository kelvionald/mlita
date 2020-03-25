/*
9.2. Простоватые числа (3)
	Студент Вася отыскивает простые числа в диапазоне от 1 до N (1 ≤  N ≤ 10^18). 
Если число M, не превосходящее N, не делится на  2, 3 и 5, Вася называет его "простоватым". 
По заданному значению N найти количество простоватых чисел.
	Ввод. В единственной строке файла INPUT.TXT находится число N.
	Вывод. В единственную строку файла OUTPUT.TXT вывести количество простоватых чисел.
Пример
	Ввод
		10
	Вывод
		2
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2017

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

typedef unsigned long long uint64;

uint64 func(uint64 N) {
	return N - (N / 2 + N / 3 + N / 5 - N / 6 - N / 10 - N / 15 + N / 30);
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint64 a;
	in >> a;
	a = func(a);
	cout << a << endl;
	out << a << endl;
	in.close();
	out.close();
}