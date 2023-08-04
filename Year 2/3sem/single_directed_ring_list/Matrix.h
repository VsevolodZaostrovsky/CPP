#ifndef MATRIX
#define MATRIX
#include "MyException.h"

struct couple
{
    int N;
    int M;
};

class Matrix
{
private:
    double *_value;
    int _N; //количество строк
    int _M; //количество столбцов

public:
    Matrix() : _N(1), _M(1), _value(new double[1]) {}
    Matrix(int N, int M);
    Matrix(const Matrix &Ma);
    ~Matrix();

    couple &getsize() const;
    void set(int n, int m, double r);

    void print() const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &M);
    friend bool operator>(const Matrix &A, const Matrix &B);

    Matrix operator+(const Matrix &Ma) const;
    Matrix &operator=(const Matrix &Ma);
};
#endif