#pragma once
#include <cmath>

#define GoodJob 0
#define NotEnoughKnotes -1
#define Incorrectab -2
# define M_PI           3.14159265358979323846

int GenerateEquidistantKnots(double a, double b, int N, double * result)
{
    if(N <= 1) return NotEnoughKnotes;
    if(N == 2)
    {
        result[0] = a;
        result[1] = b;
        return GoodJob;
    } 
    if(a > b) return Incorrectab;

    double delta = (b - a) / double(N - 1);
    double now = a;
    for(int i = 0; i < N; ++i) 
    {
        result[i] = now;
        now += delta;
    }
    return GoodJob;
} 

int GenerateChebyshevKnots(double a, double b, int N, double * result)
{
    if(N <= 1) return NotEnoughKnotes;
    if(a > b) return Incorrectab;

    double delta1 = (b + a) / 2;
    double delta2 = (b - a) / 2;

    for(int i = 0; i < N; ++i) 
    {
        result[N - 1 - i] = delta1 + delta2 * cos((2 * i + 1) * M_PI / (2 * N));
    }

    return GoodJob;
} 