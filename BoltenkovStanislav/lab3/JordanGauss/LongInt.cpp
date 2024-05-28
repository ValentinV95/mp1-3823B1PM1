#include "LongInt.h"

longInt abs(const longInt& a)
{
	longInt c = a;
	if (!c.sign) c.sign = true;
	return c;
}

void longInt::init(int newn)
{
	number.resize(newn);
	for (int i = n; i < newn; i++) number[i] = 0;
	n = newn;
	return;
}

longInt longInt::usum(const longInt& b) const
{
	longInt c;
	c.init(n + 1);
	for (int i = 0; i < n; i++)
	{
		c.number[i] += (i < b.n) ? b.number[i] + number[i] : number[i];
		bool r = c.number[i] >= BASE;
		c.number[i + 1] += r;
		if (r) c.number[i] -= BASE;
	}
	if (c.number[c.n - 1] == 0) c.init(c.n - 1);
	return c;
}

longInt longInt::udiff(const longInt& b) const
{
	longInt c;
	c.init(n);
	for (int i = 0; i < n; i++)
	{
		c.number[i] += (i < b.n) ? number[i] - b.number[i] : number[i];
		bool r = c.number[i] < 0;
		if (r)
		{
			c.number[i + 1] -= r;
			c.number[i] += BASE;
		}
	}
	int cnt = 0, ind = c.n - 1;
	while (c.number[ind] == 0 && ind >= 1)
	{
		cnt++;
		ind--;
	}
	c.init(c.n - cnt);
	return c;
}

longInt::longInt() : BASE(1000 * 1000 * 1000)
{
	n = 1;
	sign = true;
	number.resize(n);
	number[0] = 0;
}

longInt::longInt(const longInt& a) : BASE(1000 * 1000 * 1000)
{
	n = a.n;
	sign = a.sign;
	number.resize(n);
	for (int i = 0; i < n; i++)
	{
		number[i] = a.number[i];
	}
}

longInt::longInt(const int& a) : BASE(1000 * 1000 * 1000)
{
	n = 1 + (abs(a) > BASE);
	sign = a >= 0;
	number.resize(n);
	number[0] = abs(a) % BASE;
	if (n == 2) number[1] = abs(a) / BASE;
}

longInt::longInt(const long long& a) : BASE(1000 * 1000 * 1000)
{
	long long c = abs(a);
	n = 1 + (c > BASE);
	sign = a >= 0;
	number.resize(n);

	number[0] = c % BASE;
	c /= BASE;
	if (n == 2) number[1] = c % BASE;
	c /= BASE;
	if (c != 0)
	{
		number.resize(++n);
		number[2] = c;
	}

}

longInt::~longInt()
{

}

std::istream& operator>>(std::istream& in, longInt& a)
{
	std::string s;
	in >> s;
	int len = s.size(), ind = 0;
	a.init(1 + s.size() / 9);
	if (s[0] == '-')
	{
		a.sign = 0;
		s[0] = '0';
	}
	for (int i = len - 1; i >= 0; i -= 9)
	{
		if (i >= 8) a.number[ind] = atoi(s.substr(i - 8, 9).c_str());
		else a.number[ind] = atoi(s.substr(0, len % 9).c_str());
		ind++;
	}
	a.init(ind);
	return in;
}

std::ostream& operator<<(std::ostream& os, const longInt& a)
{
	if (!a.sign && !(a.n == 1 && a.number[0] == 0)) os << "-";
	os << a.number[a.n - 1];
	std::string s;
	for (int i = a.n - 2; i >= 0; i--)
	{
		for (int j = 0; j < 9 - std::to_string(a.number[i]).size(); j++) os << "0";
		os << a.number[i];
	}
	return os;
}

longInt& longInt::operator=(const longInt& b)
{
	number.resize(b.n);
	sign = b.sign;
	n = b.n;
	for (int i = 0; i < n; i++) number[i] = b.number[i];
	return *this;
}

longInt& longInt::operator=(const int& b)
{
	n = 1 + (abs(b) > BASE);
	sign = b >= 0;
	number.resize(n);
	number[0] = abs(b) % BASE;
	if (n == 2) number[1] = abs(b) / BASE;
	return *this;
}

longInt& longInt::operator=(const long long& b)
{
	long long c = abs(b);
	n = 1 + (c > BASE);
	sign = b >= 0;
	number.resize(n); 

	number[0] = c % BASE;
	c /= BASE;
	if (n == 2) number[1] = c % BASE;
	c /= BASE;
	if (c != 0)
	{
		number.resize(++n);
		number[2] = c;
	}

	return *this;
}

longInt longInt::operator+(const longInt& b) const
{
	longInt c;
	bool f = abs(*this) < abs(b);
	if (sign == b.sign)
	{
		c = (f) ? b.usum(*this) : this->usum(b);
		c.sign = this->sign;
	}
	else
	{
		if (f) c = b.udiff(*this);
		else c = this->udiff(b);
		if (c != 0 && (f && !b.sign || !f && !sign)) c.sign = 0;
	}
	return c;
}

longInt& longInt::operator+=(const longInt& b)
{
	*this = *this + b;
	return *this;
}
longInt& longInt::operator-=(const longInt& b)
{
	*this = *this - b;
	return *this;
}

longInt& longInt::operator*=(const longInt& b)
{
	*this = *this * b;
	return *this;
}

longInt& longInt::operator/=(const longInt& b)
{
	*this = *this / b;
	return *this;
}

longInt& longInt::operator%=(const longInt& b)
{
	*this = *this % b;
	return *this;
}

longInt longInt::operator-(const longInt& b) const
{
	longInt c = b;
	c.sign = !c.sign;
	c = *this + c;
	return c;
}

longInt& longInt::operator++()
{
	*this += 1;
	return *this;
}

longInt longInt::operator++(int)
{
	longInt c = *this;
	++*this;
	return c;
}

longInt& longInt::operator--()
{
	*this -= 1;
	return *this;
}

longInt longInt::operator--(int)
{
	longInt c = *this;
	--*this;
	return c;
}

longInt longInt::operator*(const longInt& b) const
{
	longInt c;
	c.init(n + b.n);
	for (int i = 0; i < b.n; i++)
	{
		long long r = 0;
		for (int j = 0; j < n; j++)
		{
			long long t = (long long)c.number[i + j] + number[j] * (long long)b.number[i] + r;
			c.number[i + j] = t % (long long)BASE;
			r = t / (long long)BASE;
		}
		if (r > 0) c.number[i + n] = r;
	}
	int cnt = 0, ind = c.n - 1;
	while (c.number[ind] == 0 && ind >= 1)
	{
		cnt++;
		ind--;
	}
	c.init(c.n - cnt);
	c.sign = !(sign != b.sign);
	return c;
}

bool longInt::operator<(const longInt& b) const
{
	if (sign != b.sign) return sign < b.sign;
	if (n != b.n) return n < b.n;
	for (int i = n - 1; i >= 0; i--)
	{
		if (number[i] < b.number[i]) return sign;
		if (number[i] > b.number[i]) return !sign;
	}
	return false;//оказались равны
}

bool longInt::operator>(const longInt& b) const
{
	return !(*this < b);
}

bool longInt::operator==(const longInt& b) const
{
	if (n == 1 && b.n == 1 && number[0] == 0 && b.number[0] == 0) return true;
	if (sign != b.sign) return false;
	if (n != b.n) return false;
	for (int i = 0; i < n; i++)
	{
		if (number[i] != b.number[i]) return false;
	}
	return true;
}

bool longInt::operator!=(const longInt& b) const
{
	return !(*this == b);
}

bool longInt::operator<=(const longInt& b) const
{
	return (*this < b) || (*this == b);
}

bool longInt::operator>=(const longInt& b) const
{
	return (*this > b) || (*this == b);
}

int binSearch(const longInt& a, const longInt& b)
{
	if (a < b) return 0;
	int res = 0, l = 0, r = 1000 * 1000 * 1000 - 1;
	while (l <= r)
	{
		int c = l + (r - l) / 2;
		longInt t = a - longInt(c) * b;
		if (t >= 0)
		{
			res = c;
			l = c + 1;
		}
		else r = c - 1;
	}
	return res;
}

longInt longInt::operator/(const longInt& b) const
{
	longInt res, ri;
	if (abs(*this) < abs(b)) return res;
	res.init(n - b.n + 1);
	res.sign = !(sign != b.sign);

	ri.init(b.n);
	for (int i = b.n - 1; i >= 0; i--) ri.number[(b.n - 1) - i] = number[(n - 1) - i];
	int ind = 0;
	while (ind < res.n)
	{
		int ci = binSearch(ri, abs(b));
		res.number[res.n - ind - 1] = ci;
		ri = ri - longInt(ci) * b;
		if (ri != 0)
		{
			ri.init(ri.n + 1);
			for (int i = ri.n - 1; i >= 1; i--)
			{
				ri.number[i] = ri.number[i - 1];
			}
		}
		if (((n - b.n) - 1) - ind >= 0) ri.number[0] = number[((n - b.n) - 1) - ind];
		ind++;
	}
	int cnt = 0;
	ind = res.n - 1;
	while (res.number[ind] == 0 && ind >= 1)
	{
		cnt++;
		ind--;
	}
	res.init(res.n - cnt);
	return res;
}

longInt longInt::operator%(const longInt& b) const
{
	longInt c = *this / b;
	return *this - b * c;
}