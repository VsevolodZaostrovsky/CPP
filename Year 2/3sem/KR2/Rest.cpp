#include "Rest.h"
#include <iostream>

Rest::Rest(int nt) : _nt(nt), _rest(new Table[nt]) {}

Rest::Rest(Rest &R) : _nt(R._nt), _rest(new Table[R._nt]) {
    for (int i = 0; i < _nt; ++i) {
        _rest[i] = R._rest[i];
    }

}
Rest::~Rest() {
    delete [] _rest; 
}

int Rest::closest_free_time(int order_time, int cl_number) {
    int closest_time = _rest[0].try_to_order(order_time, cl_number);
    int this_time;
    for (int i = 1; i < _nt; ++i) {
        if (closest_time == order_time) {
            return order_time;
        }
        this_time = 
        _rest[i].try_to_order(order_time, cl_number);
        if (closest_time < 0 && this_time > 0) {
            closest_time = this_time;
        }
        if (this_time < closest_time && this_time > 0) {
            closest_time = this_time;
        }
    }
    return closest_time;
}

int Rest::order(int order_time, int cl_number) {
    int ttime;
    for (int i = 0; i < _nt; ++i) {
        ttime = _rest[i].try_to_order(order_time, cl_number);
        if (ttime == order_time) {
            return order_time;
        }
    }
    return -1;
}

void Rest::print_all() {
    for (int i = 0; i < _nt; ++i) {
        std::cout<< "Table " << i << std::endl;
        _rest[i].print();
    }
}