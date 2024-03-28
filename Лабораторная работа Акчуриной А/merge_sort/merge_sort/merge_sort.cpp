#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void merge(double* arr, double* arr_new, int left, int middle, int right);
void mergeSort(double* arr, double* arr_new, int left, int right);
int cmp(const void* a, const void* b);
void verification(double arr[], double mas[], int size);

int main()
{
	int i, size, ans, k;
	printf("What is the size of the array?\n");
	scanf_s("%d", &size);
	printf("independent input - 1, filling in with the program - 2\n");
	scanf_s("%d", &ans);

	int left = 0, right = size;
	double* arr_new = (double*)malloc(size * sizeof(double));
	double* arr = (double*)malloc(size * sizeof(double));
	double* mas = (double*)malloc(size * sizeof(double));

    if (ans == 2) {
		srand(time(NULL));

		for (i = 0; i < size; i++) {
			arr[i] = rand();

		}
	}
	else {
		for (i = 0; i < size; i++)
			scanf_s("%lf", &arr[i]);
	}
	
	for (i = 0; i < size; i++) {
		mas[i] = arr[i];
	}
	clock_t start = clock();
	mergeSort(arr, arr_new, left, right);
	clock_t end = clock();
	for (int i = 0; i < size; i++)
		printf("%lf\n", arr[i]);
	printf("\n");
	verification(arr, mas, size);
	double time_taken = (double(end - start)) / CLOCKS_PER_SEC;
	printf("\nTime_taken: %f seconds\n", time_taken);
	return 0;
}
void mergeSort(double* arr, double* arr_new, int left, int right) {
	int  middle = (left + right) / 2;
	if (right - left == 1) return;
	mergeSort(arr, arr_new, left, middle);
	mergeSort(arr, arr_new, middle, right);
	merge(arr, arr_new, left, middle, right);
}

void merge(double* arr, double* arr_new, int left, int middle, int right) {
	double* p1 = &arr[left], * p2 = &arr[middle], * p3 = &arr_new[left];
	while ((p1 < &arr[middle]) && (p2 < &arr[right])) {
		if (*p1 <= *p2) {
			*p3 = *p1;
			p3++;
			p1++;
		}
		else {
			*p3 = *p2;
			p3++;
			p2++;
		}
	}
	while (p1 < &arr[middle]) {
		*p3 = *p1;
		p3++;
		p1++;
	}
	while (p2 < &arr[right]) {
		*p3 = *p2;
		p3++;
		p2++;
	}
	for (int i = left; i < right; i++) arr[i] = arr_new[i];
}
int cmp(const void* a, const void* b) {
	return *(double*)a - *(double*)b;
}


void verification(double arr[], double mas[], int size) {// функция сравнения сортировки с qsort
	qsort(mas, size, sizeof(double), cmp);
	bool flag = true;
	for (int i = 0; i < size; i++) {
		if (mas[i] != arr[i]) {
			flag = false;
			printf("Error ");
			break;
		}
	}
	if (flag) printf("Not error ");
}
