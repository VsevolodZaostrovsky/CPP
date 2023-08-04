#include "SetInt.h"
#include <iostream>


int main() {
    SetInt S1(9);
    S1.print();
    S1.add(5); S1.add(7); S1.add(10);
    S1.print();
    SetInt S2(8);
    S2.add(15); S2.add(71); S2.add(110);
    S2.print();
    SetInt S3(S1, S2);
    SetInt S(5);
    S = S3;
    S3.print();
    S.print();
    SetInt S4(5);
    S4 = S3 + S1;
    S4.print();
    return 0;
}