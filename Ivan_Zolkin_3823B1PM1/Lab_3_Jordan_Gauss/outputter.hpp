#pragma once
#include "vector.hpp"
#include <iostream>

template <class _Mtrx>
std::pair<vector<vector<_Mtrx>>, size_t> output(vector<vector<_Mtrx>>& matrix, vector<_max_el_cord>& main_elements, int n, int m, double EPS,vector<int>&indexes,vector<std::pair<int,int>>&trans) {
	try {
		
		std::pair<vector<vector<_Mtrx>>, size_t> ans;
		ans.second = main_elements.size();
		ans.first = vector<vector<_Mtrx>>(m - 1, vector<_Mtrx>(m - main_elements.size(), 0));

		for (int ind = 0; ind < main_elements.size(); ind++) {

			_Mtrx coef = _Mtrx(1) / matrix[main_elements[ind].str][ind];
			for (int i = main_elements.size(); i < matrix[0].size() - 1; i++) {
				_Mtrx element = -coef * matrix[main_elements[ind].str][i];
				ans.first[indexes[ind]][i - main_elements.size()] = element;
			}
			ans.first[indexes[ind]][ans.first[0].size() - 1] = coef * matrix[main_elements[ind].str][matrix[0].size() - 1];
		}
		for (int i = main_elements.size(), t = 0; i < matrix[0].size() - 1; i++, t++) {
			ans.first[indexes[i]][i - main_elements.size()] = _Mtrx(1);
		}
		for (int i = 0; i < ans.first.size(); i++) {
			std::cout << numeration_var('x', i + 1) << " = ";
			bool was_printed = 0;
			for (int j = 0; j < ans.first[0].size(); j++) {
				if (abs(ans.first[i][j]) < _Mtrx(EPS) && (j!=ans.first[0].size()-1) && (!was_printed)) continue;
				if (j != ans.first[0].size() - 1) {
					if (!was_printed) {
						std::cout << ans.first[i][j] << "*" << numeration_var('t', j + 1) << ' ';
						was_printed = 1;
					}
					else {
						if (ans.first[i][j] > _Mtrx(EPS)) {
							std::cout << "+ " << ans.first[i][j] << "*" << numeration_var('t', j + 1) << ' ';
						}
						else if (ans.first[i][j] < _Mtrx(-EPS)) {
							std::cout << "- " << -ans.first[i][j] << "*" << numeration_var('t', j + 1) << ' ';
						}
					}
				}
				else {
					if (!was_printed) {
						std::cout << ans.first[i][j];
						was_printed = 1;
					}
					else {
						if (ans.first[i][j] > _Mtrx(EPS)) {
							std::cout << "+ " << ans.first[i][j];
						}
						else if (ans.first[i][j] < _Mtrx(-EPS)) {
							std::cout << "- " << -ans.first[i][j];
						}
					}
				}
			}
			std::cout << '\n';

		}
		
		distranspos(matrix, trans);
		return ans;
	}
	catch (std::exception& e) {
		std::cout << "outputter: " << e.what() << '\n';
		exit(ERR_SYS);
	}
}