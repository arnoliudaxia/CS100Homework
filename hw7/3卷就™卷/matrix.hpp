#include <iostream>
#include <vector>

#ifndef LALALA
#define LALALA


using namespace std;
template<typename T>
class Matrix {
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int cols, const T& value = T());

    T& operator()(unsigned int r, unsigned int c);

    void Print();

    void GaussJordan();

private:
    std::vector<vector<T>>content;
};

#endif 
