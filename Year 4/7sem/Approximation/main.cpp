#include "Pn.hpp"
#include "Ln.hpp"

double module(double x)
{
    return -x * (x < 0) + x * (x > 0);
}


int main(){
    double *knot = new double[3];
    double *meanings = new double[3];
    double *coefs = new double[3];

    knot[0] = 1;  meanings[0] = 3; coefs[0] = 2;
    knot[1] = 2;  meanings[1] = 4; coefs[1] = 1;
    knot[2] = 4;  meanings[2] = 6; coefs[2] = 0;

    Ln L(3, knot, meanings);
    L.print();
    Pn P(3, coefs);
    P.print();
    for(double k = -5; k < 5; k += 0.2)
    {
        if(module(P.calculate(k) - L.calculate(k)) < 1e-10) {
//            std::cout << "Done\n";
        }
        else {
            std::cout << "!!!!!!!!!!!!ERROR!!!!!!!!!!!!\n";
            std::cout << P.calculate(k) << " != " << L.calculate(k) << "\n";
        }
    }
    std::cout << "P4: " << P.calculate(10) << '\n';
    std::cout << "L4: " << L.calculate(10) << '\n';
    
    delete [] coefs;
    delete [] meanings;
    delete [] knot;
}