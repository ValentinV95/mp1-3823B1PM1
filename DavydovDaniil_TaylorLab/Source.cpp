#include <iostream>
#include <iomanip>
#include <cmath>
#include "TaylorSeries.h"
void calculateT(float argument, float(*math)(float), float(*SumF)(float, float const, float(*)(float, int)), float(*TS)(float const, float(*)(float, float const, float(*)(float, int))));
int main()
{
	float x;
	int funcNum = 0, SumNum = 0, flag = 1;
	float (*TaylorSeries[4])(float const, float(*)(float, float const, float(*)(float, int))) = { t_sin, t_cos, t_exp, t_log };
	float (*SumFunc[3])(float, float const, float(*)(float, int)) = { directSum , extendedSum ,reverseSum };
	float (*mathFunc[4])(float) = { sin, cos, exp, log };
	do
	{
		do
		{
			system("cls");
			std::cout << "Choose function: 1 - sin, 2 - cos, 3 - exp, 4 - ln" << std::endl;
			std::cin >> funcNum;
		} while (funcNum < 1 || funcNum > 4);
		funcNum -= 1;
		do
		{
			system("cls");
			std::cout << "Choose mrthod: 1 - direct, 2 - extended, 3 - reverse" << std::endl;
			std::cin >> SumNum;
		} while (SumNum < 1 || SumNum > 3);
		SumNum -= 1;
		std::cout << "Enter x: ";
		std::cin >> x;
		calculateT(x, mathFunc[funcNum], SumFunc[SumNum], TaylorSeries[funcNum]);
		do
		{
			std::cout << "\nStart again? Yes - 1, No - 0 : ";
			std::cin >> flag;
			system("cls");
		} while (flag != 1 && flag != 0);
	} while (flag == 1);
	return 0;
}
void calculateT(float arg, float(*mathF)(float), float(*SumF)(float, float const, float(*)(float, int)), float(*TS)(float const, float(*)(float, float const, float(*)(float, int))))
{
	float myRes, machineRes;
	myRes = TS(arg, SumF);
	machineRes = mathF(arg);
	std::cout << "My result: " << myRes << "\tMachine result: " << machineRes << "\tAbsDelta: " << fabs(myRes - machineRes) << "\tRelDelta: " << fabs(1.0f - myRes / machineRes) << std::endl;
	return;
}
