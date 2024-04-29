#include <iostream>
#include <random>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, vector<T> arr) {
	for (T element : arr) {
		cout << element << " ";
	}
	return os;
}

void initializingArray(vector<int>& arr2, vector<int>& arr1, discard_block_engine<ranlux24_base, 223, 23> generator, int n) {
	for (; arr1.size() != n; ) {
		int num = generator() % 30;
		if (num >= 10) {
			arr1.push_back(num);
		}
	}
	for (; arr2.size() != 5; ) {
		int num = generator() % 30;
		if (num >= 10) {
			arr2.push_back(num);
		}
	}
}

void initializingArray(vector<char>& arraySymbols, discard_block_engine<ranlux24_base, 223, 23> generator) {
	for (; arraySymbols.size() != 5; ) {
		char num = generator() % 127;
		if (num >= 33) {
			arraySymbols.push_back(num);
		}
	}
}

void initializingArray(vector<int>& arr4, discard_block_engine<ranlux24_base, 223, 23> generator) {
	for (; arr4.size() != 20; ) {
		int num = generator() % 9000;
		if (num >= 1000) {
			arr4.push_back(num);
		}
	}
}

void outputEvenNum(vector<int> arr1) {
	int elementIndex = 0;
	int countEvenElements = 0;
	cout << "Четные числа на нечетных местах: ";
	for (int element : arr1) {
		if (elementIndex % 2 != 0 and element % 2 == 0) {
			cout << element << " ";
			countEvenElements++;
		}
		elementIndex++;
	}
	cout << "\n" << "Количество четных чисел на нечетных местах: " << countEvenElements << endl;
}

void comparingArrays(vector<int> arr1, vector<int> arr2) {
	int countRepeatNum = 0;
	for (int elementArr2 : arr2) {
		int numRepetitions = 0;
		for (int elementArr1 : arr1) {
			if (elementArr1 == elementArr2) {
				numRepetitions++;
			}
		}
		if (numRepetitions) {
			cout << "Число: " << elementArr2 << " повторяется " << numRepetitions << " раз" << endl;
			countRepeatNum++;
		}
	}
	if (countRepeatNum == 0) cout << "В массивах нет одинаковых элементов" << endl;
}

vector<char> modificationArray(vector<char> arraySymbols, int n) {
	int firstElement = arraySymbols[0];
	for (int i = 0; i < n - 1; i++) arraySymbols[i] = arraySymbols[i + 1];
	arraySymbols[n - 1] = firstElement;
	return arraySymbols;
}

int calculatingAmount(vector<int> arr4) {
	int sum = 0;
	for (int element : arr4) {
		sum += element;
	}
	return sum;
}

void sort(vector<int>& figures, int n) {
	for (int i = 0; i < n - 1; i++) { 
		int k = i;
		for (int j = i + 1; j < n; j++) if (figures[j] < figures[k]) k = j;
		int c = figures[k]; 
		figures[k] = figures[i]; 
		figures[i] = c;
	}
}

void swapPlaces(vector<int>& arr4) {
	for (int& element : arr4) {
		vector<int> figures;
		while (element > 0) {
			figures.push_back(element % 10);
			element /= 10;
		}
		sort(figures, 4);
		element = 0;
		for (int figure : figures) {
			element = element * 10 + figure;
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	discard_block_engine<ranlux24_base, 223, 23> generator (time(0));
	int n;
	cout << "Введите n" << endl;
	cin >> n;
	vector<int> arr1; vector<int> arr2; vector<char> arr3; vector<int> arr4;
	initializingArray(arr2, arr1, generator, n);
	initializingArray(arr3, generator);
	initializingArray(arr4, generator);
	cout << "Массив arr1: " << arr1 << "\nМассив arr2: " << arr2 << endl;
	outputEvenNum(arr1);
	comparingArrays(arr1, arr2);
	cout << "Массив случайных символов: " << arr3 << endl;
	cout << "Массив случайных символов после модификации: " << modificationArray(arr3, 5) << endl;
	cout << "Массив arr4: " << arr4 << endl;
	cout << "Сумма элементов массива arr4: " << calculatingAmount(arr4) << endl;
	swapPlaces(arr4);
	cout << "Массив arr4 с отсортированными цифрами в елементов: " << arr4 << endl;
	sort(arr4, 20);
	cout << "Отсортированный массив arr4: " << arr4 << endl;
	cout << "Сумма элементов массива arr4 после модификаций: " << calculatingAmount(arr4) << endl;
}