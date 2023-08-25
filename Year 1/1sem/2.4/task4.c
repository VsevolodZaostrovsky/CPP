#include <stdio.h>
#include <stdlib.h>


//Программа принимает два рациональных числовых массива из файла "input.txt". Первое число перед каждым из массивов - его длина. Первый массив в файле называется А, второй - В
//Программа выводит на экран результат сравнения (А подмножество В, В подмножество А, А и В равны или ни одно из них не является подмножеством другого)

//Функция удаляет из массива array длины len повторяющиеся элементы. Возвращает длину массива без повторяющихся элементов
int prich(double *array, int len) {
	for(int i = 0; i < len; i++) {
        	for(int j = i + 1; j < len;) {
                	if(array[i] == array[j]) {
				array[j] = array[len - 1];
                        	len--;
                	}
                	else {
                        	j = j + 1;
                	}
        	}
    	}
	return len;
}


//Фунцкия читает массив длины len из файла inp и записывает в массив array, начиная с элемента номер start
//Ввод - массив длины len и номер элемента, начиная с которого начинается запись
//Вывод - массив заполняется числами из файла. Функция принимает значение первого числа после массива

double read_array(double *array, unsigned int len, FILE *inp) {
        double ai = 0;
        int i = 0;
	int k;
	int len_b = 0;

	while ((i < len) && (fscanf(inp, "%lf", &ai) == 1)) { //заполняем массив
		array[i] = ai;
                i++;	
	}
	fscanf(inp, "%d", &len_b);
        return len_b;
}


//Функция выясняет, является ли В подмножеством А
//Ввод - имя массива А(*a), его длина l_a, имя массива B(*b), его длина l_b
//Вывод - 1 - если является, 0 - если не является

int subset(double *a, unsigned int len_a, double *b, unsigned int len_b) {
	int num = 0;
	
        for(int t1 = 0; t1 < len_a; t1++) {
        	for(int t2 = 0; t2 < len_b; t2++) {
                	if (a[t1] == b[t2]){
                        	num += 1;
                     	}
              	}
       	}
        if ((num >= len_b)) {
       		return 1;
       	}
	else {
		return 0;
	}
}

//Функция сравнивает поступившие массивы А и В (А подмножество В, В подмножество А, А и В равны или ни один из них не является подмножеством другого)
//Ввод - имя массива А(*a), его длина len_a, имя массива B(*b), его длина len_b
//Вывод - на экран выводится результат сравнения двух массивов

int compare(double *a, unsigned int len_a, double *b, unsigned int len_b) {
	int A = subset(a, len_a, b, len_b);
	int B = subset(b, len_b, a, len_a);
	if ((A == 1) && (B == 0)) {
		printf("B подмножество А\n");
	}
	if ((B == 1) && (A == 0)) {
                printf("A подмножество B\n");
        }
	if ((A == 1) && (B == 1)) {	
                printf("А равно B\n");
	}
	if ((A == 0) && (B == 0)) {
                printf("Ни одно из множеств не является подмножеством другого\n");
	}
	return 0;
}
int main() {
	double *array_a = 0; // Адрес 0-ого элемента массива А
	double *array_b = 0; // Адрес 0-ого элемента массива В
    	int len_a;  // Длина массива А
    	int len_b;  // Длина массива В
	FILE *inp;

	inp = fopen("input.txt", "r");
    	//Проверка существования файла
	if (inp == NULL) {
		printf("При попытке открыть файл произошла ошибка\n");
		return -1;
	}

	//Создание массивов А и В и обработка некоторых ошибок
    	if (fscanf(inp, "%d", &len_a) != 1) { 
       		printf("Не удалось прочитать первый элемент файла\n");
        	return -1;
    	}
	array_a = (double *)malloc(len_a * sizeof(array_a[0]));
        if(array_a == NULL) {
                printf("При выделении памяти произошла ошибка\n");
                return -1;
        }
	if (len_a < 1) {
                printf("Указана некорректная длина массива A\n");
                return -1;
        }
	len_b = read_array(array_a, len_a, inp);
	array_b = (double *)malloc(len_b * sizeof(array_b[0]));
        if(array_b == NULL) {
                printf("При выделении памяти произошла ошибка\n");
                return -1;
        }
	if (len_b < 1) {
		printf("Указана некорректная длина массива В\n");
		return -1;
	}
	read_array(array_b, len_b, inp);
	fclose(inp);

	//из каждого массива удаляются одинаковые элементы
	len_a = prich(array_a, len_a);
	len_b = prich(array_b, len_b);
	
	//программа сравнивает массивы
	compare(array_a, len_a, array_b, len_b);
	
	//освобождение памяти
    	free(array_a);
	free(array_b);

    	return 0;
}



