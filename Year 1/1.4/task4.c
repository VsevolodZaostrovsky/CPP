#include <stdio.h>


int main(){
	int num = 0; /*число, обрабатываемое в текущем цикле*/
	int num0 = 0; /*число, которое обрабатывалось в предыдцщем цикле*/
	int ans = 0;
	int d = 0;

	FILE *inp;
	inp = fopen("input.txt", "r");
	if (inp == NULL){ /*проверка существования файла*/
		printf("Не удалось открыть файл\n");
		return -1;
	}
	while (fscanf(inp, "%d", &num) == 1){ /*тело программы, перебор элементов списка */
		if (num0 < num && d != 0)
		{
			ans += 1;
		}
		num0 = num;
		d += 1;	
	}
	if (d == 0){
		printf("Не удалось прочитать первый элемент\n");
		fclose(inp);
		return -1;
	}
	fclose(inp);
	printf("Ответ:%d\n", ans);
	return 0;
}

