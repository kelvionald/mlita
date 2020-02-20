/*
TASK
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

using namespace std;

#define DEV false

int main()
{
	string line;
	ifstream in("input.txt");
	ofstream out("output.txt");
	if (in.is_open())
	{
		getline(in, line);
		if (DEV) cout << line << endl;
		try {
			// line
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