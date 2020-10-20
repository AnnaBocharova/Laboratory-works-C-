#include<iostream>
#include<cmath>
#include <conio.h>
using namespace std;
//нахождение факториала через рекурсию
unsigned long long factorial(unsigned long long N) {
	if (N == 0)
		return 1;
	return N * factorial(N - 1);
}
//Разложение на сомножители 
//Вводиться N. Розкласти число на прості множники. Наприклад, користувач вводить 10,
//програма виводить{ 2, 8 }, { 3, 4 }, { 5, 2 }, { 7, 1 }.
void task1()
{
	cout << "Enter number: ";
	unsigned long long N;
	cin >> N;
	int a = 0;
	N = factorial(N);
	int k = 0;
	int array[1000] = {};
	for (int i = 2; i <= N; i++) {
		if (N % i == 0) {
			N = N / i;
			array[k] = i;
			k++;
			i--;
		}
	}

	int multiplier = 2;
	int counter = 0;
	for (int i = 0; i <= k; i++) {
		if (array[i] == multiplier) {
			counter++;
		}
		else {
			cout << "{" << multiplier << ", " << counter << "}" << ",  ";
			counter = 1;
			multiplier = array[i];
		}

	}

}
//Дано два натуральних числа a та b. Вивести на екран період дробу .
int task9(){
setlocale(LC_ALL, "rus");
int numenator, denumenator;
cout << "Enter numenator:";
cin >> numenator;
cout << "Enter denumenator:";
cin >> denumenator;

int b = denumenator;
//Любую обыкновенную дробь а/в, знаменатель которой имеет вид 2^x*5^y*B , будет давать переодическую дробь.
int ostatok, x = 0, y = 0, lengthPeriod = 1, per = 10, predperiod, B;
//Найдем В
//1. Выделим из знаменателя дроби наибольшую ступень 2
ostatok = denumenator % 2;
while (ostatok == 0) {
	b = b / 2;
	ostatok = b % 2;
	x++;
	if (x >= 1000) {
		cout << "Ошибка! Дробь непереодичная или период больше 1000" << endl;
		return 0;
	}
}
//2. Выделеним из знаменателя дроби наибольшую степень 5
ostatok = b % 5;
while (ostatok == 0) {
	b = b / 5;
	ostatok = b % 5;
	y++;
	if (y >= 1000) {
		cout << "Ошибка! Дробь непереодичная или период больше 1000" << endl;
		return 0;
	}
}
//Находим В
B = denumenator / pow(2, x) / pow(5, y);
// Длина периода будет равна показателю к котором принадлежит 10 mod В
//3.Вычислим длину периода дроби 
if (B == 1)
cout << "Ошибка! Дробь не переодичная!" << endl;
while (per != 1) {
	per = (10 * per) % B;
	lengthPeriod++;
}
if (x >= y)  predperiod = x;
else predperiod = y;

//4.Целая часть от деления 
cout << numenator / denumenator << ".";
numenator = numenator % denumenator;

//5. Находим препериод дроби
for (int i = 0; i < predperiod; i++) {
	cout << (numenator * 10) / denumenator;
	numenator = (numenator * 10) % denumenator;
}
//6. Период дроби
cout << "(";
for (int i = 0; i < lengthPeriod; i++) {
	cout << (numenator * 10) / denumenator;
	numenator = (numenator * 10) % denumenator;
}
cout << ")" << endl;
return 0;
}
int menu();

int main() {
	setlocale(LC_ALL, "Russian");
	int answer = menu();
	switch (answer)
	{
	case 0: task1(); break;
	case 1: task9(); break;
	
	}

	
	return 0;
}
int menu() {
	setlocale(LC_ALL, "Russian");
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0) cout << "-> Розложить факториал на простые сомножители " << endl;
		else  cout << "    Разложить факториал на простые сомнажетели" << endl;
		if (key == 1) cout << "-> Вычеслить период дроби" << endl;
		else  cout << "   Вычеслить период дроби" << endl;

		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
