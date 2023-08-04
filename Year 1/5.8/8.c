#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Фунцкия читает массив длины len из файла inp и записывает в массив array, начиная с элемента номер start
//Ввод - массив длины len и номер элемента, начиная с которого начинается запись
//Вывод - массив заполняется числами из файла. Функция принимает значение первого числа после массива

double read_array(double *array, unsigned int len, FILE *inp) {
        double ai = 0;
        int i = 0;

	while ((i < len) && (fscanf(inp, "%lf", &ai) == 1)) {
		array[i] = ai;
                i++;	
	}
        return 0;
}

//Функция вычисляет расстоение между двумя точками плоскости (x, y) и (a,b)

double distance_points(double x, double y, double a, double b) {
	double ans;
	ans = (x - a)*(x - a) + (y - b)*(y - b);
	ans = sqrt(ans);

	return ans;
}

//Функция вычисляет расстояние между точкой и отрезком (отрезок a_1 a_2 - b_1 b_2 точка c_1 c_2)

double distance_segment_point(double a_1, double a_2, double b_1, double b_2, double c_1, double c_2) {
	double AB = sqrt((a_1 - b_1)*(a_1 - b_1) + (a_2 - b_2)*(a_2 - b_2));
	double BC = sqrt((c_1 - b_1)*(c_1 - b_1) + (c_2 - b_2)*(c_2 - b_2));
	double AC = sqrt((a_1 - c_1)*(a_1 - c_1) + (a_2 - c_2)*(a_2 - c_2));
	double p = (AB + BC + AC)/2;

	if (BC*BC > AC*AC + AB*AB) {
		return distance_points(a_1, a_2, c_1, c_2);
	}

	if (AC*AC > AB*AB + BC*BC) {
		return distance_points(b_1, b_2, c_1, c_2);
	}

	else {
		double S = sqrt(p*(p - AB)*(p - AC)*(p - BC));
		return 2*S/AB;
	}
}

//Функция вычисляет расстояние между двумя отрезками (a_1, a_2) (b_1, b_2) === (c_1, c_2) (d_1, d_2)

double distance_segments(double a_1, double a_2, double b_1, double b_2, double c_1, double c_2, double d_1, double d_2) {
	double dist = distance_segment_point(a_1, a_2, b_1, b_2, c_1, c_2);
	if (dist > distance_segment_point(a_1, a_2, b_1, b_2, d_1, d_2)) {  
		dist = distance_segment_point(a_1, a_2, b_1, b_2, d_1, d_2); }
	if (dist > distance_segment_point(c_1, c_2, d_1, d_2, b_1, b_2)) {
                dist = distance_segment_point(c_1, c_2, d_1, d_2, b_1, b_2); }
	if (dist > distance_segment_point(c_1, c_2, d_1, d_2, a_1, a_2)) {
                dist = distance_segment_point(c_1, c_2, d_1, d_2, a_1, a_2); }
	return dist;
}

//Функция вычисляет расстояние между двумя многоугольниками, задаваемыми массивами polygon_a и polygon_b//При этом массив интерпретируется как множество пар точек, записанных подряд

double distance_polygons(double *pol_a, int am_a, double *pol_b, int am_b) {
	double x_a, y_a, x_a_1, y_a_1, x_b, y_b, y_b_1, x_b_1, dist_min, dist, dist_b_to_A, dist_a_to_B;	
	x_a = pol_a[0]; 
	y_a = pol_a[1];
	x_a_1 = pol_a[am_a * 2 - 2];
        y_a_1 = pol_a[am_a * 2 - 1];
	x_b = pol_b[0];
        y_b = pol_b[1];
	x_b_1 = pol_b[am_b * 2 - 2];
        y_b_1 = pol_b[am_b * 2 - 1];

	dist_min = distance_segments(x_a, y_a, x_a_1, y_a_1, x_b, y_b, x_b_1, y_b_1);

	for (int k = 0; k < am_b * 2 - 2; k += 2) {
		dist = distance_segments(x_a, y_a, x_a_1, y_a_1, pol_b[k], pol_b[k + 1], pol_b[k + 2], pol_b[k + 3]);
		if (dist_min > dist) {
			dist_min = dist;
			x_b = pol_b[k];
			y_b = pol_b[k + 1];
			x_b_1 = pol_b[k + 2];
                        y_b_1 = pol_b[k + 3];
		}
	}
	
	for (int j = 0; j < am_a * 2 - 2; j += 2) {
                dist = distance_segments(x_b, y_b, x_b_1, y_b_1, pol_a[j], pol_a[j + 1], pol_a[j + 2], pol_a[j + 3]);
                if (dist_min > dist) {
                        dist_min = dist;
                        x_a = pol_a[j];
                        y_a = pol_a[j + 1];
                        x_a_1 = pol_a[j + 2];
                        y_a_1 = pol_a[j + 3];
                }
        }

	return dist_min;
}

//Два множества точек задают два выпуклых многоугольника, не лежащих один внутри другого. Функция определяет расстояние между этими многоугольниками с линейной оценкой трудоемкости по суммарному количеству вершин.
//Ввод: в файл "input.txt" записаны 2 массива. Первый элемент массива - количество точек (пар элементов) массива
//Пример: 2 1 2 3 4 2 4 5 5 6 Будет интерпретировано как {(1,2) (3,4)} {(4,5) (5,6)}
//Вывод: на экран выводится расстояние между многоугольниками, задаваемыми массивами

int main() {
	double *polygon_a = 0; 
	double *polygon_b = 0;
    	int amount_a, amount_b;  
	FILE *inp;
	FILE *out;

	inp = fopen("input.txt", "r");
    	
	if (inp == NULL) {
		printf("При попытке открыть файл произошла ошибка\n");
		return -1;
	}

	
    	if (fscanf(inp, "%d", &amount_a) != 1) {
       		printf("Не удалось прочитать первый элемент файла\n");
        	return -1;
    	}
	polygon_a = (double *)malloc(amount_a * 2 * sizeof(polygon_a[0]));
        
	if(polygon_a == NULL) {
                printf("При выделении памяти произошла ошибка\n");
                return -1;
        }
	if (amount_a < 1) {
                printf("Фигуры с такими параметрами не существует\n");
                return -1;
        }
	read_array(polygon_a, amount_a * 2, inp);
	fscanf(inp, "%d", &amount_b);
	polygon_b = (double *)malloc(amount_b * 2 * sizeof(polygon_b[0]));
        if(polygon_b == NULL) {
                printf("При выделении памяти произошла ошибка\n");
                return -1;
        }
	if (amount_b < 1) {
		printf("Фигуры с такими параметрами не существует\n");
		return -1;
	}
	read_array(polygon_b, amount_b * 2, inp);
	fclose(inp);

	double distance;
	distance = distance_polygons(polygon_a, amount_a, polygon_b, amount_b);
	
	out = fopen("output.txt", "w");
	printf("Расстояние между фигурами: %f\n", distance);
    	fprintf(out, "Расстояние между фигурами: %f\n", distance);
    	fclose(out);

	free(polygon_a);
	free(polygon_b);

	return 0;
}
