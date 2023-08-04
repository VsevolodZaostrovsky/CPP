#include <stdio.h>
#include <math.h>
#include "chord_method.h"
#define EPS 1e-5
#define NEP_NUM 2.71828182845904523

int test(RRFunc f, double a, double b, double expected_result) {
	double result;
        int work = find_root_chord_method(f, a, b, EPS, &result); 
        if (fabs(result - expected_result) < EPS && work == ROOT_OK) {
                printf("Тест пройден!\n");
		return 0;
        }
	if (work == NOT_ENOUGH_ACCURACY && expected_result == NOT_ENOUGH_ACCURACY) {
		printf("Тест пройден!\n");
		return 0;
	}
	if (work == NO_ROOT && expected_result == NO_ROOT) {
                printf("Тест пройден!\n");
		return 0;
        }
        else {
		printf("ожидаемый результат: %lf, результат: %lf\n", expected_result, result);
                printf("******* ТЕСТ ПРОВАЛЕН! *******\n");
        }
        return 0;
}

double f1(double x) {
	return 0;
}

double f2(double x) {
	return x*x - 4;
}

double f3(double x) {
	return x - 1;
}

double f4(double x) {
        return x*x - 2;
}

double f5(double x) {
	return x*x*x + 3*x*x + 3*x + 1;
}

double f6(double x) {
	return sqrt(x) - 5;
}

double f7(double x) {
	return exp(x) - 1;
}

double f8(double x) {
	return 1;
}

double f9(double x) {
	return pow((x + 5), 5);
}

double f10(double x) {
	return x - 1e20;
}

double f11(double x) {
	return x - 1e-5;
}

double f12(double x) {
	return pow((exp(x) - NEP_NUM), 5);
}

int main() {
	test(f1, 0., 1., 1.);
	test(f2, 0., 5., 2.);
   	test(f3, -4., 2., 1.);
	test(f4, -3., 1., -1.414213);
	test(f5, -2., 0., -1.);
	test(f6, 20., 30., 25.);
	test(f7, -1.25, 1.25, 0.);
	test(f8, -10., 10., -1);
	test(f9, -10., 0., -5.);
	test(f9, -10., -9., -1.);
	test(f10, 1e19, 1e21, 1e20);
	test(f11, -1e-5, 1e-2, 1e-5);
	test(f12, 0., 2., NOT_ENOUGH_ACCURACY);

	return 0;
}

