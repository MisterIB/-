#include <iostream>
#include <vector>

using namespace std;

void scoringPoints(int& pointFirstAlgorithm, int& pointSecondAlgorithm, vector<bool> firstAlgorithm, vector<bool> secondAlgorithm) {
	for (size_t i = 0; i < firstAlgorithm.size(); i++) {//Подсчет очков
		if (firstAlgorithm[i] == true and secondAlgorithm[i] == true) {
			pointFirstAlgorithm += 24;
			pointSecondAlgorithm += 24;
		}
		if (firstAlgorithm[i] == false and secondAlgorithm[i] == false) {
			pointFirstAlgorithm += 4;
			pointSecondAlgorithm += 4;
		}
		if (firstAlgorithm[i] == false and secondAlgorithm[i] == true) {
			pointFirstAlgorithm += 20;
		}
		if (firstAlgorithm[i] == true and secondAlgorithm[i] == false) {
			pointSecondAlgorithm += 20;
		}
	}
}

bool algoritmOne(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
	int count_enemy_false = 0;
	int count_enemy_true = 0;
	for (bool choices : enemy_choices) {
		if (choices) count_enemy_true += 1;
		else count_enemy_false += 1;
	}
	/*if (count_enemy_false > count_enemy_true) return false;
	if (count_enemy_false < count_enemy_true) return true;
	if (count_enemy_false == count_enemy_true) return true;*/
	if (round_number == 1) return true;
	if (enemy_choices[round_number - 2] == true) {
		if (count_enemy_false > count_enemy_true) return false;
		if (count_enemy_false < count_enemy_true) return true;
		if (count_enemy_false == count_enemy_true) return true;
	}
	if (enemy_choices[round_number - 2] == false) {
		if (count_enemy_false > count_enemy_true) return true;
		if (count_enemy_false < count_enemy_true) return false;
		if (count_enemy_false == count_enemy_true) return false;
	}
}

bool algorithmTwo(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
	int myPointAlgorithm = 0;
	int enemyPointAlgorithm = 0;
	scoringPoints(myPointAlgorithm, enemyPointAlgorithm, self_choices, enemy_choices);
	int count_enemy_false = 0;
	int count_enemy_true = 0;
	for (bool choices : enemy_choices) {
		if (choices) count_enemy_true += 1;
		else count_enemy_false += 1;
	}
	if (round_number < 75) {
		if (myPointAlgorithm < enemyPointAlgorithm) return true;
		if (myPointAlgorithm > enemyPointAlgorithm) return false;
		if (myPointAlgorithm == enemyPointAlgorithm) return true;
	}
	else {
		if (myPointAlgorithm < enemyPointAlgorithm) return false;
		if (myPointAlgorithm > enemyPointAlgorithm) return true;
		if (myPointAlgorithm == enemyPointAlgorithm) return false;
	}
}

bool algorithmThree(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
	if (round_number % 2 == 0) return true;
	if (round_number % 3 == 0) return false;
	if (round_number % 25 == 0) return false;
	if (round_number % 100 == 0) return true;
	return true;
}

int generateNumRounds() {
	srand(time(0));
	while (true) {
		int numberRounds = rand() % 201;
		if (numberRounds >= 100) {
			cout << "Колво раундов: " << numberRounds << endl;
			return numberRounds;
		}
	}
}

void battleOne(vector<bool>& firstAlgorithm, vector<bool>& secondAlgorithm) {
	int numberRounds = generateNumRounds();

	for (int i = 1; i < numberRounds; i++) {//Изменить колво раундов. Обозначить какой то переменной
		firstAlgorithm.push_back(algoritmOne(i, firstAlgorithm, secondAlgorithm));
		secondAlgorithm.push_back(algorithmTwo(i, secondAlgorithm, firstAlgorithm));
	}
}

void battleTwo(vector<bool>& firstAlgorithm, vector<bool>& secondAlgorithm) {
	int numberRounds = generateNumRounds();

	for (int i = 1; i < numberRounds; i++) {//Изменить колво раундов. Обозначить какой то переменной
		firstAlgorithm.push_back(algorithmThree(i, firstAlgorithm, secondAlgorithm));
		secondAlgorithm.push_back(algorithmTwo(i, secondAlgorithm, firstAlgorithm));
	}
}

void battleThree(vector<bool>& firstAlgorithm, vector<bool>& secondAlgorithm) {
	int numberRounds = generateNumRounds();

	for (int i = 1; i < numberRounds; i++) {//Изменить колво раундов. Обозначить какой то переменной
		firstAlgorithm.push_back(algorithmThree(i, firstAlgorithm, secondAlgorithm));
		secondAlgorithm.push_back(algoritmOne(i, secondAlgorithm, firstAlgorithm));
	}
}

void battleAlgorithms(pair<int, int> algorithms) {
	vector<bool> firstAlgorithm;
	vector<bool> secondAlgorithm;
	int pointFirstAlgorithm = 0;
	int pointSecondAlgorithm = 0;
	if ((algorithms.first == 1 and algorithms.second == 2) or (algorithms.first == 2 and algorithms.second == 1)) battleOne(firstAlgorithm, secondAlgorithm);
	if ((algorithms.first == 3 and algorithms.second == 2) or (algorithms.first == 2 and algorithms.second == 3)) battleTwo(firstAlgorithm, secondAlgorithm);
	if ((algorithms.first == 3 and algorithms.second == 1) or (algorithms.first == 1 and algorithms.second == 3)) battleThree(firstAlgorithm, secondAlgorithm);
	scoringPoints(pointFirstAlgorithm, pointSecondAlgorithm, firstAlgorithm, secondAlgorithm);
	cout << "Очки первого алгоритма: " << pointFirstAlgorithm << "\nОчки второго алгоритма: " << pointSecondAlgorithm;
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	pair<int, int> algorithms;
	cout << "Выберите 2 алгоритма" << endl;
	cin >> algorithms.first;
	cin >> algorithms.second;
	battleAlgorithms(algorithms);
}