#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 500
#define range 100

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}
int main(){
    clock_t start, end;
    double cpu_time_used;
    double arr[size];
    int i, j, p=0;
    srand(time(0));
    for (i = 0; i < size; i++){
        arr[i]=(double)(rand()%range);
    }
    printf("массив \n");
    for (i = 0; i < size; i++){
        printf("%.2lf ", arr[i]);
    }
    start = clock();
    for (j = 0; j < size - 1; j++){
        for (i = 0; i < size - j - 1; i++){
            if (arr[i]>arr[i+1]){
                p = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = p;
            }
        }
    }
    end = clock();
    printf("\nОтсортированый массив \n");
    for (i = 0; i < size; i++){
        printf ("%.2lf ", arr[i]);
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

