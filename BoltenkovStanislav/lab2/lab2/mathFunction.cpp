#include "mathFunction.h"
#include <algorithm>

float sin_next(float x, int i)
{
    return -x * x / (float)(2 * i * (2 * i + 1));
}

float cos_next(float x, int i)
{
    return -x * x / (float)(2 * i * (2 * i - 1));
}

float exp_next(float x, int i)
{
    return x / (float)i;
}

float ln_next(float x, int i)//1 + x
{
    return -(float)x * i / (float)(i + 1);
}


float sum_service(float a0, float x, float(*next)(float, int), int n)
{
    float res, ai;
    int i;
    res = ai = a0;
    for (i = 1; i <= n; i++)
    {
        ai *= next(x, i);
        res += ai;
    }
    return res;
}

float double_sum_service(float a0, float x, float(*next)(float, int), int n)
{
    float res, ai, at;
    int i;
    res = ai = a0;
    for (i = 1; i <= n; i++)
    {
        ai *= next(x, i);
        at = ai;
        if (i + 1 <= n)
        {
            ai *= next(x, ++i);
            at += ai;
        }
        res += at;
    }
    return res;
}

float double_sumr_service(float a0, float x, float(*next)(float, int), int n)
{
    float res, ai, at, t;
    int i;
    ai = a0;
    res = 0;
    for (i = 1; i <= n; i++)
    {
        t = next(x, i);
        if (abs(t) == 0.0f || abs(ai) < 1e-8)
        {
            n = i - 1;
            break;
        }
        ai *= t;
    }
    for (i = n; i >= 1; i--)
    {
        at = ai;
        ai /= next(x, i);
        if (i - 1 >= 1)
        {
            at += ai;
            ai /= next(x, --i);
        }
        res += at;
    }
    return res + a0;
}

float sumr_service(float a0, float x, float(*next)(float, int), int n)
{
    float res, an, t;
    int i;
    an = a0;
    res = 0;
    for (i = 1; i <= n; i++)
    {
        t = next(x, i);
        if (abs(t) == 0.0f || abs(an) < 1e-8f)
        {
            n = i - 1;
            break;
        }
        an *= t;
    }
    for (i = n; i >= 1; i--)
    {
        res += an;
        an /= next(x, i);
    }
    return res + a0;
}

float sin_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(x, x, sin_next, 50);
}

float cos_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(1, x, cos_next, 50);
}

float exp_(float x, float (*sum)(float, float, float(*)(float, int), int))
{
    return sum(1, x, exp_next, 50);
}

float ln_(float x, float (*sum)(float, float, float(*)(float, int), int))//1 + x 
{
    return sum(x, x, ln_next, 10);
}