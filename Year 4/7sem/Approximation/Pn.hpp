#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

class Pn {
    private:
        int _N;
        double * _coefs;


    public:
        Pn(int N, double * coefs);
        Pn(Pn &P);
        ~Pn();

        void print() const;
        double calculate(double x) const;
};