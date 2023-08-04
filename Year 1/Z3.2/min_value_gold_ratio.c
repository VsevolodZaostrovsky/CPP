#include <stdio.h>
#include <math.h>
#include "min_value_gold_ratio.h"

#define Fi 1.6180339887

static double delta(double Ans1, double Ans2) {
	if (Ans1 < Ans2) {
		double p = Ans2;
		Ans2 = Ans1;
		Ans1 = p;
	}
        if (fabs(Ans2) > 0.1) { return fabs((Ans1 - Ans2)/Ans2); }
        else return fabs(Ans1 - Ans2);
}

static double min_val_1_iter(RRFunc f, double a, double b, double *new_edge_a, double *new_edge_b) {
	double x1, x2, y1, y2;
	
	x1 = b - (b - a)/Fi;
	x2 = a + (b - a)/Fi;
	y1 = f(x1);
	y2 = f(x2);

	if (y1 >= y2) {
		*new_edge_a = x1;
		*new_edge_b = b;
		return y2;
	}

	else {
		*new_edge_a = a;
                *new_edge_b = x2;
		return y1;
	}
}

double min_val_gold(RRFunc f, double a, double b, double epsilon, int *error_code) {
	int iter = 0;
	double ans_prev = min_val_1_iter(f, a, b, &a, &b);
	double ans = min_val_1_iter(f, a, b, &a, &b);

	while ((iter < MAX_ITER) && (delta(a, b) > epsilon || delta(ans, ans_prev) > epsilon)) {
		ans_prev = ans;
		for(int k = 0; k < 33; k++) {
			ans = min_val_1_iter(f, a, b, &a, &b);
		}
		iter++;
	}
//	printf("[a=%lf, b=%lf]", a, b);
//	printf("ans_prev = %lf, ans = %lf\n", ans_prev, ans);
	if (b <= a) {
		*error_code = INVALID_INPUT;
		return ans;
	}

	if (ans + 1 == ans) {
		*error_code = THERE_IS_NO_MINIMUM;
                return ans;
        }

	
	if (iter == MAX_ITER) {
		*error_code = NOT_ENOUGH_ACCURACY;
		return ans;
	}


	*error_code = WORK_OK;
	return ans;
}
	







