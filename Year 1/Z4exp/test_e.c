#include <stdio.h>
#include <math.h>
#include "exp.h"
#define NO_COMMENT 0
#define COMMENT 1

static double delta(double Ans1, double Ans2) {
        if (Ans1 < Ans2) {
                double p = Ans2;
                Ans2 = Ans1;
                Ans1 = p;
        }
        if (fabs(Ans2) > 0.1) { return fabs((Ans1 - Ans2)/Ans2); }
        else return fabs(Ans1 - Ans2);
}

int test(double x, double epsilon, int comment) {
	double result = e(x, epsilon);
	double expected_result = exp(x);
	if (delta(expected_result, result) < epsilon || (expected_result - 10 == expected_result && result - 10 == result)) {
		if (comment) {
			printf("Тест пройден. Ожидалось: %lf Получено: %lf Погрешность: %lf \n", expected_result, result, delta(expected_result, result));
		}
		return 1;
	}

	else {
		printf("*****ТЕСТ ПРОВАЛЕН!*****\n");
		printf("получено: %lf ожидалось: %lf степень: %lf желаемая погрешность: %lf\n", result, expected_result, x, epsilon);
		return 0;
	}
}

int main() {
	int n_tests = 0;
	for (double k = -15; k < 51; k++) {
		for (double p = 0.1; p > 1e-10; p /= 10) {
		       	n_tests += test(k, p, NO_COMMENT);
	       }
	}
		       
	int ste = 0;	
	printf("Пройдено %d тестов из 660\n", n_tests);
	test(-1e10, 1e-10, COMMENT);
	test(1, 1, COMMENT);
	test(1e10, 1e-10, COMMENT);
	return 0;
}


