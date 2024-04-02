#include "stdio.h"
#include "math.h"

float exponent(float x, int N) {//прямая сумма
	float res = 0, term = 1;
	for (int i = 1; i < N; i++) {
		res += term;
		term *= x / (float)i;
	}
	return res;
}
float exp_member(float x, int i) {
	return x / i;
}
float exp_end(float x, float (*sum)(float, float, float(*)(float, int), int))
{
	return sum(1, x, exp_member, 10);
}
float my_sin(float x, int N) {//прямая сумма
	float res = 0, term = x;
	for (int i = 1; i < N; i++) {
		if (i % 2 == 0) res -= term;
		else res += term;
		term *= x * x / (float)(2 * i * (2 * i + 1));
	}
	return res;
}
float sin_member(float x, int i) {
	return -x * x / (2 * i * (2 * i + 1));
}
float sin_end(float x, float (*sum)(float, float, float(*)(float, int), int))
{
	return sum(x, x, sin_member, 5);
}
float my_cos(float x, int N) {//прямая сумма
	float res = 0, term = 1;
	for (int i = 1; i < N; i++) {
		if (i % 2 == 0) res -= term;
		else res += term;
		term *= x * x / (float)((2 * i - 1) * 2 * i);
	}
	return res;
}
float cos_member(float x, int i) {
	return -x * x / (2 * i * (2 * i - 1));
}
float cos_end(float x, float (*sum)(float, float, float(*)(float, int), int))
{
	return sum(1, x, cos_member, 5);
}

float ln(float x, int N) {//прямая сумма
	x += 1;
	double result = 0.0;

	for (int k = 1; k <= N; k++) {
		result += pow(-1, k - 1) * pow(x - 1, k) / k;
	}

	return result;
}

float ln_member(float x, int i) {
	return -x * i / (i + 1);
}
float ln_end(float x, float (*sum)(float, float, float(*)(float, int), int))
{
	return sum(x, x, ln_member, 10);
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

float par_sum(float a0, float x, float(*funk)(float, int), int N)
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
	int N = 15, i;
	int a;
	printf("\nplease write x\n");
	scanf_s("%f", &x);
	float ln_direct, ln_inverse, ln_par, sin_direct, sin_inverse, sin_par, cos_direct, cos_inverse, cos_par, exponent_direct, exponent_inverse, exponent_par;
	ln_direct = ln(x, N);
	ln_inverse = ln_end(x, inverse_sum);
	ln_par = ln_end(x, par_sum);
	sin_direct = my_sin(x, N);
	sin_inverse = sin_end(x, inverse_sum);
	sin_par = sin_end(x, par_sum);
	cos_direct = my_cos(x, N);
	cos_inverse = cos_end(x, inverse_sum);
	cos_par = cos_end(x, par_sum);
	exponent_direct = exponent(x, N);
	exponent_inverse = exp_end(x, inverse_sum);
	exponent_par = exp_end(x, par_sum);
	printf("\nsin output\n");
	printf("%f\n %f\n %f\n", sin_direct, sin_inverse, sin_par);
	printf("\ncos output\n");
	printf("%f\n %f\n %f\n", cos_direct, cos_inverse, cos_par);
	printf("\nexponent output\n");
	printf("%f\n %f\n %f\n", exponent_direct, exponent_inverse, exponent_par);
	printf("\nln output\n");
	printf("%f\n %f\n %f\n", ln_direct, ln_inverse, ln_par);

	return 0;
}