#include <iostream>

// Your code must compile.
#include "rational.hpp"
#include "rational.hpp"

using namespace std;

int main()
{
    Rational a(-6, 10);
    Rational b(1, 7);
    Rational c(4);
    Rational a1=a;
    a1 += Rational(1, 5);


    cout << a << endl;
    cout << a1<< endl;
    cout << b << endl;
    cout << c << endl;

    cout << a << " " << a+b << " " << b-a << " " << b/a << endl;
    // -3/5 -16/35 26/35 -5/21
}

