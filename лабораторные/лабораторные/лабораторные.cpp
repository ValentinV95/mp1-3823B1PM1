#include "stdio.h"
#include "math.h"

float exponent(float x, int N) {//прямая сумма
	float res = 0, term = 1;
	for (int i = 1; i < N; i++) {
		res += term;
		term *= x / (float)i;
		printf("%f", res);
	}
	return res;
}
float exp_member(float x, int i) {
	return x / i;
}
float my_sin(float x, int N) {//прямая сумма
	float res = 0, term = x;
	for (int i = 1; i < N; i++) {
		if (i % 2 == 0) res -= term;
		else res += term;
		term *= x * x / (float)(2 * i * (2 * i + 1));
		printf("%f", res);
	}
	return res;
}
float sin_member(float x, int i) {
	return -x * x / (2 * i * (2 * i + 1));
}
float my_cos(float x, int N) {//прямая сумма
	float res = 0, term = 1;
	for (int i = 1; i < N; i++) {
		if (i % 2 == 0) res -= term;
		else res += term;
		term *= x * x / (float)((2 * i - 1) * 2 * i);
		printf("%f", res);
	}
	return res;
}
float cos_member(float x, int i) {
	return -x * x / (2 * i * (2 * i - 1));
}
float ln(float x, int N) {//прямая сумма
	float res = 0, term = x;
	for (int i = 1; i < N; ++i) {
		res += term;
		if (i == 0) term *= (-1) * x / (float)(i + 1);
		else term *= (-1) * x * (float)(i) / (float)(i + 1);
		printf("%f", res);
	}
	return res;
}
float ln_member(float x, int i) {
	return -x * i / (i + 1);
}
float inverse_sum(float a0, float x, float(*funk)(float, int), int N)
{
	float res, an, b;
	an = a0;
	res = 0;
	for (int i = 1; i <= N; i++)
	{
		b = funk(x, i);
		if (b == 0)
		{
			N = i - 1;
			break;
		}
		an *= b;
	}
	for (int i = N; i >= 1; i--)
	{
		res += an;
		an /= funk(x, i);
	}
	return res + a0;
}

float parn_sum(float a0, float x, float(*funk)(float, int), int N)
{
	float res, a1, a2;
	res = a1 = a0;
	for (int i = 1; i <= N; i++)
	{
		a1 *= funk(x, i);
		a2 = a1;
		if (i + 1 <= N)
		{
			a1 *= funk(x, ++i);
			a2 += a1;
		}
		res += a2;
	}
	return res;
}
int main() {
	float x;
	int N;
	return 0;
}