#include <math.h>

#define NET_GENERATION_ERROR -1
#define NET_GENERATED_WELL 0

# define M_PI           3.14159265358979323846

// требует массив длины N+1, записывает в него сеть узлов, сгенерированных по правилам, описанным в репорте
int GenerateNet(double *net, int N) 
{
    double x_k = 0;
    double h = 0;

    if (N <= 2)
        return NET_GENERATION_ERROR;
    h = 1 / ((double)N - 0.5);
    x_k = h / 2;
    net[0] = - h / 2;
    net[N] = 1;

    for (int k = 1; k < N; k++)
    {
        net[k] = x_k;
        x_k += h;
    }
    return NET_GENERATED_WELL;
}

// перемножает попарно и считает сумму произведений элементов массивов v1 и v2 с индекса start до индекса finish, не включая последний
double SCProduct(int start, int finish, double * v1, double * v2) 
{
    double ans = 0;

    for(int m = start; m < finish; ++m)
    {
        ans += v1[m] * v2[m];
    }

    return ans;
}

// функции, вычисляющие и записывающие базисный вектор 
double Phi(int m, int k, int N) 
{
    double h = 1 / (N + 0.5);
    return sin( M_PI * m * ( - h / 2 + k * h) );
}

void WritePhiTo(int m, int N, double * ph) 
{
    for(int k = 1; k < N; ++k) 
    {
        ph[k] = Phi(m, k, N);
    }
}

int WriteCNkTo(int N, double * cNks, double (*u)(double), double * netmemory, double * umemory, double * phimemory)
{
    if(GenerateNet(netmemory, N) == NET_GENERATION_ERROR) 
    {
        return NET_GENERATION_ERROR;
    }

    for(int m = 1; m < N; ++m)
    {
        umemory[m] = u(netmemory[m]);
    }

    for(int k = 1; k < N; ++k) 
    {
        WritePhiTo(k, N, phimemory);
        cNks[k] = 2 * SCProduct(1, N, phimemory, umemory);
    }

    return 0;
}

double FourierCompute(double * coefs, int N, double x) 
{
    double ans = 0;
    for(int m = 1; m < N; ++m)
    {
        ans += coefs[m] * sin( M_PI * m * x );
    }
    return ans;
}

