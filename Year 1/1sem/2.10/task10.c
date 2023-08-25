#include <stdio.h>
#include <stdlib.h>


//Функция записывает массив длины (int *output_length) из файла (FILE *input) в переменную (double **output_array). Если при чтении файла произошла ошибка, функция возвращает -1, если ошибок не было 1

int read_arr(FILE *input, double **output_array, int *output_length)
{
    int len;
    double *array;

    if ((fscanf(input, "%d", &len) == 0) || (len < 1)) {
                return -1;
        }

    array = (double *)malloc(len * sizeof(array[0]));

    for(int k = 0; k < len; k++) {
	if (fscanf(input, "%lf", array + k) == 0) {
		return -1;
	}
    }

    *output_length = len;
    *output_array = array;

    return 0;
}

//Функция убирает из массива (double *array) длины (int len) отрицательные значения и возвращает длину получившегося массива

int remove_negative(double *array, int len) {
	int i = 0;
	int k = 0;
	while (i < len) {
		if (array[i] >= 0) {
			array[k] = array[i];
			k++;
		}
		i++;
	}
	len = k;
	return len;
}	

//Главная функция. Считывает массив из файла "input.txt". Убирает из него отрицательные элементы, возвращает длину получившегося массива и выводит получившийся его на экран. При этом исходный порядок элементов массиве сохраняется

int main() {
	int A;
	FILE *inp;
	int len;
    	double *array = NULL;

	inp = fopen("input.txt", "r");
	if (inp == NULL) {
		printf("При попытке открыть файл произошла ошибка\n");
		return -1;
	}

	A = read_arr(inp, &array, &len);
	
	if (A == -1) {
		printf("При чтении файла произошла ошибка\n");
		return -1;
	}
	
//	printf("Исходный массив:");
//	for (int j = 0; j < len; j++) {
//     		printf(" %lf", array[j]);
//   		}
//	printf("\n");

	len = remove_negative(array, len);

	if (len == 0) {
	   	printf("В исходном массиве не было положительных элементов. Положительный массив пуст\n");
		return 0;
	}
	
	printf("Количество оставшихся значений: %d\n", len);
	printf("Положительный массив:");
	for (int j = 0; j < len; j++) {
		printf(" %lf", array[j]);
	}
	printf("\n ");
	return 0;
}

