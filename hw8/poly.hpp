#ifndef POLY_HPP_
#define POLY_HPP_

#include <stdlib.h>
#include <vector>
#include<algorithm>
#include <cmath>

template<typename T>
class Poly {
public:

	/* Default constructor */
	Poly();

	/* Constructor for a poly that's a constant number */
	Poly(T constant);

	/* Given a vector of coefficients */
	Poly(const std::vector<T>& coeffs);

	/* Given an rvalue reference of a vector of coefficients */
	Poly(std::vector<T>&& coeffs);

	/* Given an array of coefficients with size of the array*/
	Poly(T* coeffs, size_t numberCoeffs);

	/* Given an initializer_list */
	Poly(std::initializer_list<T> coeffs);

	virtual ~Poly() {};

	/* Copying constructor */
	Poly(const Poly<T>& poly);

	/* Copying constructor with rvalue reference */
	Poly(Poly<T>&& poly);

	int length() { return _coeffs.size(); };
	
	///* Assignment operator */
	Poly<T>& operator=(const Poly<T>& poly);
	//
	///* Assignment operator with rvalue reference */
	Poly<T>& operator=(Poly<T>&& poly);

	/*
	 * Below are operations of polynomials.
	 * They are quite self-explanatory.
	 */

	Poly<T> operator+(const Poly<T>& rhs) const;
	Poly<T> operator-(const Poly<T>& rhs) const;
	Poly<T> operator*(const Poly<T>& rhs) const;

	Poly<T>& operator+=(const Poly<T>& rhs);
	Poly<T>& operator-=(const Poly<T>& rhs);
	Poly<T>& operator*=(const Poly<T>& rhs);

	/*
	 * This function evaluates the polynomial at "param",
	 * and returns the value of evaluation.
	 * For example, evaluating x+3 at param=7 gives 10.
	 */
	T eval(T param) const;

	/*
	 * This function takes the derivative of the polynomial,
	 * and returns a new polynomial of its derivative.
	 * For example, calling this function for x^2
	 * will return a polynomial 2x.
	 */
	Poly<T> der() const;

	/*
	* This function returns a pair of:
	* 1. the value (evaluation) of the polynomial at "param".
	* 2. the value of the first-order derivative of the polynomial at "param".
	* For example, calling this operator for x^2-2x at "param"=4
	* will return (8, 6).
	*/
	std::pair<T, T> operator()(T param) const;

private:
	std::vector<T> _coeffs;

};


#endif

template<typename T>
inline Poly<T>::Poly()
{
}

template<typename T>
inline Poly<T>::Poly(T constant)
{
	_coeffs.push_back(constant);
}

template<typename T>
inline Poly<T>::Poly(const std::vector<T>& coeffs)
{
	_coeffs = coeffs;
}

template<typename T>
inline Poly<T>::Poly(std::vector<T>&& coeffs)
{
	_coeffs = coeffs;
	coeffs.clear();
}

template<typename T>
inline Poly<T>::Poly(T* coeffs, size_t numberCoeffs)
{
	for (int i = 0;i < numberCoeffs;i++)
	{
		_coeffs.push_back(*(coeffs + i));
	}
}

template<typename T>
inline Poly<T>::Poly(std::initializer_list<T> coeffs)
{
	for (auto x : coeffs)
	{
		_coeffs.push_back(x);
	}
}

template<typename T>
inline Poly<T>::Poly(const Poly<T>& poly)
{
	_coeffs = poly._coeffs;
}

template<typename T>
inline Poly<T>::Poly(Poly<T>&& poly)
{
	_coeffs = poly._coeffs;
	poly._coeffs.clear();
	poly.~Poly();
}

template<typename T>
inline Poly<T>& Poly<T>::operator=(const Poly<T>& poly)
{
	this->_coeffs = poly._coeffs;
	return *this;
}

template<typename T>
inline Poly<T>& Poly<T>::operator=(Poly<T>&& poly)
{
	this->_coeffs = poly._coeffs;
	// poly.~Poly();
	return *this;
}

template<typename T>
inline Poly<T> Poly<T>::operator+(const Poly<T>& rhs) const
{
	//return GenNewOne(this->_coeffs, rhs._coeffs, Plus);
	using namespace std;
	vector<T>sumtemp(max(rhs._coeffs.size(), this->_coeffs.size()));
	int counter = 0;
	generate(sumtemp.begin(), sumtemp.end(), [&] {
		T result = 0;
		if (counter < rhs._coeffs.size())
			result += rhs._coeffs[counter];
		if (counter < this->_coeffs.size())
			result += this->_coeffs[counter];

		counter++;
		return result;
		});

	return (sumtemp);
}

template<typename T>
inline Poly<T> Poly<T>::operator-(const Poly<T>& rhs) const
{
	using namespace std;
	vector<T>sumtemp(max(rhs._coeffs.size(), this->_coeffs.size()));
	int counter = 0;
	generate(sumtemp.begin(), sumtemp.end(), [&] {
		T result = 0;
		if (counter < rhs._coeffs.size())
			result -= rhs._coeffs[counter];
		if (counter < this->_coeffs.size())
			result += this->_coeffs[counter];
		counter++;

		return result;
		});

	return (sumtemp);
}

template<typename T>
inline Poly<T> Poly<T>::operator*(const Poly<T>& rhs) const
{
	using namespace std;
	vector<T>sumtemp((rhs._coeffs.size() + this->_coeffs.size()));
	for (int i = 0;i < this->_coeffs.size();i++)
	{
		for (int j = 0;j < rhs._coeffs.size();j++)
		{
			T value = _coeffs[i] * rhs._coeffs[j];
			sumtemp[i + j] += value;
		}
	}
	//for_each(this->_coeffs.begin(), this->_coeffs.end(), [&](auto it) {
	//	for_each(rhs._coeffs.begin(), rhs._coeffs.end(), [&](auto itt) {
	//		T vaule = *it * (*itt);
	//		sumtemp[it-this->_coeffs.begin()+ itt- rhs._coeffs.begin()];
	//		});
	//	});

	return (sumtemp);
}

template<typename T>
inline Poly<T>& Poly<T>::operator+=(const Poly<T>& rhs)
{
	this->_coeffs = (*this + rhs)._coeffs;
	return *this;
}

template<typename T>
inline Poly<T>& Poly<T>::operator-=(const Poly<T>& rhs)
{
	this->_coeffs = (*this - rhs)._coeffs;
	return *this;
}

template<typename T>
inline Poly<T>& Poly<T>::operator*=(const Poly<T>& rhs)
{
	this->_coeffs = (*this * rhs)._coeffs;
	return *this;
}

template<typename T>
inline T Poly<T>::eval(T param) const
{
	T result = 0;
	for (int i = 0;i < _coeffs.size();i++)
	{
		result += pow(param, i) * _coeffs[i];
	}
	return result;
}

template<typename T>
inline Poly<T> Poly<T>::der() const
{
	Poly<T> deThis;
	for (int i = 1;i < this->_coeffs.size();i++)
	{

		deThis._coeffs.push_back(this->_coeffs[i] * i);
	}
	return deThis;
}

template<typename T>
inline std::pair<T, T> Poly<T>::operator()(T param) const
{
	T result1 = this->eval(param);
	T result2 = this->der().eval(param);
	std::pair<T, T>res(result1, result2);

	return res;
}
