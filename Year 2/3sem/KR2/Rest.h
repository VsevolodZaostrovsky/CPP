#include "Table.h"

class Rest {
    private:
        Table * _rest; 
        int _nt;
        Rest() {}
    public:
        Rest(int nt);
        Rest(Rest &R);
        ~Rest();

        int closest_free_time(int order_time, int cl_number);
        int order(int order_time, int cl_number);
        void print_all();

        friend class Table;
};
