#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#define SIZE 1000
#define RANGE 100
#define UCHAR_MAX 255

int compare(const void *a, const void *b){
    return (*(double*)a - *(double*)b);
}

void _swap_i(uint64_t* a, uint64_t* b) {
    uint64_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void foffset(uint8_t* mas, size_t size, size_t offset, uint64_t count[255 + 1]) { //вычисляет отступы для для поразрядной сортировки
    size_t i;
    uint64_t tmp;
    memset(count, 0, (255 + 1)*sizeof(uint64_t)); //заполняет массив нулями
    for (i = 0; i < size * sizeof(double); i += sizeof(double))
        count[mas[i + offset]]++;
    tmp = count[0];
    count[0] = 0;
    for (i = 0; i < 255; i++) {
        _swap_i(&tmp, &count[i + 1]);
        count[i + 1] += count[i];
    }
}


void _swap_p(double** a, double** b) {
    double* tmp = *a;
    *a = *b;
    *b = tmp;
}

void radix_sort_LSD(double* arr, size_t size) { //Далее следует цикл, который выполняет поразрядную сортировку по каждому байту в числах типа double. В цикле вызывается функция foffset, которая вычисляет смещение для каждого значения и сохраняет его в массиве count. Затем происходит перестановка элементов массива arr во временный массив mas2 на основе вычисленных смещений. После каждой итерации цикла массивы arr и mas2 меняются местами с помощью функции _swap_p. После завершения цикла указатель pm устанавливается на начало массива arr.
    uint8_t* pm = (uint8_t*)arr;
    uint64_t count[UCHAR_MAX + 1];
    double* mas2 = (double*)malloc(size * sizeof(double));
    size_t i, j, k;

    for (i = 0; i < sizeof(double); i++) {
        foffset(pm, size, i, count);
        for (j = 0; j < size; j++)
            mas2[count[pm[j * sizeof(double) + i]]++] = arr[j];
        _swap_p(&arr, &mas2);
        pm = (uint8_t*)arr;
    }
//Далее в коде проверяется, есть ли отрицательные числа в массиве. Если есть, то числа размещаются в начале временного массива mas2, а положительные числа - в конце. Затем элементы временного массива mas2 копируются обратно в исходный массив arr, используя цикл. В конце функции освобождается память, занятая временным массивом mas2.
    k = 0;
    if (arr[size - 1] < 0) {
        for (i = size - 1; i >= 0; i--) {
            if (arr[i] > 0) break;
            mas2[k++] = arr[i];
        }

        for (i = 0; i < size; i++) {
            if (arr[i] < 0) break;
            mas2[k++] = arr[i];
        }

        for (i = 0; i < size; i++) arr[i] = mas2[i];
    }

    free(mas2);
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    double arr[SIZE];
    int i;
    srand(time(0));
    for (i = 0; i < SIZE; i++) {
        arr[i] = (double)(rand() % RANGE);
    }
    printf("массив \n ");
    for (i = 0; i < SIZE; i++)
        printf("%.2lf ", arr[i]) ;
    start = clock();
    radix_sort_LSD(arr, SIZE) ;
    end = clock();
    printf("\nОтсортированный массив\n ");
    for (i = 0; i < SIZE; i++)
        printf("%.2lf ", arr[i]);
    qsort(arr, SIZE, sizeof(double), compare);
        printf("\nготовый массив \n");
        for (int i = 0; i < SIZE; i++){
            printf ("%.2lf ", arr[i]);
        }
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Вычисляем затраченное процессорное время
    printf("Количество тактов: %ld\n", end - start);
    return 0;
}

