#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class longInt {
	const int BASE;
	std::vector<int> number;
	int n;
	bool sign;
	void init(int newn);
	longInt usum(const longInt& b) const;
	longInt udiff(const longInt& b) const;
public:

	longInt();
	longInt(const longInt& a);
	longInt(const int& a);
	longInt(const long long& a);
	~longInt();

	longInt& operator=(const longInt& b);
	longInt& operator=(const int& b);
	longInt& operator=(const long long& b);

	longInt operator+(const longInt& b) const;
	longInt operator-(const longInt& b) const;
	longInt operator*(const longInt& b) const;
	longInt operator/(const longInt& b) const;
	longInt operator%(const longInt& b) const;

	longInt& operator+=(const longInt& b);
	longInt& operator-=(const longInt& b);
	longInt& operator*=(const longInt& b);
	longInt& operator/=(const longInt& b);
	longInt& operator%=(const longInt& b);

	longInt& operator++();
	longInt operator++(int);
	longInt& operator--();
	longInt operator--(int);

	bool operator<(const longInt& b) const;
	bool operator>(const longInt& b) const;
	bool operator==(const longInt& b) const;
	bool operator!=(const longInt& b) const;
	bool operator<=(const longInt& b) const;
	bool operator>=(const longInt& b) const;

	friend std::istream& operator>>(std::istream& in, longInt& a);
	friend std::ostream& operator<<(std::ostream& os, const longInt& a);
	friend longInt abs(const longInt& a);
};

longInt abs(const longInt& a);