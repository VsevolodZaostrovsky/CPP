#include "Matrix.h"
#include "iostream"
#include "MyException.h"

int main() {
    try
    {
        Matrix T(4, 7);
        T[0][0] = 1;
        T[1][1] = 2;
        T[2][2] = 3;
        T[3][3] = 4;
        std::cout << "Matrix T:" << std::endl;
        T.print();
        std::cout << std::endl;
        std::cout << "Matrix C(Copy of T):" << std::endl;
        Matrix C(T);
        C.print();
        std::cout << std::endl;
        Matrix D(5, 5);
        std::cout << "Matrix D=T+C:" << std::endl;
        D = (T + C);
        D.print();
        std::cout << "Matrix T:" << std::endl;
        T.print();
        std::cout << std::endl;
        Matrix::Submatrix SD(0, 0, 3, 2, D);
        std::cout << "Submatrix[0,0][3,2]" << std::endl;
        std::cout << SD[0][0] << " " << SD[0][1] << std::endl;
        std::cout << SD[1][0] << " " << SD[1][1] << std::endl;
        std::cout << SD[2][0] << " " << SD[2][1] << std::endl;
    }
    catch(MyException &error) {
        std::cout << error.Message() << std::endl;
    }
    return 0;
}