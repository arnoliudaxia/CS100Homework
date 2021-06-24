#include  "rational.hpp"


Rational safeGen(int p, int q)
{
	if (q < 0) {
		q = -q;
		p = -p;
	}
	return Rational(p, q);
}
Rational::Rational()
{
	this->m_numerator = 0;this->m_denominator = 1;
}
Rational::Rational(int p, unsigned int q)
{
	if (q == 0)
	{
		std::cout << "ERROR: initializing with a denominator of 0!" << std::endl;
		this->m_numerator = 0;this->m_denominator = 1;
		return;
	}

	const int minN = abs(p) > q ? q : abs(p);
	int maxFactor = 1;
	for (size_t i = 1; i <= minN; i++)
	{
		if (abs(p) % i == 0 && q % i == 0)maxFactor = i;
	}
	p /= maxFactor, q /= maxFactor;
	this->m_numerator = p, this->m_denominator = q;
}
Rational& Rational::operator=(const Rational& that)
{
	this->m_numerator = that.m_numerator;
	this->m_denominator = that.m_denominator;
	return *(this);
}
Rational Rational::operator+(Rational that) const
{
	int newN, newD;
	newD = this->m_denominator * that.m_denominator;
	newN = this->m_numerator * that.m_denominator + this->m_denominator * that.m_numerator;
	return Rational(newN, newD);
}
Rational& Rational::operator+=(Rational that)
{
	int newN, newD;
	newD = this->m_denominator * that.m_denominator;
	newN = this->m_numerator * that.m_denominator + this->m_denominator * that.m_numerator;

	*this = Rational(newN, newD);
	return *this;
}
Rational Rational::operator-(Rational that) const
{
	int newN, newD;
	newD = this->m_denominator * that.m_denominator;
	newN = this->m_numerator * that.m_denominator - this->m_denominator * that.m_numerator;
	return Rational(newN, newD);
}
Rational& Rational::operator-=(Rational that)
{
	int newN, newD;
	newD = this->m_denominator * that.m_denominator;
	newN = this->m_numerator * that.m_denominator - this->m_denominator * that.m_numerator;
	*this = Rational(newN, newD);
	return *this;
}
Rational Rational::operator*(Rational that) const
{
	int newN, newD;
	newD = this->m_denominator * that.m_denominator;
	newN = this->m_numerator * that.m_numerator;
	return Rational(newN, newD);
}
Rational& Rational::operator*=(Rational that)
{
	int newN, newD;
	newD = this->m_denominator * that.m_denominator;
	newN = this->m_numerator * that.m_numerator;
	*this = Rational(newN, newD);
	return *this;
}
Rational Rational::operator/(Rational that) const
{
	int newN, newD;
	newD = this->m_denominator * that.m_numerator;
	newN = this->m_numerator * that.m_denominator;
	return safeGen(newN, newD);
}
Rational& Rational::operator/=(Rational that)
{
	int newN, newD;
	newD = this->m_denominator * that.m_numerator;
	newN = this->m_numerator * that.m_denominator;
	*this = safeGen(newN, newD);
	return *this;
}
bool Rational::operator==(Rational that) const
{
	if (this->m_numerator == that.m_numerator && this->m_denominator == that.m_denominator)return true;
	return false;
}
bool Rational::operator<(Rational that) const
{
	return (this->m_numerator * 1.0 / this->m_denominator) < (that.m_numerator * 1.0 / that.m_denominator);
	return false;
}
Rational::Rational(int value)
{
	//Rational(value, 1);
	this->m_numerator = value, this->m_denominator = 1;
}

std::ostream& operator<<(std::ostream& os, const Rational& number)
{
	if (number.m_denominator == 1)os << number.m_numerator << std::endl;
	else
	{
		os << number.m_numerator << "/" << number.m_denominator;
	}
	return os;
}
