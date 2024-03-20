#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10
#define range 100

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

void combsort( double* arr, int step) {
step = size - 1;
float factor = 1.2473;
double tmp = 0;
while (step >= 1){
    for (int j = 0; j < size - step; j++) {
        if ( arr[j] > arr[j+step]){
            tmp = arr[j];
            arr[j] = arr[j+step];
            arr[j+step] = tmp;
            }
        }
    step = step / factor;
    }
}

int main () {
    clock_t start, end;
    double cpu_time_used;
    double arr[size];
    int i;
    srand(time(0));
    for ( i = 0; i < size; i++) {
        arr[i] = (double)(rand() % range);
    }
    printf ( "массив\n");
    for ( i = 0; i < size; i++)
        printf( "%.2lf ", arr[i]);
    printf ("\nотсортированный массив\n");
    start = clock();
    combsort ( arr, size);
    end = clock();
    for (int i = 0; i < size; i++) {
        printf("%.2lf ", arr[i]);
    }
    qsort(arr, size, sizeof(int), compare);
        printf("\nготовый массив \n");
        for (i = 0; i < size; i++){
            printf ("%.2lf ", arr[i]);
        }
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Вычисляем затраченное процессорное время
    printf("Количество тактов: %ld\n", end - start);
    return 0;
}
