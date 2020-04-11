/*
11.1. Треугольник и точка (5)
	В декартовой системе координат на плоскости заданы координаты вершин треугольника и 
еще одной точки. Определить, принадлежит ли эта точка треугольнику.
	Ввод из файла INPUT.TXT. В четырех строках находятся пары чисел - координаты точек. 
Числа в первых трех строках - это координаты вершин треугольника, в четвертой строке - 
координаты тестируемой точки.
	Вывод в файл OUTPUT.TXT. Вывести In, если точка находится внутри треугольника, или 
Out - если снаружи.
	Ограничения: координаты вершин - целые числа, для любой точки выполняются следующие 
условия: -10^9 ≤ x, y ≤ 10^9.
Примеры
	Ввод 1    Ввод 2    Ввод 3    Ввод 4
	0 0       0 0       0 0       0 0
	100 0     100 0     100 0     100 0
	0 100     0 100     0 100     0 100
	100 100   10 10     50 50     0 0
	Вывод 1   Вывод 2   Вывод 3   Вывод 4
	Out       In        In        In
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
#include <map>

using namespace std;

typedef double num;

struct coord
{
	num x;
	num y;
};

coord read_coord(ifstream& in) {
	coord c;
	in >> c.x;
	in >> c.y;
	return c;
}

num square(coord a, coord b, coord c) {
	return 0.5 * abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

num check(coord a, coord b, coord p) {
	return p.x * (b.y - a.y) + p.y * (a.x - b.x) + a.y * b.x - a.x * b.y;
}

bool solve(coord a, coord b, coord c, coord p) {
	bool c1 = check(a, b, p);
	bool c2 = check(b, c, p);
	bool c3 = check(c, a, p);
	cout << c1 << " ";
	cout << c2 << " ";
	cout << c3 << " ";
	return c1 >= 0 && c2 >= 0 && c3 >= 0 || c1 <= 0 && c2 <= 0 && c3 <= 0;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	coord a = read_coord(in);
	coord b = read_coord(in);
	coord c = read_coord(in);

	coord p = read_coord(in);

	if (solve(a, b, c, p)) {
		out << "In";
		cout << "In";
	}
	else {
		out << "Out";
		cout << "Out";
	}

	in.close();
	out.close();
}