#include <stdio.h>

//функция определяет номер последнего числа, равного минимуму по всей последовательности. Номера считаются с нуля.
//Ввод - файл
//Вывод - целое число

int main() { 
	int nummin = 0; /*номер минимального числа*/
	int numn = 0;	/*номер числа, обрабатываемого в цикле*/
	int min = 0;    /*значение минимального числа */	
	int n = 0;      /*значение числа, обрабатываемого в цикле */
	FILE *inp;

	inp = fopen("input.txt", "r");
	if (inp == NULL) { /*проверка существования файла*/
		printf("Не удалось открыть файл\n");
		return -1;
	}
	while (fscanf(inp, "%d", &n) == 1) { /*тело программы, перебор элементов списка */
			if((numn == 0) || (n <= min)) {
				min = n;
				nummin = numn;
			}
			numn += 1;
	}
	fclose(inp);
	if (numn == 0) { 
		printf("При чтении последовательности произошла ошибка\n");
		return -1;
	}
	printf("Ответ:%d\n", nummin);
	return 0;
}
