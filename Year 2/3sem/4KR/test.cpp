#include "Polynom.h"
#include "MyException.h"
#include <math.h>
#include <iostream>

int main() {
    try {
        Polynom A(3);
        A.set_koef(0, 1);
        A.set_koef(1, 3);
        A.print();
        Polynom B(4);
        B.set_koef(3, 3);
        B.set_koef(2, 2);
        B.set_koef(0, 1);
        B.print();
        Polynom C(5);
        C = A + B;
        C.print();
    }
    catch(MyException &error) {
        std::cout << error.Message() << std::endl;
    }
}