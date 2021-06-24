//#include "matrix.hpp"
//#include <vector>
//
//using namespace std;
//template<typename T>
//Matrix<T>::Matrix()
//{
//}
//template<typename T>
//Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const T& value)
//{
//    this->content.reserve(rows);
//    for (int i = 0; i < rows; i++)
//        this->content.push_back(vector<double>(cols, value));
//}
//
//template<typename T>
//T& Matrix<T>::operator()(unsigned int r, unsigned int c)
//{
//    return (this->content[r][c]);
//}
//
//template<typename T>
//void Matrix<T>::Print()
//{
//    for (auto i : content) {
//        for (auto element : i) {
//            cout << element << " ";
//        }
//        cout << endl;
//        cout << endl;
//    }
//}
//
//template<typename T>
//void Matrix<T>::GaussJordan()
//{
//    int h = 1, k = 1;
//    int rows = content.size(), cols = content[0].size();
//    while (h <= rows && k <= cols)
//    {
//        T max, min;
//        max = min = content[h][k];
//        int imax = 1, imin = 1;
//        for (int i = h;i <= rows;i++)
//        {
//            T pivot = content[i - 1][k - 1];
//            if (pivot > max)
//            {
//                max = pivot;
//                imax = i ;
//            }
//            if (pivot < min)
//            {
//                min = i;
//                imin = i;
//            }
//        }
//        if (content[imax][k - 1] == 0)
//        {
//            max = min;
//        }
//        if (content[imax][k - 1] == 0)
//        {
//            k++;
//        }
//        else
//        {
//            auto temp1 = content[h - 1];
//            auto temp2 = content[max - 1];
//            content.insert(content.erase(content.begin() + h - 1), temp2);
//            content.insert(content.erase(content.begin() + max - 1), temp1);
//            for (int i = h + 1;i <= rows;i++)
//            {
//                int f = content[i][k] / content[h][k];
//                content[i][k] = 0;
//                for (int j = k + 1;j <= cols;j++)
//                {
//                    content[i][j] = content[i][j] - content[h][j] * f;
//                }
//            }
//            h++, k++;
//        }
//
//    }
//}
