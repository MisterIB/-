#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, vector<T> vec) {
	for (T element : vec) {
		cout << element << " ";
	}
	return os;
}

void initializingArray(vector<int>& array, int size, discard_block_engine<ranlux24_base, 223, 23> generator) {
	for (int i = 0; i < size; i++) {
		array.push_back(generator() % 100);
	}
}

int calculatingMin(vector<int> array) {
	int minElement = 1000;
	for (int element : array) {
		if (element < minElement) minElement = element;
	}
	return minElement;
}

int calculatingMax(vector<int> array) {
	int maxElement = 0;
	for (int element : array) {
		if (element > maxElement) maxElement = element;
	}
	return maxElement;
}

int arithmeticMean(vector<int> array, int size) {
	int sum = 0;
	for (int element: array) {
		sum += element;
	}
	return sum / size;
}

int arithmeticMeanSquare(vector<int> array, int size) {
	int sum = 0;
	for (int element : array) {
		sum += pow(element, 2);
	}
	return sum / size;
}

int standardDeviation(vector<int> array, int size) {
	return sqrt(arithmeticMeanSquare(array, size) - arithmeticMean(array, size));
}

double normalCDF(double value)
{
	return 0.5 * erfc(-value * sqrt(0.5));
}

vector<double> calculatingProbability(int widthIntervals, int amountIntervals, vector<int> array, int size,vector<pair<double, double>> Intervals) {
	vector<double> probability;
	Intervals[0].first = 1;
	for (int i = 0; i <= amountIntervals; i++) {
		double P;
		if (i == 0) {
			P = normalCDF((Intervals[i].second - arithmeticMean(array, size)) / standardDeviation(array, size));	
		}
		else if (i == amountIntervals) {
			P = normalCDF(1 - normalCDF((Intervals[i].first - arithmeticMean(array, size)) / standardDeviation(array, size)));
		}
		else {
			P = normalCDF((Intervals[i].second - arithmeticMean(array, size)) / standardDeviation(array, size)) - normalCDF((Intervals[i].first - arithmeticMean(array, size)) / standardDeviation(array, size));
		}
		probability.push_back(P * size);
	}
	return probability;
}

double calculationX2(vector<double> Vn, vector<double> Vexp, int amountIntervals) {
	double X2 = 0;
	for (int i = 0; i <= amountIntervals; i++) {
		X2 += pow(Vn[i] - Vexp[i], 2) / Vexp[i];
	}
	return X2;
}

double calculatingExpected(int degreeFreedom) {
	if (degreeFreedom == 5) {
		return 15.1;
	}
	if (degreeFreedom == 4) {
		return 13.3;
	}
	if (degreeFreedom == 6) {
		return 16.8;
	}
	if (degreeFreedom == 9) {
		return 21.7;
	}
}

void hypothesisTesting(double X2, double expect) {
	if (X2 > expect) {
		cout << "Гипотеза отвергается" << endl;
	}
	else {
		cout << "Гипотеза не отвергается" << endl;
	}
}

void distributionIntervals(int size, vector<int> array) {
	int amountIntervals = 1 + log2(size);//Количество интервалов разбиения. Формула Стёрджесса
	int widthIntervals = (calculatingMax(array) - calculatingMin(array)) / amountIntervals;//Ширина каждого интервала
	vector<double> Vn;
	vector<pair<double, double>> Intervals;
	Intervals.push_back({ 0, widthIntervals });
	for (int i = 0; i <= amountIntervals; i++) {
		double frequency = 0;
		for (int element : array) {
			if (element > Intervals[i].first and element <= Intervals[i].second) frequency++;
		}
		if (frequency < 5) {
			Vn[i - 1] += frequency;
			Intervals[i - 1].second += widthIntervals;
			amountIntervals--;
		}
		else Vn.push_back(frequency);
		Intervals.push_back({ Intervals[i].second, Intervals[i].second + widthIntervals });
	}
	cout << "Частота Vn: " << Vn << endl;
	vector<double> probability = calculatingProbability(widthIntervals, amountIntervals, array, size, Intervals);
	cout << "Частота Vexp: " << probability << endl;
	cout << "Степень свободы: " << amountIntervals - 1 << endl;
	double X2 = calculationX2(Vn, probability, amountIntervals);
	double expect = calculatingExpected(amountIntervals - 1);
	cout << "Ожидаемое: " << expect << endl;
	cout << "Реальное: " << X2 << endl;
	hypothesisTesting(X2, expect);
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	vector<int> arr50;
	vector<int> arr100;
	vector<int> arr1000;
	discard_block_engine<ranlux24_base, 223, 23> generator (time(0));
	cout << "Массив 1" << "\nКоличество элементов: 50" << endl;
	initializingArray(arr50, 50, generator);
	distributionIntervals(50, arr50);
	cout << "Массив 2" << "\nКоличество элементов: 100" << endl;
	initializingArray(arr100, 100, generator);
	distributionIntervals(100, arr100);
	cout << "Массив 3" << "\nКоличество элементов: 1000" << endl;
	initializingArray(arr1000, 1000, generator);
	distributionIntervals(1000, arr1000);
}
