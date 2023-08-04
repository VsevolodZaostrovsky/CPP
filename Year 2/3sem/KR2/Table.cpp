#include "Table.h"
#include "MyException.h"
#include <iostream>

Table::Table() {
    _time = new int[12];
}

Table::Table(Table &T) {
    for (int i = 0; i < 12; i++) {
        _time[i] = T._time[i];
    }
}

Table::~Table() {
    delete [] _time;
}

int Table::is_free(int time) {
    if (time == 12) { time == 0; }
    if (time < 0 || time > 9) {
        throw MyException("Bad", BAD_TABLE);
        return -1;
    }
    if (_time[time] == 0 && _time[time + 1] == 0 && _time[time + 2] == 0) 
    {
        return 1;
    }
    return 0;
}

void Table::order(int time, int cl_num) {
    _time[time] = cl_num; 
    _time[time + 1] = cl_num; 
    _time[time + 2] == cl_num;
}

int Table::try_to_order(int time, int cl_num) {
    if (is_free(time) > 0) {
        order(time, cl_num);
        return time;
    }
    for (int j = time; j < 10; j ++) {
        if (is_free(j) > 0) {
        return time;
        }
    }
    return -1;
}

Table &Table::operator=(Table &T) {
    if (this == &T) {
        return T;
    }
    if (this -> _time != nullptr) {
        delete [] this -> _time;
    }
    for (int k = 0; k < 12; ++k) {
        this -> _time[k] = T._time[k];
    }
    return *this;
}

void Table::print() {
    for (int i = 0; i < 12; i++) {
        if (_time[i] != 0) {
            std::cout << "From " << i << " to " << i + 3 << " number: "<<_time[i] << std::endl;
            i += 3;
        }
    }
}