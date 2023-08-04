//random.cpp:

#include <iostream>
#include <fstream>
#include <string.h>
#include "par.h"
#include "BTree.h"
#include "BTree.hpp"
#include "ParCon.h"
using namespace std;


string randomStrGen(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

int main()
{
    ParCon PC;
    ParCon PC2;
    int op_num = 1000;
    string *book = new string[op_num];
    for (int i = 0; i < op_num; ++i)
    {
        int p = rand() % 5;
        int str_len = rand() % 20;
        string word = randomStrGen(str_len);
        book[i] = word;
        if (p == 0)
        {
            int value = rand() % 1000;
            PC.AddInt(word, value);
        }
        if (p == 1)
        {
            double value = (double)(rand() % 1000) + (double)((rand() % 1000) / 1000);
            PC.AddDouble(word, value);
        }
        if (p == 2)
        {
            int len = rand() % 20;
            int *values = new int[len];
            for (int j = 0; j < len; ++j)
            {
                values[j] = (double)(rand() % 1000) + (double)((rand() % 1000) / 1000);
            }
            PC.AddIntArray(word, values, len);
            delete [] values;
        }
        if (p == 3)
        {
            int len = rand() % 20;
            double *values = new double[len];
            for (int j = 0; j < len; ++j)
            {
                values[j] = rand() % 100;
            }
            PC.AddDoubleArray(word, values, len);
            delete [] values;
        }
        if (p == 4)
        {
            int str_len = rand() % 20;
            string values = randomStrGen(str_len);
            PC.AddChar(word, values);
        }
    }
    
    for (int i = 0; i < op_num; ++i)
    {
        int p = rand() % 5;
        int str_len = rand() % 20;
        string word = randomStrGen(str_len);
        if (p == 0)
        {
            int value = rand() % 1000;
            PC2.AddInt(word, value);
        }
        if (p == 1)
        {
            double value = (double)(rand() % 1000) + (double)((rand() % 1000) / 1000);
            PC2.AddDouble(word, value);
        }
        if (p == 2)
        {
            int len = rand() % 20;
            int *values = new int[len];
            for (int j = 0; j < len; ++j)
            {
                values[j] = (double)(rand() % 1000) + (double)((rand() % 1000) / 1000);
            }
            PC2.AddIntArray(word, values, len);
            delete [] values;
        }
        if (p == 3)
        {
            int len = rand() % 20;
            double *values = new double[len];
            for (int j = 0; j < len; ++j)
            {
                values[j] = rand() % 100;
            }
            PC2.AddDoubleArray(word, values, len);
            delete [] values;
        }
        if (p == 4)
        {
            int str_len = rand() % 20;
            string values = randomStrGen(str_len);
            PC2.AddChar(word, values);
        }
    }
    
    for (int k = 0; k < op_num; ++k) {
        int type;
        if (PC.GetType(book[k], type) != 1) {
            std::cout << "test_failed";
        }
    }

    PC += PC2; 

    int type;
//    std::cout << PC.data.search(book[50]) << std::endl;
/*    std::cout << "PC is: \n";
    PC.print();
    std::cout << "PC2 is: \n";
    PC2.print();
    std::cout << "PC1 += PC2 is: \n";
    PC += PC2;
    PC.print(); */
    delete [] book;
    return 0;
}