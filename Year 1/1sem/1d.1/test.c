#include <stdio.h>
#include "rank.h"


int test(double* A, int n, int m, int expected_rank) {
	int rk = rank(A, n, m);
	if (rk == expected_rank) {
		printf("Test OK\n");
	}

	else {
		printf("******TEST FAILED******\n");
		printf("expected_rank = %d, rk = %d\n", expected_rank, rk);
	}
        return 0;
}


int main(void) {
	double A1[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
	double A2[4] = {0, 0, 0, 0};
	double A3[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	double A5[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 15, 16, 17};
	double A4[12] = {0, 2, 3, 0, 5, 6, 0, 8, 9, 0, 11, 12};
	double A6[16] = {1, 0, 3, 4, 5, 0, 7, 8, 9, 0, 0, 12, 15, 13, 0, 0};
	double A7[25] = {12, 5, 6, 98, 45, 5, 6, 0, 0, 7, 9, 0, 11, 0, 12, 124, 65, 0, 0, 324, 1, 2, 3, 4, 5};
	
	test(A1, 3, 3, 1);
	test(A2, 2, 2, 0);
	test(A3, 3, 4, 2);
	test(A4, 4, 3, 3);
	test(A5, 3, 4, 3);
	test(A6, 4, 4, 4);
	test(A7, 5, 5, 5);

	return 0;
}

