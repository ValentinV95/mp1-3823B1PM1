#include "TaylorSeries.h"
#include "iostream"
float sin_next(float x, int i)
{
	return -x * x / (float)(2 * i * (2 * i + 1));
}

float cos_next(float x, int i)
{
	return x * x / (float)(2 * i * (1 - 2 * i));
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
	float const pi = 3.14159265f;
	int m = 0;
	float k = 1.0f;
	n = 0;
	if (x < 0.0f)
	{
		x = -x;
		k = -1.0f;
	}
	while (x >= 4.0f)
	{
		x /= 4.0f;
		m++;
	}
	while (m > 0)
	{
		n = (int) (x * 2.0f / pi);
		x -= (float)n * pi / 2.0f;
		x *= 4.0f;
		m--;
	}
	n = (int)(x * 2.0f / pi);
	x -= (float)n * pi / 2.0f;
	if (n % 2 == 1)
	{
		x -= pi / 2.0f;
		n += 1;
	}
	if (n == 2)
		x = -x;
	x = k * x;
	return;
}

void prepCos(float& x, int& n)
{
	float const pi = 3.14159265f;
	int m = 0;
	n = 0;
	if (x < 0.0f)
		x = -x;
	while (x >= 4.0f)
	{
		x /= 4.0f;
		m++;
	}
	while (m > 0)
	{
		n = (int)(x * 2.0f / pi);
		x -= (float)n * pi / 2.0f;
		x *= 4.0f;
		m--;
	}
	n = (int)(x * 2.0f / pi);
	x -= (float)n * pi / 2.0f;
	if (n % 2 == 1)
	{
		x -= pi / 2.0f;
		n += 1;
	}
	if (n == 2)
		n = -1;
	else n = 1;
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
	x = k * x;
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
	else if (x < 1.0f)
		while (x < 1.0f)
		{
			x *= 2.0f;
			p--;
		}
	return;
}

float directSum(float a, float const x, float(*next)(float, int))
{
	float res = a, eps = fabs(res) * 1e-6f;
	int i = 1;
	while (fabs(a) > eps)
	{
		a *= next(x, i++);
		res += a;
		eps = fabs(res) * 1e-6f;
	}
	return res;
}

float extendedSum(float a, float const x, float(*next)(float, int))
{
	float res = a, tmp, eps = fabs(res) * 1e-6f;
	int i = 1;
	a *= next(x, i++);
	res += a;
	while (fabs(a) > eps)
	{
		tmp = (a *= next(x, i++));
		tmp += (a *= next(x, i++));
		res += tmp;
		eps = fabs(res) * 1e-6f;
	}
	return res;
}

float reverseSum(float a, float const x, float(*next)(float, int))
{
	float res = 0, arr[10000], eps = 1e-15f;
	int i = 1, n = 20, tmp = n;
	arr[0] = a;
	while (fabs(a) > eps)
		arr[i++] = a *= next(x, i);
	for (i = i - 1; i >= 0; i--)
		res += arr[i];
	return res;
}

float t_sin(float const x, float(*SumFunc)( float, float const, float(*)(float, int) ))
{
	int n;
	float y = x;
	prepSin(y, n);
	return SumFunc(y, y, sin_next);
}

float t_cos(float const x, float(*SumFunc)( float, float const, float(*)(float, int) ))
{
	int n;
	float y = x;
	prepCos(y, n);
	return SumFunc(1.0f, y, cos_next) * (float)n;
}

float t_exp(float const x, float(*SumFunc)( float, float const, float(*)(float, int) ))
{
	int p, i;
	float prod = 1.0f, y = x, term;
	prepExp(y, p);
	term = SumFunc(1, y, exp_next);
	for (i = 0; i < p; i++)
		prod *= term;
	return  term;
}

float t_log(float const x, float(*SumFunc)( float, float const, float(*)(float, int) ))
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