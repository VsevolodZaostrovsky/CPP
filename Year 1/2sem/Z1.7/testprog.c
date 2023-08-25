#include "stdio.h"
#include "calc_until_g_zero_hd.h"

int test(RtoRFunc f, RRtoZFunc g, double x, int expected_result) {
	printf("test started\n");
        RtoRFunc f1 = f;
        RRtoZFunc g1 = g;

        int result = order_fg(f1, g1, x);
        printf("%lf, res = %d\n", x, result);
        if(result == expected_result) {
                printf("Test OK!\n");
        }
        else {
                printf("******* Test FAILED! *******\n");
        }
        return 0;
}

double f1(double x) {
    	return x + 1.0;
}

double f2(double x) {
	return 0.0001;
}

int g1(double x, double y) {
	if (x == 3., y == 4.) { return 0; }
    	return 1;
}

int g2(double x, double y) {
        return 1;
}

int main() {
	test(f1, g1, 0., 4);
	test(f1, g1, 2., 2);
	test(f2, g1, 2., -1);
	test(f2, g2, 10., -1);

    	return 0;
}
