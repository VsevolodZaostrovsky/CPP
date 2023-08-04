#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info_about_file.h"

int main(void) {
    	FILE *inp;
    	inp = fopen("input.txt","r");
    	if(inp == NULL) {
        	printf("Не удалось открыть файл 'input.txt'\n");
        	return -1;
    	}
    	FILE *out;
    	out = fopen("output.txt","w");
    	int *dict = (int*)malloc(255 * sizeof(int));
	for(int i = 0; i < 255; i++) {
                dict[i] = 0;
        }
    	int max_len, min_len, symbols;
    	double average;
    
	info_about_file(inp, &max_len, &min_len, &average, dict, &symbols);

	if (symbols == 0) {
		printf("'input.txt' - пуст\n");
		fclose(inp);
        	fclose(out);
        	free(dict);
	}
	
	fprintf(out, "Всего %d символов. Длина слов в файле: от %d до %d. Средняя длина слова: %lf\n\n",
			symbols, min_len, max_len, average);
    	for(int i = 0; i < 255; i++) {
		if(dict[i] != 0) {
			fprintf(out, "Символ %c встретился %d раз. Частота его появления: %lf процентов\n",
				       	i, dict[i], (double)dict[i]/(double)symbols * 100);
    		}
	}
    	fclose(inp);
    	fclose(out);
    	free(dict);
    	return 0;
}
