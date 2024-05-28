#include <iostream>
#include <string>
#include "matrix.hpp"
#include <algorithm>
#include <stdlib.h>
#include <algorithm>



int main() {

	size_t n, m;
	
	std::cout << "Ax = b SLE solver" << std::endl;

	std::cout << "Please enter number of rows and columns in Matrix A" << std::endl;
	std::cout << "rows: ";
	std::cin >> n;
	std::cout << "columns: ";
	std::cin >> m;
	matrix<double> A(n, m);
	matrix<double> b(n, 1);

	std::cout << "Now enter elements of matrix A starting with 1st row:" << std::endl;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			std::cin >> A(i, j);
		}
	}
	





	std::cout << "Now enter " << n << " elements of vector b" << std::endl;
	for (size_t i = 0; i < n; i++) {
		std::cin >> b(i, 0);
	}

	matrix<double> sol = A.solve(b);	
	
	if(sol.has_solution()){

		bool* dependent = new bool[m];
		memset(dependent, 0, m*sizeof(bool));

		
		size_t  j = 0;
		for (size_t i = 0; i < n; i++) {
			while (j < m &&  sol(i, j) == 0) j++;
			if(j < m) dependent[j] = 1;
		}

		
		int indt = 0;
		for (size_t i = 0; i < m; i++) {
			if (!dependent[i]) {
				std::cout << "x" << i + 1 << " = t" << indt++ + 1 << std::endl;
			}
			else {
				std::cout << "x" << i + 1 << " = " << sol(i, m);
				int t = 1;
				for (size_t j = 0; j < m; j++) {
					if (!dependent[j] && sol(i, j) != 0) {
						std::cout << " + " << -sol(i, j) << "*t" << t++;
					}
				}
				std::cout << std::endl;
			}
		}



		std::cout << "Accuracy check:" << std::endl;
		double* ind_values = new double(indt);
		std::cout << "Enter values of " << indt << " independent variables" << std::endl;

		for (size_t i = 0; i < indt; i++) {
			std::cin >> ind_values[i];
		}

		matrix<double> ansvec(m, 1);
		int it = 0, dt = 0;
		for (size_t j = 0; j < m; j++) {
			if (dependent[j]) {
				int t = 0;
				ansvec(j, 0) = sol(j, m);
				for (size_t j = 0; j < m; j++) {
					if (!dependent[j]) {
						ansvec(j, 0) -= sol(dt, j) * ind_values[t++];
					}
				}
				dt++;
			}
			else {
				ansvec(j, 0) = ind_values[it++];
			}
		}

		matrix <double> resvec = A * ansvec;
		double acc = 0;
		for (size_t i = 0; i < n; i++) {
			acc = std::max(acc, abs(resvec(i, 0) - b(i, 0)));
		}
		
		std::cout << acc << std::endl;

		delete ind_values;
		delete dependent;
	}
	else {
		std::cout << "The system does not have a solution" << std::endl;
	}
}