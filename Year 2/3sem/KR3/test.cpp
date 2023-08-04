#include "Clock.h"
#include "MyException.h"
#include <iostream>

int main() {
    try {
        Clock A(3, 1);
        A.local_ivent();
        A.local_ivent();
        A.print();
        Clock B(3, 0);
        B.local_ivent();
        B.get_message(A);
        B.print();
    }
    catch(MyException &error) {
        std::cout << error.Message() << std::endl;
    }
    return 0;
}
