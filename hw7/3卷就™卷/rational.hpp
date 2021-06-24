#include <iostream>

#ifndef haveDef
class Rational
{
public:
    // Constructors
    Rational();
    Rational(int value);
    Rational(int p, unsigned int q);

    // Assignment operator
    Rational& operator=(const Rational& that);

    // Arithmetic operators
    Rational  operator+(Rational that) const;
    Rational& operator+=(Rational that);
    Rational  operator-(Rational that) const;
    Rational& operator-=(Rational that);
    Rational  operator*(Rational that) const;
    Rational& operator*=(Rational that);
    Rational  operator/(Rational that) const;
    Rational& operator/=(Rational that);

    // Comparison operators: equal and less than
    bool operator==(Rational that) const;
    bool operator<(Rational that) const;

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Rational& number);

private:
    int m_numerator;
    unsigned int m_denominator;
};

#endif
#define haveDef