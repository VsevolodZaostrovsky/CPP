#include <stdio.h>
#include "interpolation.h"

#define EPS 1e-5

double modul(double x) {
        if (x < 0) { return -x; }
        else {return x; }
}

double test(double* x, int l, double* y,  double a, double expected_result, int expected_error_code, char *message) {

	int error_code;
	double result = interpole(x, l, y, a, &error_code);

	if (expected_error_code != error_code) {
		printf("*****TEST %s FAILED*****\n", message);
                printf("expected_error_code = %d, error_code = %d\n", expected_error_code, error_code);
                return 1;
	}

	if (error_code == POINT_IS_NOT_IN_BETWEEN) {
		printf("Test %s OK\n", message);
                return 1;
        }


	if (modul(result - expected_result) < EPS) {
		printf("Test %s OK\n", message);
		return 1;
	}

	else {
		printf("*****TEST %s FAILED*****\n", message);
		printf("expected_result = %lf, result = %lf\n", expected_result, result);
		return -1;
	}
}

int main(void) {
	double X[5] = {0, 2, 3, 7, 5};
	double Y[5] = {1, 3, -1, 0, 1};

	double A[5] = {0, 2e-10, 3e-10, 7e-10, 5e-10};
	double B[5] = {1e10, 3e10, -1e10, 0, 1e10};

	test(X, 5, Y, 4., 0., WORK_OK, "Test ans = 0");
	test(X, 5, Y, 0., 1., WORK_OK, "Test a = 0");
	test(X, 5, Y, 3.5, -0.5, WORK_OK, "Fraction test");
	test(X, 5, Y, 1.414, 2.414, WORK_OK, "Irrational test");
	test(X, 5, Y, -2., 0., POINT_IS_NOT_IN_BETWEEN, "Test POINT_IS_NOT_IN_BETWEEN");
	test(A, 5, B, 4e-10, 0., WORK_OK, "Test small");
        test(A, 5, B, 0., 1e10, WORK_OK, "Test big");


	return 0;
}

