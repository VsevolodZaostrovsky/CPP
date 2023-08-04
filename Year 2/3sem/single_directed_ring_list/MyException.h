#pragma once
#include <string.h>

enum ErrorCode
{
BAD_ROW = -4, 
BAD_SIZE = -3,
INDEX_IS_OUT = -2,
UNKNOWN_ERROR = -1,
MATRIX_OK = 0
};

class MyException {
    private:
        char message[256];
        int error_code;
    public:
        MyException(const char * _message, int _error_code = UNKNOWN_ERROR) {
            error_code = _error_code;
            strncpy(message, _message, 255);
        }
        int Er_Code() {return error_code; }
        const char * Message() const {return message; }
}; 
