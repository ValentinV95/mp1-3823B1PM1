#include "stdio.h"
#include "malloc.h"
#include "time.h"
#include "stdlib.h"

void radix_sort(double arr[], int n, int SIZE);
int cmp(const void* arr, const void* arr_new);
void verification(double arr[], double mas[], int k);

void radix_sort(double arr[], int n, int SIZE) {
    double* arr_new = (double*)malloc(SIZE * 8);
    unsigned char* r0, * r1;
    int num[257];
    int r, k, t, tmp, i;

    r0 = (unsigned char*)arr;
    r1 = (unsigned char*)arr_new;
    r = 0;
    for (k = 0; k < sizeof(double); k++) /*заполнение стартового массива*/
    {
        for (i = 0; i < 256; num[i++] = 0);
        for (i = 0; i < SIZE; i++)
            if (r == 0) num[r0[8 * i + k]]++;/*считает колличество чисел с одним разрядом */
        /* k-ый байт i элемента в изначальном первом массиве, идет по каждому элементу*/
            else num[r1[8 * i + k]]++;
        t = 0;/*заполнение с 1-го элемента массива*/
        for (i = 0; i < 256; i++)
        {
            tmp = num[i];
            num[i] = t;
            t += tmp;
        }
        for (i = 0; i < SIZE; i++)
            if (r == 0) arr_new[num[r0[8 * i + k]]++] = arr[i];
            else arr[num[r1[8 * i + k]]++] = arr_new[i];
        r = 1 - r;
    }
    r = 0;
    for (i = n - 1;i > -1;i--) {
        if (arr[i] < 0) {
            r++;
        }
        else {
            break;
        }
    }
    for (i = 0;i < r;i++) {
        arr_new[i] = arr[n - i - 1];
    }
    for (i = r;i < n;i++) {
        arr_new[i] = arr[i - r];
    }
    for (i = 0;i < n;i++) {
        arr[i] = arr_new[i];
    }
    free(arr_new);
}


int main() {
    int i, n, SIZE;
    printf("What is the size of the array?\n");
    scanf_s("%d", &SIZE);
    
    double* arr = (double*)malloc(SIZE * sizeof(double));
    double* mas = (double*)malloc(SIZE * sizeof(double));
    int ans ;
    printf("independent input - 1, filling in with the program - 2\n");
    scanf_s("%d", &ans);
    
    if (ans == 2) {
        srand(time(NULL));

        for (i = 0; i < SIZE; i++) {
            arr[i] = rand();
        }
    }
    else {
        for (i = 0; i < SIZE; i++)
            scanf_s("%lf", &arr[i]);
    }
    for (i = 0; i < SIZE; i++) {
        mas[i] = arr[i];
    }
    n = SIZE;
    clock_t start = clock();
    radix_sort(arr, n, SIZE);
    clock_t end = clock();
    verification(arr, mas, SIZE);
    for (i = 0; i < SIZE; i++) {
        printf("%f\n", arr[i]);
    }
    printf("\n");
    double time_taken = (double(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f second\n", time_taken);
   
    free(mas);
}

int cmp(const void* a, const void* b) {
    return *(double*)a - *(double*)b;
}

void verification(double arr[], double mas[], int SIZE) {// функция сравнения сортировки с qsort
    qsort(mas, SIZE, sizeof(double), cmp);
    bool flag = true;
    for (int i = 0; i < SIZE; i++) {
        if (mas[i] != arr[i]) {
            flag = false;
            printf("Error");
            printf("\n");
            break;
        }
    }
    if (flag) printf("Not error ");
    printf("\n");

}