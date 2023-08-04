#include "Clock.h"
#include "MyException.h"
#include <iostream>

Clock::Clock(int N, int ind) 
: _N(N), _proc(new int[_N]), _ind(ind) {
    if (N < 1 || ind < 0) {
        throw MyException("Bed_Clock", -1);
    }
}

Clock::Clock(Clock &C) 
: _N(C._N), _proc(new int[_N]), _ind(C._ind) {
    for (int k = 0; k < _N; k++) {
        _proc[k] = C._proc[k];
    }
}

Clock::~Clock() {
    delete [] _proc;
}

void Clock::local_ivent() {
    _proc[_ind] += 1;
}

void Clock::get_message(Clock &M) {
    
	if (M._N != _N) {
		throw MyException("_N are not similiar", -1);
	}

	int temp = 0;
    M._proc[M._ind] ++;
	for (int i = 0; i < _N; i++) {
		if (M._proc[i] > _proc[i]) {
			temp = M._proc[i];
        }
		else {
            temp = _proc[i];
        }

		_proc[i] = temp;
	}
	_proc[_ind]++;
}

void Clock::print() const {
    if (_N == 0) {
        std::cout << "emty" << std::endl;
    }
    for (int k = 0; k < _N; k++) {
        std::cout << _proc[k] << " ";
    }
    std::cout << std::endl;
}

Clock &Clock::operator=(const Clock& M) {
    if (this == &M) {
        return *this;
    }

    _N = M._N;
	_ind = M._ind;
	delete[] _proc;
	_proc = new int[_N];

    for (int k = 0; k < _N; k++) {
        _proc[k] = M._proc[k];
    }

    return *this;
}