#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double func(double x) {
	return 5 * sin(x) - x;
}

double kanonFunc(double x) {//Каноническое уравнение
	return 5 * sin(x);
}

double derivativeFunc(double x) {
	return 5 * cos(x) - 1;
}

void methodHalfDivision(vector<pair<double, double>> intervals, double E) {//Метод половинного деления
	cout << "Метод половинного деления" << endl;
	for (pair<double, double> interval : intervals) {
		int N = 0;
		cout << "N" << "\t" << "an" << "\t\t" << "bn" << "\t\t" << "bn - an" << endl;
		while (true) {
			double c = (interval.first + interval.second) / 2;
			if ((func(interval.first) < 0 and func(c) > 0) or (func(interval.first) > 0 and func(c) < 0)) {
				interval.second = c;
			}
			if ((func(interval.second) < 0 and func(c) > 0) or (func(interval.second) > 0 and func(c) < 0)) {
				interval.first = c;
			}
			cout << ++N << "\t" << interval.first << "\t" << interval.second << "\t" << interval.second - interval.first << endl;
			if (abs(interval.second - interval.first) < E) { 
				cout << "Корень: " << (interval.first + interval.second) / 2 << " " << endl;
				break;
			}
		}
	}
}

void newtonsMethod(vector<pair<double, double>> intervals, double E) {//Мето Ньютона
	cout << "Метод Ньютона" << endl;
	for (pair<double, double> interval : intervals) {
		int N = 0;
		cout << "N" << "\t" << "an" << "\t\t" << "bn" << "\t\t" << "bn - an" << endl;
		while (true) {
			interval.second = interval.first - func(interval.first) / derivativeFunc(interval.first);
			if (abs(interval.second - interval.first) < E) {
				cout << "Корень: " << interval.second << endl;
				break;
			}
			cout << ++N << "\t" << interval.first << "\t" << interval.second << "\t" << interval.second - interval.first << endl;
			interval.first = interval.second;
		}
	}
}

void newtonsModMethod(vector<pair<double, double>> intervals, double E) {//Модифицированный метод Ньютона
	cout << "Модифицированный метод Ньютона" << endl;
	for (pair<double, double> interval : intervals) {
		int N = 0;
		double x0 = interval.first;
		cout << "N" << "\t" << "an" << "\t\t" << "bn" << "\t\t" << "bn - an" << endl;
		while (true) {
			interval.second = interval.first - func(interval.first) / derivativeFunc(x0);
			if (abs(interval.second - interval.first) < E) {
				cout << "Корень: " << interval.second << endl;
				break;
			}
			cout << ++N << "\t" << interval.first << "\t" << interval.second << "\t" << interval.second - interval.first << endl;
			interval.first = interval.second;
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	cout << fixed << setprecision(6);
	vector<pair<double, double>> intervals{ { -3, -2}, {0.5, -1}, {2, 3} };
	double E = 0.0001;
	methodHalfDivision(intervals, E);
	cout << "-----------------" << endl;
	newtonsMethod(intervals, E);
	cout << "-----------------" << endl;
	newtonsModMethod(intervals, E);
}