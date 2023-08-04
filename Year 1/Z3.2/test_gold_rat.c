#define EPS 0.001
#include <stdio.h>
#include <math.h>
#include "min_value_gold_ratio.h"

static double delta(double Ans1, double Ans2) {
        if (Ans1 < Ans2) {
                double p = Ans2;
                Ans2 = Ans1;
                Ans1 = p;
        }
        if (fabs(Ans2) > 0.1) { return fabs((Ans1 - Ans2)/Ans2); }
        else return fabs(Ans1 - Ans2);
}


int test(RRFunc f, double a, double b, double expected_result, int expected_error_code, char *message) {
	double result;
	int error_code;
        result = min_val_gold(f, a, b, EPS, &error_code); 
	if (expected_error_code != error_code) {
		printf("ожидаемый код ошибки: %d, полученный: %d\n", expected_error_code, error_code);
                printf("******* ТЕСТ %s ПРОВАЛЕН! *******\n", message);
		return 0;
	}

        if (delta(expected_result, result) <= EPS) {
                printf("Тест %s пройден!\n", message);
		return 0;
        }
	if (error_code == INVALID_INPUT) {
		printf("Тест %s пройден!\n", message);
                return 0;
	}

	if (error_code == NOT_ENOUGH_ACCURACY) {
		printf("Тест %s пройден!\n", message);
                return 0;
        }

	if (error_code == THERE_IS_NO_MINIMUM) {
                printf("Тест %s пройден!\n", message);
                return 0;
        }


	else {
                printf("******* ТЕСТ %s ПРОВАЛЕН! *******\n", message);
		printf("погрешность: %lf\n", delta(expected_result, result));
                printf("ожидаемый результат: %lf, результат: %lf\n", expected_result, result);

        }
        return 0;
}

double f1(double x) { return -x*x*x; }

double f2(double x) { return x; }

double f3(double x) { return x*x*x-5; }

double f4(double x) { return (1 - x)*(x + 4)*(x + 2); }

double f5(double x) { return x*sin(x); }

double f6(double x) { return sin(x); }

double f7(double x) { return x - 1e5; }

double f8(double x) { return x - 1e-5; }

double f9(double x) { return x*x*log(x)*sin(x)*cos(x); }

double f10(double x) { return x*sin(x)*cos(x)*exp(0.01*x)/log(x); }

double f11(double x) { return -1/x; } 

int main() {

	test(f2, -100., 10., -100., WORK_OK, "Прямая");
	test(f1, -10., 1., -1., WORK_OK, "Отрицательная парабола");
	test(f3, -1., 4., -6., WORK_OK, "Кубическая парабола");
	test(f4, -4., 1., -4.061, WORK_OK, "Кубическая парабола с несколькими витками");
	test(f1, 10., 1., 0, INVALID_INPUT, "Неправильные границы");
	test(f5, 0., 6., -4.814, WORK_OK, "Немного страшная функция");
	test(f6, 0., 20., -1., WORK_OK, "Периодическая функция с витками");
	test(f7, -1e5, 1e6, -2e5, WORK_OK, "Большие числа");
	test(f8, -3e-5, 5e-5, -4e-4, WORK_OK, "Маленькие числа");
	test(f9, 0., 6., -2.856, WORK_OK, "Более страшная функция");
	test(f10, 2., 8., -1.706, WORK_OK, "Очень страшная функция");
	test(f11, 0., 2., 0, THERE_IS_NO_MINIMUM, "Функция не имеющая минимума");

	return 0;
}
