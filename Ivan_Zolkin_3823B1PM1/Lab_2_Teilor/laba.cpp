#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <clocale>

#pragma warning(disable: 4996)

//BEGIN-------------Вычисление множителей для последующих членов ряда---------------------------------

float sin_p(float x, int i)  //Функция вычисления множителя для следующего члена ряда для синуса
{
    return -(x * x) / (2 * i * (2 * i + 1));
}
float cos_p(float x, int i) //Функция вычисления множителя для следующего члена ряда для косинуса
{
    return -(x * x) / (2*i*(2*i-1));
}
float log_p(float x, int i) //Функция вычисления множителя для следующего члена ряда для логарифма
{
    return -(x*i) / (i + 1);
}
float exp_p(float x, int i) //Функция вычисления множителя для следующего члена ряда для экспоненты
{
    return x / i;
}

//END-------------Вычисление множителей для последующих членов ряда------------------------------------


float sum_series_forward(float a, float x, float(*next)(float, int), int n) //Прямая сумма ряда
{
    float res = a;
    for (int i = 1; i <= n; i++) {
        a = next(x, i) * a;
        res += a;
    }
    return res;
}
float sum_series_backward(float a, float x, float(*next)(float, int), int n) //Обратная сумма ряда
{
    float* series_mem = (float*)malloc((n+1) * sizeof(float)); //Члены ряда
    float res = 0;
    if (!series_mem) {
        printf("ERROR: can't allocate memory for series_mem in sum_series_backward()\n");
        getchar();
        exit(1);
    }
    series_mem[0] = a;

    for (int i = 1; i <= n; i++) {
        a = next(x, i) * a;
        series_mem[i] = a;
    }
    for (int i = n; i > -1; i--) {
        res += series_mem[i];
    }
    
    free(series_mem);

    return res;
}
float sum_series_pair_forward(float a, float x, float(*next)(float, int), int n) //Прямая сумма ряда попарно
{
    float res = 0.0;
    float tmp1,tmp2;
    for (int i = 0; i <= n; i += 2) {
        if (!i) {
            tmp1 = a;
            tmp2 = (i+1 <= n) ? next(x, i+1)*tmp1 : 0.0;
        }
        else {
            tmp1 = next(x, i)*tmp2;
            tmp2 = (i + 1 <= n) ? next(x, i + 1)*tmp1 : 0.0;
        }
        float y = tmp1 + tmp2;
        res += y;
    }
    return res;
}

float abss(float a) {
    return a < 0 ? -a : a;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int how_many_macloren = 1000000; //кол-во членов ряда
    float x = -1,a,b,c,d,error_forward,error_backward,error_forward_pair;
    int test_num = 0;

    /*FILE* output = NULL;
    output = fopen("res", "w");
    if (!output) {
        printf("OPEN FILE ERROR");
        getchar();
        exit(2);
    }*/

    //for (; x <= 1; x += 0.02,test_num++) {
    //    printf("\n---------------test %i // x = %.2f -----------------\n", test_num,x);
    //    a = sinf(x);
    //    b = sum_series_forward(x, x, sin_p, how_many_macloren);
    //    c = sum_series_backward(x, x, sin_p, how_many_macloren);
    //    d = sum_series_pair_forward(x, x, sin_p, how_many_macloren);
    //    printf("sin   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d,abss(a-b), abss(a - c), abss(a - d));
    //    //fprintf(output,"sin %.2f %.7f %.7f %.7f\n",x, abss(a - b), abss(a - c), abss(a - d));

    //    a = logf(x + 1);
    //    b = sum_series_forward(x, x, log_p, how_many_macloren);
    //    c = sum_series_backward(x, x, log_p, how_many_macloren);
    //    d = sum_series_pair_forward(x, x, log_p, how_many_macloren);
    //    printf("log   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d, abss(a - b), abss(a - c), abss(a - d));
    //    //fprintf(output, "log %.2f %.7f %.7f %.7f\n", x, abss(a - b), abss(a - c), abss(a - d));

    //    a = cosf(x);
    //    b = sum_series_forward(1, x, cos_p, how_many_macloren);
    //    c = sum_series_backward(1, x, cos_p, how_many_macloren);
    //    d = sum_series_pair_forward(1, x, cos_p, how_many_macloren);
    //    printf("cos   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d, abss(a - b), abss(a - c), abss(a - d));
    //    //fprintf(output, "cos %.2f %.7f %.7f %.7f\n", x, abss(a - b), abss(a - c), abss(a - d));

    //    a = expf(x);
    //    b = sum_series_forward(1, x, exp_p, how_many_macloren);
    //    c = sum_series_backward(1, x, exp_p, how_many_macloren);
    //    d = sum_series_pair_forward(1, x, exp_p, how_many_macloren);
    //    printf("exp   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d, abss(a - b), abss(a - c), abss(a - d));
    //    //fprintf(output, "exp %.2f %.7f %.7f %.7f\n", x, abss(a - b), abss(a - c), abss(a - d));
    //}
    //fclose(output);
    printf("Введите x: ");
    scanf("%F", &x);
    a = sinf(x);
    b = sum_series_forward(x, x, sin_p, how_many_macloren);
    c = sum_series_backward(x, x, sin_p, how_many_macloren);
    d = sum_series_pair_forward(x, x, sin_p, how_many_macloren);
    printf("sin   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d,abss(a-b), abss(a - c), abss(a - d));
    a = logf(x + 1);
    b = sum_series_forward(x, x, log_p, how_many_macloren);
    c = sum_series_backward(x, x, log_p, how_many_macloren);
    d = sum_series_pair_forward(x, x, log_p, how_many_macloren);
    printf("log   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d, abss(a - b), abss(a - c), abss(a - d));
    a = cosf(x);
    b = sum_series_forward(1, x, cos_p, how_many_macloren);
    c = sum_series_backward(1, x, cos_p, how_many_macloren);
    d = sum_series_pair_forward(1, x, cos_p, how_many_macloren);
    printf("cos   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d, abss(a - b), abss(a - c), abss(a - d));

    a = expf(x);
    b = sum_series_forward(1, x, exp_p, how_many_macloren);
    c = sum_series_backward(1, x, exp_p, how_many_macloren);
    d = sum_series_pair_forward(1, x, exp_p, how_many_macloren);
    printf("exp   %.7f %.7f %.7f %.7f || errors: %.7f %.7f %.7f\n", a, b, c, d, abss(a - b), abss(a - c), abss(a - d));
}
