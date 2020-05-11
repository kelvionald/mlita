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

const bool dev = false;

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

void prt(pairs p, int pp)
{
	if (dev)
		cout << pp << "'\n";
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

inline bool checkExists2(pair_& p1, pair_& p3, pair_& p2, pair_& p4)
{
	return p3.vi - p1.vi == p4.vi - p2.vi && p2.hi - p1.hi == p4.hi - p3.hi;
}

inline bool checkExists(pair_& p1, pair_& p3, pair_& p2, pair_& p4)
{
	return p3.hi - p1.hi == p4.hi - p2.hi && p2.vi - p1.vi == p4.vi - p3.vi;
	//&p3.hi - p1.hi != 0 && p2.vi - p1.vi != 0;
}

/*
  c d
 aaaaa
  c d
bbbbb
  c d
*/

inline int getSize(
	pair_& p1, pair_& p3, pair_& p2, pair_& p4,
	string& a, string& b, string& c, string& d)
{
	int width = calcSize(p1.hi, p2.hi, a.size(), b.size());
	int height = calcSize(p1.vi, p3.vi, c.size(), d.size());
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

	prt(ac, 1);
	prt(bc, 2);
	prt(ad, 3);
	prt(bd, 4);

	for (int i = 0; i < ac.size(); i++)
	{
		pair_ p1 = ac[i];
		for (int j = 0; j < ad.size(); j++)
		{
			pair_ p3 = ad[j];
			if (!(p1.hi < p3.hi))
				continue;

			for (int k = 0; k < bc.size(); k++)
			{
				pair_ p2 = bc[k];
				//cout << "__" << !(p1.hi < p2.hi) << p1.hi << p2.hi << endl;
				if (!(p1.vi < p2.vi))
					continue;

				for (int m = 0; m < bd.size(); m++)
				{
					pair_ p4 = bd[m];
					if (!(p3.vi < p4.vi) || !(p2.hi < p4.hi))
						continue;

					if (!checkExists(p1, p3, p2, p4)) 
						continue;

					int size = getSize(p1, p3, p2, p4, a, b, c, d);
					if (minSize == -1 || minSize > size)
					{
						minSize = size;
						cases = {
							p1,
							p3,
							p2,
							p4
						};
					}

					if (dev && "ABCDEFGHIJKLMNOPQRSTUVWXYZ" != a)
					{

						cout << "*" << endl;
						cout << p1.vi << " "
							 << p3.vi << " "
							 << p1.ch << " "
							 << p3.ch << " "

							 << p1.hi << " "
							 << p2.hi << " "
							 << p1.ch << " "
							 << p2.ch << " "

							 << p3.hi << " "
							 << p4.hi << " "
							 << p3.ch << " "
							 << p4.ch << " "

							 << p2.hi << " "
							 << p4.hi << " "
							 << p2.ch << " "
							 << p4.ch << " "

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

	cm = makeAnswer("FMPULA", "STAPE", "LUFAS", "AMPER", out);
	cout << cm.size();
	assert(cm.size() == 5);
	assert(cm[0].size() == 8);
	assert(join(cm[0]) == "**L*A***");
	assert(join(cm[1]) == "**U*M***");
	assert(join(cm[2]) == "**FMPULA");
	assert(join(cm[3]) == "STAPE***");

	cm = makeAnswer("SUP", "LIS", "SID", "US", out);
	cout << cm.size();
	assert(cm.size() == 3);
	assert(cm[0].size() == 4);
	assert(join(cm[0]) == "*SUP");
	assert(join(cm[1]) == "LIS*");
	assert(join(cm[2]) == "*D**");

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