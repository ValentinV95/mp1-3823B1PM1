#include <iostream>
#include <intrin.h>
#include <fstream>

#pragma intrinsic(__rdtsc)

template <class t>
class Vector {
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
		std::memset(array, 0, n * sizeof(t));
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

	void pop_back() {
		size--;
	}

	t& operator[](size_t i) {
		if (i >= size) {
			throw std::out_of_range("Index out of range");
		}
		return array[i];
	}

	void clean() {
		size = 0;
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
		std::cout << what() << '\n';
		std::cout << "Ошибка в строке " << str << '\n';
		std::cout << "0 = " << value << '\n' << '\n';
		abort();
	}
};


class Reduce_exception : public std::exception {
public:
	Reduce_exception(const char* msg) {
		std::cout << what();
		abort();
	}
};

template <class t>
class Matrix {
	int n, m;
	t** mat;
	t* vec_mat;
public:
	Matrix() {}
	Matrix(int n, int m) {
		mat = new t * [n];
		vec_mat = new t[n * m];
		for (int i = 0; i < n; i++) {
			mat[i] = &vec_mat[i * m];
		}
	}

	Matrix(Matrix& s) {
		for (int i = 0; i < n * m; i++) 
			vec_mat[i] = s.vec_mat[i];
	}

	t& operator ()(int i, int j) {
		return mat[i][j];
	}

	void swap(int i1, int i2) {
		std::swap(mat[i1], mat[i2]);
	}

	void print_mat() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				std::cout << mat[i][j];
			std::cout << '\n';
		}
	}

	//~Matrix() {
	//	delete vec_mat;
	//	delete mat;
	//}

};

template <class t>
class Solver {
	const t eps = pow(10, -10);
	int n, m;
	bool coop;
	Vector<int> depend;
	Vector<int> free;
	Matrix<t> orig;
	Matrix<t> mat;
public:
	Solver(int n, int m) : depend(), free(), mat(n, m), orig(n, m) {
		this->n = n;
		this->m = m;
	}

	t& operator() (int i, int j) {
		return mat(i, j);
	}

	int get_max(int str, int col) {
		t mx = eps;
		int ind = -1;
		for (int i = str; i < n; i++) {
			if (abs(mat(i,col)) > mx) {
				mx = abs(mat(i, col));
				ind = i;
			}
		}
		return ind;
	}

	void conversion(int str, int col) {
		for (int i = 0; i < n; i++) {
			t c = mat(i,col) / mat(str,col);
			if (i != str && abs(c) > eps)
				for (int j = col; j < m; j++)
					mat(i,j) = mat(i,j) - mat(str,j) * c;
		}
	}

	void normalize(int str, int col) {
		t div = mat(str,col);
		for (int j = col; j < m; j++)
			mat(str,j) = mat(str,j) / div;
	}

	void check_coop() {
		coop = 1;
		for (int i = depend.getsize(); i < n; i++)
			if (abs(mat(i,m - 1)) > eps) {
				mat.print_mat();
				throw Cooperative_exception<t>("Система несовместна", i + 1, mat(i,m - 1));
			}
	}

	void GordanGauss() {
		depend.clean();
		free.clean();
		orig = mat;
		int j = 0;
		for (int i = 0; j < m - 1 && i < n; j++) {
			int str = get_max(i, j);
			if (str != -1) {
				mat.swap(str, i);
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
			if (mat(i,depend[i]) != 0)
				normalize(i, depend[i]);

		check_coop();
	}

	void answer() {
		if (depend.getsize() + free.getsize() == 0)
			throw Reduce_exception("Система не приведена");
		for (int i = 0; i < depend.getsize(); i++) {
			std::cout << 'x' << depend[i] + 1 << " = " << mat(i,m - 1);
			for (int j = 0; j < free.getsize(); j++) {
				int c = free[j];
				if (abs(mat(i, c)) > eps) {
					std::cout << " + " << mat(i, c) << " * t" << j + 1;
				}
			}
			std::cout << '\n';
		}
		for (int i = 0; i < free.getsize(); i++) {
			std::cout << 'x' << free[i] + 1 << " = " << 't' << i+1 << '\n';
		}
	}

	void check_ans() {
		if (depend.getsize() + free.getsize() == 0)
			throw Reduce_exception("Система не приведена");

		Vector<t> values(free.getsize() + depend.getsize());

		if (free.getsize() > 0) {
			std::cout << "Введите значения свободных переменных\n";
			for (int i = 0; i < free.getsize(); i++) {
				std::cout << 't' << i + 1 << " = ";
				int ind = free[i];
				std::cin >> values[ind];
			}
		}

		for (int i = 0; i < depend.getsize(); i++) {
			values[depend[i]] = mat(i, m - 1);
			for (int j = 0; j < free.getsize(); j++) {
				int c = free[j];
				values[depend[i]] -= mat(i, c) * values[c];
			}
		}

		t dif = 0;
		for (int i = 0; i < n; i++) {
			t s = 0;
			for (int j = 0; j < values.getsize(); j++) {
				t val = orig(i, j);
				s += values[j] * val;
			}
			dif += abs(s - orig(i, m - 1));
		}

		std::cout << "Погрешность вычисления - " << dif << '\n';
	}
};

int main() {
	std::setlocale(LC_ALL, "rus");
	std::cout << std::fixed;
	std::cout.precision(3);
	unsigned long long n, m;
	std::cin >> n >> m;
	Solver<double> mat(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat(i, j) = rand();
	mat.GordanGauss();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			std::cout << mat(i, j) << '\t';
		std::cout << '\n';
	}
	mat.answer();
	mat.check_ans();
}
