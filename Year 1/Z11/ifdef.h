#define STRING_IS_NOT_COMMAND 0
#define IFDEF_OK 1
#define IFDEF_NO_OK -1
#define ELSE 2
#define ENDIF 3

int ifdef (FILE *inp, FILE *out, char **True_names, int True_names_len);
