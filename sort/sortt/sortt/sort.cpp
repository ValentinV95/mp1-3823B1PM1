#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <locale.h>
#include <math.h>
#pragma intrinsic(__rdtsc)

int match(const void* a, const void* b) {
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
    qsort(a_cpy, n, sizeof(float), match);
    for (int i = 0; i < n; i++)
        if (a[i] != a_cpy[i])
            return 'b';
    return 'p';
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

void shell(float* a, float n) {
    int g, i, j;
    float temp;
    for (g = n / 2; g != 0; g /= 2) {
        for (i = g; i < n; i++) {
            temp = a[i];
            for (j = i; (j >= g) && (a[j - g] > temp); j -= g) {
                a[j] = a[j - g];
            }
            a[j] = temp;
        }
    }
}

void choise(float* arr, float n) {
    int i = 0, j = 0;
    int minI;
    float tmp;
    for (i = 0; i < n - 1; i++) {
        minI = i;
        for (j = i; j < n; j++) {
            if (arr[minI] > arr[j]) {
                minI = j;
            }
        }
        tmp = arr[i];
        arr[i] = arr[minI];
        arr[minI] = tmp;

    }
}


void radix(float* arr, float* tmp, int n) {
    unsigned char* pm = (unsigned char*)arr;
    int count[256];
    for (int byte_num = 0; byte_num < sizeof(float); byte_num++) {
        for (int i = 0; i < 256; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            count[pm[i * sizeof(float) + byte_num]]++;
        int temp = count[0];
        count[0] = 0;
        for (int i = 1; i < 256; i++) {
            int t = count[i];
            count[i] = temp;
            temp = t;
            count[i] += count[i - 1];
        }
        for (int i = 0; i < n; i++) {
            tmp[count[pm[i * sizeof(float) + byte_num]]++] = arr[i];
        }

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


void realize() {
    int status = 1;
    while (status) {
        printf("Выберите сортировку\n1 - Выбором, 2 - Шелла, 3 - Слиянием, 4 - Поразрядная\n");
        int c, rand_or_not;
        scanf_s("%d", &c);
        int order;
        printf("Выберите сортировку\n1 - в порядке возрастания, 2 - в порядке убывания\n");
        scanf_s("%d", &order);
        printf("Введите количество элементов:\n");
        unsigned long long n;
        scanf_s("%llu", &n);
        printf("1 - Ввести вручную, 2 - генерация случайных чисел\n");
        float* a = (float*)malloc(n * sizeof(float));
        scanf_s("%d", &rand_or_not);
        if (rand_or_not - 1)
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
            choise(a, n);
            break;
        case 2:
            ratio = n * log2(n);
            shell(a, n);
            break;
        case 3:
            ratio = n * log2(n);
            mergeSort(a, tmp, 0, n - 1);
            break;
        case 4:
            ratio = n;
            radix(a, tmp, n);
            float* t = a;
            a = tmp;
            tmp = t;
            break;
        }
        time = __rdtsc() - time;
        printf("Такты: %llu\n", time);
        printf("Корректность: %c\n", check_sort(a, n));
        printf("Константа: %f\n", float(time) / ratio);
        int c3;
        printf("Вывести массив?\n1 - нет, 2 - да\n");
        scanf_s("%d", &c3);
        if (c3 - 1)
            print_array(a, n, order - 1);
        free(tmp);
        free(a);
   
    }
}

void time_sort()
{
    unsigned long long start, time;
    unsigned long long startOn, On;
    printf("choise\n");
    for (unsigned long long n = 1e4; n <= 4; n += 1e4) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        choise(arr, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (n * n));
        free(arr);
    }
    printf("\shell\n");
    for (unsigned long long n = 5 * 1e6; n <= 2; n += 1e6) {
        float* arr = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        shell(arr, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / (n * log(n)));
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
        free(tmpdata);
        free(arr);
    }
    printf("\nradix\n");
    for (unsigned long long n = 1e7; n <= 1e10; n += 1e7) {
        float* arr = (float*)malloc(n * sizeof(float));
        float* tmpdata = (float*)malloc(n * sizeof(float));
        random_nums(arr, n);
        start = __rdtsc();
        radix(arr, tmpdata, n);
        time = __rdtsc() - start;
        printf("n = %d \n", n);
        printf("ratio - %f\n", (float)time / n);
        free(arr);
        free(tmpdata);
    }
}

int main() {
    setlocale(LC_ALL, ".1251");
    realize();
}