typedef double (*RRFunc)(double x);

#define NOT_ENOUGH_ACCURACY 0 
#define WORK_OK 1
#define INVALID_INPUT 2
#define MAX_ITER 1000
#define THERE_IS_NO_MINIMUM 3


//Функция находит минимальное значение функции f на отрезке [a,b] c погрешностью epsilon и записывает код ошибки в переменную error_code
//Примечание: погрешность записывается в десятичных долях. При этом, например, 0.1 понимается как погрешность в 10%

double min_val_gold(RRFunc f, double a, double b, double epsilon, int *error_code);
