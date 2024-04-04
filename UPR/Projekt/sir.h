typedef struct
{
    double s;
    double i;
    double r;
}SIR;

typedef struct
{
    int suspectable;
    int infected;
    int recovered;
    double b;
    double y;
    SIR *history;
}Parameters;

double S(int d, Parameters params);
double I(int d, Parameters params);
double R(int d, Parameters params);
int inithistory(Parameters *param, int len);
int freehistory(Parameters *param);