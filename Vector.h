#pragma once
#include <iostream>

template <class T>
class VectorT {
	T * coords = nullptr;
	int size;
public:
	int getSize() const { return size; }
	// конструктор по размеру 
	VectorT(int n=0) : size(n) {
		coords = new T[size];
		for (int i = 0; i < size; i++) coords[i] = 0;
	} 
	// конструктор копирования
	VectorT(const VectorT & v) : size(v.getSize()) {
		coords = new T[size];
		for (int i = 0; i < size; i++) {
			coords[i] = v[i];
		}
	}
	// конструктор через массив и размер
	VectorT(T * arr, int n) : size(n) {
		coords = new T[size];
		for (int i = 0; i < size; i++) coords[i] = arr[i];
	}
	// конструктор преобразования типа 
	template<class T2>
	VectorT(const VectorT<T2> & v) : size(v.getSize()) {
		coords = new T[size];
		for (int i = 0; i < size; i++) {
			coords[i] = static_cast<T>(v[i]);
		}
	}

	T & operator[](int index) const { return coords[index]; }
	VectorT& operator=(const VectorT & v) {
		if (&v != this) {
			this->size = v.size;
			delete[] coords;
			coords = new T[size];
			for (int i = 0; i < size; i++) coords[i] = v.coords[i];
			return *this;
		}
		return *this;
	}
	double operator*(const VectorT& b) const {
		double P = this->For(b);
		return P;
	}
	double For(const VectorT & res) const {
		double tmp = 0;
		for (int i = 0; i < size; i++) tmp += (this->coords[i] * res.coords[i]);
		return tmp;
	}
	friend std::istream& operator>>(std::istream & istr, VectorT & v) {
		for (int i = 0; i < v.size; i++) {
			istr >> v[i];
		}
		return istr;
	}
	friend std::ostream& operator<<(std::ostream & ostr, const VectorT & v) {
		ostr << "(";
		for (int i = 0; i < v.size-1; i++) {
			ostr << v[i] << ", ";
		}
		ostr << v[v.size - 1] << ")\n";
		return ostr;
	}
	~VectorT() {
		delete[] coords;
	}
};

using Vector = VectorT<double>;
