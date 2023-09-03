#include "Pn.hpp"
#include "Ln.hpp"

#include "knots.cpp"

double module(double x)
{
    return -x * (x < 0) + x * (x > 0);
}

double f(double x)
{
    return 2 * x * x + x + 2;
}

void PrintTable(double * knots, int N, Pn * P, Ln * L, double (*f)(double))
{
    printf("Knotes                     Pn                      Ln                     f\n");
    for(int i = 0; i < N - 1; ++i)
    {
        double xi = knots[i];
        printf("%10.2lf %10.2lf %10.2lf %10.2lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
        double xi1 = xi / 3 + 2 * knots[i + 1] / 3;
        printf("%10.2lf %10.2lf %10.2lf %10.2lf \n", xi1, P->calculate(xi1), L->calculate(xi1), f(xi1));
        double xi2 = 2 * xi / 3 + knots[i + 1] / 3;
        printf("%10.2lf %10.2lf %10.2lf %10.2lf \n", xi2, P->calculate(xi1), L->calculate(xi1), f(xi1));
    }
    double xi = knots[N];
    printf("%10.2lf %10.2lf %10.2lf %10.2lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));

}

int main(){
    int N = 3;
    double a = 0;
    double b = 2;
    double * knots1 = new double[N];
    double * knots2 = new double[N];
    double * mean1 = new double[N];
    double * mean2 = new double[N];


    GenerateEquidistantGrid(a, b, N, f, knots1, mean1);
    GenerateEquidistantGrid(a, b, N, f, knots2, mean2);

    Pn P(N, knots1, mean1);
    Ln L(N, knots2, mean2);

    PrintTable(knots1, N, &P, &L, f);

    delete [] knots2;
    delete [] knots1;
    delete [] mean2;
    delete [] mean1;
}