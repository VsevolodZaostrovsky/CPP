#include <stdio.h>
#include "calc_until_g_zero_hd.h"


int order_fg(RtoRFunc f, RRtoZFunc g, double x){
	double x_1 = x;
	double x_2;
        x_2 = (*f)(x);
	int len = 2;

	while (len < 1000) {
		x_1 = (*f)(x_1);
                x_2 = (*f)(x_2);

		if ((*g)(x_1, x_2) == 0) {
//			printf("Len is %d\n", len);
			return len;
		}
//		printf("x1 is %f x2 is %f len is %d\n", x_1, x_2, len);
		len++;

	}
	printf("len > 999\n");
	return -1;
}
