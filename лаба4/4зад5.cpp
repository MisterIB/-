#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, vector<uint64_t> array) {
	int i = 0;
	for (uint64_t element : array) {
		if (i % 10 == 0) cout << "\n";
		cout << element << " ";
		i++;
	}
	return os;
}

uint64_t gcd(uint64_t c, uint64_t m) {//Нахождение НОД
	if (m == 0) {
		return c;
	}
	return gcd(m, c % m);
}

uint64_t calculateRandValue(uint64_t x, uint64_t M) {//Нахождение случайного числа
	return (x * x) % M;
}

uint64_t calculateX(uint64_t M) {//Нахождение x
	while (true) {
		uint64_t x = rand() % 10000;
		if (gcd(M, x) == 1) return x;
	}
}

void calculatePandQ(uint64_t& p, uint64_t& q) {//Нахождение p и q
	while (100) {
		p = rand() % 10000;
		q = rand() % 10000;
		if (p > 1000 and q > 1000) {
			if (p % 4 == 3 and q % 4 == 3) break;
		}
	}
}

void generatingNumbers(uint64_t M, vector<uint64_t>& array) {//Генерация случайных чисел
	uint64_t previousX = calculateX(M);
	for (int i = 0; i < 20; i++) {
		uint64_t xn = calculateRandValue(previousX, M);
		previousX = xn;
		array.push_back(xn);
	}
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	srand(time(0));
	vector<uint64_t> randNumbers;
	uint64_t p;
	uint64_t q;
	calculatePandQ(p, q);
	uint64_t M = p * q;
	cout << "p = " << p << "\n" << "q = " << q  << "\n"<< "M = "<< M << "\n" << "Случайные числа: ";
	generatingNumbers(M, randNumbers);
	cout << randNumbers;
}