#include "stdio.h"
#include "mathFunction.h"
#include <algorithm>
#include <fstream>
#include <math.h>
#include <iomanip>

#pragma warning(disable : 4996)

void test(float (*testFunc)(float x, float (*)(float, float, float(*)(float, int), int)), float (*mathFunc)(float), float st, float en)
{
    float x, y1, y2, y3, y4, y5;
    for (x = st; x < en; x += 1.0f / 256.0f)
    {
        y2 = mathFunc(x);
        y1 = testFunc(x, sum_service);
        y3 = testFunc(x, sumr_service);
        y4 = testFunc(x, double_sum_service);
        y5 = testFunc(x, double_sumr_service);
        printf("%1.13f %1.13f %1.13f %1.13f %1.13f\n", x, y1 - y2, y3 - y2, y4 - y2, y5 - y2);
    }
    return;
}

int main()
{
    int numberFunction;
    scanf("%i", &numberFunction);

    if (numberFunction < 0 || numberFunction > 3) return 0;

    float (*testFunctions[4])(float x, float (*)(float, float, float(*)(float, int), int)) = { sin_ , cos_, exp_, ln_ };
    float (*mathFunctions[4])(float) = { sinf, cosf, expf, logf };

    test(testFunctions[numberFunction], mathFunctions[numberFunction], ((numberFunction == 3) ? 32.0f : 0.0f) - 32.0f, 32.0f);
   
    return 0;
}