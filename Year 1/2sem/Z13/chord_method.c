#include <stdio.h>
#include <math.h>
#include "chord_method.h"
#define MAX_ITER 1000000

//Функция осуществляет один шаг метода хорд на отрезке [a,b]. Возвращается приближенное значение х. В переменную new_edge записывается граница следующего отрезка
double iter_cm(RRFunc f, double a, double b, double *new_edge){
	double A = f(a);
	double B = f(b);
	double x = (a*B-b*A)/(B-A);

	if (B*f(x) < 0) { (*new_edge) = b; }
	if (A*f(x) < 0) { (*new_edge) = a; }
	if (f(a) == 0) { x = a; (*new_edge) = a; }
	if (f(b) == 0) { x = b; (*new_edge)  = b; }
	return x;
}

int find_root_chord_method(RRFunc f, double a, double b, double eps, double *x) {
	double x0, new_edge;
	int iter = 0;
	double delta = fabs(a - b);
	double A = a;
	double B = b;

	while (iter < MAX_ITER && fabs(a - b) > eps) {
		x0 = iter_cm(f, a, b, &new_edge);
		a = x0;
		b = new_edge;
		iter++;
	}
	(*x) = x0;	
//	printf("a - b = %lf Iter = %d\n", fabs(a - b), iter);
	if (fabs(a - b) > delta || x0 < A || x0 > B) {
//		printf("На данном промежутке функция не имеет корней\n");
       		return NO_ROOT;
	}

	if (iter > MAX_ITER - 1) {
//	        printf("Ответ получен с недостаточной точностью\n");
		return NOT_ENOUGH_ACCURACY;
	}

	return ROOT_OK;
}
	


