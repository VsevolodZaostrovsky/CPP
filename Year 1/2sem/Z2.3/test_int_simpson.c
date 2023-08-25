#include <stdio.h>
#include <math.h>
#include "integral_simpson.h"

static double delta(double expected_result, double result) {
	if (fabs(expected_result) > 0.1) { return fabs((result - expected_result)/expected_result); }
	else return fabs(result);
}

static int test(RRFunc f, double a, double b, double expected_result, int expected_work) {
	double result; 
	int work = integral_sympson(f, a, b, 0.0001, &result); 
	if (work != expected_work) {
	                printf("ТЕСТ ПРОВАЛЕН! НЕПРАВИЛЬНЫЙ РЕЖИМ РАБОТЫ\n(фактический %d ожидалось %d)\n", work, expected_work);
			printf("ожидаемый результат: %lf, результат: %lf\n", expected_result, result);
			return 0;
	}
	
	if (delta(expected_result, result) < 0.01 && work == INTEGRAL_OK) {
//		printf("ожидаемый результат: %lf, результат: %lf\n", expected_result, result);
                printf("Тест пройден!\n");
		return 0;
        }
	
	if (work == NOT_ENOUGH_ACCURACY) {
		printf("Тест пройден! \n");
		return 0;
	}

	if (work == INTEGRAL_DIVERGES) {
		printf("Тест пройден! \n");
                return 0;
        }
	
	else {
		printf("ожидаемый результат: %lf, результат: %lf\n", expected_result, result);
                printf("******* ТЕСТ ПРОВАЛЕН! *******\n");
        }
	return 1;
}

static double f1(double x) { return 0; }

static double f2(double x) { return x*x - 4; }

static double f3(double x) { return x; }

static double f4(double x) { return 1/x; }

static double f5(double x) { return 1e5; }

static double f6(double x) { return 1e-5; } 

static double f7(double x) { return x*x*sin(x); }

static double f8(double x) { return x*x*sin(x)*log(x); }

int main() {
	test(f1, 0., 3., 0., INTEGRAL_OK);
	test(f2, 0., 3., -3., INTEGRAL_OK);
 	test(f3, 0., 1., 0.5, INTEGRAL_OK);
	test(f4, 0., 3., 0., INTEGRAL_DIVERGES);
	test(f4, -3., 0., 0., INTEGRAL_DIVERGES);
	test(f5, 2., 5., 3e5, INTEGRAL_OK);
	test(f6, 2., 5., 3e-5, INTEGRAL_OK);
	test(f7, 0., 1., 0.2232, INTEGRAL_OK);
	test(f7, 0., 100., -8724., INTEGRAL_OK);
	test(f8, 1., 12., -335.3548, INTEGRAL_OK);

	return 0;
}
