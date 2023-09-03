#include "Pn.hpp"
#include "Ln.hpp"

#include "knots.cpp"

double module(double x)
{
    return -x * (x < 0) + x * (x > 0);
}

double f(double x)
{
    return sin(x);
}

void PrintTable(double *knots, int N, Pn *P, Ln *L, double (*f)(double))
{
    printf("Knotes                     Pn                      Ln                     f\n");
    for (int i = 0; i < N - 1; ++i)
    {
        double xi = knots[i];
        printf("%10.15lf %10.15lf %10.15lf %10.15lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
        double xi1 = 2 * xi / 3 + knots[i + 1] / 3;
        printf("%10.15lf %10.15lf %10.15lf %10.15lf \n", xi1, P->calculate(xi1), L->calculate(xi1), f(xi1));
        double xi2 = xi / 3 + 2 * knots[i + 1] / 3;
        printf("%10.15lf %10.15lf %10.15lf %10.15lf \n", xi2, P->calculate(xi2), L->calculate(xi2), f(xi2));
    }
    double xi = knots[N - 1];
    printf("%10.15lf %10.15lf %10.15lf %10.15lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
}

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        std::cout << "Wrong number of parameters, must be 5 in format:\n"
                  << "N k a b name \n"
                  << "where: \n N - number of knots \n k - type of knots (0 or 1) \n [a, b] - interval of approx \n name - name of the file with answer \n";
        return -1;
    }

    int N = atoi(argv[1]);    // число узлов
    int k = atoi(argv[2]);    // тип узлов
    double a = atof(argv[3]); // левая
    double b = atof(argv[4]); // и правая границы отрезка
    std::string m = argv[5];  // имя файла, в который нужно записать ответ

    if (N <= 1)
    {
        std::cout << "Wrong N: it must be 1\n";
        return -1;
    }
    if (a >= b)
    {
        std::cout << "Wrong k: it must be 0 or 1\n";
        return -1;
    }
    if (k != 1 && k != 0)
    {
        std::cout << "Wrong k (=" << k << "): it must be 0 or 1\n";
        return -1;
    }
    double *knots1 = new double[N];
    double *knots2 = new double[N];
    double *mean1 = new double[N];
    double *mean2 = new double[N];

    try
    {
        GenerateEquidistantGrid(a, b, N, f, knots1, mean1);
        GenerateEquidistantGrid(a, b, N, f, knots2, mean2);

        std::cout << "Grids generated\n";

        Ln L(N, knots2, mean2);
        std::cout << "Lagr Polynom built\n";

        Pn P(N, knots1, mean1);
        std::cout << "Polynom built\n";

        PrintTable(knots1, N, &P, &L, f);
    }
    catch (const char *error_message)
    {
        std::cout << error_message << std::endl;
    }

    delete[] knots2;
    delete[] knots1;
    delete[] mean2;
    delete[] mean1;

    return 0;
}