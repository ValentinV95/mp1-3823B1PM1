#include "GaussSolver.h"
#include <ctime>
void check_input(int x, int y) {
	try {
		if (x==0 && y == 0) {
			throw std::domain_error("Ошибка при вводе. Ведите ненулевые значения строк и столбцов, пожалуйста.");
		}
	}
	catch (std::domain_error& e) {
		std::cout << "Исключение `domain_error`: " << e.what() << std::endl;
	}
}
int main() {
	setlocale(LC_ALL, "ru");

	int x, y;
	std::cout << "Введите число строк:" << std::endl;
	std::cin >> x;
	std::cout << "Введите число столбцов:" << std::endl;
	std::cin >> y;
	try {
		check_input(x, y);
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

		Matrix A(x, y);
		for (int i = 0; i < A.getN(); i++) {
			for (int j = 0; j < A.getM(); j++) {
				srand(time(0));
				int tmp = (rand()+j+i)%101;//для диапазона от 0 до 100
				A(i,j) = tmp;
			}
		}
		Vector v1(x);
		for (int i = 0; i < v1.getSize(); i++) v1[i] = 1;
		Vector v = A * v1;
		//std::cout << v << std::endl;
		GaussSolver<double> R;
		std::vector<Vector> a=R.solve(A, v);//вектор решений
		for (int i = 0; i < a.size(); i++) std::cout << a[i];
	return 0;
}