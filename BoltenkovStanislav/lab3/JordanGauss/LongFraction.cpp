#include "LongFraction.h"

longInt gcd(longInt a, longInt b)
{
	if (a == 0) return b;
	return gcd(b, a % b);
}

longFraction abs(const longFraction& a)
{
	longFraction b = a;
	if (!b.sign) b.sign = true;
	return b;
}

void longFraction::reducingFraction()
{
	longInt c = gcd(numerator, denominator);
	numerator /= c;
	denominator /= c;
	wholePart += numerator / denominator;
	numerator %= denominator;
	if (wholePart == 0 && numerator == 0) sign = true;
	return;
}

longFraction::longFraction(const longInt& wholePart, const longInt& numerator, const longInt& denominator)
{
	this->numerator = numerator;
	this->denominator = denominator;
	sign = wholePart >= 0;
	if (!sign) this->wholePart = abs(wholePart);
	else this->wholePart = wholePart;
	reducingFraction();
}

longFraction::longFraction(const longInt& wholePart)
{
	this->numerator = 0;
	this->denominator = 1;
	sign = wholePart >= 0;
	if (!sign) this->wholePart = abs(wholePart);
	else this->wholePart = wholePart;
	reducingFraction();
}

longFraction::longFraction(const longFraction& b)
{
	numerator = b.numerator;
	denominator = b.denominator;
	wholePart = b.wholePart;
	sign = b.sign;
}

longFraction::longFraction(const int& b)
{
	numerator = 0;
	denominator = 1;
	wholePart = abs(b);
	sign = b >= 0;
}

longFraction::longFraction(const long long& b)
{
	numerator = 0;
	denominator = 1;
	wholePart = abs(b);
	sign = b >= 0;
}

longFraction::~longFraction()
{

}

longFraction& longFraction::operator=(const longFraction& b)
{
	numerator = b.numerator;
	denominator = b.denominator;
	wholePart = b.wholePart;
	sign = b.sign;
	return *this;
}

longFraction& longFraction::operator=(const int& b)
{
	numerator = 0;
	denominator = 1;
	wholePart = abs(b);
	sign = b >= 0;
	return *this;
}

longFraction& longFraction::operator=(const long long& b)
{
	numerator = 0;
	denominator = 1;
	wholePart = abs(b);
	sign = b >= 0;
	return *this;
}

std::istream& operator>>(std::istream& in, longFraction& a)
{
	in >> a.wholePart >> a.numerator >> a.denominator;
	a.sign = !((a.numerator >= 0) ^ (a.wholePart >= 0));
	a.numerator = abs(a.numerator);
	a.wholePart = abs(a.wholePart);
	a.reducingFraction();
	return in;
}

std::ostream& operator<<(std::ostream& os, const longFraction& a)
{
	if (!a.sign) os << '-';
	if (a.wholePart != 0) os << a.wholePart;
	if (a.numerator != 0 && a.wholePart != 0) os << '(' << a.numerator << '/' << a.denominator << ')';
	else if (a.numerator != 0) os << a.numerator << '/' << a.denominator;
	else if (a.wholePart == 0 && a.numerator == 0) os << 0;
	return os;
}

longFraction longFraction::udiff(const longFraction& b) const
{
	longFraction c;
	if (!b.sign)
	{
		c.numerator = (this->numerator + this->wholePart * this->denominator) * b.denominator - (b.numerator + b.wholePart * b.denominator) * this->denominator;
	}
	else
	{
		c.numerator = (b.numerator + b.wholePart * b.denominator) * this->denominator - (this->numerator + this->wholePart * this->denominator) * b.denominator;
	}
	c.denominator = this->denominator * b.denominator;
	if (c.numerator < 0)
	{
		c.sign = false;
		c.numerator = abs(c.numerator);
	}
	c.reducingFraction();
	return c;
}

longFraction longFraction::usum(const longFraction& b) const
{
	longFraction c;
	c.wholePart = this->wholePart + b.wholePart;
	c.numerator = this->numerator * b.denominator + b.numerator * this->denominator;
	c.denominator = this->denominator * b.denominator;
	if (c != 0) c.sign = b.sign;
	c.reducingFraction();
	return c;
}

longFraction longFraction::operator+(const longFraction& b) const
{
	if (sign == b.sign) return this->usum(b);
	return this->udiff(b);
}

longFraction longFraction::operator-(const longFraction& b) const
{
	longFraction c = b;
	c.sign = !c.sign;
	return *this + c;
}

longFraction longFraction::operator*(const longFraction& b) const
{
	longFraction c;
	c.numerator = (this->numerator + this->wholePart * this->denominator) * (b.numerator + b.wholePart * b.denominator);
	c.denominator = this->denominator * b.denominator;
	if (sign != b.sign)
	{
		c.sign = false;
		c.numerator = abs(c.numerator);
	}
	c.reducingFraction();
	return c;
}

longFraction longFraction::operator/(const longFraction& b) const
{
	longFraction c;
	c.sign = b.sign;
	c.numerator = b.denominator;
	c.denominator = b.numerator + b.denominator * b.wholePart;
	c.reducingFraction();
	return *this * c;
}

longFraction& longFraction::operator+=(const longFraction& b)
{
	*this = *this + b;
	return *this;
}

longFraction& longFraction::operator-=(const longFraction& b)
{
	*this = *this - b;
	return *this;
}

longFraction& longFraction::operator*=(const longFraction& b)
{
	*this = *this * b;
	return *this;
}

longFraction& longFraction::operator/=(const longFraction& b)
{
	*this = *this / b;
	return *this;
}

bool longFraction::operator<(const longFraction& b) const
{
	if (this->sign != b.sign) return sign < b.sign;
	bool res = (this->numerator + this->wholePart * this->denominator) * b.denominator < (b.numerator + b.wholePart * b.denominator) * this->denominator;
	return (sign) ? res : !res;
}

bool longFraction::operator>(const longFraction& b) const
{
	return !(*this < b);
}

bool longFraction::operator==(const longFraction& b) const
{
	if (this->sign != b.sign) return false;
	return (this->numerator + this->wholePart * this->denominator) * b.denominator == (b.numerator + b.wholePart * b.denominator) * this->denominator;;
}

bool longFraction::operator!=(const longFraction& b) const
{
	return !(*this == b);
}

bool longFraction::operator>=(const longFraction& b) const
{
	return *this == b || *this > b;
}

bool longFraction::operator<=(const longFraction& b) const
{
	return *this == b || *this < b;
}