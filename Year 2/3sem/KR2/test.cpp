#include "Rest.h"

int main() {
    Rest T(5);
    T.order(3, 811);
    T.order(8, 822);
    T.order(8, 833);
    T.order(8, 844);
    T.print_all();
    return 0;
}