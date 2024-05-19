#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <clocale>

#pragma warning(disable: 4996)

float sin_next(float x, int i)  //Функция вычисления множителя для следующего члена ряда для синуса
{
    return -(x * x) / (2 * i * (2 * i + 1));
}
float cos_next(float x, int i) //Функция вычисления множителя для следующего члена ряда для косинуса
{
    return -(x * x) / (2 * i * (2 * i - 1));
}
float log_next(float x, int i) //Функция вычисления множителя для следующего члена ряда для логарифма
{
    return -(x * i) / (i + 1);
}
float exp_next(float x, int i) //Функция вычисления множителя для следующего члена ряда для экспоненты
{
    return x / i;
}




float sum_forward(float x0, float x, float(*next)(float, int), int n) //Прямая сумма 
{
    float res = x0;
    for (int i = 1; i <= n; i++) {
        x0 = next(x, i) * x0;
        res += x0;
    }
    return res;
}

float sum_backward(float x0, float x, float(*next)(float, int), int n) //Обратная сумма 
{
//   float res, xn, t;
//   xn = x0;
//   res = 0;
//   for (int i = 1; i <= n; i++)
//   {
//       t = next(x, i);
//       if (t == 0)
//       {
//           n = i - 1;
//           break;
//       }
//       xn *= t;
//   }
//   for (int i = n; i >= 1; i--)
//   {
//       res += xn;
//       xn /= next(x, i);
//   }
//   return res + x0;
    float* series_mem = (float*)malloc((n + 1) * sizeof(float)); //Члены ряда
    float res = 0;
    if (!series_mem) {
        exit(1);
    }
    series_mem[0] = x0;
    for (int i = 1; i <= n; i++) {
        x0 = next(x, i) * x0;
        series_mem[i] = x0;
    }
    for (int i = n; i > -1; i--) {
        res += series_mem[i];
    }

    free(series_mem);

    return res;
}

float sum_pair(float x0, float x, float(*next)(float, int), int n) //попарная сумма 
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
    return sum(x, x, log_next, 10);
}



int main(){
    setlocale(LC_ALL, "ru");
    float a, b, c, d;
    
    int n = 10000; //кол-во членов ряда
    float x;
   
    printf("Введите x: ");
    scanf("%f", &x);



    a = sinf(x);
    b = sum_forward(x, x, sin_next, n);
    c = sum_backward(x, x, sin_next, n);
    d = sum_pair(x, x, sin_next, n);
    printf("sin: %.7f  forward = %.7f backward = %.7f pair = %.7f\n", a, b, c, d);

    a = logf(x + 1);
    b = sum_forward(x, x, log_next,n);
    c = sum_backward(x, x, log_next, n);
    d = sum_pair(x, x, log_next, n);
    printf("log: %.7f forward = %.7f backward = %.7f pair = %.7f\n", a, b, c, d);

    a = cosf(x);
    b = sum_forward(1, x, cos_next, n);
    c = sum_backward(1, x, cos_next, n);
    d = sum_pair(1, x, cos_next,n);
    printf("cos: %.7f forward = %.7f backward = %.7f pair = %.7f\n", a, b, c, d);

  
    a = expf(x);
    b = sum_forward(1, x, exp_next, n);
    c = sum_backward(1, x, exp_next, n);
    d = sum_pair(1, x, exp_next, n);
    printf("exp: %.7f forward = %.7f backward = %.7f pair = %.7f\n", a, b, c, d);

  



 //   float k;

//   for (float i = 0; i < 64; i += 1.0f / 128.0f)
//   {
//       a = ln_(i, sum_forward);
//       b = ln_(i, sum_backward);
//       c = ln_(i, sum_pair);
//       printf("%1.13f %1.13f %1.13f\n", a, b, c);
//   }
//
//   for (float i = 0; i < 32; i += 1.0f / 128.0f)
//   {
//       
//       a = cos_(i, sum_forward);
//       b = cos_(i, sum_backward);
//       c = cos_(i, sum_pair);
//       printf("%1.13f %1.13f %1.13f\n", a, b, c);
//   }

//    for (float i = 0; i < 64; i += 1.0f / 128.0f)
//    {
//        k = sinf(i);
//        a = sin_(i, sum_forward);
//        b = sin_(i, sum_backward);
//        c = sin_(i, sum_pair);
//       printf("%1.7f %1.7f %1.7f %1.7f\n",k, a, b, c);
//   }
//   for (float i = 0; i < 64; i += 1.0f / 128.0f)
//   {
//       k = expf(i);
//       a = exp_(i, sum_forward);
//       b = exp_(i, sum_backward);
//       c = exp_(i, sum_pair);
//       printf("%1.13f\n", i);
//   }


 
        

    return 0;
}

