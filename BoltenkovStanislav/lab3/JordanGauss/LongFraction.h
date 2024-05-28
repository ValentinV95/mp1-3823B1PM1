#pragma once
#include "LongInt.h"

class longFraction
{
private:
	longInt numerator, denominator, wholePart;
	bool sign;
	
	void reducingFraction();
	longFraction usum(const longFraction& b) const;
	longFraction udiff(const longFraction& b) const;

public:
	longFraction(const longInt& wholePart, const longInt& numerator, const longInt& denominator);
	longFraction(const longInt& wholePart = 0);
	longFraction(const longFraction& b);
	longFraction(const int& b);
	longFraction(const long long& b);
	~longFraction();

	longFraction& operator=(const longFraction& b);
	longFraction& operator=(const int& b);
	longFraction& operator=(const long long& b);

	longFraction operator+(const longFraction& b) const;
	longFraction operator-(const longFraction& b) const;
	longFraction operator*(const longFraction& b) const;
	longFraction operator/(const longFraction& b) const;

	longFraction& operator+=(const longFraction& b);
	longFraction& operator-=(const longFraction& b);
	longFraction& operator*=(const longFraction& b);
	longFraction& operator/=(const longFraction& b);

	bool operator<(const longFraction& b) const;
	bool operator>(const longFraction& b) const;
	bool operator==(const longFraction& b) const;
	bool operator!=(const longFraction& b) const;
	bool operator>=(const longFraction& b) const;
	bool operator<=(const longFraction& b) const;

	friend std::istream& operator>>(std::istream& in, longFraction& a);
	friend std::ostream& operator<<(std::ostream& os, const longFraction& a);
	friend longFraction abs(const longFraction& a);
};

longFraction abs(const longFraction& a);