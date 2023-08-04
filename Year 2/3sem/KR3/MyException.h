#pragma once
#include <string.h>

enum ErrorCode
{
ERROR = -1
};

class MyException {
    private:
        char message[256];
        int error_code;
    public:
        MyException(const char * _message, int _error_code = 0) {
            error_code = _error_code;
            strncpy(message, _message, 255);
        }
        int Er_Code() {return error_code; }
        const char * Message() const {return message; }
}; 