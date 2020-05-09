/*
13.7. Кроссворд (7)
	Заданы четыре слова, в каждом из которых нет повторяющихся букв.
Требуется составить минимальный по количеству клеток прямоугольный
кроссворд, в котором два первых слова расположены горизонтально, и
первое выше второго, а два последних - вертикально, и третье левее
четвертого. Каждое горизонтальное слово должно пересекаться с обоими
вертикальными словами.
	Ввод из файла INPUT.TXT. В первых четырех строках записаны слова,
состоящие из заглавных латинских букв. Длина каждого слова до 20
символов.
	Вывод в файл OUTPUT.TXT. Вывести кроссворд в виде прямоугольника
из минимального количества клеток. Проставить звездочки в те позиции,
где нет букв. Левый край кроссворда должен быть в первой позиции, а
верхний край - в первой строке. Если решений несколько, вывести любое
из них. При отсутствии решений вывести No.
Пример
Ввод
	STAMPING	--
	FORMULA		--
	STOP		||
	SPELING		||
Вывод
	*****S***
	*STAMPING
	*T***E***
	FORMULA**
	*P***I***
	*****N***
	*****G***
*/
// Автор: Турецкий Сергей ПС-22
// Среда разработки: Visual Studio 2019

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const bool dev = true;

struct pair_
{
	int hi, vi;
	char ch;
};

struct case_
{
	pair_ ac, ad, bc, bd;
};

typedef vector<pair_> pairs;

void prt(pairs p)
{
	if (dev) cout << "'\n";
	for (size_t i = 0; i < p.size(); i++)
	{
		if (dev) cout << " " << p[i].hi << " " << p[i].vi << " " << p[i].ch << endl;
	}
}

pairs find_collisions(string l, string r)
{
	pairs p;
	for (int i = 0; i < l.size(); i++)
	{
		for (int k = 0; k < r.size(); k++)
		{
			if (l[i] == r[k])
			{
				p.push_back({ i, k, l[i] });
			}
		}
	}
	return p;
}

int calcSize(int a, int b, int al, int bl)
{
	if (b > a)
	{
		int d = b - a;
		if (al + d > b)
		{
			return al + d;
		}
		else
		{
			return b;
		}
	}
	else
	{
		int d = a - b;
		if (bl + d > a)
		{
			return bl + d;
		}
		else
		{
			return a;
		}
	}
	return 0;
}

/*
  c d
 aaaaa
  c d
bbbbb
  c d
*/

inline bool checkExists(pair_& ac, pair_& ad, pair_& bc, pair_& bd)
{
	return ad.hi - ac.hi == bd.hi - bc.hi && bc.vi - ac.vi == bd.vi - ad.vi;
}

inline int getSize(
	pair_& ac, pair_& ad, pair_& bc, pair_& bd,
	string& a, string& b, string& c, string& d)
{
	int width = calcSize(ac.hi, bc.hi, a.size(), b.size());
	int height = calcSize(ad.vi, ad.vi, c.size(), d.size());
	/*if (dev) cout << "width: " << width << endl;
	if (dev) cout << "height: " << height << endl;
	if (dev) cout << " " << ac.hi << " " << bc.hi << endl;
	if (dev) cout << " " << ad.vi << " " << ad.vi << " " << c.size() << " " << d.size() << endl;*/
	return width * height;
}

case_ cases;
int minSize = -1;

void form(string a, string b, string c, string d)
{
	minSize = -1;
	pairs ac = find_collisions(a, c);
	pairs ad = find_collisions(a, d);
	pairs bc = find_collisions(b, c);
	pairs bd = find_collisions(b, d);

	/*prt(ac);
	prt(ad);
	prt(bc);
	prt(bd);*/

	for (int i = 0; i < ac.size(); i++)
	{
		pair_ ac_ = ac[i];
		for (int j = 0; j < ad.size(); j++)
		{
			pair_ ad_ = ad[j];
			if (!(ac_.vi < ad_.vi))
				continue;

			for (int k = 0; k < bc.size(); k++)
			{
				pair_ bc_ = bc[k];
				if (!(ac_.hi < bc_.hi))
					continue;

				for (int m = 0; m < bd.size(); m++)
				{
					pair_ bd_ = bd[m];
					if (!(ad_.hi < bd_.hi) || !(bc_.vi < bd_.vi))
						continue;

					if (!checkExists(ac_, ad_, bc_, bd_))
						continue;

					int size = getSize(ac_, ad_, bc_, bd_, a, b, c, d);
					if (minSize == -1 || minSize > size)
					{
						minSize = size;
						cases = {
							ac_,
							ad_,
							bc_,
							bd_
						};
					}

					if (dev && "ABCDEFGHIJKLMNOPQRSTUVWXYZ" != a)
					{

						cout << "*" << endl;
						cout << ac_.vi << " "
							 << ad_.vi << " "
							 << ac_.ch << " "
							 << ad_.ch << " "

							 << ac_.hi << " "
							 << bc_.hi << " "
							 << ac_.ch << " "
							 << bc_.ch << " "

							 << ad_.hi << " "
							 << bd_.hi << " "
							 << ad_.ch << " "
							 << bd_.ch << " "

							 << bc_.hi << " "
							 << bd_.hi << " "
							 << bc_.ch << " "
							 << bd_.ch << " "

							 << endl;
					}
				}
			}
		}
	}
}

/*
  c d
 aaaaa
  c d
bbbbb
  c d
*/

const int SIZE = 26 * 3;
const int CENTER = SIZE / 2;

char** createCrossword(case_ cases, string a, string b, string c, string d)
{
	char** matrix = new char*[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		matrix[i] = new char[SIZE];
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = '*';
		}
	}
	for (int i = 0; i < a.size(); i++)
	{
		int xi = i + CENTER;
		matrix[CENTER][xi] = a[i];
		if (cases.ac.hi == i)
		{
			for (int j = 0; j < c.size(); j++)
			{
				int yi = CENTER - cases.ac.vi + j;
				matrix[yi][xi] = c[j];
				if (cases.bc.vi == j)
				{
					for (int k = 0; k < b.size(); k++)
					{
						matrix[yi][xi + k - cases.bc.hi] = b[k];
					}
				}
			}
		}
		if (cases.ad.hi == i)
		{
			for (int j = 0; j < d.size(); j++)
			{
				matrix[CENTER - cases.ad.vi + j][i + CENTER] = d[j];
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//if (dev) cout << matrix[i][j];
		}
		//if (dev) cout << " " << i << "\n";
	}
	return matrix;
}

void findCutCoord(char** matrix, int& top, int& left, int& right, int& bottom)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j] != '*')
			{
				top = i - 1;
				goto a;
			}
		}
	}

a:
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[j][i] != '*')
			{
				left = i - 1;
				goto b;
			}
		}
	}

b:
	for (int i = SIZE - 1; i != 0; i--)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[j][i] != '*')
			{
				right = i + 1;
				goto c;
			}
		}
	}

c:
	for (int i = SIZE - 1; i != 0; i--)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (matrix[i][j] != '*')
			{
				bottom = i + 1;
				return;
			}
		}
	}
}

typedef vector<char> charArr;
typedef vector<vector<char>> charMatrix;

void outputCross(char** matrix, int& top, int& left, int& right, int& bottom, ofstream& out, charMatrix& cm)
{
	for (int i = top + 1; i < bottom; i++)
	{
		charArr ca;
		for (int j = left + 1; j < right; j++)
		{
			out << matrix[i][j];
			if (dev) cout << matrix[i][j];
			ca.push_back(matrix[i][j]);
		}
		cm.push_back(ca);
		out << endl;
		if (dev)
			cout << endl;
	}
}

charMatrix makeAnswer(string a, string b, string c, string d, ofstream& out)
{
	charMatrix cm;

	form(a, b, c, d);

	if (minSize == -1)
	{
		out << "No";
	}
	else
	{
		int top, left, right, bottom;
		char** matrix = createCrossword(cases, a, b, c, d);
		findCutCoord(matrix, top, left, right, bottom);
		/*if (dev) cout << top << " "
			 << left << " "
			 << right << " "
			 << bottom << endl;*/
		outputCross(matrix, top, left, right, bottom, out, cm);
	}
	out.close();
	return cm;
}

string join(const vector<char>& vec)
{
	string s;
	for (int i = 0; i < vec.size(); i++)
		s += vec[i];
	return s;
}

void makeTests() {
	ofstream out("tmp.txt");
	charMatrix cm;

	cm = makeAnswer("STAMPING", "FORMULA", "STOP", "SPELING", out);
	assert(cm.size() == 7);
	assert(cm[0].size() == 9);
	assert(join(cm[1]) == "*STAMPING");
	assert(join(cm[2]) == "*T***E***");
	assert(join(cm[3]) == "FORMULA**");
	assert(join(cm[4]) == "*P***I***");

	cm = makeAnswer("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", out);
	assert(cm.size() == 27);
	assert(cm[0].size() == 27);
	assert(join(cm[0]) == "**A************************");
	assert(join(cm[1]) == "*ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	assert(join(cm[2]) == "ABCDEFGHIJKLMNOPQRSTUVWXYZ*");
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	string a, b, c, d;

	in >> a;
	in >> b;
	in >> c;
	in >> d;

	assert(calcSize(0, 1, 3, 3) == 4);
	assert(calcSize(0, 1, 2, 3) == 3);
	assert(calcSize(1, 0, 3, 3) == 4);
	assert(calcSize(1, 0, 3, 2) == 3);
	assert(calcSize(1, 2, 3, 4) == 4);

	if (dev)
	{
		makeTests();
	}
	else
	{
		makeAnswer(a, b, c, d, out);
	}
	in.close();
}