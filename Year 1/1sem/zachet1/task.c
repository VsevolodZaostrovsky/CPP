#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>


//Возвращает длину строки
int str_len(char *str) {
        int len = 0;
        while(str[len] != '\0') {
                len++;
        }
        return len;
}

//Читает массив из файла inp, записывает в массив matrix. Содержимое файла интерпретируется, как массив длины l
int read_matrix(FILE *inp, char **matrix, int l) {
	size_t len = 0;
	int i = 0;
	matrix[i] = '\0';
	while (getline(&matrix[i], &len , inp) != -1) {
	// printf("len = %ld\n", len);
		i++;
		matrix[i] = '\0';
	}
	if (i > l) {
		return -1;
	}
	return 1;
}

//Выводит массив на экран
int print_matrix(char **matrix, int l) {
        for (int i = 1; i < l + 1; i++) {
                printf("%s\n", matrix[i]);
        }
        return 1;
}

//Возвращает "совсем" kый элемент массива. 
//Под совсем-строкой я понимаю гипотетическую строку, образованную записанными подряд элементами массива строк matrix
//Под "совсем" kым элементом понимается kый элемент совсем-строки. Нумерация начинается с нуля
//Пример: массив 
// qwr 
// ty <--- вот тут "совсем" 3 
// yu
// Совсем-строка для него: qwrtyyu
// "Совсем" 3 я называю 't'

char array_k_point_ml(char **matrix, int l, int k) {
	int str_ind = 1;
	for (int i = 1; i < l + 1; i++) {
		k -= str_len(matrix[i]) - 1;
		if (k < 0) {
			str_ind = i;
			break;
		}
	}
	return matrix[str_ind][k + str_len(matrix[str_ind]) - 1];
}

//Проверяет, образует ли массив строк, будучи записанным в одну строку, полиндром. Если да, возвращает 1, если нет, возвращает 0
//Например, массив из предыдущего комментария образует строку qwrtyyu 
//Он полиндромом не является, так что функция вернёт 0

int is_polyndrom(char **matrix, int l) {
        int len_main = 0;
        for(int i = 0; i < l + 1; i ++) {
                len_main += str_len(matrix[i]) - 1;
        }
	int j;
	if (len_main%2 == 0) {
		j = len_main/2;
	}

	if (len_main%2 == 1) {
                j = (len_main - 1)/2;
        }

	int flag = 1;
//	printf("len_main = %d j = %d\n", len_main, j);
	for (int p = 0; p < j; p++) {
	      	if (array_k_point_ml(matrix, l, p) != array_k_point_ml(matrix, l, len_main - p - 1)) {
	      		flag = 0;
//			printf("len_main - p = %d\n", len_main - p);
	      }
	}

	return flag;
}	

int main(void) {
        FILE *inp;
	int len;

	inp = fopen("inp.txt", "r");
	if(inp == NULL || fscanf(inp, "%d", &len) != 1) {
		fclose(inp);
                return -1;
        }

	if (len < 1) {
		fclose(inp);
                return -1;
        }

	char **lines = (char **) malloc ((len + 2) * sizeof(char *));
        read_matrix(inp, lines, len);
//	print_matrix(lines, len);

	if (is_polyndrom(lines, len)) {
		printf("Полиндром\n");
	}
	else 
		printf("Не полиндром\n");

	for (int p = 0; p < len + 2; p++) {
		free(lines[p]);
	}
	free(lines);
        fclose(inp);

	return 1;
}
