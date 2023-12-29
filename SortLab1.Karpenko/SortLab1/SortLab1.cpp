
#include "stdio.h"
#include "math.h"
#include "time.h"
#include "stdlib.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}


void InputArray(int* mas, int size) {
	int i = 0;
	for (int i = 0;i < size;i++) {
		printf("%d ", mas[i]);
		if (i == size - 1) {
			printf("\n");
		}
	}
}

void InputArrayD(double* mas, int size) {
	int i = 0;
	for (int i = 0;i < size;i++) {
		printf("%f ", mas[i]);
		if (i == size - 1) {
			printf("\n");
		}
	}
}


void swap(int* ptr1, int* ptr2) {
	int temp;
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

void swap_p(int** a, int** b) {
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}


void sorting_check(int* mas, int size) {
	int i = 0;
	int flag = 1;
	for (int i = 0;i < size - 1;i++) {
		if (mas[i] > mas[i + 1]) {
			flag = 0;
			break;
		}
	}
	if (flag == 1) {
		printf("Correct sort");
	}
	else {
		printf("error in sorting");
	}
}

void sorting_checkD(double* mas, int size) {
	int i = 0;
	int flag = 1;
	for (int i = 0;i < size - 1;i++) {
		if (mas[i] > mas[i + 1]) {
			flag = 0;
			break;
		}
	}
	if (flag == 1) {
		printf("Correct sort");
	}
	else {
		printf("error in sorting");
	}
}





int partition(int* mas, int s, int f) {
	float a = mas[s + rand() % (f - s + 1)];
	f--;
	while (s < f) {
		while (mas[s] < a)   s++;
		while (mas[f] > a)   f--;
		if (s < f) {
			swap((mas + s), (mas + f));
			s++;
			f--;
		}
	}
	return s;
}
void qsort(int s, int f, int* mas) {
	int p;
	if ((f - s) < 2) {
		return;
	}
	p = partition(mas, s, f);

	qsort(s, p, mas);

	qsort(p, f, mas);

	return;
}




void insertion(int* mas, int size) {
	int i, j;
	for (i = 0; i < size - 1; i++) {
		j = i + 1;
		while (j > 0 && mas[j - 1] > mas[j]) {
			swap(&mas[j - 1], &mas[j]);
			j--;
		}
	}
}


void RandGeneration(int* mas, int size, int upp_border, int low_border) {
	int i = 0;
	for (int i = 0;i < size;i++) {
		mas[i] = (low_border + rand() % (upp_border - low_border + 1));
	}
}

void RandGenerationD(double* mas, int size, int upp_border, int low_border) {
	int i = 0;
	for (int i = 0;i < size;i++) {
		mas[i] = (low_border + rand() % (upp_border - low_border + 1));
	}
}


void merge(int* a, int* b, int* data, int an, int bn) {
	int ai = 0;
	int bi = 0;
	int di = 0;

	while (ai < an && bi < bn) { //an,bn - размеры
		if (a[ai] < b[bi]) {
			data[di++] = a[ai++];
		}
		else {
			data[di++] = b[bi++];
		}
	}
	for (; ai < an; ai++) {
		data[di++] = a[ai];
	}
	for (; bi < bn; bi++) {
		data[di++] = b[bi];
	}
}

void mergesort(int* m, int size) {
	int counter = 0;
	int step;
	int i;
	int* tmpdata = (int*)malloc(size * sizeof(int));
	for (step = 1; step < size; step *= 2) {
		for (i = 0; i < size; i += 2 * step) {
			merge(&m[i], &m[i + step], &tmpdata[i], max(0, min(step, size - i)), max(0, min(step, size - step - i)));
		}
		swap_p(&m, &tmpdata);
		counter++;
	}
	if ((counter % 2) != 0) {
		swap_p(&m, &tmpdata);
	}
	free(tmpdata);
}




void foffset(unsigned char* mas, int size, int offset, int count[257]) {
	int i = 0;
	int tmp;
	for (i = 0; i < 257; count[i++] = 0) {};
	for (i = 0; i < size; i++) {
		count[mas[offset + i * sizeof(double)]]++;
	}
	tmp = count[0];
	count[0] = 0;
	for (i = 0; i < 256; i++) {
		swap(&tmp, &count[i + 1]);
		count[i + 1] += count[i];
	}
}

void radix_sort(double* mas, int size) {
	unsigned char* pm = (unsigned char*)mas;
	int count[257];
	int i = 0, j = 0;
	double* mas2 = (double*)malloc(size * sizeof(double));
	for (; i < sizeof(double); i++) {
		foffset(pm, size, i, count);
		for (j = 0; j < size; j++) {
			mas2[count[pm[j * sizeof(double) + i]]++] = mas[j];
		}
		double* tempp;
		tempp = mas;
		mas = mas2;
		mas2 = tempp;
		pm = (unsigned char*)mas;
	}
	free(mas2);
}




int main() {
	int* mas;
	double* masD; //массива типа double для radix sort
	int q;
	int size;
	int upp_b, low_b;
	time_t start, finish;



	printf("Choose the way to sort the array\n");
	printf("Enter '1' - merge sort\nEnter '2' - radix sort for double array\nEnter '3' - insertion sort\nEnter '4' - quick sort\n");
	scanf_s("%d", &q);
	printf("specify size of array: ");
	scanf_s("%d", &size);

	mas = (int*)malloc(size * sizeof(int)); // выделение памяти для массива 
	masD = (double*)malloc(size * sizeof(double)); // выделение памяти для массива типа double

	printf("specify the upper limit of the array: ");
	scanf_s("%d", &upp_b);
	printf("specify the lower boundary of the array: ");
	scanf_s("%d", &low_b);


	if (q == 2) {
		RandGenerationD(masD, size, upp_b, low_b); // заполнение массива произвольными элементами
	}
	else {
		RandGeneration(mas, size, upp_b, low_b);
	}


	if (q == 1) {
		q = 0;
		start = time(NULL);
		mergesort(mas, size);
		finish = time(NULL);
		printf("%d second(s) to sort\n", finish - start);
		printf("Enter '1' to check that the sorting is correct: ");
		scanf_s("%d", &q);
		if (q == 1) {
			sorting_check(mas, size);
		}
	}
	else if (q == 2) {
		q = 0;
		start = time(NULL);
		radix_sort(masD, size);
		finish = time(NULL);
		printf("%d second(s) to sort\n", finish - start);
		printf("Enter '1' to check that the sorting is correct: ");
		scanf_s("%d", &q);
		if (q == 1) {
			sorting_checkD(masD, size);
		}
	}
	else if (q == 3) {
		q = 0;
		start = time(NULL);
		insertion(mas, size);
		finish = time(NULL);
		printf("%d second(s) to sort\n", finish - start);
		printf("Enter '1' to check that the sorting is correct: ");
		scanf_s("%d", &q);
		if (q == 1) {
			sorting_check(mas, size);
		}
	}
	else if (q == 4) {
		q = 0;
		start = time(NULL);
		qsort(0, size, mas);
		finish = time(NULL);
		printf("%d second(s) to sort\n", finish - start);
		printf("Enter '1' to check that the sorting is correct: ");
		scanf_s("%d", &q);
		if (q == 1) {
			sorting_check(mas, size);
		}
	}

	else {
		printf("wrong input");
	}

	return 0;
}