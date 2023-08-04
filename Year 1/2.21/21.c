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

//Функция меняет местами блок из чисел от j+1 до i и число с индексом j
//Пример: (0 1 2 3 4 5 6) ==(change(array, 5, 1))=> (0 2 3 4 5 1 6)

int change(double *array, int i, int j) {
	double c;
	while (i > j) {
		c = array[i];
        	array[i] = array[i-1];
        	array[i-1] = c;
		i--;
	}
	return 0;
}

//Функция выполняет преобразование, описанное в задаче - группирует числа с чётными индексами в начале массива, а с нечётными - в конце, сохраняя их порядок 

int group_even_numbers(double *array, int len) {
	int j = 1;
	int iter;
	if (len % 2 == 1) {
		iter = len/2 + 1;
	}
	else {
		iter = len/2;
	}

	while (j < iter) {
		int i = j*2;
	       	change(array, i, j);	
		j++;
	}
	return 0;
}

//Функция выполняет следующее преобразование. Элементы с четными индексами группирует в начале массива с сохране-нием их исходного порядка относительно друг друга, а элементы с нечетными индексами группирует в конце массива также с сохранением их исходного порядка.
//Ввод: массив длины len в файле "input.txt" (длина - первый элемент в файле)
//Вывод: на экран выводятся исходный и обработанный массивы

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

	fclose(inp);

	printf("Исходный массив:");

	for (int j = 0; j < len; j++) {
     		printf(" %lf", array[j]);
   		}
	printf("\n");

	group_even_numbers(array, len);
	
	printf("Преобразованный массив:");
	for (int j = 0; j < len; j++) {
		printf(" %lf", array[j]);
	}
	printf("\n");
	return 0;
}
