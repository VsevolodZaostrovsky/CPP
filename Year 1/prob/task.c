#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double read_array(int *array, unsigned int len, FILE *inp) {
        int ai = 0;
        int i = 0;

	while ((i < len) && (fscanf(inp, "%d", &ai) == 1)) {
		array[i] = ai;
                i++;
	}
        return 0;
}

double write_array(int *array, unsigned int len, FILE *out) {
	fprintf(out, "%d ", len);
	for (int k = 0; k < len; k++) {
		fprintf(out, "%d ", array[k]);
	}
	return 0;
}

int bit_rang(int A) {
	int bit_rang = 0;
	while (A > 0) {
		A = A/2;
		bit_rang ++;
	}
	return bit_rang;
}

int max_val(int *array, unsigned int len) {
	int max = array[0];
	for (int k = 0; k < len; k++) {
		if (max < array[k]) {
			max = array[k];
		}
	}
	return max;
}


int elem_R(int A, int B) {
	if (bit_rang(A) > bit_rang(B)) {
		return 1;
	}
	
	else {
                return 0;
        }
}

int R_rang(int x, int *array_A, unsigned int len_A) {
	int rang = 0;
	for (int k = 0; k < len_A; k++) {
		if (elem_R(x, array_A[k])) { 
				rang ++;
				}
			}
	return rang;
	}
				
int array_R(int *array_A, unsigned int len_A, int *array_B, unsigned int len_B) {
	for (int k = 0; k < len_A; k++) {
		int f = 0;
		for (int j = 0; j < len_B; j++) {
			if (array_A[k] == array_B[j]) {
				f = 1;
				}
		}
		if (f == 0) {
			return R_rang(array_A[k], array_A, len_A);
		}
	}

	return -1;
}

int main_funk(int *array_A, unsigned int len_A, int *array_B, unsigned int len_B, FILE *out) {
	int AB = array_R(array_A, len_A, array_B, len_B);
	int BA = array_R(array_A, len_A, array_B, len_B);
	if (AB > BA) {
		int max = max_val(array_A, len_A);
		for (int p = 0; p < len_B; p++) {
			array_B[p] = array_B[p] - max;
		}
		write_array(array_B, len_B, out);
		return 0;
	}

	if (AB < BA) {
		int max = max_val(array_B, len_B);
		for (int k = 0; k < len_A; k++) {
                        array_A[k] = array_A[k] - max;
                }
		write_array(array_A, len_A, out);
		return 0;
        }

	return 0;
}


int main() {
	int *array_A = 0;
	int *array_B = 0;
    	int len_A, len_B;  
	FILE *inp_A;
	FILE *inp_B;
	FILE *out;

	inp_A = fopen("impA.txt", "r");
	inp_B = fopen("impB.txt", "r");
	out = fopen("output.txt", "w");

	if ((inp_B == NULL) || (inp_A == NULL)) {
      		printf("При попытке открыть один из файлов произошла ошибка\n");
               	return -1;
        }

	if (fscanf(inp_A, "%d", &len_A) != 1) {
       		printf("Не удалось прочитать первый элемент файла\n");
        	return -1;
    	}

	if (fscanf(inp_B, "%d", &len_B) != 1) {
       		printf("Не удалось прочитать первый элемент файла\n");
        	return -1;
    	}

	array_A = (int *)malloc(len_A * sizeof(array_A[0]));
	array_B = (int *)malloc(len_B * sizeof(array_B[0]));
	
	read_array(array_A, len_A, inp_A);
	read_array(array_B, len_B, inp_B);
	
	main_funk(array_A, len_A, array_B, len_B, out);
	
	free(array_A);
	free(array_B);
	fclose(inp_A);
	fclose(inp_B);
	fclose(out);
	
	return 0;
}

