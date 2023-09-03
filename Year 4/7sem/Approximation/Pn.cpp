#include "Pn.hpp"

Pn::Pn(int N, double * coefs) : _N(N), _coefs(new double[N])
{
	if (N <= 0)
	{
		throw "Pn::Pn - size <=0";
	}
	for (int k = 0; k < N; k++)
	{
		this->_coefs[k] = coefs[k];
	}
}

Pn::Pn(Pn &P) : _N(P._N)
{
	if (this == &P) return;

//    delete [] _coefs;
    _coefs = new double[_N];
	for (int k = 0; k < _N; k++)
	{
		this->_coefs[k] = P._coefs[k];
	}
}

Pn::~Pn()
{
	delete[] _coefs;
	_N = 0;
}

void Pn::print() const
{
	for (int k = 0; k < _N; k++)
	{
		std::cout << _coefs[k] << "x^" << k;
        if(k != _N - 1) std::cout << " + ";
        
	}
	std::cout << std::endl;
}

double Pn::calculate(double x) const
{
    double ans = 0;
    double m = 1;
	for (int k = 0; k < _N; k++)
	{
		ans += _coefs[k] * m;
        m *= x;
	}
	return ans;
}