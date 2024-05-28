#pragma 
#include <string.h>
#include <algorithm>
#include <exception>
#include <string>

class BadMatrix : public std::exception {
public:
	std::string msg;
	
	BadMatrix(const std::string &s) {
		msg = s;
	}
		
	const char* what() {
		return msg.c_str();
	}
};








template <class T>
class matrix{
protected:
	
public:
	size_t rows, columns;
	T* data;

	const size_t getrows() {return rows;}
	const size_t getcolumns() {return columns;}
	T& operator()(size_t row, size_t column) { return data[row * columns + column]; }
	const T& operator()(size_t row, size_t column)  const {return data[row * columns + column]; }

	matrix(size_t _rows = 10, size_t _columns= 10, const T &value = T(0)) {
		if (_rows == 0 || _columns == 0) throw BadMatrix("Invalid matrix size"); // no matrix because size

		rows = _rows;
		columns = _columns;
		data = new T[rows * columns];
		for (int i = 0; i < rows * columns; i++) data[i] = T(value);
	}

	matrix(const matrix<T>& mat) {
		rows = mat.rows;
		columns = mat.columns;
		data = new T[rows * columns];
		for (int i = 0; i < rows * columns; i++) data[i] = T(mat.data[i]);
	}

	matrix operator*(const matrix<T> mat2) {
		const matrix<T>& mat1 = *this;
		if (mat1.columns != mat2.rows) {
			throw BadMatrix("invalid sizes in matrix product"); //no product
		}
		
		matrix<T> res(rows, mat2.columns, 0);
		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < mat2.columns; j++)
				for (size_t k=0 ; k < columns; k++)
					res(i, j) += mat1(i, k) * mat2(k, j);

		return res;
	}


	void swaprows(size_t r1, size_t r2) {
		for (size_t i = 0; i < columns;i++) {
			T t = (*this)(r1, i);
			(*this)(r1, i) = (*this)(r2, i);
			(*this)(r2, i) = t;
		}
	}
	void adiv(size_t r1, T d) {
		for (size_t i = 0; i < columns; i++) {
			(*this)(r1, i) /= d;
		}
	}
	void bpma(size_t r1, size_t r2, T m) {
		for (size_t i = 0; i < columns; i++) {
			(*this)(r1, i) += (*this)(r2, i) * m;
		}
	}

	matrix<T> solve(const matrix<T>& b) {

		if (b.columns != 1) throw BadMatrix("invalid value vector size: too wide"); //bad value vector (b)
		if (rows != b.rows) throw BadMatrix("invalid value vector size: did not match the main SLE matrix"); // number of values(b) doesn't equal number of equations(A)

		matrix <T> mat(rows, columns + 1);
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				mat(i, j) = (*this)(i, j);
			}
		}
		for (size_t i = 0; i < rows; i++) {
			mat(i, columns) = b(i, 0);
		}

		size_t last_row = 0;
		for (size_t j = 0; j < columns; j++) {
			size_t ind = 0;
			T mxval = 0;
			bool f = 0;
			for (size_t i = last_row; i < mat.rows; i++) {
				if (mat(i, j) > mxval || mat(i, j) < -mxval) {
					mxval = mat(i,j) > 0 ? mat(i, j) : -mat(i,j);
					ind = i;
					f = 1;
				}
			}

			if (f) {
				mat.swaprows(ind, last_row);
				mat.adiv(last_row, mat(last_row, j));
				for (size_t i = 0; i < mat.rows; i++) {
					if (i != last_row) {
						mat.bpma(i, last_row, -mat(i, j));
						mat(i, j) = 0;
					}
				}
				last_row++;
			}
		}

		return mat;
	}

	bool has_solution() {
		if (columns <= 1) throw BadMatrix("invalid solution matrix size"); //smth smth
		
		for (size_t i = 0; i < rows; i++) {
			if ((*this)(i, columns-1) != 0) {
				bool f = 0;
				for (size_t j = 0; j < columns - 1; j++) {
					if ((*this)(i, j) != 0) {
						f = 1;
						break;
					}
				}
				if (!f) {
					return 0;
				}
			}
		}
		return 1;
	}



	void setval(const T& value) {
		for (int i = 0; i < rows * columns; i++) data[i] = T(value);
	}
	void print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				std::cout << data[i * columns + j] << "\t";
			}
			std::cout << "\n";
		}
	}

	~matrix () {
		delete data;
	}
};


