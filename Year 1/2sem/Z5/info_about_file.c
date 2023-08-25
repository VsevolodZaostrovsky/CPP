#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "info_about_file.h"

int str_len(char *str) {
        int len = 0;
        while(str[len] != '\0') {
                len++;
        }
        return len;
}

int info_about_file(FILE *inp, int *max_len, int *min_len, double *average, int *dict, int *symbols) {
	char *str = '\0';
	int words = 0;
    	int word_len = 0;
    	int symbol, len;
	size_t l;
	*min_len = 0;
    	*max_len = 0;
    	*symbols = 0;

	while(getline(&str, &l, inp) != -1) {
		len = str_len(str);

		for(int p = 0; p < len; p++) {
	    		symbol = str[p];
	    		if(p != len - 1 && symbol != ' ') {
				dict[symbol]++;
				(*symbols)++;
				word_len++;
			}
			
			else {
				words++;
				if (word_len > *max_len) { *max_len = word_len; }
				if (word_len < *min_len || *min_len == 0 && word_len > 0) { 
					*min_len = word_len; 
				}
				word_len = 0;
			}
		}
		*average = (double)*symbols / (double)words;
    		}
	free(str);
	return 0;
}

	

