#include <iostream>
#include <cmath> // Use <cmath> instead of <math.h>

using namespace std;

class Geometry
{
public:
    Geometry() {}
    virtual double obvod() = 0;
    virtual double obsah() = 0;
    virtual ~Geometry() {}
};

//-----------------------------------------------------
class kruh : public Geometry
{
private:
    double polomer;

public:
    kruh(double p);
    double obvod() override;
    double obsah() override;
};

kruh::kruh(double p) : polomer(p) {}

double kruh::obvod()
{
    return M_PI * 2 * polomer;
}

double kruh::obsah()
{
    return M_PI * (polomer * polomer);
}

//----------------------------------------------------
class ctverec : public Geometry
{
private:
    double strana;

public:
    ctverec(double s);
    double obvod() override;
    double obsah() override;
};

ctverec::ctverec(double s) : strana(s) {}

double ctverec::obvod()
{
    return 4 * strana;
}

double ctverec::obsah()
{
    return strana * strana;
}

//--------------------------------------------------
class obdelnik : public Geometry
{
private:
    double stranaA;
    double stranaB;

public:
    obdelnik(double a, double b);
    double obvod() override;
    double obsah() override;
};

obdelnik::obdelnik(double a, double b) : stranaA(a), stranaB(b) {}

double obdelnik::obvod()
{
    return 2 * (stranaA + stranaB);
}

double obdelnik::obsah()
{
    return stranaA * stranaB;
}

//------------------------------------------------------
class skupina
{
private:
    Geometry **objekty;
    int objektycount;
    int capacity;

public:
    skupina(int a);
    bool add(Geometry *a);
    double obsahy();
    ~skupina();
};

skupina::skupina(int a) : capacity(a), objekty(new Geometry *[a]), objektycount(0) {}

skupina::~skupina()
{
    for (int i = 0; i < objektycount; ++i)
    {
        delete objekty[i];
    }
    delete[] objekty;
}

bool skupina::add(Geometry *a)
{
    objekty[objektycount++] = a;
    return true;
}

double skupina::obsahy()
{
    double total_area = 0;
    for (int i = 0; i < objektycount; ++i)
    {
        total_area += objekty[i]->obsah();
    }
    return total_area;
}

int main()
{
    obdelnik *A = new obdelnik(5, 10);
    ctverec *B = new ctverec(5);
    kruh *C = new kruh(5);
    skupina *S = new skupina(10);
    S->add(A);
    S->add(B);
    S->add(C);
    cout << "Total area: " << S->obsahy() << endl;
    delete S;
    return 0;
}
