#ifndef FUNCTIONAL_FORMS_HPP_
#define FUNCTIONAL_FORMS_HPP_

#include <stdlib.h>
#include <math.h>

/* For all lambda functions below, if you are not clear how they work, please refer to the given example for details. */


/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1+f2)(m) as first, and (d(f1+f2)/dx)(m) as second.
 */
auto derSum = [](auto f1, auto f2 ){
	return [=] (auto m){
		double re1 = f1(m).first + f2(m).first;
		double re2 = f1(m).second+ f2(m).second;
		std::pair<double, double> re(re1, re2);
		return re;
	};
};


/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1-f2)(m) as first, and (d(f1-f2)/dx)(m) as second.
 */
auto derSub = []( auto f1, auto f2 ){
	return [=](auto m) {
		double re1 = f1(m).first - f2(m).first;
		double re2 = f1(m).second - f2(m).second;
		std::pair<double, double> re(re1, re2);
		return re;
	};
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1*f2)(m) as first, and (d(f1*f2)/dx)(m) as second.
 */
auto derMul = []( auto f1, auto f2 ){
	return [=](auto m) {
		double re1 = f1(m).first * f2(m).first;
		double re2 = f1(m).second * f2(m).first+f1(m).first*f2(m).second;
		std::pair<double, double> re(re1, re2);
		return re;
	};
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1/f2)(m) as first, and (d(f1/f2)/dx)(m) as second.
 */
auto derDiv = []( auto f1, auto f2 ){

	return [=](auto m) {
		double re1 = f1(m).first / f2(m).first;
		double re2 = (f1(m).second * f2(m).first - f1(m).first * f2(m).second)/pow(f2(m).first,2);
		std::pair<double, double> re(re1, re2);
		return re;
	};
};

Poly<double> pow(Poly<double>f, int power)
{
	Poly<double> mulre(1);
	for (size_t i = 0; i < power; i++)
	{
		mulre *= f;
	}
	return mulre;
};
/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1(f2))(m) as first, and (d(f1(f2))/dx)(m) as second.
 */
auto derComp =[](auto f1, auto f2) {
	return [=](auto m) {
		double re1 = f2(f1(m).first).first;
		double re2 = f2(f1(m).first).second * f1(m).second;
		std::pair<double, double> re(re1, re2);
		return re;
	};
	//return [=](double m) {
		//decltype(f1) compoud;
		//Poly<double>compoud;
		//for (int i = 0;i < f1._coeffs.size();i++)
		//{
		//	compoud += Poly<double>(f1._coeffs[i]) * pow(f2, i);
		//}
		//return compoud;
		//double re1 = compoud.eval(m);
		//double re2 = compoud.der().eval(m);
		//std::pair<double, double> re(re1, re2);
		//return re;
	//};
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has [(f1)(m)]^exp as first, and (d(f1^exp)/dx)(m) as second.
 */
auto derPow = []( auto f, int exp ) {
	return [=](auto m) {
		double re1 = pow(f(m).first, exp);
		double re2 = exp*pow(f(m).first,exp-1)*f(m).second;
		std::pair<double, double> re(re1, re2);
		return re;
	};
};

#endif