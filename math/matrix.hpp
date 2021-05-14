#ifndef _DYNAMOL_MATRIX_H_
#define _DYNAMOL_MATRIX_H_
#include <vector>
#include <string>
/* Matrix class (never used in this code though :p) */
class Matrix {
    public:
    std::vector<double> val;

    public:
    int row, col;
    
    Matrix(int row, int col);
    Matrix(int row, int col, std::vector<double> m0);
    ~Matrix();

    /* Linear access */
    double &operator[](int i) {return val[i]; };
    double operator[](int i) const {return val[i]; };
    
    /* Wrapped access */
    double& operator()(int i,int j);
    double operator()(int i, int j) const;

    /* Operator overloads*/
    friend Matrix operator+(Matrix const &m1, Matrix const &m2);
    friend Matrix operator+(double const& c, Matrix const& m1);
    friend Matrix operator+(Matrix const& m1, double const& c);
    friend Matrix operator-(Matrix const& m1, Matrix const& m2);
    friend Matrix operator-(Matrix const& m1, double const& c);
    friend Matrix operator*(double const &k, Matrix const &m1);
    friend Matrix operator*(Matrix const &m1, double const &k);
    friend Matrix operator*(Matrix const &m1, Matrix const &m2);
    friend Matrix operator/(Matrix const &m1,double const &k);

    /*Norm*/
    double norm();

    /*Stringify */
    std::string strfy();
};

#endif