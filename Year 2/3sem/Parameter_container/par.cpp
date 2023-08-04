#include <string.h>
#include "par.h"

par::par(const par &K) {
    switch(K.type) {
        case INT_PAR: cnum_int = K.cnum_int; type = INT_PAR; break;
        case DOUBLE_PAR: cnum_double = K.cnum_double; type = DOUBLE_PAR; break;
        case ARRAY_INT_PAR:
            len = K.len;
            carray_int = new int[len];
            for(int i = 0; i < K.len; ++i) {
                carray_int[i] = K.carray_int[i];
            }
            type = ARRAY_INT_PAR;
//            std::cout << "its done (copy)\n";
            break;
        case ARRAY_DOUBLE_PAR:
            len = K.len;
            carray_double = new double[len];
            for(int i = 0; i < K.len; ++i) {
                carray_double[i] = K.carray_double[i];
            }
            type = ARRAY_DOUBLE_PAR;
            break;
        case STRING_PAR: word = K.word; type = STRING_PAR; break;
    }
}

par::par(int cvalue) 
: cnum_int(cvalue), type(INT_PAR) {}

par::par(double cvalue) 
: cnum_double(cvalue), type(DOUBLE_PAR) {}

par::par(int *arr_int, size_t arr_len) 
: type(ARRAY_INT_PAR), len(arr_len), carray_int(arr_int) {
    carray_int = new int[len];
    for(int i = 0; i < len; ++i) {
        carray_int[i] = arr_int[i];
        }
}

par::~par() {
    if(type == ARRAY_INT_PAR) {
        delete [] carray_int;
    }
    if(type == ARRAY_DOUBLE_PAR) {
        delete [] carray_double;
    }
}

par::par(double *arr_double, size_t arr_len) 
: carray_double(arr_double), len(arr_len), type(ARRAY_DOUBLE_PAR) {
    carray_double = new double[len];
    for(int i = 0; i < len; ++i) {
        carray_double[i] = arr_double[i];
        }
}

par &par::operator=(const par &K) {
    if(this == &K) {
        return *this;
    }
    switch(type) {
        case INT_PAR: cnum_int = 0; break;
        case DOUBLE_PAR: cnum_double = 0; break;
        case ARRAY_INT_PAR: delete [] carray_int; len = 0; break;
        case ARRAY_DOUBLE_PAR: delete [] carray_double; len = 0; break;
        case STRING_PAR: break;
    }
    switch(K.type) {
        case INT_PAR: cnum_int = K.cnum_int; type = INT_PAR; break;
        case DOUBLE_PAR: cnum_double = K.cnum_double; type = DOUBLE_PAR; break;
        case ARRAY_INT_PAR:
            len = K.len;
            carray_int = new int[len];
            for(int i = 0; i < K.len; ++i) {
                carray_int[i] = K.carray_int[i];
            }
            type = ARRAY_INT_PAR;
//            std::cout << "its done = \n";
            break;
        case ARRAY_DOUBLE_PAR:
            len = K.len;
            carray_double = new double[len];
            for(int i = 0; i < K.len; ++i) {
                carray_double[i] = K.carray_double[i];
            }
            type = ARRAY_DOUBLE_PAR;
            break;
        case STRING_PAR: word = K.word; type = STRING_PAR; break;
    }
    return *this;
}

par::par(string word) : word(word), type(STRING_PAR) {}

std::ostream &operator<<(std::ostream &os, const par &c) {
    switch (c.type) {
        case INT_PAR:
            std::cout << c.cnum_int;
            break;
        case DOUBLE_PAR:
            std::cout << c.cnum_double;
            break;
        case ARRAY_DOUBLE_PAR:
            std::cout << "[";
            if (c.len == 0) { std::cout << "empty array]"; break; }
            for(int k = 0; k < c.len - 1; ++k) {
                std::cout << c.carray_double[k] << " ";
            }
            std::cout << c.carray_double[c.len - 1] << "]";
            break;
        case ARRAY_INT_PAR:
        std::cout << "[";
            if (c.len == 0) { std::cout << "empty array]"; break; }
            for(int k = 0; k < c.len - 1; ++k) {
                std::cout << c.carray_int[k] << " ";
            }
            std::cout << c.carray_int[c.len - 1] << "]";
            break;
        case STRING_PAR:
            std::cout << c.word; 
            break;
    }
    return os;
}

