#include "stdio.h"
#include <algorithm>
#include <time.h>

void insertionSort(double* mas, int size) {
	int i, j;
	for (i = 1; i < size; i++) {
		for (j = i; j > 0 && mas[j] < mas[j - 1]; j--) {
			std::swap(mas[j], mas[j - 1]);
		}
	}
	return;
}

void combSort(double* mas, int size) {
	int step, j;
	double factor;
	step = size - 1;
	factor = 1.2473309;
	while (step >= 1) {
		for (j = 0; j < size - step; j++) {
			if (mas[j] > mas[j + step]) {
				std::swap(mas[j], mas[j + step]);
			}
		}
		step = step / factor;
	}
	return;
}

void merge(double* masa, double* masb, double* res, int sizea, int sizeb) {
	int i, j, r;
	i = 0;
	j = 0;
	r = 0;
	while (sizea > i && sizeb > j)
	{
		if (masa[i] < masb[j]) {
			res[r++] = masa[i++];
		}
		else {
			res[r++] = masb[j++];
		}

	}
	for (; i < sizea; i++) {
		res[r++] = masa[i];
	}
	for (; j < sizeb; j++) {
		res[r++] = masb[j];
	}
	return;
}

void mergeSort(double* mas, int size) {
	double* tmpdata;
	int step, i, count;
	tmpdata = (double*)malloc(size * sizeof(double));
	step = 1;
	count = 0;
	for (; step < size; step *= 2) {
		for (i = 0; i < size; i += 2 * step) {
			merge(mas + i, mas + i + step, tmpdata + i, std::max(0, std::min(step, size - i)), std::max(0, std::min(step, size - step - i)));
		}
		std::swap(mas, tmpdata);
		count++;
	}
	if (count % 2 == 1)
	{
		std::swap(mas, tmpdata);
		for (i = 0; i < size; i++) mas[i] = tmpdata[i];
	}
	free(tmpdata);
	return;
}

void foffset(unsigned char* mas, int size, int offset, int count[257]) {
	int i;
	for (i = 0; i < 257; i++) {
		count[i] = 0;
	}
	for (i = 0; i < size; i++) {
		count[1 + mas[offset + i * sizeof(double)]]++;
	}
	for (i = 0; i < 256; i++) {
		count[i + 1] += count[i];
	}
	return;
}

void lsdSort(double* mas, int size) {
	int count[257];
	double* tmpdata;
	unsigned char* pm;
	int i, j;
	pm = (unsigned char*)mas;
	tmpdata = (double*)malloc(size * sizeof(double));
	for (i = 0; i < sizeof(double); i++) {
		foffset(pm, size, i, count);
		for (j = 0; j < size; j++) {
			tmpdata[count[pm[j * sizeof(double) + i]]++] = mas[j];
		}
		for (j = 0; j < size; j++) {
			mas[j] = tmpdata[j];
		}
	}
	j = size - 1;
	i = 0;
	while (tmpdata[j] < 0) mas[i++] = tmpdata[j--];
	j = 0;
	while (tmpdata[j] > 0) mas[i++] = tmpdata[j++];
	free(tmpdata);
	return;
}

void printMas(double* mas, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%f ", mas[i]);
	}
	printf("\n");
	return;
}

void rmf(double* mas, int size, int left, int right) {
	int i;
	for (i = 0; i < size; i++) {
		mas[i] = (left + ((double)rand() / RAND_MAX) * abs(left - right));
	}
	return;
}

void copyData(double* mas1, double* mas2, int size) {
	int i;
	for (i = 0; i < size; i++) {
		mas1[i] = mas2[i];
	}
	return;
}

int comp(const void* a, const void* b) {
	float it1, it2;
	it1 = *(const double*)a;
	it2 = *(const double*)b;
	if (it1 < it2) return -1;
	if (it1 > it2) return 1;
	return 0;
}

bool check(double* mas, double* initmas, int size) {
	int i;
	qsort(initmas, size, sizeof(double), comp);
	for (i = 0; i < size; i++)
		if (mas[i] != initmas[i]) {
			return false;
		}
	return true;
}

int main() {
	int size, i;
	clock_t start, end;
	double* mas;
	double* tmpdata;
	double seconds;

	scanf_s("%i", &size);

	mas = (double*)malloc(size * sizeof(double));
	tmpdata = (double*)malloc(size * sizeof(double));
	if (mas == NULL || tmpdata == NULL) {
		printf_s("program failed\n");
		return 0;
	}

	srand(time(NULL));
	rmf(mas, size, -1000, 1000);
	copyData(tmpdata, mas, size);
	printf_s("initial mas\n");
	printMas(mas, size);

	start = clock();
	insertionSort(mas, size);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	if (check(mas, tmpdata, size) == 0) {
		printf_s("insertion sort failed\n");
	}
	else printf_s("insertion sort - %f\n", seconds);
	printMas(mas, size);
	copyData(mas, tmpdata, size);

	start = clock();
	combSort(mas, size);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	if (check(mas, tmpdata, size) == 0) {
		printf_s("comb sort failed\n");
	}
	else printf_s("comb sort - %f\n", seconds);
	printMas(mas, size);
	copyData(mas, tmpdata, size);

	start = clock();
	mergeSort(mas, size);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	if (check(mas, tmpdata, size) == 0) {
		printf_s("merge sort failed\n");
	}
	else printf_s("merge sort - %f\n", seconds);
	printMas(mas, size);
	copyData(mas, tmpdata, size);

	start = clock();
	lsdSort(mas, size);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	if (check(mas, tmpdata, size) == 0) {
		printf_s("lsd sort failed\n");
	}
	else printf_s("lsd sort - %f\n", seconds);
	printMas(mas, size);

	return 0;
}
