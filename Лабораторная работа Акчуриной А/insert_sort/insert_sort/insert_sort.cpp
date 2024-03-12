#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void insert_sort(double* mas, int size);
int cmp(const void* mas, const void* mas_new);
void verification(double mas[], double mas_new[], int size);

int main(int size, int i) {
	int ans = 0;
	
	printf("What is the size of the array?\n");
	scanf_s("%d", &size);
	printf("independent input - 1, filling in with the program - 2\n");
	scanf_s("%d", &ans);
	double* mas = (double*)malloc(size * sizeof(double));
	double* mas_new = (double*)malloc(size * sizeof(double));

	if (ans == 2) {
		srand(time(NULL));
		
		for (i = 0; i < size; i++) {
			mas[i] = rand();

		}
	}
	else {
		for(i = 0; i < size; i++)
		scanf_s("%lf", &mas[i]);
	}
	for (i = 0; i < size; i++) {
		mas_new[i] = mas[i];
	}
	clock_t start = clock();
	insert_sort(mas, size);
	clock_t end = clock();
	for (int i = 0; i < size; i++)
		printf("%lf\n", mas[i]);
	printf("\n");
	verification(mas, mas_new, size);
	printf("\n");
	double time_taken = (double(end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken: %f second\n", time_taken);
	return 0;
}
void insert_sort(double* mas, int size) {
	int j, i;
	double tmp;
	for (i = 1; i < size; i++) {
		tmp = mas[i];
		for (j = i - 1; j >= 0 && mas[j] > tmp; j--) {
			mas[j + 1] = mas[j];
			mas[j] = tmp;
		}

	}
}
int cmp(const void* a, const void* b) {
	return *(double*)a - *(double*)b;
}


void verification(double mas[], double mas_new[], int size) {// функция сравнения сортировки с qsort
	qsort(mas_new, size, sizeof(double), cmp);
	bool flag = true;
	for (int i = 0; i < size; i++) {
		if (mas_new[i] != mas[i]) {
			flag = false;
			printf("Error ");
			break;
		}
	}
	if (flag) printf("Not error ");
}