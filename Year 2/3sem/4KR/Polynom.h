class Polynom
{
private:
    double * _koef;
    int _maxdegree;
    Polynom();
public:
    Polynom(int maxdegree);
    Polynom(Polynom &D);
    ~Polynom();

    double mean(double value) const;
    double koef(int k) const;
    bool set_koef(int k, double value);
    void print() const;


    Polynom friend operator+(const Polynom &A, const Polynom &B);
    Polynom& operator=(const Polynom &A);
};


