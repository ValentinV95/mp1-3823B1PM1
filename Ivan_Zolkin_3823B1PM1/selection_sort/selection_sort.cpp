﻿//Selection sort for DOUBLE
//coder: IVAN ZOLKIN
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h";
#include "stdlib.h"
//#include "intrin.h"
//#pragma intrinsic(__rdtsc)

void swap(double* a,double* b) {   //swap variables
    double temp = *a;
    *a = *b;
    *b = temp;
}
//qsort compare functions start
//int cmp(const void* a, const void* b)
//{
//    const double* ad, * bd;
//
//    ad = (const double*)a;
//    bd = (const double*)b;
//
//    if (*ad < *bd)
//    {
//        return -1;
//    }
//    else if (*ad > *bd)
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//}
//qsort compare functions end

void selection_s(double* ptr, int n) { //every time find the min element (to the right of i-element) and swap with i-element
    int i = 0, minI, j;
    for (i = 0; i < n - 1; i++) {   //run for elements to swap
        minI = i;
        for (j = i; j < n; j++) {   //finding the min element to the right of the selected
            if (ptr[minI] > ptr[j]) {
                minI = j;
            }
        }
        swap(&ptr[i], &ptr[minI]);
    }
}

int main()
{
    int n, i = 0;
    //unsigned __int64 a, b; //ticks test
    scanf("%d", &n);
    double* mas = (double*)malloc(n * sizeof(double));
    //double* mas_TRUE = (double*)malloc(n * sizeof(double));   //for correct test
    
    //random start
    /*for(;i<n;i++){
        mas[i] = double(rand())/RAND_MAX * 2000.0 - 1000.0;
        mas_TRUE[i] = mas[i];
    }*/
    //random end
    
    
    for (; i < n; i++) {
        scanf("%lf", &mas[i]);
    }
    
    
    //tick test start   !UNCOMMENT inlude and pragma
    //a = __rdtsc();
    selection_s(mas, n);
    //b = __rdtsc();
    //printf_s("%I64d ticks\n", b - a);
    //tick test end
    
    //correct test start    !UNCOMMENT cmp() function!
    /*qsort(mas_TRUE,n,sizeof(double),cmp);
    for (i = 0; i < n; i++) {
        if (!(mas[i]*mas[i] - mas_TRUE[i]*mas_TRUE[i] > -1e-6 && mas[i] * mas[i] - mas_TRUE[i] * mas_TRUE[i] < 1e-6)) {
            printf("ERROR! %lf %lf",mas[i],mas_TRUE[i]);
            return 1;
        }
    }
    printf("OK!");*/
    //correct test finish
    
    for (i = 0; i < n; i++) {
        printf("%lf ", mas[i]);
    }

    free(mas);

    return 0;
}
