#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "ifdef.h"

int str_len(char *str) {
        int len = 0;
        while(str[len] != '\0') {
                len++;
        }
        return len;
}

int comp_len(char *Astr, char *Bstr, int len) {
    for (int p = 0; p < len; p++) {
        if (Astr[p] != Bstr[p]) {return 0; }
    }
    return 1;
}

int comp(char *Astr, char *Bstr) {
    int lenA = str_len(Astr);
    int lenB = str_len(Bstr);

    if (lenA != lenB)
	return 0;

    for (int d = 0; d < lenA - 1; d++) {
	if (Astr[d] != Bstr[d])
	    return 0;
    }
    return 1;
}

int is_True_name(char *name, char **True_names, int True_names_len) {
	for (int p = 0; p < True_names_len; p++) {
		if (comp(name, True_names[p])) {
			return 1;
		}
	}
	return 0;
}

int ifdef_one_step(char *string, char **True_names, int True_names_len) {
	char ifdef[] = "#ifdef";
	char els[] = "#else";
	char endif[] = "#endif";
	char space[] = " ";
	char *name = (char*)malloc(sizeof(char) * (str_len(string)+1));

	if (string[0] != ifdef[0]) {free(name); return STRING_IS_NOT_COMMAND; }
	if (comp_len(string, ifdef, 5)) {
		int t = 0;
    		while (string[t] != ' ') {t++; }
		while (string[t] == ' ') {t++; }
		int g = 0;
    		while (string[t] != '\n') {
            		name[g] = string[t];
           		g++; t++; }
		name[g] = '\0';
		if (is_True_name(name, True_names, True_names_len)) {
			free(name);
			return IFDEF_OK;
		}
		else {
	    		free(name);
	    		return IFDEF_NO_OK;
		}
	}
	
	if (comp_len(string, els, 5)) {free(name); return ELSE; }
	if (comp_len(string, endif, 6)) {free(name); return ENDIF; }
}

int ifdef_prime(FILE *inp, FILE *out, char **True_names, int True_names_len, int write) {
        size_t l;
        int ifdefs = 0;
        char *string = '\0';

        while(getline(&string, &l, inp) != -1) {
                switch(ifdef_one_step(string, True_names, True_names_len)) {
                        case IFDEF_OK:
                                if(ifdefs > 0) {
//                                        printf("ifdefOK: ifdef\n");
                                        ifdef_prime(inp, out, True_names, True_names_len, 1);
                                }
                                write = 1;
                                ifdefs++;
                                break;
                        case IFDEF_NO_OK:
                                if(ifdefs > 0) {
//                                        printf("ifdefNOOK: ifdef\n");
                                        ifdef_prime(inp, out, True_names, True_names_len, 0);
                                }
                                ifdefs++;
                                write = 0;
                                break;
                        case ELSE:
				if(write == 1) {write = 0; }
                                else
                                        write = 1;
                                break;
                        case ENDIF:
				free(string);
                                return 0;
                      	case STRING_IS_NOT_COMMAND:
                                if (write) {
                                        fprintf(out, "%s\n", string);
                                        printf("%s\n", string);
                                }
                                break;
                        default:
                                return -1;
                                break;
                }
        }
        free(string);
        return 0;
}

int ifdef (FILE *inp, FILE *out, char **True_names, int True_names_len) {
	size_t l;
	int a = 0; int b = 0;
	int ifdefs = 0;
	int write;
	char *string = '\0';

	while(getline(&string, &l, inp) != -1) {
		switch(ifdef_one_step(string, True_names, True_names_len)) {
			case IFDEF_OK:
				if(ifdefs > 0) {
//					printf("ifdefOK: ifdef\n");
					ifdef_prime(inp, out, True_names, True_names_len, 1);
				}
//				printf("ifdefOK\n");
				write = 1;
				ifdefs++;
				break;
	    		case IFDEF_NO_OK:
				if(ifdefs > 0) {
//					printf("ifdefNOOK: ifdef\n");
                                        ifdef_prime(inp, out, True_names, True_names_len, 0);
                                }
//				printf("ifdefNOOK\n");
				ifdefs++;
		 		write = 0;		
				break;
			case ELSE:
				if(write == 1) {write = 0; }
				else 
					write = 1;
				break;
	    		case ENDIF:
				free(string);
				return 0;
			case STRING_IS_NOT_COMMAND:
				if (write) {
					fprintf(out, "%s\n", string); 
					printf("%s\n", string);
				}
				break;
	    		default:
				return -1;
				break;
		}
	}
	free(string);
	return 0;
}
