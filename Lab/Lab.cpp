#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <locale.h>
#include <math.h>

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
    return 0;
}

char check_sort(float* a, int n) {
    float* a_cpy = (float*)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
        a_cpy[i] = a[i];
    qsort(a_cpy, n, sizeof(float), compare);
    for (int i = 0; i < n; i++)
        if (a[i] != a_cpy[i]) 
            return 'n';
    return 's';
}

void random_nums(float* a, unsigned long long n)
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

void radixSort(float* arr, float* tmp, int n) {
    unsigned char* pm = (unsigned char*)arr;
    int count[256];
    for (int byte_num = 0; byte_num < sizeof(float); byte_num++) {
        for (int i = 0; i < 256; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            count[pm[i * sizeof(float) + byte_num]]++;
        for (int i = 1; i < 256; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            tmp[--count[pm[i * sizeof(float) + byte_num]]] = arr[i];
        float* t = arr;
        arr = tmp;
        tmp = t;
        pm = (unsigned char*)arr;
    }
    int p = 0;
    for (int i = n - 1; arr[i] <= 0; i--)
        tmp[p++] = arr[i];
    for (int i = 0; arr[i] >= 0; i++)
        tmp[p++] = arr[i];
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


void Client() {
    int status = 1;
    while (status) {
        printf("Выберите сортировку\n1 - Выбором, 2 - Расческой, 3 - Слиянием, 4 - Поразрядная\n");
        int c, rand_or_not;
        scanf_s("%d", &c);
        printf("Порядок сортировки элементов\n1 - по возрастанию, 2 - по убыванию\n");
        int order;
        scanf_s("%d", &order);
        printf("Введите количество элементов:\n");
        unsigned long long n;
        scanf_s("%llu", &n);
        printf("1 - Ввести элементы вручную, 2 - генерация случайных чисел от -10^6 до 10^6\n");
        float* a = (float*)malloc(n * sizeof(float));
        scanf_s("%d", &rand_or_not);
        if (rand_or_not-1)
            random_nums(a, n);
        else
            for (int i = 0; i < n; i++)
                scanf_s("%f", &a[i]); 
        float* tmp = (float*)malloc(n * sizeof(float));
        unsigned long long ratio;
        unsigned long long time = __rdtsc();
        switch (c) {
        case 1:
            ratio = n * n;
            choose(a, n);
            break;
        case 2:
            ratio = n * log2(n);
            comb_sort(a, n);
            break;
        case 3:
            ratio = n * log2(n);
            mergeSort(a, tmp, 0, n - 1);
            break;
        case 4:
            ratio = n;
            radixSort(a, tmp, n);
            float* t = a;
            a = tmp;
            tmp = t;
            break;
        }
        time = __rdtsc() - time;
        printf("Количество тактов процессора - %llu\n", time);
        printf("Корректность работы - %c\n", check_sort(a, n));
        printf("константа - %f\n", float(time)/ratio);
        int c3;
        printf("Вывести массив?\n1 - нет, 2 - да\n");
        scanf_s("%d", &c3);
        if (c3 - 1)
            print_array(a, n, order-1);
        free(tmp);
        free(a);
        printf("Продолжить работу?\n0 - выйти из программы, 1 - продолжить\n");
        scanf_s("%d", &status);
    }
}

void time_sort()
{
    unsigned long long start, time;
    unsigned long long startOn, On;
    printf("choose\n");
    for (unsigned long long n = 1e4; n <= 1e5; n += 1e4) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        choose(arr, n);
        time = __rdtsc() - start;
        //print_array(arr_sort, n, 0);
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (n * n));
        //printf("%c\n", check_sort(arr, arr_sort, n));
        free(arr);
    }
    printf("\ncomb\n");
    for (unsigned long long n = 1e7; n <= 1e8; n += 1e7) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        comb_sort(arr, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (n * log2(n)));
        //printf("%c\n", check_sort(arr, arr_sort, n));
        free(arr);
    }
    printf("\nmerge\n");
    for (unsigned long long n = 1e7; n <= 1e8; n += 1e7) {
        float* arr = (float*)malloc(n * sizeof(float));
        float* tmpdata = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        mergeSort(arr, tmpdata, 0, n - 1);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (n * log2(n)));
        //printf("%c\n", check_sort(arr, arr_sort, n));
        free(tmpdata);
        free(arr);
    }
    printf("\nradix\n");
    for (unsigned long long n = 1e8; n <= 1e9; n += 1e8) {
        float* arr = (float*)malloc(n * sizeof(float));
        float* tmpdata = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        radixSort(arr, tmpdata, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / n);
        //printf("%c\n", check_sort(arr, n));
        free(arr);
        free(tmpdata);
    }
}

int main() {
    setlocale(LC_ALL, ".1251");
    Client();
    //time_sort();
}

