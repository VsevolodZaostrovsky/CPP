#include "SetInt.h"
#include <iostream>

SetInt::SetInt(int len) : _len(len), _full(0), _data(new int[len]) {}

SetInt::SetInt(SetInt &Set) 
: _len(Set._len), _full(Set._full), _data(new int[Set._len]) {
    for (int k = 0; k < this->_full; k++) {
        this -> _data[k] = Set._data[k];
    }
}

SetInt::SetInt(SetInt &S1, SetInt &S2)
 : _len(S1._len + S2._len), _full(0), 
 _data(new int[S1._len + S2._len]) {
     for(int i = 0; i < S1._full; i++) {
         this -> add(S1._data[i]);
     }
     for(int i = 0; i < S2._full; i++) {
         this -> add(S2._data[i]);
     }
}

SetInt::~SetInt() {
    delete [] _data;
}

bool SetInt::is_full() {
    if (_full == _len) { return 1;}
    return 0;
}

bool SetInt::is_there(int k) {
    if (_full == 0) {
        return 0;
    }
    for (int p = 0; p < _full; p++) {
        if (this -> _data[p] == k) {
            return 1;
        } 
    }
    return 0;
}

void SetInt::add(int k) {
    if (this->is_full()) {
        return;
    }
    if (this->is_there(k)) {
        return;
    }

    _data[_full] = k;
    _full++;
}

void SetInt::print() {
    if (_full == 0) {
        std::cout << "empty" << std::endl;
    }
    for(int k = 0; k < _full; k++) {
        std::cout << _data[k] << " ";
    }
    std::cout << std::endl;
}

SetInt& SetInt::operator=(const SetInt &Set) {
    if (this -> _len > 0) {
        delete [] this -> _data;
    }
    this -> _full = Set._full;
    this -> _len = Set._len;
    this -> _data = new int[(this -> _len)];
    for (int j = 0; j < this -> _full; j++) {
        this -> _data[j] = Set._data[j]; 
    } 
    return *this;
}

SetInt operator+ (SetInt const & A, SetInt const & B) {
			SetInt C(A._len + B._len);
			for(int i = 0; i != A._full; ++i) {
            	C.add(A._data[i]);
    		}
    
    		for(int i = 0; i != B._full; ++i) {
            	C.add(B._data[i]);
            }
    		return C;
		}

SetInt U(SetInt const & A, SetInt const & B) {
    			SetInt C(A._len + B._len);
			for(int i = 0; i != A._full; ++i) {
            	C.add(A._data[i]);
    		}
    
    		for(int i = 0; i != B._full; ++i) {
            	C.add(B._data[i]);
            }
            SetInt & ref = C;
    		return ref;
		}