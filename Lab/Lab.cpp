#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <intrin.h>
#include <locale.h>
#include <math.h>
using namespace std;

#pragma intrinsic(__rdtsc)

int compare(const void* a, const void* b) {
    float* ptr_a = (float*)a;
    float* ptr_b = (float*)b;

    if (*ptr_a <= *ptr_b) {
        return -1;
    }
    else if (*ptr_a > *ptr_b) {
        return 1;
    }
    else {
        return 0;
    }
}

char check_sort(float* a, float* sorted_a, int n) {
    for (int i = 0; i < n - 1; i++)
        if (sorted_a[i] > sorted_a[i + 1])
            return 'n';
    qsort(a, n, sizeof(float), compare);
    for (int i = 0; i < n; i++)
        if (a[i] != sorted_a[i]) 
            return 'n';
    return 's';
}

void random_nums(float* a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = (((float)rand() / RAND_MAX) * 2 - 1) * 1e6;
}

void print_array(float* a, int n, int order)
{
    if (order == 0)
        for (int i = 0; i < n; i++)
            printf("%.2f ", a[i]);
    else
        for (int i = n - 1; i >= 0; i--)
            printf("%.2f ", a[i]);
    printf("\n");
}

void choose(float* a, int n)
{
    int minI;
    float t;
    for (int i = 0; i < n; i++) {
        minI = i;
        for (int j = i; j < n; j++) {
            if (a[minI] > a[j])
                minI = j;
        }
        t = a[minI];
        a[minI] = a[i];
        a[i] = t;
    }
}

void comb_sort(float* a, int n) {
    double factor = 1.2473309;
    int step = n - 1;
    while (step >= 1) {
        for (int j = 0; j < n - step; j++) {
            if (a[j] > a[j + step]) {
                float t = a[j];
                a[j] = a[j + step];
                a[j + step] = t;
            }
        }
        step = step / factor;
    }
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                float t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                flag = 1;
            }
        }
    }
}

void radixSort(float arr[], int n) {
    unsigned char* pm = (unsigned char*)arr;
    float* output = (float*)malloc(n * sizeof(float));
    int count[256];
    for (int byte_num = 0; byte_num < sizeof(float); byte_num++) {
        for (int i = 0; i < 256; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            count[pm[i * sizeof(float) + byte_num]]++;
        for (int i = 1; i < 256; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            output[--count[pm[i * sizeof(float) + byte_num]]] = arr[i];
        float* tmp = arr;
        arr = output;
        output = tmp;
        pm = (unsigned char*)arr;
    }
    free(output);
}

void merge(float* arr, int l, int r, float* tmp) {
    int mid = (l + r) / 2;
    int lp = l, rp = mid + 1;
    int k = l;
    while (lp <= mid && rp <= r) {
        if (arr[lp] > arr[rp])
            tmp[k++] = arr[rp++];
        else
            tmp[k++] = arr[lp++];
    }
    for (; lp <= mid; lp++)
        tmp[k++] = arr[lp];
    for (; rp <= r; rp++)
        tmp[k++] = arr[rp];
    for (int i = l; i <= r; i++)
        arr[i] = tmp[i];
}



void mergeSort(float* arr, float* tmpdata, int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        mergeSort(arr, tmpdata, l, mid);
        mergeSort(arr, tmpdata, mid + 1, r);
        merge(arr, l, r, tmpdata);
    }
}

void time_sort()
{
    unsigned long long start, time;
    unsigned long long startOn, On;
    printf("choose\n");
    for (int n = 1e5; n <= 1e6; n += 1e5) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        float* arr_sort = (float*)malloc(n * sizeof(float));
        startOn = __rdtsc();
        for (int i = 0; i < n; i++)
            arr_sort[i] = arr[i];
        On = __rdtsc() - startOn;
        start = __rdtsc();
        choose(arr_sort, n);
        time = __rdtsc() - start;
        print_array(arr_sort, n, 0);
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (On * On));
        //printf("%c\n", check_sort(arr, arr_sort, n));
        free(arr);
        free(arr_sort);
    }
    printf("\ncomb\n");
    for (int n = 1e7; n <= 1e8; n += 1e7) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        float* arr_sort = (float*)malloc(n * sizeof(float));
        startOn = __rdtsc();
        for (int i = 0; i < n; i++)
            arr_sort[i] = arr[i];
        On = __rdtsc() - startOn;
        start = __rdtsc();
        comb_sort(arr_sort, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (On * log(On)));
        //printf("%c\n", check_sort(arr, arr_sort, n));
        free(arr);
        free(arr_sort);
    }
    printf("\nmerge\n");
    for (int n = 1e7; n <= 1e8; n += 1e7) {
        float* arr = (float*)malloc(n * sizeof(float));
        float* tmpdata = (float*)malloc(n * sizeof(float));
        float* arr_sort = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        startOn = __rdtsc();
        for (int i = 0; i < n; i++)
            arr_sort[i] = arr[i];
        On = __rdtsc() - startOn;
        start = __rdtsc();
        mergeSort(arr_sort, tmpdata, 0, n - 1);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (On * log(On)));
        //printf("%c\n", check_sort(arr, arr_sort, n));
        free(tmpdata);
        free(arr);
        free(arr_sort);
    }
    printf("\nradix\n");
    for (int n = 5 * 1e7; n <= 1e9; n += 1e7) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        float* arr_sort = (float*)malloc(n * sizeof(float));
        startOn = __rdtsc();
        for (int i = 0; i < n; i++)
            arr_sort[i] = arr[i];
        On = __rdtsc() - startOn;
        start = __rdtsc();
        radixSort(arr_sort, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (On));
        float* tmp = (float*)malloc(n * sizeof(float));
        int l = 0, r = n - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (arr_sort[mid] > 0)
                l = mid + 1;
            else {
                res = mid;
                r = mid - 1;
            }
        }
        int p = 0;
        if (res != -1) {
            for (int i = n - 1; i >= res; i--)
                tmp[p++] = arr_sort[i];
            for (int i = 0; i < res; i++)
                tmp[p++] = arr_sort[i];
        }
        else {
            for (int i = 0; i < res; i++)
                tmp[p++] = arr_sort[i];
        }
        //printf("%c", check_sort(arr_sort, tmp, n));
        free(arr);
        free(arr_sort);
        free(tmp);
    } 
}
void Client() {
    int status = 1;
    while (status) {
        printf("Выберите сортировку\n1 - Выбором, 2 - Расческой, 3 - Слиянием, 4 - Поразрядная\n");
        int c;
        scanf_s("%d", &c);
        printf("Порядок сортировки элементов\n0 - по возрастанию, 1 - по убыванию\n");
        int order;
        scanf_s("%d", &order);
        printf("Введите количество элементов:\n");
        int n;
        scanf_s("%d", &n);
        printf("Введите элементы по порядку:\n");
        float* a = (float*)malloc(n * sizeof(float));
        for (int i = 0; i < n; i++)
            scanf_s("%f", &a[i]);
        float* tmp = (float*)malloc(n * sizeof(float));
        switch (c) {
        case 1:
            choose(a, n);
            print_array(a, n, order);
            break;
        case 2:
            comb_sort(a, n);
            print_array(a, n, order);
            break;
        case 3:
            mergeSort(a, tmp, 0, n - 1);
            print_array(a, n, order);
            break;
        case 4:
            radixSort(a, n);
            print_array(a, n, order);
            break;
        }
        free(tmp);
        free(a);
        printf("Продолжить работу?\n0 - закончить, 1 - продолжить\n");
        scanf_s("%d", &status);
    }
}

int main() {
    setlocale(LC_ALL, ".1251");
    time_sort();
}
