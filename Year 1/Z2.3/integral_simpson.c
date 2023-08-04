#include <stdio.h>
#include <math.h>
#include "integral_simpson.h"

static double delta(double Ans1, double Ans2) {
        if (fabs(Ans2) > 0.1) { return fabs((Ans1 - Ans2)/Ans2); }
        else return fabs(Ans1);
}


//С помощью метода симпсона вычисляет определенный интеграл на отрезке [a, b], разбивая его на Num_of_sygments частей

static double integral_for_Num_of_sygments(RRFunc f, double a, double b, int Num_of_sygments) {
	double h = (b - a) / Num_of_sygments;
	double S1 = 0;
       	double S2 = (*f)(a + (Num_of_sygments - 1)*h);

	for(int j = 1; j < Num_of_sygments / 2; j++) {
		S1 += (*f)(a + 2*j*h);
		S2 += (*f)(a + 2*(j - 1)*h);
	}
	double integral = (h/3)*(f(a) + 2*S1 + 4*S2 + f(b));
	return integral;
}

int integral_sympson(RRFunc f, double a, double b, double epsilon, double *answer) {
	int N = 100;
	int iter = 0;
	double Ans1 = integral_for_Num_of_sygments(f, a, b, N);
	double Ans2 = integral_for_Num_of_sygments(f, a, b, N*2);

	while (delta(Ans1, Ans2) > epsilon && iter < 15) {
		N *= 2;
		Ans1 = integral_for_Num_of_sygments(f, a, b, N);
		Ans2 = integral_for_Num_of_sygments(f, a, b, N*2);
//		printf("Итерация: %d ответ1: %lf ответ2: %lf\n", iter, Ans1, Ans2);
		iter++;
	}

	(*answer) = Ans2;
//	printf("Количество итераций: %d ответ2: %lf ответ1: %lf\n", iter, Ans2, Ans1);

	if (2*Ans2 == Ans2 && fabs(Ans2) > 1) {
		return INTEGRAL_DIVERGES;
	}

	if (iter == 15) {
		return NOT_ENOUGH_ACCURACY;
	}
	
	return INTEGRAL_OK;
}






