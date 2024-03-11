#include "TaylorSeries.h"
#include "iostream"
#include "cmath"
float sin_next(float x, int i)
{
	return -x * x / (float)(4 * i * i + 2 * i);
}

float cos_next(float x, int i)
{
	return x * x / (float)(2 * i - 4 * i * i);
}

float exp_next(float x, int i)
{
	return x / (float)i;
}

float log_next(float x, int i)
{
	return x * x * float(2 * i - 1) / float(2 * i + 1);
}

void prepSin(float& x, int& n)
{
	float tmp;
	float const pi = 3.14159265f;
	n = 0;
	do
	{
		tmp = x * 2.0f / pi;
		n += (int)tmp;
		if (x < 0.0f)
			n--;
		x -= (float)n * pi / 2.0f;
		n = ((n % 4) + 4) % 4;
	} while (fabs(x) > (pi / 2.0f));
	if (n % 2 == 1)
	{
		x -= pi / 2.0f;
		n += 1;
	}
	if (n == 2)
		x = -x;
	return;
}

void prepCos(float& x, int& n)
{
	float tmp;
	float const pi = 3.14159265f;
	n = 0;
	do
	{
		tmp = x * 2.0f / pi;
		n += (int)tmp;
		if (x < 0.0f)
			n--;
		x -= (float)n * pi / 2.0f;
		n = ((n % 4) + 4) % 4;
	} while (fabs(x) > (pi / 2.0f));
	if (n % 2 == 1)
	{
		x -= pi / 2.0f;
		n += 1;
	}
	if (n == 2)
		n = -1;
	return;
}

void prepExp(float& x, int& p)
{
	float k = 1.0f;
	int tmp = 1, i;
	p = 0;
	if (x < 0.0f)
	{
		x = -x;
		k = -1.0f;
	}
	if (x > 2.0f)
	{
		while (x > 2.0f)
		{
			x /= 2.0f;
			p++;
		}
		for (i = 0; i < p; i++)
			tmp *= 2;
	}
	p = tmp;
	if (x < 1.0f)
		while (x < 1.0f)
		{
			x *= 2.0f;
			p--;
		}
	if (k == -1.0f)
		x = -x;
	return;
}

void prepLog(float& x, int& p)
{
	p = 0;
	if (x > 2.0f)
		while (x > 2.0f)
		{
			x /= 2.0f;
			p++;
		}
	if (x < 1.0f)
		while (x < 1.0f)
		{
			x *= 2.0f;
			p--;
		}
	return;
}

float directSum(float a, float const x, float(*next)(float, int))
{
	float res = a, const eps = 1e-6f;
	int i = 1;
	while (fabs(a) > eps)
	{
		a *= next(x, i++);
		res += a;
	}
	return res;
}

float extendedSum(float a, float const x, float(*next)(float, int))
{
	float res = a, tmp, const eps = 1e-6f;
	int i = 1;
	a *= next(x, i++);
	res += a;
	while (fabs(a) > eps)
	{
		tmp = (a *= next(x, i++));
		tmp += (a *= next(x, i++));
		res += tmp;
	}
	return res;
}

float reverseSum(float a, float const x, float(*next)(float, int))
{
	float res = 0, arr[20], const eps = 1e-6f;
	int i = 1, n = 20, tmp = n;
	arr[0] = a;
	while (fabs(a) > eps)
		arr[i++] = a *= next(x, i);
	for (i = i - 1; i >= 0; i--)
		res += arr[i];
	return res;
}

float t_sin(float const x, float(*SumFunc)(float, float const, float(*)(float, int)))
{
	int n;
	float y = x;
	prepSin(y, n);
	return SumFunc(y, y, sin_next);
}

float t_cos(float const x, float(*SumFunc)(float, float const, float(*)(float, int)))
{
	int n;
	float y = x;
	prepCos(y, n);
	return SumFunc(1.0f, y, cos_next) * (float)n;
}

float t_exp(float const x, float(*SumFunc)(float, float const, float(*)(float, int)))
{
	int p, i;
	float prod = 1.0f, y = x, term, k = 1.0f;
	if (x < 0)
		k = -1.0f;
	prepExp(y, p);
	term = SumFunc(1, y, exp_next);
	for (i = 0; i < p; i++)
		prod *= term;
	return  prod;
}

float t_log(float const x, float(*SumFunc)(float, float const, float(*)(float, int)))
{
	int p;
	float y = x;
	if (x <= 0)
	{
		std::cout << "Invalid loagarithm argument" << std::endl;
		exit(2);
	}
	prepLog(y, p);
	y = 1.0f - 2.0f / (y + 1.0f);
	return 2.0f * (p * SumFunc(1.0f / 3.0f, 1.0f / 3.0f, log_next) + SumFunc(y, y, log_next));
}