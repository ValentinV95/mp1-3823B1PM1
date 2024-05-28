#pragma once
#include <iostream>
#include "j_error.hpp"
#include "DEFINES.hpp"
#include "complex.hpp"

template <typename T>
class vector {

	size_t capacity;
	size_t sizev;
	T* data;

	void swap_mas(T** a, T** b) {
		try {
			T** tmp = *a;
			*a = *b;
			*b = *tmp;
		}
		catch (std::exception& e) {
			std::cout << "vector swap function: " << e.what()<< '\n';
			exit(ERR_VEC);
		}
	}
public:
	vector() {
		try {
			capacity = 10;
			sizev = 0;
			data = new T[capacity];
		}
		catch (std::exception& e) {
			std::cout <<"vector default constructor: "<< e.what() << '\n';
			exit(ERR_VEC);
		}
	}
	~vector() {
		try {
			delete[] data;
		}
		catch (std::exception& e) {
			std::cout << "vector destructor: " << e.what() << '\n';
		}
	}

	vector(int _size, T el = T(0)) {
		try {
			capacity = _size;
			sizev = _size;
			data = new T[capacity];
			for (int i = 0; i < sizev; i++) {
				data[i] = el;
			}
		}
		catch (std::exception& e) {
			std::cout << "vector " << e.what() << '\n';
			exit(ERR_VEC);
		}
	}

	T& operator[] (const int& i) {
		try {
			if (i < 0 || i >= sizev) throw j_error("vector out of range");
			return data[i];
		}
		catch (std::exception& e) {
			std::cout << "vector operator[]: "<<e.what() << '\n';
			if (!CORRECT_TEST) {
				exit(ERR_VEC_1);
			}
		}
	}

	void push_back(const T& el) {
		try {
			if (sizev < capacity) {
				data[sizev] = el;
				sizev++;
			}
			else {
				T* nm = new T[capacity * 2];
				for (int i = 0; i < sizev; i++) {
					nm[i] = data[i];
				}
				delete[] data;
				data = nm;
				data[sizev] = el;
				sizev++;
				capacity *= 2;
			}
		}
		catch (std::exception& e) {
			std::cout <<"vector push_back(): " << e.what() << '\n';
			exit(ERR_VEC);
		}
	}
	void pop_back() {
		try {
			if(sizev > 0) {sizev--; }
			else { throw j_error("vector size cant be lower 0! "); }
		}
		catch (std::exception& e) {
			std::cout << e.what() << '\n';
			exit(ERR_VEC_1);
		}
	}
	void clear() {
		try {
			sizev = 0;
		}
		catch (std::exception& e) {
			std::cout << e.what() << '\n';
			exit(ERR_VEC);
		}
	}
	vector<T>& operator=(const vector<T>& v) {
		try {
			capacity = v.capacity;
			sizev = v.sizev;
			delete[] data;
			data = new T[capacity];
			for (int i = 0; i < sizev; i++) {
				data[i] = v.data[i];
			}
			return *this;
		}
		catch (std::exception& e) {
			std::cout << "vector operator= " << e.what() << '\n';
			exit(ERR_VEC);
		}
	}

	vector(const vector& v) {
		try {
			capacity = v.capacity;
			sizev = v.sizev;
			data = new T[capacity];
			for (int i = 0; i < sizev; i++) {
				data[i] = v.data[i];
			}
		}
		catch (std::exception& e) {
			std::cout << "vector copy constructor: " << e.what() << '\n';
			exit(ERR_VEC);
		}
	}
	
	size_t size() {
		return sizev;
	}
};