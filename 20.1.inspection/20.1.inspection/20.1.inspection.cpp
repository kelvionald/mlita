/*
20.1. Осмотр (4)
	Для того, чтобы быть допущенным к занятиям в бассейне, необходимо предъявить справку,
на которой должны поставить свои подписи K врачей. Некоторые врачи отказываются ставить
подписи на справке до тех пор, пока на ней не распишется другой врач. Например, стоматолог
отказывается ставить подпись, пока не будет принесена справка от психиатра, потому что
однажды его укусил психически неуравновешенный студент. Составлен список, какому врачу нужны
какие справки. Нужно определить, можно ли получить все справки, а также в какой последовательности
необходимо обходить врачей.
	Ввод. В первой строке файла INPUT.TXT содержится общее количество врачей (1 ≤ K ≤ 100).
В следующих K строках описываются необходимые справки. Первое число j в i+1 строке входного
файла означает, сколько справок нужно i-му врачу. Затем в той же строке, содержится j чисел
- номера врачей, чьи подписи надо предварительно поставить, чтобы получить подпись i-го врача.
	Вывод. Если подписи всех врачей собрать невозможно, то в выходной файл OUTPUT.TXT следует
вывести NO. Если же все справки собрать возможно, то в первой строке выходного файла должно
содержаться YES, а в следующих K строках - последовательность, в которой нужно получать справки.
В случае нескольких решений выдать любое из них.
Пример
Ввод
	4
	1 2
	0
	2 1 4
	1 1
Вывод
	YES
	2
	1
	4
	3
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2019

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

#define DEV 0

typedef map<int, vector<int>> Inputs;
typedef map<int, map<int, bool>> Outputs;

const int VISITED = true;
const int UNVISITED = false;

int doctor_count;
vector<int> path;

void deepshow(int deep)
{
	for (int i = 0; i < deep; i++)
	{
		cout << ' ';
	}
}

void base_walk(Inputs& inputs, Outputs& outputs, int index, int deep = 0)
{
	if (DEV)
	{
		deepshow(deep);
		cout << index << endl;
	}
	path.push_back(index);
	for (int i = 0; i < inputs[index].size(); i++)
	{
		int nextIndex = inputs[index][i];
		outputs[nextIndex][index] = VISITED;
		for (auto it = outputs[nextIndex].cbegin(); it != outputs[nextIndex].cend(); ++it)
		{
			if (it->second == UNVISITED)
			{
				goto a;
			}
		}
		base_walk(inputs, outputs, nextIndex, deep + 1);
	a:;
	}
}

inline bool checkNodes(Outputs& outputs)
{
	for (auto it = outputs.cbegin(); it != outputs.cend(); ++it)
	{
		for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2)
		{
			if (it2->second == UNVISITED)
			{
				return false;
			}
		}
	}
	return true;
}

inline void initial_walk(Inputs& inputs, Outputs& outputs, vector<int>& start_doctors, ostream& out)
{
	path.clear();
	for (int i = 0; i < start_doctors.size(); i++)
	{
		int index = start_doctors[i];
		base_walk(inputs, outputs, index);
	}
	if (checkNodes(outputs))
	{
		out << "YES\n";
		for (int i = 0; i < path.size(); i++)
		{
			out << path[i] + 1 << endl;
		}
		return;
	}
	out << "NO\n";
}

void program(istream& in, ostream& out)
{
	in >> doctor_count;
	Inputs inputs;
	Outputs outputs;
	vector<int> start_doctors;
	for (int i = 0; i < doctor_count; i++)
	{
		int requires_signatures_count;
		in >> requires_signatures_count;
		for (int k = 0; k < requires_signatures_count; k++)
		{
			int require_signature_num;
			in >> require_signature_num;
			inputs[require_signature_num - 1].push_back(i);
			outputs[i].insert({ require_signature_num - 1, UNVISITED });

			if (DEV)
			{
				cout << " " << require_signature_num - 1 << " > " << i << endl;
			}
		}
		if (requires_signatures_count == 0)
		{
			start_doctors.push_back(i);
		}
	}
	initial_walk(inputs, outputs, start_doctors, out);
}

void makeTest(string input, string expect) {
	istringstream in(input);
	ostringstream out;
	program(in, out);
	string actual = out.str();
	cout << "_" << actual << endl;
	assert(actual == expect);
}

void tests()
{
	makeTest("4\n1 2\n0\n2 1 4\n1 1", "YES\n2\n1\n4\n3\n");
	makeTest("3\n0\n0\n2 1 2", "YES\n1\n2\n3\n");
	makeTest("3\n0\n1 1\n1 1", "YES\n1\n2\n3\n");
	makeTest("4\n1 4\n1 1\n1 2\n1 3", "NO\n");
	makeTest("5\n0\n1 1\n1 2\n2 1 3\n1 3", "YES\n1\n2\n3\n5\n4\n");
	makeTest("5\n0\n1 3\n0\n1 1\n0", "YES\n1\n4\n3\n2\n5\n");
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
		program(in, out);
		in.close();
		out.close();
	}
	return 0;
}