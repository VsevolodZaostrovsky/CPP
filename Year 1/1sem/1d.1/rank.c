#include <stdlib.h>
#include <stdio.h>

double mod(double x) {
    if (x < 0) { return -x; }
    else return x;
}

int print_matrix(double* A, int n, int m) {
	for(int k = 0; k < n * m; k++) {
		printf("%lf ", A[k]);
		if ((k + 1) % n == 0) {
			printf("\n");
		}
	}
	printf("\n");
	return 0;
}


double i_plus_Bj(int i, double B, int j, double* A, int n) {
	for(int p = 0; p < n; p++) {
		A[i * n + p - n] = A[i * n + p - n] + B * A[j * n + p - n];
	}
	return 0;
}

double step_view_one_step(double* A, int n, int m) {
	double k = 0, B;
	int k_p = 0;
	for (int p = 0; p < n * m; p += n) {
		if (mod(A[p]) > 1e-30) {
			k = A[p];
			k_p = p;
			break;
		}
	}
	int imp_str = k_p / n + 1;


	for (int t = 0; t < m; t++) {
		if (mod(A[t * n]) > 1e-30 && (t * n) != k_p) {
			B = -A[t * n] / k;
			i_plus_Bj(t + 1, B, imp_str, A, n);
		}
	}
//	printf("\n");
	
	if (mod(k) < 1e-30) { return 0; }
	return 1;
}

double del_left_high_corner(double* A, int n, int m) {
        int i = n + 1;
        int u = 0;
        for (i = n + 1; i < n * m; i++) {
                if (i % n != 0) {
                        A[u] = A[i];
                        u++;
                }
        }
        return 0;
}

int min(int a, int b) { if (a < b) { return a; } else {return b; } }

int rank(double* A, int n, int m) {
//	print_matrix(A, n, m);
	int rk = 0;
	int mi = min(n, m);
	for (int d = 0; d < mi; d++) {
		rk += step_view_one_step(A, n, m);
		del_left_high_corner(A, n, m);
		n--;
		m--;
//		printf("rk = %d\n", rank);
//		print_matrix(A, n, m);

	}
	return rk;
}

