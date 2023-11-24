//Comb sort for DOUBLE
//coder: IVAN ZOLKIN
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <algorithm>
#include "intrin.h"
#pragma intrinsic(__rdtsc)
using namespace std;

void swap(double* a, double* b) //swap variables
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

void comb_s(double* mas, int n) {
    int step = n - 1;
    double basis = (1 + sqrt(5)) / 2.0;
    double factor = 1.0 / (1.0 - exp(-basis));  //"magic digit" - constant for step reduction
    int j;

    while (step >= 1) {
        for (j = 0; j < n - step; j++) {    //run for (0 to n-step) and compare values with step
            if (mas[j] > mas[j + step]) {
                swap(&mas[j], &mas[j + step]);
            }
        }
        step /= factor;
    }
}

int main()
{
    int n, i = 0;
    unsigned __int64 a, b;
    scanf("%d", &n);
    double* mas = (double*)malloc(n * sizeof(double));
    //double* mas_TRUE = (double*)malloc(n * sizeof(double));   //for correct test
    //random start
    /*
    for (; i < n / 2; i++) {
        mas[i] = -10000 + ((rand() % (int)pow(10, 7)) / pow(10, 7)) * (10000 - -10000);
        //mas_TRUE[i] = mas[i];
    }
    for (i = n / 2; i < n; i++) {
        mas[i] = ((rand() % (int)pow(10, 7)));
        //mas_TRUE[i] = mas[i];
    }
    */
    //random end
    
    for (; i < n; i++) {
        scanf("%lf", &mas[i]);
    }
    
    //a = __rdtsc();
    comb_s(mas, n);
    //b = __rdtsc();
    //printf_s("%I64d ticks\n", b-a);
    //correct test start
    /*
    sort(mas_TRUE, mas_TRUE + n);
    for (i = 0; i < n; i++) {
        if (!(mas[i]*mas[i] - mas_TRUE[i]*mas_TRUE[i] > -1e-6 && mas[i] * mas[i] - mas_TRUE[i] * mas_TRUE[i] < 1e-6)) {
            printf("ERROR! %lf %lf %lf",mas[i],mas_TRUE[i], abs(mas[i] - mas_TRUE[i]));
            return 1;
        }
    }
    printf("OK!");
    */
    //correct test finish

    for (i = 0; i < n; i++) {
        printf("%lf ", mas[i]);
    }

    free(mas);

    return 0;
}
