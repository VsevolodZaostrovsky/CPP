#include <stdio.h>
#include <stdlib.h>

int read_array(double *array, unsigned int len, FILE *inp) {
	int i = 0;
	double ai = 0;

	while (i < len) {
		if (fscanf(inp, "%lf", &ai) != 1) {
			return -1;
		}
		array[i] = ai;
		i++;
	}

	return 0;
}

int print_array(double *array, unsigned int len) {
	printf("%d ", len);
	for (int i = 0; i < len; i++) {
		printf("%lf ", array[i]);
	}
	printf("\n");
}

double write_array(double *array, unsigned int len, FILE *out) {
 
 	fprintf(out, "%d ", len);

        for (int i = 0; i < len; i++) {
                fprintf(out, "%lf ", array[i]);
        }
	return 0;
}



double S(double *A, int k) {
	double s = 0;
	for (int i = 0; i < k + 1; i++) {
		s += A[i];
	}
	return s;
}

double MS(double *A, int len) {
	double max_sum = A[0];
	for (int i = 1; i < len; i++) {
		if (max_sum < S(A, i)) {
			max_sum = S(A, i);
		}
	}
	return max_sum;
}

double mod(double d) {
	if (d >= 0) { return d; }
	if (d < 0) { return -d; }
}

int T(double *A, int len, double d, int k) {
	double sum = S(A, k);
	double max = MS(A, len);
	if (mod(max - sum) <= d) { return 1; }
	else { return 0; }
}

double W(double d, double *A, int len) {
	double sum = 0;
	for (int t = 0; t < len; t++) {
	       if (T(A, len, d, t) == 1) {
	       sum = sum + A[t];
	       }
	}
	return sum;
}	

int remove_bed_W(double *A, int len) {
        int i = 0;
        int k = 0;
        double We = W(0.1, A, len);
        while (i < len) {
                if (mod(A[i]) <= We) {
                        A[k] = A[i];
                        k++;
                }
                i++;
        }
        len = k;
        return len;
}
	
int cicle_compozition(double *A, int la, double *B, int lb) {
	for (int i = 0; i < la; i++) {
		A[i] = A[i] * B[i % lb];
	}
	return 0;
}

int final_funk(double *A, int la, double *B, int lb) {
	la = remove_bed_W(A, la);
	lb = remove_bed_W(B, lb);
	
	if ((la == 0) || (lb == 0)) {
		return 0;
	}

	if (la >= lb) {
		cicle_compozition(A, la, B, lb);
		return la;
	}

	if (la < lb) {
                cicle_compozition(B, lb, A, la);
                return -lb;
        }
}


int main(int arc, char *argv[]) {
	double *A = 0;
	double *B = 0;
	int len_a, len_b;
	FILE *inp_a;
	FILE *inp_b;
	FILE *out;
		
	inp_a = fopen(argv[1], "r");
	inp_b = fopen(argv[2], "r");
	out = fopen("output.txt", "w");

	if ((inp_a == NULL) || (inp_b == NULL) || (out == NULL)) {
		printf("Не удалось открыть файл\n");

		return -1;
	}

	if (fscanf(inp_a, "%d", &len_a) != 1) {
		fclose(inp_a);
                fclose(inp_b);
                fclose(out);
		printf("Не удалось прочитать первый элемент файла\n");
		return -1;
	}

	if (len_a < 1) {
	       	fclose(inp_a);
		fclose(inp_b);
		fclose(out);	
		return -1; 
	}

	A = (double *)malloc(len_a * sizeof(A[0]));
	if (read_array(A, len_a, inp_a) == -1) {
		printf("Не удалось прочитать элементы файла\n");
                fclose(inp_a);
                fclose(inp_b);
                fclose(out);
                free(A);
		return -1;
	}

	if (fscanf(inp_b, "%d", &len_b) != 1) {
		printf("Не удалось прочитать первый элемент файла\n");
		fclose(inp_a);
                fclose(inp_b);
                fclose(out);
		free(A);
		return -1;
	}

	if (len_b < 1) { 
		fclose(inp_a);
                fclose(inp_b);
                fclose(out);
                free(A);
		return -1; 
	}

	B = (double *)malloc(len_b * sizeof(B[0]));
	if (read_array(B, len_b, inp_b) == -1) {
                printf("Не удалось прочитать элементы файла\n");
                fclose(inp_a);
                fclose(inp_b);
                fclose(out);
                free(A);
		free(B);
                return -1;
        }


	int f = final_funk(A, len_a, B, len_b);
	
	if (f == 0) {
		free(A);
        	free(B);
        	fclose(inp_a);
        	fclose(inp_b);
        	fclose(out);
		printf("-1\n");
		return -1;
	}
	if (f > 0) { 
		print_array(A, f);
       		write_array(A, f, out);	
	}
	if (f < 0) { 
		print_array(B, mod(f));
       		write_array(B, mod(f), out); 
	}

	free(A);
	free(B);
	fclose(inp_a);
        fclose(inp_b);
        fclose(out);

	return 0;

}	
