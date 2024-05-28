#pragma once
#include "vector.hpp"
#include <iostream>
#include "DEFINES.hpp"

struct _max_el_cord {
	int str;
	int col;
};
template <class _Mtrx>
void print(vector<vector<_Mtrx>>& matrix) {
	try {
		std::cout << "-------------------------\n";
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				std::cout << matrix[i][j] << ' ';
			}
			std::cout << '\n';
		}
		return;
	}
	catch (...) {
		std::cout << "print function unnamed error\n";
		exit(ERR_UTIL);
	}
}
std::string numeration_var(char sym, int num) { return sym + std::to_string(num); };

template <class _Mtrx>
int max_cords(vector<vector<_Mtrx>>& _matrix, int _Colum, vector<bool>& _used,double INF)
{
	try {
		_Mtrx MIN_EL = _Mtrx(-INF);
		std::pair<_Mtrx, int> max_elemnt = { MIN_EL, -1 };
		for (int i = 0; i < _matrix.size(); i++)
			if ((!_used[i]) && abs(_matrix[i][_Colum]) >= max_elemnt.first)
				max_elemnt.first = abs(_matrix[i][_Colum]), max_elemnt.second = i;
		if(max_elemnt.second!=-1)
		_used[max_elemnt.second] = true;
		return max_elemnt.second;
	}
	catch (...) {
		std::cout << "max_cords function unnamed error\n";
		exit(ERR_SYS);
	}
};

template <class _Mtrx>
bool Checker(int begin, int end, vector<_Mtrx>& v, double EPS) {
	try {
		if (begin<0 || end>v.size()) throw j_error("function checker matrix out of range");
		for (int i = begin; i < end; i++) {
			if (abs(v[i]) > EPS) {
				return true;
			}
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
		exit(ERR_UTIL_1);
	}
	catch (...) {
		std::cout << "accumulate function unnamed error\n";
		exit(ERR_UTIL);
	}
}
template <class _Mtrx>
void input(vector<vector<_Mtrx>>& matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cin >> matrix[i][j];
		}
	}
	return;
}
template <class _Mtrx>
void swap(_Mtrx& a, _Mtrx& b) {
	_Mtrx c = a;
	a = b;
	b = c;
	return;
}template <class _Mtrx>
bool isNull_col(vector<vector<_Mtrx>>& matrix, int n, double EPS) {
	for (int i = 0; i < matrix.size(); i++) {
		if (abs(matrix[i][n]) > _Mtrx(EPS))return false;
	}
	return true;
}
template<class _Mtrx>
vector<std::pair<int, int>> transpos(vector<vector<_Mtrx>>& matrix, double EPS,vector<int>& indexes) {
	vector<std::pair<int, int>> trans;
	bool is_exit = false;
	for (int i = 0; i < matrix[0].size() - 1; i++) {
		if (isNull_col(matrix, i, EPS)) {
			for (int j = matrix[0].size() - 2; j > -1; j--) {
				if (j == i) {
					is_exit = 1;
					break;
				}
				if (!isNull_col(matrix, j, EPS)) {
					trans.push_back({ i, j });
					std::swap(indexes[i], indexes[j]);
					for (int p = 0; p < matrix.size(); p++) {
						swap(matrix[p][i], matrix[p][j]);
					}
					break;
				}
			}
		}
		if (is_exit)break;
	}
	return trans;
}
template <class _Mtrx>
void distranspos(vector<vector<_Mtrx>>& matrix, vector<std::pair<int, int>>& trans) {
	for (int i = 0; i < trans.size(); i++) {
		for (int p = 0; p < matrix.size(); p++) {
			swap(matrix[p][trans[i].first], matrix[p][trans[i].second]);
		}
	}
	return;
}
