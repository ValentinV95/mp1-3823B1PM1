<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#pragma intrinsic (__rdtsc)
#define min(i, j) (((i)<(j))?(i):(j))
#define max(i, j) (((i)>(j))?(i):(j))
void swaplf(double* a, double* b);
void swapp(double** a, double** b);
void det_arrlf(double* array, long long int size);
void equalize_arrlf(double* source, double* assigned, long long int size);
void print_arrlf(double* array, long long int size);
int comparelf(const void*, const void*);
void sort_cocktail_arrlf(double* array, long long int size);
void sort_quick_arrlf(double* array, long long int start, long long int finish);
void partition(double* array, long long int* left, long long int* right);
void sort_merge_arrlf(double* array, long long int size);
void merge_arrlf(double* source1, double* source2, double* assigned, long long int size1, long long int size2);
void sort_radix_backward_LSD_arrlf(double* array, long long int size);
void foffset(unsigned char* arrayuc, long long int size, int digit, int count[256]);
int main()
{
	double* main_arr, * sorted_arr, d;
	long long int n=0;
	unsigned long long int i, j, k;
	int c, f = 0, x = 1;
	while(x)
	{
		printf("Choose size of array: ");
		do
			scanf_s("%lld", &n);
		while (n <= 0);
		main_arr = (double*)malloc(n * sizeof(double));
		sorted_arr = (double*)malloc(n * sizeof(double));
		if ((main_arr == 0) || (sorted_arr == 0))
		{
			free(main_arr);
			free(sorted_arr);
			printf("Memory error!\n");
			return 0;
		}
		det_arrlf(main_arr, n);
		equalize_arrlf(main_arr, sorted_arr, n);
		printf("Do you want to see generated array? Yes - 1; No - 0\n");
		do
		{
			scanf_s("%d", &c);
		} while ((c != 0) && (c != 1));
		if (c)
		{
			printf("Generated array:\n");
			print_arrlf(main_arr, n);
		}
		c = 0;
		printf("\nChoose sorting algorythm:\n1 - bubble sort;\n2 - quick sort;\n3 - merge sort;\n4 - radix sort\n");
		do
			scanf_s("%d", &c);
		while ((c > 4) && (c < 1));
		//Sorting massive
		{
			j = (__rdtsc());
			if (c == 1)
				sort_cocktail_arrlf(sorted_arr, n);
			else if (c == 2)
				sort_quick_arrlf(sorted_arr, 0, n - 1);
			else if (c == 3)
				sort_merge_arrlf(sorted_arr, n);
			else if (c == 4)
				sort_radix_backward_LSD_arrlf(sorted_arr, n);
			k = (__rdtsc());
		}
		qsort((void*)main_arr, n, sizeof(double), comparelf);
		//Checking array
		{
			for (i = 0; i < n; i++)
			{
				if (main_arr[i] != sorted_arr[i])
				{
					f = 1;
					break;
				}
			}
			if (f == 0)
				printf("Everything is fine\n");
			else
			{
				printf("Sort was FU\n");
				printf("\n%llu\n", i);
			}
			printf("Sorting time: %llu ticks\n", (k - j));
		}
		printf("Do you want to see sorted array? Yes - 1; No - 0\n");
		do
			scanf_s("%d", &c);
		while ((c != 0) && (c != 1));
		if (c)
		{
			printf("Sorted array:\n");
			print_arrlf(sorted_arr, n);
		}
		printf("Do you want to restart? Yes - 1; No - 0\n");
		do
			scanf_s("%d", &x);
		while ((x != 0) && (x != 1));
		free(main_arr);
		free(sorted_arr);
	}
	return 0;
}
void swaplf(double* p1, double* p2)
{
	double tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	return;
}
void swapp(double** p1, double** p2)
{
	double* p3;
	p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
	return;
}
void det_arrlf(double* arr, long long int n)
{
	long long int i;
	for (i = 0; i < n; i++)
	{
		arr[i] = -1000. + (double)rand() / ((double)RAND_MAX / 2000.);
	}
	return;
}
void equalize_arrlf(double* arr1, double* arr2, long long int n)
{
	long long int i;
	for (i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	return;
}
void print_arrlf(double* arr, long long int n)
{
	long long int i;
	for (i = 0; i < n; i++)
	{
		printf("%.3f   ", arr[i]);
		if ((i % 10) == 9)
			printf("\n");
	}
	printf("\n\n");
	return;
}
int comparelf(const void* var1, const void* var2)
{
	double a, b;
	a = *(double*)var1;
	b = *(double*)var2;
	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else return 0;
}
void sort_cocktail_arrlf(double* arr, long long int n)
{
	long long int i, left = 0, right = n - 1, control = 0;
	while (left != right)
	{
		for (i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swaplf((arr + i), (arr + i + 1));
				control = i;
			}
		}
		right = control;
		for (i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				swaplf((arr + i), (arr + i - 1));
				control = i;
			}
		}
		left = control;
	}
	return;
}
void sort_quick_arrlf(double* arr, long long int s, long long int f)
{
	long long int i = s, j = f;
	{
		partition(arr, &i, &j);
		if ((j - s) > 0)
			sort_quick_arrlf(arr, s, j);
		if ((f - i) > 0)
			sort_quick_arrlf(arr, i, f);
	}
	return;
}
void partition(double* arr, long long int* s, long long int* f)
{
	double a = arr[*s + rand() % (*f - *s + 1)];
	while (*s <= *f)
	{
		while (arr[*s] < a)
			(*s)++;
		while (arr[*f] > a)
			(*f)--;
		if (*s <= *f)
		{
			swaplf((arr + *s), (arr + *f));
			(*s)++;
			(*f)--;
		}
	}
	return;
}
void sort_merge_arrlf(double* arr, long long int n)
{
	double* tmp_arr;
	long long int step, i;
	int f = 0;
	tmp_arr = (double*)malloc(n * sizeof(double));
	if (tmp_arr == 0)
	{
		printf("Memory error! SM");
		exit(0);
	}
	for (step = 1; step < n; step *= 2)
	{
		for (i = 0; i < n; i += 2 * step)
			merge_arrlf(arr + i, arr + i + step, tmp_arr + i, min(step, n - i), max(0, min(step, n - step - i)));
		swapp(&arr, &tmp_arr);
		f = 1 - f;
	}
	if (f)
	{
		equalize_arrlf(arr, tmp_arr, n);
		swapp(&arr, &tmp_arr);
	}
	free(tmp_arr);
	return;
}
void merge_arrlf(double* m1, double* m2, double* m3, long long int n1, long long int n2)
{
	long long int i, j, k;
	for (k = 0, i = 0, j = 0; k < n1 + n2; k++)
	{
		if (i == n1)
			m3[k] = m2[j++];
		else if (j == n2)
			m3[k] = m1[i++];
		else
		{
			if ((m1[i]) < m2[j])
				m3[k] = m1[i++];
			else m3[k] = m2[j++];
		}
	}
	return;
}
void sort_radix_backward_LSD_arrlf(double* arr, long long int n)
{
	unsigned char* pm = (unsigned char*)arr;
	int count[256], i, j, sgnp;
	double* arr2 = (double*)malloc(n * sizeof(double));
	if (arr2 == 0)
	{
		printf("Memory error! SR");
		exit(0);
	}
	for (i = 0; i < sizeof(double); i++)
	{
		foffset(pm, n, i, count);
		for (j = n - 1; j >= 0; j--)
			arr2[count[pm[j * sizeof(double) + i]]--] = arr[j];
		swapp(&arr2, &arr);
		pm = (unsigned char*)arr;
	}
	if (arr[n - 1] < 0)
	{
		i = 0, j = n - 1;
		while ((j - i) > 1)
		{
			sgnp = (j + i) / 2;
			if (arr[sgnp] >= +0)
				i = sgnp;
			else
				j = sgnp;
		}
		if (arr[sgnp] >= +0)
			sgnp += 1;
	}
	equalize_arrlf(arr, arr2, sgnp);
	for (i = sgnp; i < n; i++)
		arr2[i] = arr[n - i + sgnp - 1];
	equalize_arrlf(arr2 + sgnp, arr, n - sgnp);
	equalize_arrlf(arr2, arr + (n - sgnp), sgnp);
	free(arr2);
	return;
}
void foffset(unsigned char* arr, long long int n, int digit, int count[256])
{
	int i;
	for (i = 0; i < 256; i++)
	{
		count[i] = 0;
	}
	for (i = 0; i < n; i++)
		count[arr[digit + i * sizeof(double)]]++;
	count[0] -= 1;
	for (i = 1; i < 256; i++)
		count[i] += count[i - 1];
=======
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#pragma intrinsic (__rdtsc)
#define min(i, j) (((i)<(j))?(i):(j))
#define max(i, j) (((i)>(j))?(i):(j))
void swaplf(double* a, double* b);
void swapp(double** a, double** b);
void det_arrlf(double* array, long long int size);
void equalize_arrlf(double* source, double* assigned, long long int size);
void print_arrlf(double* array, long long int size);
int comparelf(const void*, const void*);
void sort_cocktail_arrlf(double* array, long long int size);
void sort_quick_arrlf(double* array, long long int start, long long int finish);
void partition(double* array, long long int* left, long long int* right);
void sort_merge_arrlf(double* array, long long int size);
void merge_arrlf(double* source1, double* source2, double* assigned, long long int size1, long long int size2);
void sort_radix_backward_LSD_arrlf(double* array, long long int size);
void foffset(unsigned char* arrayuc, long long int size, int digit, int count[256]);
int main()
{
	double* main_arr, * sorted_arr, d;
	long long int n=0;
	unsigned long long int i, j, k;
	int c, f = 0, x = 1;
	while(x)
	{
		printf("Choose size of array: ");
		do
			scanf_s("%lld", &n);
		while (n <= 0);
		main_arr = (double*)malloc(n * sizeof(double));
		sorted_arr = (double*)malloc(n * sizeof(double));
		if ((main_arr == 0) || (sorted_arr == 0))
		{
			free(main_arr);
			free(sorted_arr);
			printf("Memory error!\n");
			return 0;
		}
		det_arrlf(main_arr, n);
		equalize_arrlf(main_arr, sorted_arr, n);
		printf("Do you want to see generated array? Yes - 1; No - 0\n");
		do
		{
			scanf_s("%d", &c);
		} while ((c != 0) && (c != 1));
		if (c)
		{
			printf("Generated array:\n");
			print_arrlf(main_arr, n);
		}
		c = 0;
		printf("\nChoose sorting algorythm:\n1 - bubble sort;\n2 - quick sort;\n3 - merge sort;\n4 - radix sort\n");
		do
			scanf_s("%d", &c);
		while ((c > 4) && (c < 1));
		//Sorting massive
		{
			j = (__rdtsc());
			if (c == 1)
				sort_cocktail_arrlf(sorted_arr, n);
			else if (c == 2)
				sort_quick_arrlf(sorted_arr, 0, n - 1);
			else if (c == 3)
				sort_merge_arrlf(sorted_arr, n);
			else if (c == 4)
				sort_radix_backward_LSD_arrlf(sorted_arr, n);
			k = (__rdtsc());
		}
		qsort((void*)main_arr, n, sizeof(double), comparelf);
		//Checking array
		{
			for (i = 0; i < n; i++)
			{
				if (main_arr[i] != sorted_arr[i])
				{
					f = 1;
					break;
				}
			}
			if (f == 0)
				printf("Everything is fine\n");
			else
			{
				printf("Sort was FU\n");
				printf("\n%llu\n", i);
			}
			printf("Sorting time: %llu ticks\n", (k - j));
		}
		printf("Do you want to see sorted array? Yes - 1; No - 0\n");
		do
			scanf_s("%d", &c);
		while ((c != 0) && (c != 1));
		if (c)
		{
			printf("Sorted array:\n");
			print_arrlf(sorted_arr, n);
		}
		printf("Do you want to restart? Yes - 1; No - 0\n");
		do
			scanf_s("%d", &x);
		while ((x != 0) && (x != 1));
		free(main_arr);
		free(sorted_arr);
	}
	return 0;
}
void swaplf(double* p1, double* p2)
{
	double tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	return;
}
void swapp(double** p1, double** p2)
{
	double* p3;
	p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
	return;
}
void det_arrlf(double* arr, long long int n)
{
	long long int i;
	for (i = 0; i < n; i++)
	{
		arr[i] = -1000. + (double)rand() / ((double)RAND_MAX / 2000.);
	}
	return;
}
void equalize_arrlf(double* arr1, double* arr2, long long int n)
{
	long long int i;
	for (i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	return;
}
void print_arrlf(double* arr, long long int n)
{
	long long int i;
	for (i = 0; i < n; i++)
	{
		printf("%.3f   ", arr[i]);
		if ((i % 10) == 9)
			printf("\n");
	}
	printf("\n\n");
	return;
}
int comparelf(const void* var1, const void* var2)
{
	double a, b;
	a = *(double*)var1;
	b = *(double*)var2;
	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else return 0;
}
void sort_cocktail_arrlf(double* arr, long long int n)
{
	long long int i, left = 0, right = n - 1, control = 0;
	while (left != right)
	{
		for (i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swaplf((arr + i), (arr + i + 1));
				control = i;
			}
		}
		right = control;
		for (i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				swaplf((arr + i), (arr + i - 1));
				control = i;
			}
		}
		left = control;
	}
	return;
}
void sort_quick_arrlf(double* arr, long long int s, long long int f)
{
	long long int i = s, j = f;
	{
		partition(arr, &i, &j);
		if ((j - s) > 0)
			sort_quick_arrlf(arr, s, j);
		if ((f - i) > 0)
			sort_quick_arrlf(arr, i, f);
	}
	return;
}
void partition(double* arr, long long int* s, long long int* f)
{
	double a = arr[*s + rand() % (*f - *s + 1)];
	while (*s <= *f)
	{
		while (arr[*s] < a)
			(*s)++;
		while (arr[*f] > a)
			(*f)--;
		if (*s <= *f)
		{
			swaplf((arr + *s), (arr + *f));
			(*s)++;
			(*f)--;
		}
	}
	return;
}
void sort_merge_arrlf(double* arr, long long int n)
{
	double* tmp_arr;
	long long int step, i;
	int f = 0;
	tmp_arr = (double*)malloc(n * sizeof(double));
	if (tmp_arr == 0)
	{
		printf("Memory error! SM");
		exit(0);
	}
	for (step = 1; step < n; step *= 2)
	{
		for (i = 0; i < n; i += 2 * step)
			merge_arrlf(arr + i, arr + i + step, tmp_arr + i, min(step, n - i), max(0, min(step, n - step - i)));
		swapp(&arr, &tmp_arr);
		f = 1 - f;
	}
	if (f)
	{
		equalize_arrlf(arr, tmp_arr, n);
		swapp(&arr, &tmp_arr);
	}
	free(tmp_arr);
	return;
}
void merge_arrlf(double* m1, double* m2, double* m3, long long int n1, long long int n2)
{
	long long int i, j, k;
	for (k = 0, i = 0, j = 0; k < n1 + n2; k++)
	{
		if (i == n1)
			m3[k] = m2[j++];
		else if (j == n2)
			m3[k] = m1[i++];
		else
		{
			if ((m1[i]) < m2[j])
				m3[k] = m1[i++];
			else m3[k] = m2[j++];
		}
	}
	return;
}
void sort_radix_backward_LSD_arrlf(double* arr, long long int n)
{
	unsigned char* pm = (unsigned char*)arr;
	int count[256], i, j, sgnp;
	double* arr2 = (double*)malloc(n * sizeof(double));
	if (arr2 == 0)
	{
		printf("Memory error! SR");
		exit(0);
	}
	for (i = 0; i < sizeof(double); i++)
	{
		foffset(pm, n, i, count);
		for (j = n - 1; j >= 0; j--)
			arr2[count[pm[j * sizeof(double) + i]]--] = arr[j];
		swapp(&arr2, &arr);
		pm = (unsigned char*)arr;
	}
	if (arr[n - 1] < 0)
	{
		i = 0, j = n - 1;
		while ((j - i) > 1)
		{
			sgnp = (j + i) / 2;
			if (arr[sgnp] >= +0)
				i = sgnp;
			else
				j = sgnp;
		}
		if (arr[sgnp] >= +0)
			sgnp += 1;
	}
	equalize_arrlf(arr, arr2, sgnp);
	for (i = sgnp; i < n; i++)
		arr2[i] = arr[n - i + sgnp - 1];
	equalize_arrlf(arr2 + sgnp, arr, n - sgnp);
	equalize_arrlf(arr2, arr + (n - sgnp), sgnp);
	free(arr2);
	return;
}
void foffset(unsigned char* arr, long long int n, int digit, int count[256])
{
	int i;
	for (i = 0; i < 256; i++)
	{
		count[i] = 0;
	}
	for (i = 0; i < n; i++)
		count[arr[digit + i * sizeof(double)]]++;
	count[0] -= 1;
	for (i = 1; i < 256; i++)
		count[i] += count[i - 1];
>>>>>>> a1f503fe4edba25dc7b07b2f74a50060259ebdf8
}