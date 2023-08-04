typedef double (*RRFunc)(double x);

#define ROOT_OK 1
#define NOT_ENOUGH_ACCURACY 0
#define NO_ROOT -1

//С помощью метода хорд находит корень функции f на отрезке [a,b]
//Результат записывается в переменную x
//В случае нормальной работы, функция возвращает 1
//Если корней нет, -1
//Если корень найти удалось, но точность меньше заявленной, 0

int find_root_chord_method(RRFunc f, double a, double b, double eps, double *x);
