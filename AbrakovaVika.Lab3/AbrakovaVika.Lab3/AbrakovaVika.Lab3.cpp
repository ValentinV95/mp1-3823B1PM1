#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

// Класс вектор
template <class T>
class Vector {
private:

    T* data;
    int size;

public:

    Vector() {
        data = nullptr;
        size = 0;
    }

    Vector(int size) : size(size) {
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            data[i] = T();//Инициализация элементов
        }
    }

    ~Vector() {
        delete[] data;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        delete[] data;
        this->size = size;
        data = new T[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = T();
        }
        return;
    }
};

// Класс матрица, реализованный как вектор векторов
template <class T>
class Matrix {
protected:
    Vector<Vector<T>> data;

public:

    Matrix(int rows, int cols) {
        data.setSize(rows);
        for (int i = 0; i < rows; ++i) {
            data[i].setSize(cols);
        }
    }
    ~Matrix()
    {

    }
    Vector<T>& operator[](int index) {
        if (index < 0 || index >= data.getSize()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const Vector<T>& operator[](int index) const {
        if (index < 0 || index >= data.getSize()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    int rows() const {
        return data.getSize();
    }
    int cols() const {
        return data[0].getSize();
    }
};

// Функция для вывода матрицы
template <typename T>
void printMatrix(const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            if (abs(matrix[i][j]) > 1e-14) {
                std::cout << matrix[i][j] << " ";
            }
            else {
                std::cout << 0 << " ";
            }

        }
        std::cout << std::endl;
    }
}

template <typename T>
class JordanGaussMatrix : public Matrix<T> {
public:
    JordanGaussMatrix(int rows, int cols) : Matrix<T>(rows, cols) {}

    void solve() {
        int n = this->rows();
        for (int i = 0; i < std::min(this->rows(), this->cols()); ++i) {
            // Поиск максимального по модулю элемента в столбце
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs(this->data[k][i]) > std::abs(this->data[maxRow][i])) {
                    maxRow = k;
                }
            }
            //меняем строки местами
            if (maxRow != i) {
                for (int j = 0; j < this->cols(); ++j) {
                    std::swap(this->data[i][j], this->data[maxRow][j]);
                }
            }

            //нулевой столбец
            T scale = this->data[i][i];
            if (abs(scale) < 1e-14) {
                continue;
            }

            // Приводим диагональный элемент к 1
            for (int j = 0; j < this->cols(); ++j) {
                this->data[i][j] /= scale;
            }

            // Зануляем оставшиеся элементы в столбце
            for (int k = 0; k < n; ++k) {
                if (k != i) {
                    T factor = this->data[k][i];
                    for (int j = 0; j < this->cols(); ++j) {
                        this->data[k][j] -= factor * this->data[i][j];
                    }
                }
            }
        }
    }
    Vector<T> getSolution() const {
        Vector<T> solution(this->rows());
        for (int i = 0; i < this->rows(); ++i) {
            solution[i] = this->data[i][this->cols() - 1];
        }
        return solution;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    int n, m;
    std::cout << "Введите количество строк матрицы: ";
    std::cin >> n;
    std::cout << "Введите количество столбцов матрицы: ";
    std::cin >> m;

    JordanGaussMatrix<double> matrix(n, m);
    for (int i = 0; i < n; ++i) {
         std::cout << "Введите элементы " << i + 1 << "-й строки через пробел: ";
         for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::cout << "Введенная матрица:" << std::endl;
    printMatrix(matrix);

    try {
        matrix.solve();
        std::cout << "Матрица в ступенчатом виде:" << std::endl;
        printMatrix(matrix);

        Vector<double> solution = matrix.getSolution();
        std::cout << "Решение системы:" << std::endl;
        for (int i = 0; i < solution.getSize(); ++i) {
            std::cout << "x" << i + 1 << " = " << solution[i] << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}