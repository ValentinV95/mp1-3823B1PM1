#pragma once
#include <iostream>
#include "vector.hpp"
#include "utils.hpp"


template<class _Mtrx>
vector<int> Solver(vector<vector<_Mtrx>>& matrix, vector<_max_el_cord>& main_elements, int n, int m, double EPS,double INF,vector<std::pair<int,int>>& trans) {
	try {
		_Mtrx NULL_EL = _Mtrx(0);
		_Mtrx coef;
		vector<bool> used(n, false);
		vector<int> indexes(m - 1);
		for (int i = 0; i < m - 1; i++) indexes[i] = i;
		trans = transpos(matrix,EPS,indexes);
		
		for (int i = 0; i < n && i < m; ++i) {
			
			int max_el_pos = max_cords(matrix, i, used,INF);
			if (max_el_pos == -1) continue;

			
			if ((!Checker(0, m - 1, matrix[max_el_pos], EPS)) && abs(matrix[max_el_pos][m - 1]) > _Mtrx(EPS)) {
				CORRECT_TEST_NEED = false;
				throw j_error("Inconsistent system");
			}

			if (abs(matrix[max_el_pos][i]) < _Mtrx(EPS)) continue;

			main_elements.push_back({ max_el_pos,i });

			for (int k = 0; k < n; k++) {	//Идем по строкам

				if (k == max_el_pos) continue;

				coef = -matrix[k][i] / matrix[max_el_pos][i];
				matrix[k][i] = NULL_EL;
				for (int j = i + 1; j < m; j++) {		//считаем текущую строку

					matrix[k][j] = matrix[k][j] + matrix[max_el_pos][j] * coef;
					if (abs(matrix[k][j]) < _Mtrx(EPS)) matrix[k][j] = NULL_EL;
				}
				if ((!Checker(0, m - 1, matrix[k],EPS)) && abs(matrix[k][m - 1]) > _Mtrx(EPS)) {
					CORRECT_TEST_NEED = false;
					throw j_error("Inconsistent system");
				}

			}
			
		}
		
		for (int i = std::min(n, m); i < n; i++) {
			if ((!Checker(0, m - 1, matrix[i],EPS)) && abs(matrix[i][m - 1]) > _Mtrx(EPS)) {
				CORRECT_TEST_NEED = false;
				throw j_error("Inconsistent system");
			}
		}
		return indexes;
	}
	catch (std::exception& e) {
		
		if (!CORRECT_TEST) { std::cout << e.what() << '\n'; exit(ERR_SYS_1); }
		
	}
	catch (...) {
		std::cout << "unnamed error\n";
		exit(ERR_UNNAMED);
	}
	
};

