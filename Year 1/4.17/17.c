#include <stdio.h>
#include <stdlib.h>

//Функция заполняет массив по следующему правилу: на нечётные места ставятся остатки, получающиеся при делении 1/num, на чётные - числа из "хвоста" 1/num
//Пример: num = 7
//Нечетные места: (10 % 7 =) 3 (30 % 7 =) 2 (20 % 7 =) 6 ....
//Четные места: 1/7 = 0,142857... 
//Массив: {1 3 4 2 2 6 ...}

int rem_tail_array(int *array, int len, int num) {
	int rem = 1;
       	int i = 0;
	while (i < len) {
		array[i] = 10*rem / num;
                rem = 10*rem % num;
                array[i + 1] = rem;
                i += 2;
		}
	return 0;
        }

//Функция ищет в массиве первый повторившийся элемент и записывает в start "координату" его первого появления, в finish - второго. При этом рассматриваются только элементы массива, стоящие на чётных позициях и накладывается дополнительное условие: элементы с нечётной координатой, непосредственно следующие за равными элементами с четными координатами должны быть равны
//Пример: {1 2 2 4 3 5 4 2 3 4 3 5} => start = 4, finish = 10

int find_cycle(int *array, int len, int *start, int *finish) {
	int f = 0;
	for (int i = 0; i < len; i+=2) {
		for (int j = i + 2; j < len; j+=2) {
//			printf("i=%d j=%d array[i]=%d array[j]=%d\n", i, j, array[i], array[j]);
			if ((array[i] == array[j]) && (array[i+1] == array[j+1]))  {
				(*finish) = j;
				(*start) = i;
				f = 1;
				break;
			}
		}
		if (f == 1) {
                               break;
                        }

	}
	return 0;
}

//Функция распечатывает неотрицательный целочисленный массив в виде array 0,abc...(def...) до элемента finish. Здесь a b c...d e f...  - элементы массива. Скобки стоят между элементами с номерами start и finish

int print_number(int *array, int start, int finish) {

	printf("\n0,");
        for (int i = 0; i < start; i+=2) {
                printf("%d", array[i]);
        }
        printf("(");
        for (int k = start; k < finish; k+=2) {
                printf("%d", array[k]);
        }
        printf(")\n");
	return 0;
}

//Функция вычисляет представление числа 1/N в виде десятичной дроби (начало и период)
//Ввод: с клавиатуры вводится натуральное число N
//Вывод: на экран печатается десятичная дробь вида 0,ab..(cde..), равная числу 1/N
//Пример: 66 => 0,0(15) 

int decimal_representation(int N) {
	int start, finish;
        int len;
        int *array = 0;


	if (N < 1) {
                printf("Введено неправильное число\n");
                return -1;
        }
        if (N == 1) {
                printf("1,(0)\n");
                return 0;
        }

        len = N * 4;
        array = (int *)malloc(len * sizeof(array[0]));

        rem_tail_array(array, len, N);
        find_cycle(array, len, &start, &finish);
        print_number(array, start, finish);

        free(array);
	return 0;
}

//Запускается функция decimal_representation. Обрабатывается неправильный ввод

int main() {
	int N;

	printf("Введите натуральное число N, представление 1/N которого нужно вычислить\n");
	if (scanf("%d", &N) != 1) {
		printf("Неправильные входные данные\n");
		return -1;
	}

	decimal_representation(N);

	return 0;
}
