#pragma once
#include "MathVector.h"
#include "exeptionMatrixProc.h"

template<class T>
class matrix
{
private:
    mathVector< mathVector<T> > A;

public:
    matrix(size_t n = 0, size_t m = 0);
    matrix(const matrix<T>& mt);
    ~matrix();

    size_t getm() const;
    size_t getn() const;

    mathVector<T>& operator[](int i);
    mathVector<T>& operator[](int i) const;
    matrix& operator()(const int& i, const char& operation, const int& j, const T& a = 1); //для двух строк
    matrix& operator()(const int& i, const char& operation, const T& a); //для одной строки

    matrix<T>& operator=(const matrix<T>& B);

    matrix<T> operator*(const matrix<T>& B);
    matrix<T> operator-(const matrix<T>& B);
    matrix<T> operator+(const matrix<T>& B);

    template<class T>
    friend std::ostream& operator<<(std::ostream& os, const matrix<T>& mt);
    template<class T>
    friend std::istream& operator>>(std::istream& in, matrix<T>& mt);
};

template<class T>
inline size_t matrix<T>::getm() const
{
    if (A.getSize() == 0) return 0;
    return A[0].getSize();
}

template<class T>
inline size_t matrix<T>::getn() const
{
    return A.getSize();
}

template<class T>
matrix<T>::matrix(size_t n, size_t m)
{
    A.setSize(n);
    for (int i = 0; i < n; i++)
    {
        A[i].setSize(m);
    }
}

template<class T>
matrix<T>::matrix(const matrix<T>& mt)
{
    A.setSize(mt.getn());
    for (int i = 0; i < mt.getn(); i++)
    {
        A[i].setSize(mt.getm());
    }
    A = mt.A;
}

template<class T>
matrix<T>::~matrix()
{
    
}

template<class T>
mathVector<T>& matrix<T>::operator[](int i)
{
    return A[i];
}

template<class T>
mathVector<T>& matrix<T>::operator[](int i) const
{
    return A[i];
}

template<class T>
matrix<T>& matrix<T>::operator()(const int& i, const char& operation, const int& j, const T& a)
{
    if (operation == '+')
    {
        A[i] = A[i] + A[j] * a;
    }
    else if (operation == '-')
    {
        A[i] = A[i] - A[j] * a;
    }
    else if (operation == 't')
    {
        std::swap(A[i], A[j]);
    }
    return *this;
}

template<class T>
matrix<T>& matrix<T>::operator()(const int& i, const char& operation, const T& a)
{
    if (operation == '*')
    {
        A[i] = A[i] * a;
    }
    else if (operation == '/')
    {
        A[i] = A[i] / a;
    }
    return *this;
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& mt)
{
    A.setSize(mt.getn());
    for (int i = 0; i < mt.getn(); i++)
    {
        A[i].setSize(mt.getm());
    }
    A = mt.A;
    return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& mt)
{
    for (int i = 0; i < mt.A.getSize(); i++)
    {
        os << mt[i] << std::endl;
    }
    return os;
}

template<class T>
inline std::istream& operator>>(std::istream& in, matrix<T>& mt)
{
    for (int i = 0; i < mt.A.getSize(); i++)
    {
        in >> mt[i];
    }
    return in;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& B)
{
    if (getm() != B.getn())
    {
        throw exeptionMatrixProc("the dimensions of the matrices do not coincide", 4);
    }
    
    matrix<T> C(getn(), B.getm());
    for (int i = 0; i < C.getn(); i++)
    {
        for (int j = 0; j < C.getm(); j++)
        {
            C[i][j] = T(0);
            for (int k = 0; k < getm(); k++)
            {
                C[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
    return C;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& B)
{
    if (getn() != B.getn() || getm() != B.getm())
    {
        throw exeptionMatrixProc("", 5);
    }

    matrix<T> C(getn(), getm());
    for (int i = 0; i < C.getn(); i++)
    {
        for (int j = 0; j < C.getm(); j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& B)
{
    if (getn() != B.getn() || getm() != B.getm())
    {
        throw exeptionMatrixProc("", 5);
    }

    matrix<T> C(getn(), getm());
    for (int i = 0; i < C.getn(); i++)
    {
        for (int j = 0; j < C.getm(); j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}