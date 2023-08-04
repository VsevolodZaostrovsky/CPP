#ifndef MATRIX
#define MATRIX
#include "MyException.h"

struct couple {
    int N; 
    int M;
};

class Matrix {
    private:
        double * _value;
        int _N; //количество строк
        int _M; //количество столбцов

        Matrix();

    public:
        class Row {
            private:
                int _len; //длина строки
                double * _rvalue; //ссылка на массив в основной матрице
                Row();
            public:
                Row(double * value, int len);
                double & operator[] (int m) const;

        };
        class Submatrix {
            private:
                int _i, _j, _n, _m, _N, _M;
                double * _value;
            public:
                Submatrix(int i, int j, int n, int m, const Matrix &Ma);
                Row& operator[] (int k) const;
        };

        public:
            Matrix(int N, int M);
            Matrix(const Matrix &Ma);
            ~Matrix();

            couple& getsize() const;

            void print() const;

            Matrix operator+(const Matrix& Ma) const;
            Matrix& operator=(const Matrix &Ma);
            Row& operator[](int n) const;
};
#endif