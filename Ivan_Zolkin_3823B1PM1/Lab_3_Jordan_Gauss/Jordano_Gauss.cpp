#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cmath>
#include "vector.hpp"
#include "j_error.hpp"
#include "DEFINES.hpp"
#include "solver.hpp"
#include "outputter.hpp"
#include "correct_test.hpp"
#include "shadow_outputter.hpp"

template <class _Mtrx>
std::pair<vector<vector<_Mtrx>>, size_t> root(double EPS,double INF) {
	std::pair<vector<vector<_Mtrx>>, size_t> ans;
	if (CORRECT_TEST) {	//Для включения изменить соответствующий флаг в DEFINES.hpp

		/*outputT = fopen("res2", "wb");
		if (!outputT) {
			printf("OPEN FILE ERROR");
			getchar();
			exit(2);
		}*/

		for (int m = 1; m <= 30; m++) {
			for (int n = 1; n <m; n++) {
				if (m == 1) continue;
				std::cout << n << ' ' << m << '\n';
				vector<_max_el_cord> main_elements;
				vector<vector<_Mtrx>> matrix(n, vector <_Mtrx>(m));
				inputRAND(matrix);
				
				CORRECT_TEST_NEED = true;
				vector<std::pair<int, int>> trans;
				vector<int> indexes = Solver(matrix, main_elements, n, m, EPS, INF,trans);
				std::cout << "----------------------\n";
				if (CORRECT_TEST_NEED) {
					ans = output_s(matrix, main_elements, n, m,EPS,indexes,trans);
				}
				else { std::cin >> CORRECT_TEST_NEED; continue; }
				
				///////////CORRECT TEST PLACE

				correct_test(matrix, ans, EPS);

				/////////////////////////////
			}
		}
	}
	else {
		int n, m;
		std::cin >> n >> m;
		try {
			if ( m == 1) throw j_error("System cant be Ax1! ");
			//if (n >= m) throw j_error("There should be no fewer variables than equations!\n");
			vector<_max_el_cord> main_elements;
			vector<vector<_Mtrx>> matrix(n, vector <_Mtrx>(m));
			input(matrix);

			vector<std::pair<int, int>> trans;
			vector<int> indexes = Solver(matrix, main_elements, n, m, EPS, INF,trans);
			std::cout << "----------------------\n";
			ans = output(matrix, main_elements, n, m,EPS,indexes,trans);
			///////////CORRECT TEST PLACE

			//correct_test(matrix, ans, EPS);

			/////////////////////////////
		}
		catch (std::exception& e) {
			std::cout << e.what() << '\n';
			exit(ERR_SYS_2);
		}
	}
	return ans;
}


signed main() {

	std::cout << "What type are we working with?:\n1 - double\n2 - complex\n3 - float\nAnswer: ";
	int q;std::cin >> q;
	
	if (q == 1) {
		std::pair<vector<vector<double>>, size_t> ans = root<double>(EPS_DOUBLE,INF_DOUBLE);
	}
	//else if (q == 3) {	//warning//<------- a/b also int ------->
	//	std::pair<vector<vector<int>>, size_t> ans = root<int>(EPS_DOUBLE, INF_INT);
	//}
	else if (q == 2) {
		std::pair<vector<vector<Complex>>, size_t> ans = root<Complex>(EPS_DOUBLE, INF_DOUBLE);
	}
	else if (q == 3) {
		std::pair<vector<vector<float>>, size_t> ans = root<float>(EPS_FLOAT, INF_FLOAT);
	}
	//fclose(outputT);
}