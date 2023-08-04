#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include "par.h"
#include "BTree.h"
using namespace std;

enum error_code { GET_OK = 1, GET_NEOK = 0 };

class ParCon
{
public:
    BTree<string, par> data;

public:
    ParCon() {
        BTree<string, par> data(5);
    }
    ParCon(const ParCon &PC) = delete;
//    ~ParCon() = default;

    //считывание пар ключ-значение из файла
    bool ReadFrom(string file_name);

    //функции добавления пары ключ-значение (ключ - массив char *word длины w_len)
    void AddInt(string word, int value) { data.Add(word, par(value)); }

    void AddDouble(string word, double value) { data.Add(word, par(value)); }

    void AddIntArray(string word, int *values, size_t values_len) { data.Add(word, par(values, values_len)); }

    void AddDoubleArray(string word, double *values, size_t values_len) { data.Add(word, par(values, values_len)); }

    void AddChar(string word, string values) { data.Add(word, par(values)); }

    //функции получения значения по ключу
    int GetInt(string key, int &error_code)
    {
        par *ans = data.search(key);
        if (ans == nullptr)
        {
            error_code = GET_NEOK;
            return 0;
        }
        if (ans->type != INT_PAR) { error_code = GET_NEOK; }
        error_code = GET_OK;
        return ans->cnum_int;
    }

    double GetDouble(string key, int &error_code)
    {
        par *ans = data.search(key);
        if (ans == nullptr)
        {
            error_code = GET_NEOK;
            return 0;
        }
        if (ans->type != DOUBLE_PAR) { error_code = GET_NEOK; }
        error_code = GET_OK;
        return ans->cnum_double;
    }

    const int *GetIntArray(string key, size_t *array_len, int &error_code)
    {
        par *ans = data.search(key);
        if (ans == nullptr)
        {
            error_code = GET_NEOK;
            return nullptr;
        }
        if (ans->type != ARRAY_INT_PAR) { error_code = GET_NEOK; }
        error_code = GET_OK;
        *array_len = ans->len;
        return ans->carray_int;
    }

    const double *GetDoubleArray(string key, size_t *array_len, int &error_code)
    {
        par *ans = data.search(key);
        if (ans == nullptr)
        {
            error_code = GET_NEOK;
            return nullptr;
        }
        if (ans->type != ARRAY_DOUBLE_PAR) { error_code = GET_NEOK; }
        error_code = GET_OK;
        *array_len = ans->len;
        return ans->carray_double;
    }

    string GetString(string key, int &error_code)
    {
        par *ans = data.search(key);
        if (ans == nullptr)
        {
            error_code = GET_NEOK;
            return nullptr;
        }
        if (ans->type != STRING_PAR) { error_code = GET_NEOK; }
        error_code = GET_OK;
        return ans->word;
    }

    int GetType(string key, int &type) 
    {
        par *ans = data.search(key);
        if (ans == nullptr)
        { return 0; }
        type = ans->type;
        return 1;
     }

    //функция теоретико-множественного прибавления (при совпадении ключей остаётся ключ из множества, к которому прибавляется другое)
    ParCon &operator+=(const ParCon &p) { data += p.data; return *this; }

    //оператор печати
    void print() { data.print(); } //оператор печати
};


bool ParCon::ReadFrom(string file_name) {
    ifstream inp(file_name);
    if(inp.is_open()) {
        while (!inp.eof()) {
            string word;
            string k;
            inp >> word;
            inp >> k;
            if (k == "=i") {
                int i; inp >> i; 
                AddInt(word, i); 
                }
            if (k == "=d") {
                double i; inp >> i; 
                AddDouble(word, i);
                }
            if ( k == "=s") {
                string i; inp >> i;
                AddChar(word, i);
                }
            if (k == "=ai") {
                int i; inp >> i;
                int len = i; int *array = new int[len];
                for (int k = 0; k < len; ++k) {
                    inp >> i;
                    array[k] = i;
                }
                AddIntArray(word, array, len);
                delete [] array;
                }
            if (k == "=ad") {
                int i; inp >> i;
                int len = i; double *array = new double[len];
                double d;
                for (int k = 0; k < len; ++k) {
                    inp >> d;
                    array[k] = d;
                }
                AddDoubleArray(word, array, len);
                delete [] array;
            }
        }
    }
    else {
        cout << "cant open file\n"; 
        inp.close(); return 0; 
        }
    inp.close();
    return 1;
}