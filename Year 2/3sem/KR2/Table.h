class Table 
{
    private:
        int * _time;
        void order(int time, int cl_num);
    public:
        Table();
        Table(Table &T);
        ~Table();

        int is_free(int time);
        int try_to_order(int time, int cl_num);
        Table& operator=(Table &R);
        void print(); 
        friend class Rest;
};