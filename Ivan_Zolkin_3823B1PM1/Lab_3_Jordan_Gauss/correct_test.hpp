#include <random>
template <class _Mtrx>
void correct_test(vector<vector<_Mtrx>> matrix, std::pair<vector<vector<_Mtrx>>, size_t> ans, double EPS) {
	vector<_Mtrx> T_Column(ans.first.size());
	//double* crtest = new double[2];
	if (abs(EPS - EPS_DOUBLE) < EPS_DOUBLE) {
		EPS *= _C_C;
	}
	else {
		EPS *= C_;
	}
	_Mtrx tmp;
	for (int i = 0; i < ans.first[0].size() - 1; i++) {
		for (int j = 0; j < ans.first.size(); j++) {
			T_Column[j] = ans.first[j][i];
		}
		for (int u = 0; u < matrix.size(); u++) {
			tmp = _Mtrx(0);
			for (int j = 0; j < matrix[0].size() - 1; j++) {
				tmp = tmp + matrix[u][j] * T_Column[j];
			}
			/*crtest[0] = T_Column.size();
			crtest[1] = tmp;
			all_c++;
			fwrite(crtest, sizeof(double), 2, outputT);*/

			if (abs(tmp) > _Mtrx(EPS)) {
				std::cout<<' '<< "INCORRECT!\n";
				exit(ERR_UNNAMED);
			}
		}
	}
	std::cout << "Ok\n";
	return;
}
template <>
void correct_test(vector<vector<Complex>> matrix, std::pair<vector<vector<Complex>>, size_t> ans, double EPS) {
	vector<Complex> T_Column(ans.first.size());
	EPS *= _C_C;
	Complex tmp;
	//double* crtest = new double[2];
	for (int i = 0; i < ans.first[0].size() - 1; i++) {
		for (int j = 0; j < ans.first.size(); j++) {
			T_Column[j] = ans.first[j][i];
		}
		for (int u = 0; u < matrix.size(); u++) {
			tmp = 0.0;
			for (int j = 0; j < matrix[0].size() - 1; j++) {
				tmp = tmp + matrix[u][j] * T_Column[j];
			}
			/*crtest[0] = T_Column.size();
			crtest[1] = tmp.module();
			all_c++;
			fwrite(crtest, sizeof(double), 2, outputT);*/
			if (abs(tmp) >Complex(EPS)) {
				std::cout<<"INCORRECT!\n";
				exit(ERR_UNNAMED);
			}
		}
	}
	std::cout << "Ok\n";
	return;
}
template <class _Mtrx>
void inputRAND(vector<vector<_Mtrx>>& matrix) {
	std::random_device random_device; // Источник энтропии.
	std::mt19937 generator(random_device()); // Генератор случайных чисел.
	std::uniform_int_distribution<> distribution(-100, 100);
	double tmp;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			tmp = distribution(generator);
			matrix[i][j] = _Mtrx(tmp);
			std::cout << tmp<<'\n';
		}
	}
	return;
}
template <>
void inputRAND(vector<vector<Complex>>& matrix) {
	std::random_device random_device; // Источник энтропии.
	std::mt19937 generator(random_device()); // Генератор случайных чисел.
	std::uniform_int_distribution<> distribution(-100000, 100000);
	double tmp;
	Complex temp;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			tmp = distribution(generator);
			temp.setReal(tmp);
			std::cout << tmp << ' ';
			tmp = distribution(generator);
			temp.setImg(tmp);
			std::cout << tmp << '\n';
			matrix[i][j] = temp;
		}
	}
	return;
}