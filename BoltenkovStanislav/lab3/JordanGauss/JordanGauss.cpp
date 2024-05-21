#include <iostream>
#include "LongFraction.h"
#include "matrixProcessing.h"
#include "exeptionMatrixProc.h"

using namespace std;

typedef double TYPE;

void printSolution(const matrixProcessing<TYPE>& p)
{
    matrix<TYPE> A = p.getA(), B = p.getB();
    for (int indColumn = 0; indColumn < B.getm(); indColumn++)
    {
        std::cout << "solution number " << indColumn + 1 << ":" << std::endl;
        if (!p.checkSolutionColumn(indColumn))
        {
            std::cout << "no decision" << std::endl;
            return;
        }

        mathVector<bool> used(A.getm(), false);
        for (int i = 0; i < std::min(A.getn(), A.getm()); i++)
        {
            if (A[i][i] != __ZERO)
            {
                std::cout << "x" << i + 1 << " = " << ((B[i][indColumn] != __ZERO) ? B[i][indColumn] : 0);
                used[i] = true;
                for (int j = i + 1; j < A.getm(); j++)
                {
                    if (A[i][j] != __ZERO) std::cout << " + " << A[i][j] * (-1) << "x" << j + 1;
                }
                std::cout << std::endl;
            }
            else
            {
                int ind = -1;
                for (int j = i + 1; j < A.getm(); j++)
                {
                    if (A[i][j] != __ZERO)
                    {
                        ind = j;
                        break;
                    }
                }

                if (ind == -1) continue;
                used[ind] = true;
                std::cout << "x" << ind + 1 << " = " << ((B[i][indColumn] != __ZERO) ? B[i][indColumn] : 0);
                for (int j = ind + 1; j < A.getm(); j++)
                {
                    if (A[i][j] != __ZERO) std::cout << " + " << A[i][j] * (-1) << "x" << j + 1;
                }
                std::cout << std::endl;
            }
        }

        for (int i = 0; i < A.getm(); i++)
        {
            if (!used[i])
            {
                std::cout << "x" << i + 1 << " - any number\'s" << std::endl;
            }
        }

    }
    return;
}

matrix<TYPE> inverseMatrix(const matrix<TYPE>& A)
{
    matrix<TYPE> B(A.getn(), A.getm());
    for (int i = 0; i < B.getn(); i++)
    {
        for (int j = 0; j < B.getm(); j++)
        {
            if (i == j) B[i][i] = 1;
            else B[i][j] = 0;
        }
    }

    matrixProcessing<TYPE> p1(A, B);
    p1.GaussMethod();
    if (p1.determinantA() == __ZERO)
    {
        throw exeptionMatrixProc("det(A) = 0", 3);
    }
    p1.JordanGaussMethod();
    return p1.getB();
}

TYPE getDeterminant(const matrix<TYPE>& A)
{
    matrix<TYPE> B(A.getn(), 1);
    matrixProcessing<TYPE> p1(A, B);
    p1.GaussMethod();
    return p1.determinantA();
}

//0 - найти обратную матрицу
//1 - вычислить определитель
//2 - решить СЛУ

int main()
{
    cout << "0 - inverse matrix search" << endl;
    cout << "1 - calculate determinant" << endl;
    cout << "2 - decide system of equations" << endl;
    int numberSituation;
    cin >> numberSituation;
    try
    {
        if (numberSituation == 0)
        {
            cout << "entering the number of columns and rows of matrix: ";
            int n;
            cin >> n;
            matrix<TYPE> A(n, n);
            cin >> A;
            cout << A << endl;
            cout << endl << inverseMatrix(A) << endl;
        }
        else if (numberSituation == 1)
        {
            cout << "entering the number of columns and rows of matrix: ";
            int n;
            cin >> n;
            matrix<TYPE> A(n, n);
            cin >> A;
            cout << "det(A) = " << getDeterminant(A);
        }
        else if (numberSituation == 2)
        {
            cout << "entering the number of columns, matrix rows and equations: ";
            int n, m, cntSystem;
            cin >> n >> m >> cntSystem;
            matrix<TYPE> A(n, m), B(n, cntSystem);
            cin >> A >> B;
            matrixProcessing<TYPE> p1(A, B);
            p1.GaussMethod();
            p1.JordanGaussMethod();
            printSolution(p1);
        }
        else throw 0;
    }
    catch (const exeptionMatrixProc& ex)
    {
        cout << ex.what() << endl;
        cout << "code error: " << ex.getCodeError() << endl;
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
    }
    catch (...)
    {
        cout << "unhandled error" << endl;
    }
    return 0;
}