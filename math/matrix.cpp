#include "./matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <cmath>

Matrix::Matrix(int _row, int _col){
    row = _row; col = _col;
    if(row * col == 0){
        std::invalid_argument("Matrix::Matrix : Dimension of col/row cannot be zero");
        return;
    }
    val = std::vector<double>(row*col,0);
};

Matrix::Matrix(int _row, int _col, std::vector<double> m0){
    row = _row; col = _col;
    if(row * col == 0){
        std::invalid_argument("Matrix::Matrix : Dimension of col/row cannot be zero");
        return;
    }
    val = m0;
}

Matrix::~Matrix(){
}

double& Matrix::operator()(int i,int j){
    assert((0<=i && i<row && 0<=j && j<col));
    return val[i*col + j];
}

double Matrix::operator()(int i,int j) const {
    assert((0<=i && i<row && 0<=j && j<col));
    return val[i*col + j];
}

Matrix operator+(Matrix const &m1, Matrix const &m2) {
    assert((m1.row == m2.row && m1.col == m2.col));
    Matrix m3(m1.row,m1.col);
    for(int i=0;i<m1.row*m1.col;i++){
        m3[i] = m1[i] + m2[i];
    }
    return m3;
}

Matrix operator+(double const& c, Matrix const& m1){
    Matrix m2(m1.row,m1.col);
    for(int i =0; i < m1.row*m1.col;i++){
        m2[i] = m1[i] + c;
    }
    return m2;
}

Matrix operator+(Matrix const& m1,double const& c){
    return c + m1;
}

Matrix operator-(Matrix const& m1, Matrix const& m2) {
    assert((m1.row == m2.row && m1.col == m2.col));
    Matrix m3(m1.row,m1.col);
    for(int i=0;i<m1.row*m1.col;i++){
        m3[i] = m1[i] - m2[i];
    }
    return m3;
}

Matrix operator-(Matrix const& m1, double const& c){
    return -c + m1;
}

Matrix operator*(double const &k, Matrix const &m1){
    Matrix m2(m1.row,m1.col);
    for(int i =0; i < m1.row*m1.col;i++){
        m2[i] = k*m1[i];
    }
    return m2;
}

Matrix operator*(Matrix const &m1,double const &k){
    return k*m1;
}


Matrix operator*(Matrix const &m1, Matrix const &m2) {
    assert(m1.col == m2.row);
    Matrix m3(m1.row,m2.col);
    for(int r=0;r<m1.row;r++){
        for(int c=0;c<m2.col;c++){
            m3(r,c) = 0;
            for(int k=0;k<m1.col;k++){
                m3(r,c) += m1(r,k)*m2(k,c);
            }
        }
    }
    return m3;
}

Matrix operator/(Matrix const &m1,double const &k) {
    return (1.0/k)*m1;
}


double Matrix::norm(){
    // [sum i,j (aij)^2]^0.5
    double sum = 0;
    for(int i =0; i < row*col;i++){
        sum += val[i]*val[i];
    }
    return sqrt(sum);
}


std::string Matrix::strfy(){
    char buff[500];
    char* str = buff;
    str += sprintf(str,"Matrix(\n");
    for(int r=0;r<row;r++){
        str += sprintf(str,"       ");
        for(int c=0; c<col;c++){
            str += sprintf(str,"%8.3lf",val[r*col+c]);
        }
        str += sprintf(str,"\n");
    }
    str += sprintf(str,")");
    return std::string(buff);
}