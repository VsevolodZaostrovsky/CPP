class SetInt
{
    private:
        int _len;
        int _full;
        int * _data;
        SetInt();
    public:
        SetInt(int len);
        SetInt(SetInt &Set);
        SetInt(SetInt &S1, SetInt &S2);
        ~SetInt();

        bool is_full();
        bool is_there(int k);
        void add(int k);
        void print();

        SetInt& operator=(const SetInt& Set);

        friend SetInt operator+ (SetInt const & A, SetInt const & B);
        friend SetInt U(SetInt const & A, SetInt const & B);
};