#include <stdio.h>
#include <stdlib.h>
#include "ifdef.h"

int main(int argc, char *argv[]) {
    printf("\n");
    FILE *inp;
    FILE *out;

    inp = fopen(argv[1], "r");
    if (inp == NULL) {
        printf("При попытке открыть файл %s произошла ошибка\n", argv[1]);
        return -1;
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("При попытке открыть файл %s произошла ошибка\n", argv[2]);
	return -1;
    }
    int True_len = argc - 3;
    char *True_names[True_len];


    for (int i = 0; i < True_len; i++) {
        True_names[i] = argv[i + 3];
    }
    ifdef(inp, out, True_names, True_len);
    fclose(inp);
    fclose(out);
    return 0;
}

