#pragma once
#include <iostream>

class Complex {
public:
	Complex() {
		real = 0;
		img = 0;
	}
	Complex(const Complex& v) {
		this->real = v.real;
		this->img = v.img;
	}
	Complex(double a) {
		if (abs(a + INF_DOUBLE) < EPS_DOUBLE) {
			real = img = 0;
		}
		else {
			real = a;
			img = 0;
		}
	}
	Complex(double a, double b) {
		this->img = b;
		this->real = a;
	}
	~Complex() {
		img = real = 0;
	}
	double module() const {
		return sqrt(img * img + real * real);
	}
	double angle()const {
		return atan2(img, real);
	}
	Complex operator + (const Complex& c) {
		return Complex(this->real + c.real, this->img + c.img);
	}
	Complex operator + (const Complex& c)const {
		return Complex(this->real + c.real, this->img + c.img);
	}
	Complex operator - () const {
		return Complex(-real, -img);
	}
	Complex operator - (const Complex& c) {
		return Complex(this->real - c.real, this->img - c.img);
	}
	Complex operator / (const Complex& c) {
		return Complex(((this->real * c.real) + (this->img * c.img)) / (c.real * c.real + c.img * c.img), ((this->img * c.real) - (this->real * c.img)) / (c.real * c.real + c.img * c.img));
	}
	Complex operator / (const Complex& c)const {
		return Complex(((this->real * c.real) + (this->img * c.img)) / (c.real * c.real + c.img * c.img), ((this->img * c.real) - (this->real * c.img)) / (c.real * c.real + c.img * c.img));
	}
	Complex operator * (const Complex& c) {
		return Complex(this->real * c.real - this->img * c.img, this->real * c.img + this->img * c.real);
	}
	Complex operator * (const Complex& c)const {
		return Complex(this->real * c.real - this->img * c.img, this->real * c.img + this->img * c.real);
	}
	Complex& operator=(const Complex& c) {
		if (&c != this) {
			real = c.real;
			img = c.img;
		}
		return *this;
	}
	bool operator == (const Complex& c) {
		return this->module() == c.module() && this->angle() == c.angle();
	}
	bool operator > (const Complex& c) {
		return (this->module() > c.module()) || (this->module() == c.module() && this->angle() > c.angle());
	}
	bool operator < (const Complex& c) {
		return (this->module() < c.module()) || (this->module() == c.module() && this->angle() < c.angle());
	}
	bool operator >= (const Complex& c) {
		return (this->module() == c.module() && this->angle() == c.angle()) || ((this->module() > c.module()) || (this->module() == c.module() && this->angle() > c.angle()));
	}
	bool operator <= (const Complex& c) {
		return (this->module() == c.module() && this->angle() == c.angle()) || ((this->module() < c.module()) || (this->module() == c.module() && this->angle() < c.angle()));
	}
	bool operator != (const Complex& c) {
		return this->module() != c.module() || this->angle() != c.angle();
	}
	void setReal(double val) {
		this->real = val;
	}
	void setImg(double val) {
		this->img = val;
	}
	double getReal() {
		return real;
	}
	double getImg() {
		return img;
	}
	double getReal() const{
		return real;
	}
	double getImg() const{
		return img;
	}
private:
	double real;
	double img;
};

std::istream& operator>>(std::istream& is, Complex& c) {
	double tmp;
	is >> tmp;
	c.setReal(tmp);
	is >> tmp;
	c.setImg(tmp);
	return is;
}
std::ostream& operator<<(std::ostream& os, const Complex& c) {
	os << '{' << c.getReal() << " , " << c.getImg() << '}';
	return os;
}
Complex abs(const Complex& val) {
	return val.module();
}
