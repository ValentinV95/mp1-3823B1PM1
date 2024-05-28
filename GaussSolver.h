#pragma once
#include "Matrix.h"
#include <vector>

template<class T>
class GaussSolver {
public:
	bool comp(double& b) const {
		double epsilone=0.;
		return abs(b)==epsilone;
	}
	std::vector<Vector> solve(const Matrix& A, const Vector& v){//метод Гаусса
		Matrix M(A.getN(), A.getM() + 1);//создает матрицу n*(m+1)
		for (int i = 0; i < M.getN(); i++) {
			M[i][M.getM() - 1] = v[i];
			for (int j = 0; j < A.getM(); j++) M[i][j] = A[i][j];
		}
		std::cout << M << std::endl;
		int n = M.getN(), m = M.getM();
		int rank = 0;
		VectorT<int>  indexVed(n);
		for (int i = 0; i < n; i++) indexVed[i] = 100000000;//вектор хранит индексы ведущих переменных в каждой строке
		for (int i = 0; i < n; i++) {
			T Ved;
			int indexV = 0;
			while ((indexV < m - 1) && (M[i][indexV]==0)) indexV++;
			if (indexV < m - 1) {
				Ved = M[i][indexV];//обновляет ранг матрицы
				rank++;
				indexVed[i] = indexV;//сохраняет индекс ведущей переменной
				for (int t = 0; t < m; t++) M[i][t] = (double)M[i][t] / Ved;
				Ved = 1;
				for (int t = 0; t < n; t++) {
					if ((t != i) && (M[t][indexV]!=0)) {//элементарное преобразование строк Гаусса
						double tmp = (double)M[t][indexV] / Ved;
						for (int j = 0; j < m; j++) {
							M[t][j] -= (M[i][j] * tmp);
						}
					}
				}
			}
		}
		for (int i = 1; i < n; i++) {//цикл для сортировки строк по возрастанию индексов ведущих элементов
			for (int j = 1; j < n; j++) {
				if (indexVed[j] < indexVed[j - 1]) {
					Vector tmp(n);
					tmp = M[j - 1];
					M[j - 1] = M[j];
					M[j] = tmp;
					int tmp2 = indexVed[j - 1];
					indexVed[j - 1] = indexVed[j];
					indexVed[j] = tmp2;
				}
			}
		}
		bool Flag = true;//проверка на существование решения 
		for (int i = 0; i < n; i++) {
			int j = 0;
			bool flag = false;
			while (j < m - 1) {//проверяет есть ли хотя бы олин ненулевой элемент в строке
				if (!comp(M[i][j])) {
					flag = true;
					break;
				}
				j++;
			}
			if ((flag == false)&&(!comp(M[i][m-1]))) Flag = false;
		}
		std::cout << M << std::endl;
		if (Flag == true) {
			std::vector<Vector> ans(m - rank);//создание вектора решений
			for (int i = 0; i < m - rank; i++) ans[i] = Vector(m - 1);//заполнение вектора решений базовыми переменными
			int p = 1;
			for (int i = 0; i < m - 1; i++) {
				bool flag = true;
				for (int j = 0; j < n; j++) {
					if (indexVed[j] == i) {
						flag = false;
						ans[0][j] = M[j][m - 1];
						break;
					}
				}
				if (flag == true) {//заполнение вектора решений свободными переменными
					for (int j = 0; j < n; j++) ans[p][j] = -M[j][i];
					ans[p][i] = 1;
					p++;
				}
			}
			return ans;
		}
		std::vector<Vector> ans;
		return ans;
	}
};
