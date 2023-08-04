#include "Polynom.h"
#include "MyException.h"
#include <math.h>
#include <iostream>

Polynom::Polynom(int maxdegree)
    : _maxdegree(maxdegree),
      _koef(new double[maxdegree + 1])
{
    if (maxdegree < 0)
    {
        throw MyException("Bed size", ERROR);
    }
    for (int p = 0; p <= _maxdegree; ++p)
    {
        _koef[p] = 0;
    }
}

Polynom::Polynom(Polynom &D)
    : _maxdegree(D._maxdegree), _koef(new double[D._maxdegree + 1])
{
    for (int i = 0; i < _maxdegree; ++i)
    {
        _koef[i] = D._koef[i];
    }
}

Polynom::~Polynom()
{
    delete[] _koef;
}

double Polynom::koef(int k) const
{
    if (k < 0 || k > _maxdegree)
    {
        throw MyException("Bed koef", ERROR);
    }
    return _koef[k];
}

double Polynom::mean(double value) const
{
    double sum = 0;
    for (int k = 0; k <= _maxdegree; ++k)
    {
        sum += pow(value, k) * koef(k);
    }
    return sum;
}

bool Polynom::set_koef(int k, double value)
{
    if (k < 0 || k > _maxdegree)
    {
        throw MyException("Bed set koef", ERROR);
        return 0;
    }
    _koef[k] = value;
    return 1;
}

Polynom &Polynom::operator=(const Polynom &A)
{
    if (this == &A)
    {
        return *this;
    }

    _maxdegree = A._maxdegree;
    delete[] _koef;
    _koef = new double[_maxdegree + 1];
    for (int k = 0; k <= _maxdegree; k++)
    {
        _koef[k] = A._koef[k];
    }
    return *this;
}

Polynom operator+(const Polynom &A, const Polynom &B)
{
    int md = 0;
    int min = 0;
    if (A._maxdegree < B._maxdegree)
    {
        md = B._maxdegree;
        min = A._maxdegree;
    }
    else
    {
        md = A._maxdegree;
        min = B._maxdegree;
    }
    Polynom Sum(md);
    for (int i = 0; i <= min; ++i)
    {
        double t = A.koef(i) + B.koef(i);
        Sum.set_koef(i, t);
    }
    for (int i = min; i < md; ++i)
    {
        if (A._maxdegree < B._maxdegree)
        {
            Sum.set_koef(i, B.koef(i));
        }
        else
        {
            Sum.set_koef(i, A.koef(i));
        }
    }
    return Sum;
}

void Polynom::print() const
{
    for (int k = 0; k <= _maxdegree; k++)
    {
        std::cout << _koef[k] << " ";
    }
    std::cout << std::endl;
}