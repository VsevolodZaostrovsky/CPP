#include <iostream>
#include "Matrix.h"

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

std::ostream &operator<<(std::ostream &os, const Matrix &M)
{
    for(int k = 0; k < M._M * M._N; k++) {
        if (k % M._M == 0) { std::cout << std::endl; }
        std::cout << M._value[k] << " ";
    }
    std::cout << std::endl; 
    return os;
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

bool operator>(const Matrix& A, const Matrix& B) {
    double Sum_A = 0;
    double Sum_B = 0;
    for (int k = 0; k < A._N * A._M; ++k) {
        Sum_A += A._value[k] * A._value[k];
    }
    for (int i = 0; i < B._N * B._M; ++i) {
        Sum_B += B._value[i] * B._value[i];
    }
    if(Sum_A > Sum_B) {
        return 1;
    }
    return 0;
}

void Matrix::set(int n, int m, double r) {
    if (n >= _N || m >= _M) {
        throw MyException("Matrix::set.Bad size of the matrix.",BAD_SIZE);
        return;
    }
    _value[_M*n + m] = r;
}