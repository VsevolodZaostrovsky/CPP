//Коды ошибок
#define WORK_OK 0
#define POINT_IS_NOT_IN_BETWEEN 1
       
//Функция вычисляет значение функции, восстанавливаемой по len точек, координаты х которых содержатся в массиве х, а у - в у, в точке а.
//Интерполяция линейная

double interpole(double* x, int len, double* y, double a, int *error_code); 
