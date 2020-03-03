/*
TASKS
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

using namespace std;

#define DEV false
typedef long long int64;

int64 rabbit(int64 N, int64 K)
{
	return 0;
}

void tests()
{

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