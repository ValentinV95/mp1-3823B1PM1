#include <iostream>
#include <cmath>
#include <locale.h>

float nextsin(float x, size_t i) {
	return -(x * x) / (2*i * (2*i + 1.0f));
}
float nextcos(float x, size_t i) {
	return -(x * x) / (2*i * (2*i - 1.0f));
}
float nextexp(float x, size_t i) {
	return x / i;
}
float nextlog(float x, size_t i) {
	return -(x * i) / (i + 1.0f);
}

void print(float s, float reference) {
	std::cout << "Значение - " << s << '\n';
	std::cout << "Погрешность - " << abs(s - reference) << '\n';
}

void infelicity(float reference, float* values, int n) {
	float s = 0;
	for (int i = 0; i < n; i++) 
		s += values[i];
	printf("Прямое суммирование\n");
	print(s, reference);
	s = 0;
	for (int i = n - 1; i >= 0; i--) 
		s += values[i];
	printf("Обратное суммирование\n");
	print(s, reference);
	s = 0;
	for (int i = 0; i + 1 < n; i+=2) 
		s += (values[i] + values[i + 1]);
	if (n % 2)
		s += values[n - 1];
	printf("Прямое попарное суммирование\n");
	print(s, reference);
	s = 0;
	for (int i = n-1; i-1 >= 0; i -= 2) 
		s += (values[i] + values[i - 1]);
	if (n % 2)
		s += values[0];
	printf("Обратное попарное суммирование\n");
	print(s, reference);
} 

void summ(float x, int n, float* values, float (*next)(float, size_t)) {
	for (int i = 1; i < n; i++) 
		values[i] = values[i - 1] * next(x, i);
}

void exp_t(float x, int n, float (*next)(float, size_t), float* values) {
	float e = exp(x);
	values[0] = 1;
	summ(x, n, values, next);
	infelicity(e, values, n);
}

void log_t(float x, int n, float (*next)(float, size_t), float* values) {
	float lg = log(x+1);
	values[0] = x;
	summ(x, n, values, next);
	infelicity(lg, values, n);
}

void sin_t(float x, int n, float (*next)(float, size_t), float* values) {
	float sinx = sin(x);
	values[0] = x;
	summ(x, n, values, next);
	infelicity(sinx, values, n);
}

void cos_t(float x, int n, float (*next)(float, size_t), float* values) {
	float cosx = cos(x);
	values[0] = 1;
	summ(x, n, values, next);
	infelicity(cosx, values, n);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	std::string func; int n; float x;
	std::cout << "Введите название фукнции (exp, log, cos, sin):\n";
	std::cin >> func;
	std::cout << "Число членов последовательности:  \n";
	std::cin >> n;
	std::cout << "Аргумент:\n";
	std::cin >> x;
	float* values = (float*)malloc(n * sizeof(float));
	if (func == "exp")
		exp_t(x, n, nextexp, values);
	else if (func == "log")
		log_t(x-1, n, nextlog, values);
	else if (func == "cos")
		cos_t(x, n, nextcos, values);
	else if (func == "sin")
		sin_t(x, n, nextsin, values);
	else
		std::cout << "некорректный ввод";
}
