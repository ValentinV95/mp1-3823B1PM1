#pragma once

float sin_next(float x, int i);

float cos_next(float x, int i);

float exp_next(float x, int i);

float ln_next(float x, int i);

float sin_(float x, float (*sum)(float, float, float(*)(float, int), int));

float cos_(float x, float (*sum)(float, float, float(*)(float, int), int));

float exp_(float x, float (*sum)(float, float, float(*)(float, int), int));

float ln_(float x, float (*sum)(float, float, float(*)(float, int), int));

float sum_service(float a0, float x, float(*next)(float, int), int n);

float double_sum_service(float a0, float x, float(*next)(float, int), int n);

float double_sumr_service(float a0, float x, float(*next)(float, int), int n);

float sumr_service(float a0, float x, float(*next)(float, int), int n);