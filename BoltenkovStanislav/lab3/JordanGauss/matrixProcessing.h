#pragma once
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "ZERO.h"
#include "exeptionMatrixProc.h"

template<class T>
class matrixProcessing
{
private:
	matrix<T> A, B;
    mathVector<bool> solution;
    void checkSolution() const; //проверка наличия решения каждой системы

public:

	matrixProcessing(const matrix<T>& A, const matrix<T>& B);
    ~matrixProcessing();

    matrix<T> getA() const;
    matrix<T> getB() const;

    void setMatrix(matrix<T>& A, matrix<T>& B);

    void GaussMethod();
    void JordanGaussMethod();

    T determinantA() const;
    T determinantB() const;

    bool checkSolutionColumn(int indColumn) const; //проверка наличия решения для произвольного столбца в В после Жордама-Гауса

};

template<class T>
bool matrixProcessing<T>::checkSolutionColumn(int indColumn) const
{
    return solution[indColumn];
}

template<class T>
void matrixProcessing<T>::checkSolution() const
{
    for (int j = 0; j < B.getm(); j++)
    {
        solution[j] = 1;
    }

    for (int i = 0; i < A.getn(); i++)
    {
        int ind = -1;//индек первого не нулевого в строке
        for (int j = 0; j < A.getm(); j++)
        {
            if (A[i][j] != __ZERO)
            {
                ind = j;
                break;
            }
        }
        if (ind == -1) //нулевая строка в матрице А
        {
            for (int j = 0; j < B.getm(); j++)
            {
                if (B[i][j] != __ZERO) solution[j] = 0;//система не совместна
            }
        }
    }
    return;
}

template<class T>
matrixProcessing<T>::matrixProcessing(const matrix<T>& A, const matrix<T>& B)
{
    if (A.getn() != B.getn())
    {
        throw exeptionMatrixProc("the number of lines is not equal", 2);
    }
	this->A = A;
	this->B = B;
    solution.setSize(B.getm());
}

template<class T>
matrixProcessing<T>::~matrixProcessing()
{

}

template<class T>
inline matrix<T> matrixProcessing<T>::getA() const
{
    return A;
}

template<class T>
inline matrix<T> matrixProcessing<T>::getB() const
{
    return B;
}

template<class T>
inline void matrixProcessing<T>::setMatrix(matrix<T>& A, matrix<T>& B)
{
    if (A.getn() != B.grtn())
    {
        throw exeptionMatrixProc("the number of lines is not equal", 2);
    }
    this->A = A;
    this->B = B;
    solution.setSize(B.getm());
    return;
}

template<class T>
void matrixProcessing<T>::GaussMethod()
{
    for (int i = 0; i < std::min(A.getm(), A.getn()); i++)
    {
        int ind = -1; //индекс первого не нулевого элемента
        for (int j = i; j < A.getn(); j++)
        {
            if (A[j][i] != __ZERO && ind == -1 || ind != -1 && abs(A[j][i]) > abs(A[ind][i]))
            {
                ind = j;
            }
        }
        if (ind == -1) continue;
        if (ind != i) //ненулевой максимальный элемент оказался не на пересечение i-го столбца и i-ой строки
        {
            A(i, 't', ind);
            B(i, 't', ind);
        }
        for (int j = i + 1; j < A.getn(); j++)
        {
            T a = (A[j][i] / A[i][i]);
            A(j, '-', i, a);
            B(j, '-', i, a);
        }
    }
    return;
}

template<class T>
void matrixProcessing<T>::JordanGaussMethod()
{
    for (int i = 0; i < std::min(A.getm(), A.getn()); i++)
    {
        if (A[i][i] == __ZERO)
        {
            int ind = -1;//номер столбца с первым не 0 элементом на i-ой строке
            for (int j = 0; j < A.getm(); j++)
            {
                if (A[i][j] != __ZERO)
                {
                    ind = j;
                    break;
                }
            }
            if (ind == -1) continue;//нулевая строка
            for (int j = 0; j < A.getn(); j++)
            {
                if (j == i) continue;
                T a = (A[j][ind] / A[i][ind]);
                A(j, '-', i, a);
                B(j, '-', i, a);
            }
            B(i, '/', A[i][ind]);
            A(i, '/', A[i][ind]);
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                T a = (A[j][i] / A[i][i]);
                A(j, '-', i, a);
                B(j, '-', i, a);
            }

            B(i, '/', A[i][i]);
            A(i, '/', A[i][i]);
        }
        
    }
    checkSolution();
    return;
}

template<class T>
T matrixProcessing<T>::determinantA() const
{
    if (A.getn() != A.getm())
    {
        throw exeptionMatrixProc("matrix A is not square", 1);
    }
    T res = 1;
    for (int i = 0; i < A.getn(); i++)
    {
        res *= A[i][i];
    }
    return res;
}

template<class T>
T matrixProcessing<T>::determinantB() const
{
    if (A.getn() != A.getm())
    {
        throw exeptionMatrixProc("matrix B is not square", 1);
    }
    T res = 1;
    for (int i = 0; i < B.getn(); i++)
    {
        res *= B[i][i];
    }
    return res;
}