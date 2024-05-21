#pragma once
#define EPS_DOUBLE 1e-14
#define EPS_FLOAT 1e-6
#define INF_DOUBLE (std::numeric_limits<double>::max())
#define INF_FLOAT (std::numeric_limits<float>::max())
#define INF_INT (std::numeric_limits<int>::max())
#define ERR_SYS_1 111
#define ERR_SYS_2 112
#define ERR_SYS 11
#define ERR_UNNAMED 10
#define ERR_UTIL 12
#define ERR_UTIL_1 121
#define ERR_VEC_1 131
#define ERR_VEC 13
#define C_ 100000
#define _C_C 1000000
//<------------------------Correct test and experiment----------------------------------->
#define CORRECT_TEST false	//USE THIS FOR CORRECT_TESTING
extern bool CORRECT_TEST_NEED = true;
//extern FILE* outputT = NULL;	//FOR USE UNCOMMENT IN J*_G*.cpp and correct_test.hpp
//extern int all_c = 0;