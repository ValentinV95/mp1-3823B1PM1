#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//series functions
void series_sin(float* mas, int n, float x) {
	int i;
	memset(mas, 0, sizeof(float) * (n+1));
	mas[1] = x;

	for (i = 3; i <= n; i += 2)
		mas[i] = -(mas[i - 2] * x * x) / (i * (i - 1));

	return;
}

void series_cos(float* mas, int n, float x) {
	int i;
	memset(mas, 0, sizeof(float) * (n + 1));
	mas[0] = 1;

	for (i = 2; i <= n; i += 2)
		mas[i] = -(mas[i - 2] * x * x) / (i * (i - 1));
}

void series_exp(float* mas, int n, float x) {
	int i;
	mas[0] = 1;
	for (i = 1; i <= n; i++) {
		mas[i] = mas[i - 1] * x / i;
	}
}

void series_lnplus1(float* mas, int n, float x) {
	int i;
	mas[0] = 0;
	float var = x;
	for (i = 1; i <= n; i++) {
		mas[i] = i % 2 ? var / i : -var / i;
		var *= x;
	}
}


//summation functions
float direct_sum(float* mas, int n) {
	float sum = 0;
	int i;
	for (i = 0; i <= n; i++) {
		sum += mas[i];
	}
	return sum;
}

float reverse_sum(float* mas, int n) {
	float sum = 0;
	int i;
	for (i = n; i >= 0; i--) {
		sum += mas[i];
	}
	return sum;
}

float paired_direct_sum(float* mas, int n) {
	float sum = 0;
	float buf = 0;
	int k = 0;
	int i;
	for (i = 0; i <= n; i++) {
		if (mas[i] != 0) {
			buf += mas[i];
			k++;
			if (k == 2) {
				sum += buf;
				k = 0;
				buf = 0;
			}
		}

	}
	sum += buf;

	return sum;
}

float paired_reverse_sum(float* mas, int n) {
	float sum = 0;
	float buf = 0;
	int k = 0;
	int i;
	for (i = n; i >= 0; i--) {
		if (mas[i] != 0) {
			buf += mas[i];
			k++;
			if (k == 2) {
				sum += buf;
				k = 0;
				buf = 0;
			}
		}
	}
	sum += buf;

	return sum;
}


//the taylor func itself
float taylor(float x, void(*series_function)(float*, int, float), float(*summation_function)(float*, int), int highest_degree) {
	float* mas;
	float res;

	mas = (float*)malloc((highest_degree+1) * sizeof(float));
	series_function(mas, highest_degree, x);
	res = summation_function(mas, highest_degree);


	free(mas);

	return res;
}


//for data collection
void small_x() {
	float x;
	float* mas;
	float res;
	int highest_degree = 1000000;
	int n;
	float(*summation_function)(float*, int);
	float(*std_func)(float) = sinf;
	void(*series_function)(float*, int, float) = series_sin;


	mas = (float*)malloc((highest_degree + 1) * sizeof(float));


	
	n = highest_degree;

	
	
	
	for (x = 0; x <= 6; x += 0.24) {
		series_function(mas, highest_degree, x);

		printf("%.8f\t", x);
		
		summation_function = direct_sum;
		printf("%.8f\t", fabs(std_func(x) - summation_function(mas, n)));

		summation_function = reverse_sum;
		printf("%.8f\t", fabs(std_func(x) - summation_function(mas, n)));

		summation_function = paired_direct_sum;
		printf("%.8f\t", fabs(std_func(x) - summation_function(mas, n)));

		summation_function = paired_reverse_sum;
		printf("%.8f\t", fabs(std_func(x) - summation_function(mas, n)));

		printf("\n");
	}
	
	
	

}



//


//log
float logfp1(float x) {
	return logf(x + 1);
}

//menu
void func_choose() {
	printf("Choose the function:\n");
	printf("(1) sin(x)\n");
	printf("(2) cos(x)\n");
	printf("(3) exp(x)\n");
	printf("(4) ln(x+1)\n");
	printf("(0) exit\n");
}
void summ_choose() {
	printf("Choose the summation method:\n");
	printf("(1) direct sum(x)\n");
	printf("(2) reversed sum\n");
	printf("(3) paired direct sum\n");
	printf("(4) paired reversed sum\n");
	printf("(0) exit\n");
}




int main() {
	int n;
	float x;
	int ans;
	void(*series_function)(float*, int, float);
	float(*summation_function)(float*, int);
	float res;
	float (*std_func)(float);
	while (1) {
		func_choose();
		scanf_s("%i", &ans);
		switch (ans)
		{
		case 1:
			series_function = series_sin;
			break;
		case 2:
			series_function = series_cos;
			break;
		case 3:
			series_function = series_exp;
			break;
		case 4:
			series_function = series_lnplus1;
			break;
		default:
			return 0;
			break;
		}

		summ_choose();
		scanf_s("%i", &ans);
		switch (ans)
		{
		case 1:
			summation_function = direct_sum;
			std_func = sinf;
			break;
		case 2:
			summation_function = reverse_sum;
			std_func = cosf;
			break;
		case 3:
			summation_function = paired_direct_sum;
			std_func = expf;
			break;
		case 4:
			summation_function = paired_reverse_sum;
			std_func = logfp1;
			break;
		default:
			return 0;
			break;
		}

		printf("x = ");
		scanf_s("%f", &x);


		printf("highest degree in series = ");
		scanf_s("%i", &n);


		res = taylor(x, series_function, summation_function, n);
		printf("%.7f\n", res);
		printf("Error = %.7f\n\n", std_func(x) - res);
	}


	small_x();




	
	
	
	return 0;
}