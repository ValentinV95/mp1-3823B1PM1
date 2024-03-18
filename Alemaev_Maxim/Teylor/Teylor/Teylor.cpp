#include <iostream>
#include <cmath>
#include <locale.h>

using namespace std;

float nextsin(float x, size_t i) {
	return -(x * x) / (i*(i-1.0f));
}
float nextcos(float x, size_t i) {
	return -(x * x) / (i * (i - 1.0f));
}
float nextexp(float x, size_t i) {
	return x / i;
}
float nextlog(float x, size_t i) {
	return -(x * i) / (i + 1.0f);
}

void infelicity(float reference, float* values, int n) {
	float s = 0;
	for (int i = 0; i < n; i++) 
		s += values[i];
	printf("Прямое суммирование\n");
	cout << "Значение - " << s << endl;
	cout << "Погрешность - " << abs(s - reference) << endl << endl;
	s = 0;
	for (int i = n - 1; i >= 0; i--) 
		s += values[i];
	printf("Обратное суммирование\n");
	cout << "Значение - " << s << endl;
	cout << "Погрешность - " << abs(s - reference) << endl << endl;
	s = 0;
	for (int i = 0; i + 1 < n; i+=2) 
		s += (values[i] + values[i + 1]);
	if (n % 2)
		s += values[n - 1];
	printf("Прямое попарное суммирование\n");
	cout << "Значение - " << s << endl;
	cout << "Погрешность - " << abs(s - reference) << endl << endl;
	s = 0;
	for (int i = n-1; i-1 >= 0; i -= 2) {
		s += (values[i] + values[i - 1]);
	}
	if (n % 2)
		s += values[0];
	printf("Обратное попарное суммирование\n");
	cout << "Значение - " << s << endl;
	cout << "Погрешность - " << abs(s - reference) << endl << endl;
} 

void exp_t(float x, int n, float (*next)(float, size_t)) {
	float e = exp(x);
	float* values = (float*)malloc(n * sizeof(float));
	values[0] = 1;
	for (int i = 1; i < n; i++) {
		values[i] = values[i-1] * next(x, i);
	}
	infelicity(e, values, n);
	free(values);
}

void log_t(float x, int n, float (*next)(float, size_t)) {
	x--;
	float lg = log1p(x+1);
	float* values = (float*)malloc(n * sizeof(float));
	values[0] = x;
	for (int i = 1; i < n; i++) 
		values[i] = values[i-1] * next(x,i);
	infelicity(lg, values, n);
	free(values);
}

void sin_t(float x, int n, float (*next)(float, size_t)) {
	float sinx = sin(x);
	float* values = (float*)malloc(n * sizeof(float));
	for (int i = 0; i < n; i++)
		values[i] = 0;
	values[0] = x;
	for (int i = 3; i < 2*n; i += 2) 
		values[i/2] = values[i/2-1] * next(x, i);
	infelicity(sinx, values, n);
	free(values);
}

void cos_t(float x, int n, float (*next)(float, size_t)) {
	float cosx = cos(x);
	float* values = (float*)malloc(n * sizeof(float));
	for (int i = 0; i < n; i++)
		values[i] = 0;
	values[0] = 1;
	int c = 1;
	for (int i = 2; i < 2*n; i += 2) {
		values[i/2] = values[i / 2 - 1] * next(x, i);
	}
	infelicity(cosx, values, n);
	free(values);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string func;
	cout << "Введите название фукнции (exp, log, cos, sin):\n";
	cin >> func;
	int n,x;
	cout << "Число членов последовательности:  \n";
	cin >> n;
	cout << "Аргумент:\n";
	cin >> x;
	if (func == "exp")
		exp_t(x, n, nextexp);
	else if (func == "log")
		log_t(x, n, nextlog);
	else if (func == "cos")
		cos_t(x, n, nextcos);
	else if (func == "sin")
		sin_t(x, n, nextsin);
	else
		cout << "Неправильный ввод данных\n"; 
}
