#include <iostream>
#include <intrin.h>
#include <fstream>

#pragma intrinsic(__rdtsc)

template <class t>
class Vector {
private:
	t* array;
	size_t size, capacity;

public:
	Vector() {
		array = new t[1];
		capacity = 1;
		size = 0;
	}

	Vector(size_t n) {
		array = new t[n];
		capacity = n;
		size = n;
	}

	size_t getsize() {
		return size;
	}

	void push_back(t value) {
		if (size == capacity) {
			t* newArray = new t[capacity * 2];
			for (size_t i = 0; i < size; i++) {
				newArray[i] = array[i];
			}
			delete array;
			array = newArray;
			capacity *= 2;
		}
		array[size++] = value;
	}

	t& operator[](size_t i) {
		if (i >= size) {
			throw std::out_of_range("Index out of range");
		}
		return array[i];
	}

	~Vector() {
		delete array;
	}
};


template <class t>
class Cooperative_exception : public std::exception {
	int str;
	t value;
public:
	Cooperative_exception(const char* msg, int str, t value) : std::exception(msg) {
		this->str = str;
		this->value = value;
	}
	int num_of_string() {
		return str;
	}
	t num_of_value() {
		return value;
	}
};

template <class t>
void exception(Cooperative_exception<t>& e) {
	std::cout << e.what() << '\n';
	std::cout << "Ошибка в строке " << e.num_of_string() << '\n';
	std::cout << "0 = " << e.num_of_value() << '\n' << '\n';
}

template <class t>
class Matrix {
	const t eps = pow(10, -10);
	int n, m;
	t** orig;
	t** mat;
	t* vec_mat;
	t* vec_orig;
	bool coop;
	Vector<int> depend;
	Vector<int> free;
public:
	Matrix(int n, int m) : depend(), free() {
		this->n = n;
		this->m = m;
		orig = new t * [n];
		mat = new t * [n];
		vec_orig = new t[n * m];
		vec_mat = new t[n * m];
		memset(vec_orig, 0, n * m * sizeof(t));
		for (int i = 0; i < n; i++) {
			mat[i] = &vec_mat[i * m];
			orig[i] = &vec_orig[i * m];
		}
	}

	t& operator ()(int i, int j) {
		return mat[i][j];
	}

	int get_max(int str, int col) {
		t mx = eps;
		int ind = -1;
		for (int i = str; i < n; i++) {
			if (abs(mat[i][col]) > mx) {
				mx = abs(mat[i][col]);
				ind = i;
			}
		}
		return ind;
	}

	void conversion(int str, int col) {
		for (int i = 0; i < n; i++) {
			t c = mat[i][col] / mat[str][col];
			if (i != str && abs(c) > eps)
				for (int j = col; j < m; j++)
					mat[i][j] = mat[i][j] - mat[str][j] * c;
		}
	}

	void normalize(int str, int col) {
		t div = mat[str][col];
		for (int j = col; j < m; j++)
			mat[str][j] = mat[str][j] / div;
	}

	void check_coop() {
		try {
			coop = 1;
			for (int i = 0; i < n; i++) {
				t s = 0;
				for (int j = 0; j < m - 1; j++)
					s += mat[i][j];
				if (abs(mat[i][m - 1]) > eps && abs(s)<eps) {
					throw Cooperative_exception<t>("Система несовместна", i + 1, mat[i][m - 1]);
				}
			}
		}
		catch (Cooperative_exception<t>& e) {
			coop = 0;
			exception(e);
		}
	}

	void GordanGauss() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				orig[i][j] = mat[i][j];
		int j = 0;
		for (int i = 0; j < m - 1 && i < n; j++) {
			int str = get_max(i, j);
			if (str != -1) {
				std::swap(mat[str], mat[i]);
				conversion(i, j);
				depend.push_back(j);
				i++;
			}
			else
				free.push_back(j);
		}
		for (; j < m - 1; j++)
			free.push_back(j);

		for (int i = 0; i < depend.getsize(); i++)
			if (mat[i][depend[i]] != 0)
				normalize(i, depend[i]);
	}

	void answer() {
		check_coop();
		if (coop) {
			for (int i = 0; i < depend.getsize(); i++) {
				std::cout << 'x' << depend[i] + 1 << " = " << mat[i][m - 1];
				for (int j = 0; j < free.getsize(); j++) {
					if (abs(mat[i][free[j]]) > eps)
						std::cout << " + " << mat[i][free[j]] << " * x" << free[j] + 1;
				}
				std::cout << '\n';
			}
		}
	}

	void check_ans() {
		check_coop();
		if (coop) {
			Vector<t> values(m-1);
			if (free.getsize() > 0) {
				std::cout << "Введите значения свободных переменных\n";
				for (int i = 0; i < free.getsize(); i++) {
					std::cout << 'x' << free[i] + 1 << " = ";
					int ind = free[i];
					std::cin >> values[ind];
				}
			}
			for (int i = 0; i < depend.getsize(); i++) {
				values[depend[i]] = mat[i][m - 1];
				for (int j = 0; j < free.getsize(); j++)
					values[depend[i]] -= mat[i][free[j]] * values[free[j]];
			}
			t dif = 0;
			for (int i = 0; i < n; i++) {
				t s = 0;
				for (int j = 0; j < m-1; j++)
					s += values[j] * orig[i][j];
				dif = std::max(abs(s - orig[i][m - 1]), dif);
			}
			std::cout << "Погрешность: " << dif;
		}
	}

	~Matrix() {
		delete mat;
		delete orig;
		delete vec_mat;
		delete vec_orig;
	}
};

/* int main() {
	std::setlocale(LC_ALL, "rus");
	std::cout << std::fixed;
	std::cout.precision(3);
	int n, m;
	std::cout << "Введите число строк и столбцов:\n";
	std::cin >> n >> m;
	Matrix<double> mat(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> mat(i, j);
	mat.GordanGauss();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			std::cout << mat(i, j) << "\t";
		std::cout << '\n';
	}
	mat.answer();
	mat.check_ans();
} */
