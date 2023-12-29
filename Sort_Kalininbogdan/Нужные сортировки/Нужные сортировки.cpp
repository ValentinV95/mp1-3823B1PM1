#define _CRT_SECURE_NO_WARNINGS
#include "intrin.h"
#pragma intrinsic(__rdtsc)
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>


/*
РЕАЛИЗОВАТЬ

ПУЗЫРЁК - ок
РАСЧЕСКА - ок
СЛИЯНИЕ  - не ок
ПОРАЗРЯД - ок

ПРОВЕРКА - ок

ВРЕМЯ - ок

МЕНЮ - ок


НА ФЛОТАХ
*/


// ИНСТРУМЕНТЫ
void swap_float(float* a, float* b) {
	*(int*)a^=* (int*)b^=* (int*)a^=* (int*)b;
	
}
void swap_float_tmp(float* a, float* b) {
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void rand_array_float(float* mas, int size) {
	int i;
	for (i = 0; i < size; i++) {
		mas[i] = (rand() / (float)RAND_MAX)*2000 - 1000;
	}
	// заполняет массив случайными флотами в диапазоне [-1000; 1000]
	// заполнение равномерное
}
void copy_array_float(float* source, float* reciever, int lenght) {
	int i;
	for (i = 0; i < lenght; i++) {
		reciever[i] = source[i];
	}
}
void print_array_float(float* mas, int size) {
	int i;
	printf("[");
	for (i = 0; i < size-1; i++) {
		printf("%f, ", mas[i]);
	}
	printf("%f]\n", mas[size-1]);
}
void print_array_uint(unsigned int* mas, int size) {
	int i;
	printf("[");
	for (i = 0; i < size - 1; i++) {
		printf("%d,", mas[i]);
	}
	printf("%d]\n", mas[size-1]);
}
void null_array_int(int* mas, int size) {
	int i;
	for (i = 0; i < size; i++) {
		mas[i] = 0;
	}
	// обнуляет массив целых чисел
}
void swap_pointers_uint(unsigned int** a, unsigned int** b) {
	unsigned int* tmpptr = *a;
	*a = *b;
	*b = tmpptr;
}
void swap_pointers_float(float** a, float** b) {
	float* tmpptr;
	tmpptr = *a;
	*a = *b;
	*b = tmpptr;
}
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
int min(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

// ПРОВЕРКА
int compare_func(const void* x1, const void* x2) {
	if (*(float*)x1 < *(float*)x2) {
		return -1;
	}
	if (*(float*)x1 == *(float*)x2) {
		return 0;
	}
	return 1;
}
int check_sorted_float(float* sorted, float* orig, int n) {
	int i;
	qsort(orig, n, sizeof(float), compare_func);
	for (i = 0; i < n; i++) {
		if (orig[i] != sorted[i]) {
			return 0;
		}
	}
	return 1;
}


// ПУЗЫРЁК
void bubble_sort_float(float* mas, int size) {
	int i, j, f;
	for (i = 0; i < size - 1; i++) {
		f = 1; 
		for (j = 0; j < size - i - 1; j++) {
			if (mas[j] > mas[j + 1]) {
				swap_float(&mas[j], &mas[j + 1]);
				f = 0;
			}
		}
		if (f) {
			break;
		}
	}
}

// РАСЧЁСКА 
void comb_sort_float(float* mas, int size) {
	int step = size - 1;
	double factor = 1.0 / (1.0 - exp(-(1 + sqrt(5)) / 2.0));
	int j;

	while (step >= 1) {
		for (j = 0; j < size - step; j++) {    
			if (mas[j] > mas[j + step]) {
				swap_float(&mas[j], &mas[j + step]);
			}
		}
		step /= factor;
	}
}

// СЛИЯНИЕ
void merge(float* a, int an, float* b, int bn, float* res) {
	int ai, bi, k;
	k = 0;
	ai = 0;
	bi = 0;
	while (ai < an && bi < bn) {
		if(a[ai] < b[bi]) {
			res[k++] = a[ai++];
		}
		else {
			res[k++] = b[bi++];
		}
	}
	for (; ai < an; ai++) {
		res[k++] = a[ai];
	}
	for (; bi < bn; bi++) {
		res[k++] = b[bi];
	}
	return;
}
void merge_sort_float(float* mas, int size) {
	float* mas2;
	int i;
	int swap_count = 0;
	int step = 1;
	mas2 = (float*)malloc(size * sizeof(float));
	for (; step < 2*size; step *= 2) {
		for (i = 0; i < size; i += (2*step))
			merge(&mas[i], max(0, min(step, size - i)), &mas[i + step], max(0, min(step, size - step - i)), &mas2[i]);
		swap_pointers_float(&mas, &mas2);
		swap_count++;
	}
	
	

	if (swap_count % 2) {
		swap_pointers_float(&mas, &mas2);
	}


	free(mas2);
}

// ПОРАЗРЯДНАЯ
void offset(int count[256], unsigned char* mas, int size, int offset) {
	int i;
	null_array_int(count, 256);

	//подсчёт кол-ва элементов по значениям данного разряда
	for (i = 0; i < size; i++) {
		count[mas[offset + i*sizeof(unsigned int)]]++;
	}

	//перевод count в массив индексов начал элементов по разряду (подсчёт префиксной суммы и её сдвиг вправо)
	for (i = 1; i < 256; i++) {
		count[i] += count[i - 1];
	}
	for (i = 255; i>0; i--) {
		count[i] = count[i - 1];
	}
	count[0] = 0;

}
void radix_sort_uint(unsigned int* mas, int size){
	unsigned char* pm = (unsigned char*)mas;
	unsigned int* mas2 = (unsigned int*)malloc(size * sizeof(unsigned int));
	int count[256];
	int i, j;




	for (i = 0; i < sizeof(unsigned int); i++) {
		
		offset(count, pm, size, i); //собирает список начал по байту i

		for (j = 0; j < size; j++) {
			mas2[count[pm[j * sizeof(unsigned int) + i]]++] = mas[j]; // то самое заклинание с тремя индексами
			//записывает текущий элемент первого массива во второй
			//при этом выбирает для записи такой индекс, который соответствует текущему номеру для записи чисел с данным i-м разрядом (из count)
			//увеличивает count[значение i-го байта], для того, чтобы следующий элемент таким же с i-м байтом был записан в последующую ячейку
		}

		swap_pointers_uint(&mas, &mas2);
		pm = (unsigned char*)mas; // обновление pm
	}

	free(mas2); //так-как произошло чётное количество swap'ов (sizeof(uint)/sizeof(char) = 4) исходный массив остался в mas  
}
void radix_sort_float(float* mas, int size){
	int i;


	//реализация для флотов происходит путём преобразования (float в uint) с сохранением их порядка 
	//основана на том, что все биты в реализации float'а распологаются в порядке убывания "важности" 
	unsigned int* ptr;
	ptr = (unsigned int*)mas;
	
	for (i = 0; i < size; i++) {
		if (ptr[i] >> 31) {
			//отрицательные числа преобразуются в обратный код 
			//обратный код позволяет инвертировать порядок отрицательных чисел (чем больше модуль отрицательного числа тем оно меньше)
			//также меняет самый старший бит на 0 делая их меньше всех положительных
			ptr[i] = (ptr[i] ^ 4294967295) + 1;
		}
		else {
			//неотрицательные числа изначально расположены в правильном порядке после преобразования в uint 
			//запись 1 в старший бит позволяет расположить неотрицательные числа после отрицательных; 
			ptr[i] = ptr[i] ^ 2147483648;
		}
	}

	radix_sort_uint(ptr, size);


	//обратное преобразование (из uint в float)
	for (i = 0; i < size; i++) {
		if (ptr[i] >> 31) {
			ptr[i] = ptr[i] ^ 2147483648;
		}
		else {
			ptr[i] = (ptr[i] - 1) ^ 4294967295;
		}
	}
}


// ЗАМЕРЫ ВРЕМЕНИ
unsigned __int64 clock_measure(float* mas, int n, void(*sort)(float*, int)) {
	unsigned __int64 start, end;
	start = __rdtsc();
	sort(mas, n);
	end = __rdtsc();
	return end - start;
}
unsigned __int64 average_clock_measure(float* mas, int n, void(*sort)(float*, int), int number_of_tries) {
	int i;
	unsigned __int64 all_ticks = 0;
	for (i = 0; i < number_of_tries; i++) {
		rand_array_float(mas, n);
		all_ticks += clock_measure(mas, n, sort);
	}
	return all_ticks/ number_of_tries;
}


// МЕНЮ

void flush_stdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
int start_menu() {
	int ans, ex;
	ex = 0;
	do {
		printf("Что вы хотите сделать?\n");
		printf("(1) - Начать\n");
		printf("(2) - Выход\n");

		printf("-> ");
		scanf("%d", &ans);

		if (ans == 1 || ans == 2) {
			ex = 1;
		}
		else {
			flush_stdin();
			printf("Ошибка ввода\n\n");
		}

	} while (not ex);
	return ans%2;
}
void massive_menu(float** masptr, int* n) {
	int ans, ex, i;
	float* mas;
	ex = 0;
	do {
		printf("Выберите способ задания массива\n");
		printf("(1) - Вручную\n");
		printf("(2) - Случайно [-1000; 1000]\n");
		
		printf("-> ");
		scanf("%d", &ans);

		switch (ans) {
		case 1:
			printf("Введите длину массива:  ");

			scanf("%d", n);

			mas = *masptr = (float*)malloc(*n * sizeof(float));

			printf("Введите элементы массива: ");
			for (i = 0; i < *n; i++) {
				scanf("%f", &(mas[i]));
			}
			ex = 1;

			break;


		case 2:
			printf("Введите длину массива:  ");

			printf("->");
			scanf("%d", n);

			mas = *masptr = (float*)malloc(*n * sizeof(float));
			rand_array_float(mas, *n);
			ex = 1;
			
			break;


		default:
			flush_stdin();
			printf("Ошибка ввода\n\n");
			break;
		}

	} while (not ex);


}
void function_menu(void(**sort_tmp)(float*, int)){
	int ans;
	int ex;
	ex = 0;
	do {
		ex = 1;
		printf("Выберите сортировочный алгоритм\n");
		printf("(1) - Пузырёк\n");
		printf("(2) - Расчёска\n");
		printf("(3) - Слияние\n");
		printf("(4) - Поразрядная\n");

		printf("-> ");
		scanf("%i", &ans);
		
		switch (ans) {
		case 1:
			*sort_tmp = bubble_sort_float;
			break;


		case 2:
			*sort_tmp = comb_sort_float;
			break;

		case 3:
			*sort_tmp = merge_sort_float;
			break;

		case 4:
			*sort_tmp = radix_sort_float;
			break;


		default:
			ex = 0;
			printf("Ошибка ввода\n\n");
			flush_stdin();
			break;
		}
	} while (not ex);





}
void manual_check(float* mas, int n) {

}


int main() {
	int  n;
	float* mas;
	float* mas2;
	void(*sort)(float*, int);

	setlocale(LC_ALL, "Rus");
	
	while (start_menu()) {
		massive_menu(&mas, &n);
		printf("\n");
		
		mas2 = (float*)malloc(n * sizeof(float));
		copy_array_float(mas, mas2, n);

		function_menu(&sort);
		printf("\n");

		printf("Массив отсортирован за %i тактов\n", clock_measure(mas, n, sort));
		printf("Проверка сортировки: ");
		if (check_sorted_float(mas, mas2, n)) {
			printf("массив отсортирован правильно\n");
		}
		else {
			printf("массив отсортирован неправильно\n");
		}
		printf("\n");
		free(mas);
		free(mas2);
	}
	




	

	return 0;
}