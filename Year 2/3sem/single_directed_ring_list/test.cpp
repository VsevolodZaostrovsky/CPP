#include <iostream>
#include "SRList.h"
#include "SRList.hpp"
#include "MyExceptionSDRL.h"
#include "Matrix.h"

int main()
{
    try
    {
        SRList<Matrix> SRMatrixList;
        Matrix V(2, 3);
        V.set(0, 0, 1);
        V.set(0, 1, 2);
        V.set(0, 2, 3);
        Matrix U(1, 3);
        U.set(0, 0, 3);
        U.set(0, 1, 2);
        U.set(0, 2, 1);
        Matrix O(3, 3);
        SRMatrixList.pushAfterFirst(V);
        SRMatrixList.pushAfterFirst(U);
        SRMatrixList.pushAfterFirst(O);
        std::cout << SRMatrixList;
        SRMatrixList.sort();
        std::cout << SRMatrixList;
        return 0;
    }
    catch (MyException &error)
    {
        std::cout << error.Message() << std::endl;
    }
}