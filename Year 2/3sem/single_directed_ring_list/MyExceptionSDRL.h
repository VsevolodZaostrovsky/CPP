#pragma once
#include <string.h>

enum ErrorCodeSDRL
{
SDRL_ERROR = -1010,
EC_MEMORY = -10,
};

class MyExceptionSDRL {
    private:
        char message[256];
        int error_code;
    public:
        MyExceptionSDRL(const char * _message, int _error_code = 0) {
            error_code = _error_code;
            strncpy(message, _message, 255);
        }
        int Er_Code() {return error_code; }
        const char * Message() const {return message; }
}; 