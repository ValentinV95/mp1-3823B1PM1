#include "stdio.h"
#include "algorithm"
#include "math.h"
#include "locale"

#pragma warning(disable : 4996)

float sin_next(float x, int i) {//Функция вычисления множителя для следующего члена ряда для синуса
    return -x * x / (2 * i * (2 * i + 1));
}

float cos_next(float x, int i) {//Функция вычисления множителя для следующего члена ряда для косинуса
    return -x * x / (2 * i * (2 * i - 1));
}

float exp_next(float x, int i) {//Функция вычисления множителя для следующего члена ряда для экспоненты
    return x / i;
}

float ln_next(float x, int i) {//Функция вычисления множителя для следующего члена ряда для логарифма
    return -x * i / (i + 1);
}


float directSum(float x0, float x, float(*next)(float, int), int n) {//Прямая сумма
    float res, xi;
    res = xi = x0;
    for (int i = 1; i <= n; i++)
    {
        xi *= next(x, i);
        res += xi;
    }
    return res;
}

float inverseSum(float x0, float x, float(*next)(float, int), int n)//Обратная сумма
{
    float res, xn, t;
    xn = x0;
    res = 0;
    for (int i = 1; i <= n; i++)
    {
        t = next(x, i);
        if (t == 0)
        {
            n = i - 1;
            break;
        }
        xn *= t;
    }
    for (int i = n; i >= 1; i--)
    {
        res += xn;
        xn /= next(x, i);
    }
    return res + x0;
}

float pairSum(float x0, float x, float(*next)(float, int), int n)//Попарное суммирование
{
    float res, xi, xj;
    res = xi = x0;
    for (int i = 1; i <= n; i++)
    {
        xi *= next(x, i);
        xj = xi;
        if (i + 1 <= n)
        {
            xi *= next(x, ++i);
            xj += xi;
        }
        res += xj;
    }
    return res;
}

float sin_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(x, x, sin_next, 5);
}

float cos_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(1, x, cos_next, 5);
}

float exp_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(1, x, exp_next, 10);
}

float ln_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(x, x, ln_next, 10);
}

int main(){
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = ln_(i, directSum), , k2 = ln_(i, inverseSum), k3 = ln_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1, k2, k3);
    }
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = cos_(i, directSum), k2 = cos_(i, inverseSum), k3 = cos_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1, k2, k3);
    }
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = sin_(i, directSum), k2 = sin_(i, inverseSum), k3 = sin_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1, k2, k3);
    }
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = exp_(i, directSum), k2 = exp_(i, inverseSum), k3 = exp_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1, k2, k3);
    }
    /*for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = ln_(i, directSum), k2 = log(1+i), k3 = ln_(i, inverseSum), k4 = ln_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1 - k2, k3 - k2, k4 - k2);
    }
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = cos_(i, directSum), k2 = cos(i), k3 = cos_(i, inverseSum), k4 = cos_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1 - k2, k3 - k2, k4 - k2);
    }
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = sin_(i, directSum), k2 = sin(i), k3 = sin_(i, inverseSum), k4 = sin_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1 - k2, k3 - k2, k4 - k2);
    }
    for (float i = 0; i < 32; i += 1.0f / 128.0f)
    {
        float k1 = exp_(i, directSum), k2 = exp(i), k3 = exp_(i, inverseSum), k4 = exp_(i, pairSum);
        printf("%1.13f %1.13f %1.13f\n", k1 - k2, k3 - k2, k4 - k2);
    }*/
    return 0;
}