#include <iostream>
#include <cmath>

float next_sin(float x, int i) {
        return  -x * x / ((2*i + 1)*2*i);
}

float next_cos(float x, int i){
    return -x * x / ((2*i)*(2*i-1));
}

float next_exp(float x, int i){
    return x / i;
}

float next_ln ( float x, int i){
    return (-x * i) / (i + 1);
}

float sum_function(float a0, float x, float(*next)(float, int), int n){
    float res, ai;
    res = ai = a0;
    for (int i = 1; i <= n; i++) {
        ai *= next(x, i);
        res += ai;
    }
    return res;
}

float sumreverse_function(float a0, float x, float(*next)(float, int), int n) {
    float res, ai;
    int size = n + 1;
    float* arr = new float[size];
    res = 0;
    ai = a0;
    arr[0] = a0;
    for (int i = 1; i < size; i++) {
        ai *= next(x, i);
        arr[i] = ai;

    }
    for (int i = 0; i < size / 2; i++) {
        float tmp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = tmp;
    }

    for (int i = 0; i < size; i++) {
        res += arr[i];
    }
    delete[] arr;
    return res;
}

float pairwisesum_function(float a0, float x, float(*next)(float, int), int n) {
    float res, ai, tmp;
    res = ai = a0;
    for (int i = 1; i <= n; i++) {
        ai *= next(x, i);
        tmp = ai;
        if (i + 1 <= n)
        {
            i++;
            ai *= next(x, i);
            tmp += ai;
        }
        res += tmp;
    }
    return res;
}
int main() {
    setlocale(LC_ALL, "Rus");

    float x;
    int n;

    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите количество итераций n: ";
    std::cin >> n;

    std::cout << "Значения различных функций в точке x = " << x << ":" << std::endl;

    float sin_value = sum_function(x, x, next_sin, n);
    std::cout << "Синус: " << sin_value << std::endl;

    float cos_value = sum_function(1.0, x, next_cos, n);
    std::cout << "Косинус: " << cos_value << std::endl;

    float exp_value = sum_function(1.0, x, next_exp, n);
    std::cout << "Экспонента: " << exp_value << std::endl;
    
    float ln_value = sum_function(x, x, next_ln, n);
    std::cout << "Логарифм: " << ln_value << std::endl;

    float reverse_sin_value = sumreverse_function(x, x, next_sin, n);
    std::cout << "Сумма обратного ряда синусов: " << reverse_sin_value << std::endl;
    
    float reverse_cos_value = sumreverse_function(1.0, x, next_cos, n);
    std::cout << "Сумма обратного ряда косинусов: " << reverse_cos_value << std::endl;
    
    float reverse_exp_value = sumreverse_function(1.0, x, next_exp, n);
    std::cout << "Сумма обратного ряда экспоненты : " << reverse_exp_value << std::endl;

    float reverse_ln_value = sumreverse_function(x, x, next_ln, n);
    std::cout << "Сумма обратного ряда логарифма: " << reverse_ln_value << std::endl;

    float pairwise_exp_value = pairwisesum_function(1.0, x, next_exp, n);
    std::cout << "Попарная сумма экспоненциального ряда: " << pairwise_exp_value << std::endl;
    
    float pairwise_sin_value = pairwisesum_function(x, x, next_sin, n);
    std::cout << "Попарная сумма ряда синусов: " << pairwise_sin_value << std::endl;
    
    float pairwise_cos_value = pairwisesum_function(1.0, x, next_cos, n);
    std::cout << "Попарная сумма ряда косинусов: " << pairwise_cos_value << std::endl;
    
    float pairwise_ln_value = pairwisesum_function(x, x, next_ln, n);
    std::cout << "Попарная сумма ряда логарифма: " << pairwise_ln_value << std::endl;
    
    std::cout << sin(x) <<std::endl;
    std::cout << cos (x)<<std::endl;
    std::cout << exp (x)<<std::endl;
    std::cout << log(1 + x)<<std::endl;

    return 0;
}



