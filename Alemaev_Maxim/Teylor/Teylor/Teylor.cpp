#include <iostream>
#include <cmath>
#include <locale.h>

float nextsin(float x, size_t i) {
	return -(x * x) / (2 * i * (2 * i + 1.0f));
}
float nextcos(float x, size_t i) {
	return -(x * x) / (2 * i * (2 * i - 1.0f));
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
	for (int i = 0; i + 1 < n; i += 2)
		s += (values[i] + values[i + 1]);
	if (n % 2)
		s += values[n - 1];
	printf("Прямое попарное суммирование\n");
	print(s, reference);
	s = 0;
	for (int i = n - 1; i - 1 >= 0; i -= 2)
		s += (values[i] + values[i - 1]);
	if (n % 2)
		s += values[0];
	printf("Обратное попарное суммирование\n");
	print(s, reference);
}

void taylor(float x, int n, float (*next)(float, size_t), float* values, float x0, float ref) {
	values[0] = x0;
	for (int i = 1; i < n; i++)
		values[i] = values[i - 1] * next(x, i);
	infelicity(ref, values, n);
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
	if (func == "exp") {
		float ref = exp(x);
		taylor(x, n, nextexp, values, 1, ref);
	}
	else if (func == "log") {
		float ref = log(x);
		taylor(x - 1, n, nextlog, values, x, ref);
	}
	else if (func == "cos") {
		float ref = cos(x);
		taylor(x, n, nextcos, values, 1, ref);
	}
	else if (func == "sin") {
		float ref = sin(x);
		taylor(x, n, nextsin, values, x, ref);
	}
	else
		std::cout << "некорректный ввод";
}
