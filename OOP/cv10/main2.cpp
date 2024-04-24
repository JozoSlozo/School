#include <iostream>
#include <cmath>

using namespace std;

class Geometry
{
public:
    Geometry();
    virtual double obvod();
    virtual double obsah();
};
Geometry::Geometry(){}
double Geometry::obvod(){
    return 0;
}
double Geometry::obsah(){
    return 0;
}
//-----------------------------------------------------
class kruh : public Geometry
{
private:
    double polomer;

public:
    kruh(double p);
    double obvod();
    double obsah();
};

kruh::kruh(double p){
    this->polomer = p;
}

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
    double obvod();
    double obsah();
};

ctverec::ctverec(double s){
    this->strana = s;
}

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
    double obvod();
    double obsah();
};
    int hitPoints;
    int manaPoints;
public:
    item(string name, int damage);
    item()

obdelnik::obdelnik(double a, double b){
    this->stranaA = a;
    this->stranaB = b;
}

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
public:
    skupina(int a);
    bool add(Geometry *a);
    double obsahy();
    double obvody();
    ~skupina();
};

skupina::skupina(int a){
    this->objekty = new Geometry*[a];
    this->objektycount = 0;
}

skupina::~skupina()
{
    for (int i = 0; i < this->objektycount; ++i)
    {
        delete this->objekty[i];
    }
    delete[] this->objekty;
}

bool skupina::add(Geometry *a)
{
    this->objekty[this->objektycount++] = a;
    return true;
}

double skupina::obsahy()
{
    double temp = 0;
    for (int i = 0; i < this->objektycount; ++i)
    {
        temp += this->objekty[i]->obsah();
    }
    return temp;
}
double skupina::obvody()
{
    double temp = 0;
    for (int i = 0; i < this->objektycount; ++i)
    {
        temp += this->objekty[i]->obvod();
    }
    return temp;
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
    cout << "obsahy: " << S->obsahy() << endl;
    cout << "obvody: " << S->obvody() << endl;
    delete S;
    return 0;
}
