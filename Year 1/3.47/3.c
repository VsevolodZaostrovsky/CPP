#include <time.h>
#include <stdio.h>
#include <stdlib.h>


//Программа проверяет трудоёмкость сортировок: вставка с последовательным поиском, пирамидальная сортировка (heapsort) и сортировка с использованием библиотечной функции qsort
//Тесты проводятся на массивах длины 100, 1000 и 10000 из случайных рациональных чисел
//У каждой сортировки измеряется время работы и правильность сортировки


//Заполняет массив array длины len случайными действительными числами, не превышающими 100
void fill_random(double *array, unsigned int len) {
        unsigned int seed = time(0);
        srandom(seed);

    	for(unsigned int k = 0; k < len; k++) {
        	array[k] = 100 * ((double) random() / RAND_MAX);
    	}
}

//Функция проверяет корректность сортировки массива. 
//На экран выводится одна из надписей: "Сортировка выполнена с ошибками" или "Сортировка выполнена без ошибок"
int checking_for_order(double *array, unsigned int len) {
	for (int k = 0; k < len - 1; k++) {
		if (array[k] > array[k+1]) {
			printf("Сортировка выполнена с ошибками. ");
			return -1;
		}
	}
	printf("Сортировка выполнена без ошибок. ");
	return 0;

}

//Реализован алгоритм медленной сортировки "вставка с последовательным поиском"
void sort_insert_with_search(double *array, unsigned int len) {
	int location;
	double newElement;

    	for (int i = 1; i < len; i++) {
        	newElement = array[i];
        	location = i - 1;
        	while((location >= 0) && (array[location] > newElement)){
            		array[location+1] = array[location];
            		location = location - 1;
        	}
        	array[location+1] = newElement;
    	}
    	return;
}

//Реализуется подготовка массива к пирамидальной сортировке: просеивание массива
void sifting(double *array, int root, int bottom) {
	int max_child;
  	int done = 0; 
  	while ((root * 2 <= bottom) && (!done)) {
    		if (root * 2 == bottom)    
      			max_child = root * 2;    
    		else if (array[root * 2] > array[root * 2 + 1])
      			max_child = root * 2;
    		else {
      			max_child = root * 2 + 1;
		}
    		if (array[root] < array[max_child]) {
			double temp = array[root]; 
      			array[root] = array[max_child];
      			array[max_child] = temp;
      			root = max_child;
    		}
    		else { 
      			done = 1; 
		}
  	}
}

//Пирамидальная  сортировка
void sort_pyramidal(double *array, unsigned int len) {
  	for (int i = (len / 2) - 1; i >= 0; i--) {
    		sifting(array, i, len - 1);
	}
  	for (int i = len - 1; i >= 1; i--) {
    		double temp = array[0];
    		array[0] = array[i];
    		array[i] = temp;
    		sifting(array, 0, i - 1);
  	}
}

//Проверяется корректность сортировки "вставка с последовательным поиском", измеряется время её работы
//На экран выводится результат проверки корректности сортировки ("Сортировка выполнена с ошибками" или "Сортировка выполнена без ошибок") и время её выполнения в секундах и "клоках"
int check_sort_insert(double *array, unsigned int len) {
	time_t begin, end;

        begin = clock();
        sort_insert_with_search(array, len);
        end = clock();
	
        checking_for_order(array, len);
        printf("Потрачено %ld клоков = %f секнуд\n", (long int)(end-begin), ((double)(end-begin))/CLOCKS_PER_SEC);
	return 1;
}

//Проверяется корректность сортировки "пирамидальная сортировка", измеряется время её работы
//На экран выводится длина обрабатываемого массива, результат проверки корректности сортировки ("Сортировка выполнена с ошибками" или "Сортировка выполнена без ошибок") и время её выполнения в секундах и "клоках"

int check_sort_pyramidal(double *array, unsigned int len) {
        time_t begin, end;

        begin = clock();
        sort_pyramidal(array, len);
        end = clock();

        checking_for_order(array, len);
        printf("Потрачено %ld клоков = %f секнуд\n", (long int)(end-begin), ((double)(end-begin))/CLOCKS_PER_SEC);
        return 1;
}

//Функция сравнивает числа p1 и p2
//Вывод: p1 > p2 => 1 || p1 < p2 => -1 || p1==p2 => 0
static int compare_doubles(const void *p1, const void *p2) {
    double x = *((double *) p1);
    double y = *((double *) p2);
    if(x > y) return 1;
    if(x < y) return -1;
    return 0;
}

//Проверяется корректность библиотечной сортировки, измеряется время её работы
//На экран выводится длина обрабатываемого массива, результат проверки корректности сортировки ("Сортировка выполнена с ошибками" или "Сортировка выполнена без ошибок") и время её выполнения в секундах и "клоках"

int check_qsort(double *array, unsigned int len) {
        time_t begin, end;

        begin = clock();
        qsort(array, len, sizeof(array[0]), compare_doubles);
        end = clock();

        checking_for_order(array, len);
        printf("Потрачено %ld клоков = %f секнуд\n", (long int)(end-begin), ((double)(end-begin))/CLOCKS_PER_SEC);
   	printf("\n");
   	return 1;
}

//Функция копирует рациональный массив array в copy_array
void copy_array(double *array, unsigned int len, double *copy_array) {
	for (int i = 0; i < len; i++) {
			copy_array[i] = array[i];
	}
}

//Функция создаёт рациональный массив длины len и проверяет работу каждой из 3 сортировок на этом массиве
//На экран выводится длина обрабатываемого массива, результат проверки корректности каждой из сортировок ("Сортировка выполнена с ошибками" или "Сортировка выполнена без ошибок") и время выполнения каждой из них в секундах и "клоках"
void total_check(unsigned int len) {
	double A[len], B[len], C[len];
	unsigned int seed = time(0);

        srandom(seed);
        fill_random(A, len);

	copy_array(A, len, B);
	copy_array(A, len, C);
	
	printf("Длина обрабатываемого массива: %d\n", len );
	printf("Пирамидальная сортировка\n");
	check_sort_pyramidal(A, len);
	printf("Вставка с последовательным поиском\n");
	check_sort_insert(B, len);
	printf("Библиотечная функция\n");
	check_qsort(C, len);
}



int main() {	
	int len = 100;
	total_check(len);
	total_check(len * 10);
	total_check(len * 100);
    	return 0;
}
