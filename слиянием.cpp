#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 1000
#define range 100

int compare(const void *a, const void *b){
    return (*(double*)a - *(double*)b);
}
void _mergesort(double* m, int left, int right);
int main(){
    clock_t start, end;
    double cpu_time_used;
    double arr[SIZE];
    for (int i = 0; i < SIZE; i++){
        arr[i] = (double)(rand()%range);
    }
    printf("массив \n");
    int n = SIZE;
    for (int i = 0; i < n; i++){
        printf("%.2lf ", arr[i]);
    }
    start = clock();
    _mergesort (arr, 0, n);
    end = clock();
    printf("\nотсортированный массив \n");
    for (int i = 0; i < n; i++) {
        printf("%.2lf ", arr[i]);
    }
    qsort(arr, SIZE, sizeof(double), compare);
        
        printf("\nготовый массив \n");
        for (int i = 0; i < SIZE; i++){
            printf ("%.2lf ", arr[i]);
        }
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Вычисляем затраченное процессорное время
    printf("Количество тактов: %ld\n", end - start);
    return 0;
}

void _mergesort(double* m, int left, int right){
    int middle = left + ( right - left ) / 2; //Здесь вычисляется середина сортируемой части массива и объявляются переменные ai, bi и di. Переменная middle равна индексу, соответствующему середине массива. Переменные ai и bi будут использоваться в цикле слияния для отслеживания текущих индексов в левой и правой половинах массива, соответственно. Переменная di будет использоваться для отслеживания текущего индекса нового временного массива.
    int ai = left, bi = middle, di = 0;
    if (left + 2 < right) { //Это условие позволяет выполнить рекурсивные вызовы _mergesort, если размер сортируемой части массива больше 2 элементов. Рекурсивные вызовы осуществляются для левой и правой половин массива.
        _mergesort(m, left, middle);
        _mergesort(m, middle, right);
    }
    double* tmp = (double*)malloc((right - left) * sizeof(double)); //Здесь выделяется память для нового временного массива tmp, который будет использоваться для объединения отсортированных половин массива.
    while (ai < middle && bi < right) { //Это цикл слияния. Он выполняет сравнение элементов из левой и правой половин массива и записывает их в tmp в порядке возрастания. Переменные ai и bi увеличиваются каждый раз, когда элементы записываются в tmp. Переменная di отслеживает текущий индекс в tmp.
        if (m[ai] < m[bi])
            tmp[di++] = m[ai++];
        else
            tmp[di++] = m[bi++];
    }
    //Эти два цикла заполняют tmp оставшимися элементами из левой и правой половин массива, если одна из половин закончилась и вторая содержит оставшиеся элементы.
    for (; ai < middle; ai++)
        tmp[di++] = m[ai];
    for (; bi < right; bi++)
        tmp[di++] = m[bi];
    memcpy(m+left, tmp, (right - left) * sizeof(double)); //Здесь выполняется копирование элементов из временного массива tmp обратно в исходный массив m с помощью функции memcpy. Затем освобождается память, выделенная для временного массива.
    free(tmp);
    
}

