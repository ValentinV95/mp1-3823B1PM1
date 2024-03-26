#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//series functions
void series_sin(float* mas, int n, float x) {
	int i;
	mas[0] = x;

	for (i = 1; i < n; i ++)
		mas[i] = -(mas[i - 1] * x * x) / ((2*i+1)*2*i);

	return;
}

void series_cos(float* mas, int n, float x) {
	int i;
	mas[0] = 1;
	for (i = 1; i < n; i ++)
		mas[i] = -(mas[i - 1] * x * x) / (2*i * (2*i - 1));
}

void series_exp(float* mas, int n, float x) {
	int i;
	mas[0] = 1;
	for (i = 1; i < n; i++) {
		mas[i] = mas[i - 1] * x / i;
	}
}

void series_lnplus1(float* mas, int n, float x) {
	int i;
	float var = x;
	for (i = 0; i < n; i++) {
		mas[i] = i % 2 ? -var / (i+1) : var / (i+1);
		var *= x;
	}
}


//summation functions
float direct_sum(float* mas, int n) {
	float sum = 0;
	int i;
	for (i = 0; i < n; i++) {
		sum += mas[i];
	}
	return sum;
}

float reverse_sum(float* mas, int n) {
	float sum = 0;
	int i;
	for (i = n-1; i >= 0; i--) {
		sum += mas[i];
	}
	return sum;
}

float paired_direct_sum(float* mas, int n) {
	float sum = 0;
	float buf = 0;
	int k = 0;
	int i;
	for (i = 0; i < n; i++) {
		buf += mas[i];
		k++;
		if (k == 2) {
			sum += buf;
			k = 0;
			buf = 0;
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
	for (i = n-1; i >= 0; i--) {
		buf += mas[i];
		k++;
		if (k == 2) {
			sum += buf;
			k = 0;
			buf = 0;
		}
	}
	sum += buf;

	return sum;
}


//the taylor func itself
float taylor(float x, void(*series_function)(float*, int, float), float(*summation_function)(float*, int), int num_of_elements) {
	float* mas;
	float res;

	mas = (float*)malloc((num_of_elements) * sizeof(float));
	series_function(mas, num_of_elements, x);
	res = summation_function(mas, num_of_elements);

	free(mas);

	return res;
}



//for data collection
void get_data() {
	float x;
	float* mas;
	float res;
	int num_of_elements = 100000;
	int n;
	float(*summation_function)(float*, int);
	float(*std_func)(float) = log1pf;
	void(*series_function)(float*, int, float) = series_lnplus1;
	double mean_dir, mean_rev, mean_pd, mean_pr;
	float max_x, dx;
	float err;

	mas = (float*)malloc((num_of_elements + 1) * sizeof(float));
	n = num_of_elements;

	mean_dir = mean_rev = mean_pd = mean_pr = 0;

	max_x = 0.8; dx = (float)1/(100);

	
	for (x = -0.8; x <= max_x; x += dx) {
		series_function(mas, n, x);
		
		printf("%.8f\t", x);
		
		summation_function = direct_sum;
		err = fabs(std_func(x) - summation_function(mas, n));
		mean_dir += (double)err ;
		printf("%.8e\t", err);

		summation_function = reverse_sum;
		err = fabs(std_func(x) - summation_function(mas, n));
		mean_rev += (double)err;
		printf("%.8e\t", err);

		summation_function = paired_direct_sum;
		err = fabs(std_func(x) - summation_function(mas, n));
		mean_pd += (double)err;
		printf("%.8e\t", err);

		summation_function = paired_reverse_sum;
		err = fabs(std_func(x) - summation_function(mas, n));
		mean_pr += (double)err;
		printf("%.8e\t", err);

		printf("\n");
	}
	printf("mean: %.8e\t %.8e\t %.8e\t %.8e\t", (mean_dir * dx) / max_x, (mean_rev * dx) / max_x, (mean_pd * dx) / max_x, (mean_pr * dx) / max_x);
	free(mas);
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
			std_func = sinf;
			break;
		case 2:
			series_function = series_cos;
			std_func = cosf;
			break;
		case 3:
			series_function = series_exp;
			std_func = expf;
			break;
		case 4:
			series_function = series_lnplus1;
			std_func = log1pf;
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
			break;
		case 2:
			summation_function = reverse_sum;
			break;
		case 3:
			summation_function = paired_direct_sum;
			
			break;
		case 4:
			summation_function = paired_reverse_sum;
			break;
		default:
			return 0;
			break;
		}

		printf("x = ");
		scanf_s("%f", &x);

		printf("number of elements in series = ");
		scanf_s("%i", &n);

		res = taylor(x, series_function, summation_function, n);
		printf("Result = %.8e\n", res);
		printf("Std = %.8e\n", std_func(x));
		printf("Error = %.8e\n\n", fabs(std_func(x) - res));
	}


	return 0;
}