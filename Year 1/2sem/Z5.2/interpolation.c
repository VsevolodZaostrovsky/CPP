#include <stdio.h>
#include <math.h>
#include "interpolation.h"

#define MAX 1
#define MIN 0

double mod(double x) {
        if (x < 0) { return -x; }
        else {return x; }
}

int find_the_nearest_right(double* x, int len, double a) {
        double delt;
        double delt_now = -1;
        int iter = 0;

        while (delt_now < 0 && iter < len) {
                delt_now = x[iter] - a;
                iter++;
        }

        delt = delt_now;
        int n_min = iter - 1;

        if (delt_now < 0) {
                return -1;
        }

        for(int j = 0; j < len; j++) {
                delt_now = x[j] - a;
                if (delt_now < delt && delt_now >= 0) {
//                        printf("j = %d delt_now = %lf", j, delt_now);
                        delt = delt_now;
                        n_min = j;
                }
        }
//        printf("delt = %lf", delt);
        return n_min;
}

double find(double* x, int len, int work_mode) {
    double min = x[0];
    double max = x[0];

    for (int i = 0; i < len; i++) {
        if (x[i] < min) { min = x[i]; }
        if (x[i] > max) { max = x[i]; }
    }

    if (work_mode) { return max; }
    else return min;
}



int find_the_nearest_left(double* x, int len, double a) {
        double delt;
	double delt_now = -1;
	int iter = 0;

	while (delt_now < 0 && iter < len) {
		delt_now = a - x[iter];
		iter++;
	}

	delt = delt_now;
	int n_min = iter - 1;

	if (delt_now < 0) {
		return -1;
	}

        for(int j = 0; j < len; j++) {
		delt_now = a - x[j];
                if (delt_now < delt && delt_now >= 0) {
//			printf("j = %d delt_now = %lf", j, delt_now);
                       	delt = delt_now;
                       	n_min = j;
                }
        }
//	printf("delt = %lf", delt);
        return n_min;
}

double interpole(double* x, int len, double* y, double a, int *error_code) {
        double min = find(x, len, MIN);
        double max = find(x, len, MAX);

        if (a < min || a > max) {
            *error_code = POINT_IS_NOT_IN_BETWEEN;
            return 0;
        }


	int left = find_the_nearest_left(x, len, a);
	int right = find_the_nearest_right(x, len, a);

	double y1 = y[left];
	double x1 = x[left];

	double y2 = y[right];
	double x2 = x[right];

	if (left == right) { return y1; }
	double ans = (y1 - y2)*(a - x1)/(x1 - x2) + y1;
	
       
	*error_code = WORK_OK;
	return ans;

}


