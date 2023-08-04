#pragma once
#include <iostream>
#include <string.h>
using namespace std; 

enum par_type{ 
    STRING_PAR = 4, ARRAY_INT_PAR = 3, ARRAY_DOUBLE_PAR = 2, DOUBLE_PAR = 1, INT_PAR = 0
};

//структура, задающая пару: ключевое слово + значение
//значение может быть одним из пяти вариантов: целое или действительное число, массив целых или действительных чисел, массив char
struct par
{
    int cnum_int = 0; double cnum_double = 0;
    int *carray_int; double *carray_double;
    size_t len;
    string word;
    par_type type; //тип значения, хранящегося в паре (см. enum type)

    par() { type = INT_PAR; cnum_int = 0; }
    par(const par & C);
    par(int cvalue);
    par(double cvalue);
    par(int *cvalue, size_t cvalue_len);
    par(double *cvalue, size_t cvalue_len);
    par(string word);
    ~par();

    par &operator=(const par &K);
    friend std::ostream & operator<<(std::ostream & os, const par & C); //оператор печати
};
