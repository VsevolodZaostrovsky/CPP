#include "MyException.h"

class Clock {
    private:
        int _N;
        int _ind;
        int * _proc;
        Clock() {}
    public:
        Clock(int N, int ind);
        Clock(Clock &C);
        ~Clock();

        Clock& operator =(const Clock& M);
		void local_ivent();
		void get_message(Clock& M);
        void print() const;

        bool friend operator< (const Clock &C1, const Clock &C2) {
            int flag = 0;
            if (C1._N != C2._N) {
                throw MyException("NEOKB_<", 0);
                return 0;
            }
            for (int k = 0; k < C1._N; k++) {
                if (C1._proc[k] > C2._proc[k]) {
                    return 0;
                }
                if (C1._proc[k] < C2._proc[k]) {
                    flag = 1;
                }
                return flag;
            }
        }

};