//Merge sort for DOUBLE
//coder: IVAN ZOLKIN
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <algorithm>
#include "intrin.h"
#pragma intrinsic(__rdtsc)
using namespace std;

int max(int a, int b) { //return max value
    if (a > b) {
        return a;
    }
    return b;
}
int min(int a, int b) { //return min value
    if (a < b) {
        return a;
    }
    return b;
}
void merge(double* a, double* b, double* res, int an, int bn) //unite two arrays in one ordered array 'res'
{
    int ia = 0, ib = 0, ir = 0;
    while (an > ia && ib < bn) //two pointer on 'a' and 'b', if element from 'a' < el from 'b' --> res.append(a[ia]) and move pointer on next element else append(b[bi]), bi++
    {
        if (a[ia] < b[ib]) {
            res[ir++] = a[ia++];
        }
        else {
            res[ir++] = b[ib++];
        }
    }
    /*
    after 'while' one of the pointers on the edge and we put the remaining elements
    */
    for (; ia < an; ia++) {
        res[ir++] = a[ia];
    }
    for (; ib < bn; ib++) {
        res[ir++] = b[ib];
    }
}
void merge_s(double* mas, int n) {
    double* tmpdata = (double*)malloc(n * sizeof(double));
    int step = 1, i;
    double* temp;
    for (; step < n; step *= 2) {
        for (i = 0; i < n; i += 2 * step) {
            merge(&mas[i], &mas[i + step], &tmpdata[i], max(0, min(step, n - i)), max(0, min(step, n - step - i)));
            /* arguments merge(1,2,3,4,5):
                1 - pointer on the beginning of first subarray (double*)
                2 - pointer on the beginning of second subarray (double*)
                3 - res array (double*)
                4 - length of the first array (int)
                5 - length of the second array (int)
            */
        }
        temp = mas; //swap res array and original array for using true data
        mas = tmpdata;
        tmpdata = temp;
    }
}

int main() {
	
    int n, i = 0;

    scanf("%d", &n);
    double* mas = (double*)malloc(n * sizeof(double));
    //double* mas_TRUE = (double*)malloc(n * sizeof(double));   //for correct test
    unsigned __int64 a, b;
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
    merge_s(mas, n);
    //b = __rdtsc();
    //printf_s("%I64d ticks\n", b - a);
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