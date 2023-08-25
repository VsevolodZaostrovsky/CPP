#include <stdio.h>
#include "exp.h"


static double fabsol(double x) {
	if (x < 0) { return -1 * x; }
	return x;
}

static double delta(double Ans1, double Ans2) {
        if (Ans1 < Ans2) {
                double p = Ans2;
                Ans2 = Ans1;
                Ans1 = p;
        }
        if (fabsol(Ans2) > 0.1) { return fabsol((Ans1 - Ans2)/Ans2); }
        else return fabsol(Ans1 - Ans2);
}

static double expan(double x, int n) {
	double sum = 0;
	double si = 1;
	for (int k = 0; k < n; k++) {
		sum += si;
		si = si*x/(k+1);
	}
	return sum;
}	


double e(double x, double epsilon) {
	int t = 10;
	double ans_prev = expan(x, t);
	double ans = expan(x, t*2);

	while (delta(ans, ans_prev) > epsilon) {
		ans_prev = ans;
		t *= 4;
		ans = expan(x, t);
	}
	if (x < -16) {
		return 0;
	}
	return ans;
}



