typedef double (*RRFunc)(double x);
#define NOT_ENOUGH_ACCURACY 0
#define INTEGRAL_OK 1
#define INTEGRAL_DIVERGES 2

//Функция с заданной точностьюл вычисляет определённый интеграл Римана от данной функции f(x), интегрируемой на отрезке [a,b],на этом отрезке с помощью формулы Симпсона с N отрезками
//epsilon задаётся в процентах (epsilon = 0.01 понимается, как точность в 1%)
int integral_sympson(RRFunc f, double a, double b, double epsilon, double *answer);

