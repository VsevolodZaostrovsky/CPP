#include "Matrix.h"
#include <iostream>

couple& Matrix::getsize() const{
    couple Size;
    Size.N = _N;
    Size.M = _M;
    couple &ref = Size;
    return ref;
}

Matrix::Matrix(int N, int M) : _N(N), _M(M), _value(new double[N * M]) {
    if (N <= 0 || M <= 0) {
        throw MyException("Matrix::Matrix.Bad size of the matrix.",BAD_SIZE);
    }
    for(int k = 0; k < N*M; k++) {
        this->_value[k] = 0;
    }
}

Matrix::~Matrix() {
    delete[] _value;
    _N = 0; _M = 0;
   // std::cout << "destruction is done"<< std::endl;
}

void Matrix::print() const{
    for(int k = 0; k < _N*_M; k++) {
        if (k % _M == 0) { std::cout << std::endl; }
        std::cout << _value[k] << " ";
    }
    std::cout << std::endl; 
}

Matrix::Matrix(const Matrix &Ma) {
    _N = Ma._N; 
    _M = Ma._M; 
    _value = new double[_N * _M];  
    for(int k = 0; k < _N * _M; k++) {
        this->_value[k] = Ma._value[k]; 
    }
}

Matrix Matrix :: operator+ (const Matrix& Ma) const {
    if (this -> _N != Ma._N || this -> _M != Ma._M) {
        throw MyException("Matrix::operator+.Bad size of the matrix.",BAD_SIZE);
    }
    Matrix Sum(Ma._N, Ma._M);

    for(int k = 0; k < _N * _M; k++) {
            Sum._value[k] = this -> _value[k] + Ma._value[k];
    } 
    Matrix &ref = Sum;
    return ref;
}

Matrix &Matrix :: operator= (const Matrix &Ma) {
    if (this == &Ma) {
        return *this;
    }

    this -> _N = Ma._N;
    this -> _M = Ma._M;
    delete [] this -> _value;
    this -> _value = new double[_N*_M];
    for(int k = 0; k < _N * _M; k++) {
            this -> _value[k] = Ma._value[k];
    }
    return *this;

}

Matrix::Submatrix::Submatrix(int i, int j, int n, int m, const Matrix &Ma)
    : _i(i), _j(j), _m(m), _n(n), _value(Ma._value), _N(Ma._N), _M(Ma._M) { 
      if ((i + n) > Ma._N || (j + m) > Ma._M) {
        throw MyException("76 Submatrix.Bad size of the submatrix.", BAD_SIZE);
    } 
}  

Matrix::Row::Row(double * value, int len) {
    _rvalue = value;
    _len = len;
}

Matrix::Row& Matrix::operator[](int n) const {
    if (n > _N - 1) {
        throw MyException("87 Matrix::operator[] Index is out of the row", BAD_ROW);
    }
    Row R(_value + n * _M, _M);
    Row &ref = R;
    return ref;
}

Matrix::Row& Matrix::Submatrix::operator[] (int k) const{
    if (k > _n + _i - 1 || k < _i - 1) {
        throw MyException("96 Submatrix::operator[] Row is out of the submatrix", BAD_ROW);
    }
    Row R(_value + (_i + k) * _M + _j, _m);
    Row & ref = R;
    return ref;
}

double & Matrix::Row::operator[](int k) const {
    if (k > _len - 1) {
        throw MyException("105 Row. Index is out of the row", BAD_ROW);
    }
    return _rvalue[k];
}