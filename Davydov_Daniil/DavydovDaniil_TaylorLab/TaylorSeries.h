#pragma once
float sin_next(float x, int i);

float cos_next(float x, int i);

float exp_next(float x, int i);

float log_next(float x, int i);

void prepSin(float& x, int& n);

void prepCos(float& x, int& n);

void prepExp(float& x, int& p);

void prepLog(float& x, int& p);

float directSum(float a0, float const x, float(*next)(float, int));

float extendedSum(float a0, float const x, float(*next)(float, int));

float reverseSum(float a0, float const x, float(*next)(float, int));

float t_sin(float const x, float(*SumFunc)(float, float const, float(*)(float, int)));

float t_cos(float const x, float(*SumFunc)(float, float const, float(*)(float, int)));

float t_exp(float const x, float(*SumFunc)(float, float const, float(*)(float, int)));

float t_log(float const x, float(*SumFunc)(float, float const, float(*)(float, int)));