#include <stdio.h>
#include <iostream>
using namespace std;

float f_exp1(float x, int i) {
	return x / i;
}
float f_sin1(float x, int i) {
	return -(x * x) / (2 * i * (2 * i + 1.0f));
}

float f_cos1(float x, int i) {
	return -(x * x) / (2 * i * (2 * i - 1.0f));
}

float f_log1(float x, int i) {
	return -(x * i) / (i + 1.0f);
}


float sum1(float x0, float x, int n, float(*f)(float, int)) {
	float xi, res;
	xi = res = float(x0);
	for (int i = 1; i < n; i++) {
		xi *= f(x, i);
		res += xi;
	}
	return res;
}

float ln_pr(float x, int n, float(*f)(float, int)) {
	float res = 0, xi = x;
	for (int i = 1; i < n; ++i) {
		res += xi;
		if (i == 0) xi *= (-1) * x / (float)(i + 1);
		else xi *= f(x, i);
	}
	return res;
}

float sum2(float x0, float x, int n, float(*f)(float, int)) {
	float xi, res = 0, v;
	xi = float(x0);
	for (int i = 1; i <= n; i++) {
		v = f(x, i);
		if (v == 0) {
			n = i - 1;
			break;
		}
		xi *= v;
	}
	for (int i = n; i >= 1; i--) {

		res += xi;
		xi = xi / (f(x, i));
	}
	return res + float(x0);
}

float sum3(float x0, float x, int n, float(*f)(float, int)) {
	float xi, xn, res;
	xi = res = float(x0);
	for (int i = 1; i <= n; i = i + 2) {
		xi *= f(x, i);
		xn = xi;
		res += xi;
		if (i + 1 < n) {
			xn *= f(x, i + 1);
			xi = xn;
			res += xn;
		}
	}

	return res;
}



int main() {
	setlocale(LC_ALL, "ru");
	int n = 10;
	float x;
	char str;
	cout << "число членов последовательности = 15 " << endl;
	cout << "аргумент = " << endl;
	cin >> x;
	cout << "выберите функцию (exp - e, sin - s, cos - c, log - l (*en раскладка)) " << endl;
	cin >> str;


	float res;
	switch (str) {
	case 'e':
	{
		res = sum1(1, x, n, f_exp1);
		cout << "Прямая сумма = " << endl;
		printf("%.8f\n", res);
		res = sum2(1, x, n, f_exp1);
		cout << "Обратная сумма = " << endl;
		printf("%.8f\n", res);
		res = sum3(1, x, n, f_exp1);
		cout << "Парная сумма = " << endl;
		printf("%.8f\n", res);

		break;
	}
	case 'c':
	{
		res = sum1(1, x, n, f_cos1);
		cout << "Прямая сумма = " << endl;
		printf("%.8f\n", res);
		res = sum2(1, x, n, f_cos1);
		cout << "Обратная сумма = " << endl;
		printf("%.8f\n", res);
		res = sum3(1, x, n, f_cos1);
		cout << "Парная сумма = " << endl;
		printf("%.8f\n", res);

		break;
	}
	case 's':
	{
		res = sum1(x, x, n, f_sin1);
		cout << "Прямая сумма = " << endl;
		printf("%.8f\n", res);
		res = sum2(x, x, n, f_sin1);
		cout << "Обратная сумма = " << endl;
		printf("%.8f\n", res);
		res = sum3(x, x, n, f_sin1);
		cout << "Парная сумма = " << endl;
		printf("%.8f\n", res);
		break;
	}
	case 'l':
	{
		if (x > -1 && x <= 1) {
			res = ln_pr(x, n, f_log1);
			cout << "Прямая сумма = " << endl;
			printf("%.8f\n", res);
			res = sum2(x, x, n, f_log1);
			cout << "Обратная сумма = " << endl;
			printf("%.8f\n", res);
			res = sum3(x, x, n, f_log1);
			cout << "Парная сумма = " << endl;
			printf("%.8f\n", res);
		}
		else cout << "недопустимое значение аргумента";
		break;
	}
	default:
		cout << "неправильный ввод функции";
	}
}