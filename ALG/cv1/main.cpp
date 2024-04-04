#include <iostream>
#include <cmath>
using namespace std;

int SolveEquation(const double a, const double b, const double c, double& x1, double& x2){
    double D = b * b - 4 * a * c;
    if (D > 0){
        x1 = (-b - sqrt(D)) / (2 * a);
        x2 = (-b + sqrt(D)) / (2 * a);
        return 2;
    }
    if(D == 0){
        x1 = -b/(2*a);
        x2 = x1;
        return 1;
    }
    if (D < 0){
        return 0;
    }
    return 3;
}

int MaxSpolecnyDelitelRekurze(int a, int b){
    if(a==b){
        return a;
    }
    if (a > b)
    {
        MaxSpolecnyDelitelRekurze(a-b, b);
    }else{
        MaxSpolecnyDelitelRekurze(a, b-a);
    }
}
int MaxSpolecnyDelitel(int a, int b){
    while (a != b)
    {
            if (a > b)
            {
                a -= b;
            }
            if (b > a)
            {
                b -= a;
            } 
    }   
    return b;
}
int MaxSpolecnyDelitelModulo(int a, int b){
    int temp;
    while (b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

bool JePrvocislo(int a){
    switch (a)
    {
    case 0:
        return false;
    case 1:
        return false;
    default:
        break;
    }
    for (int i = 2; i < a; i++)
    {
        if (a % i == 0)
        {
            return false;
        }
    }
    return true;
}
int PoleInit(bool pole[]){
    for (int i = 0; i < 100; i++)
    {
        pole[i] = true;
    }
    pole[0] = false;
    pole[1] = false;
}
int Sito(bool pole[]){

    for (int i = 2; i*i < 100; i++)
    {
        if (pole[i])
        {
            pole[i] = true;
            for (int l = i+i; l < 100; l+=i)
            {
                pole[l] = false;
            }
        }
    }  
}
int PP(bool pole[]){
    for (int i = 0; i < 10; i++)
    {
        for (int l = 0; l < 10; l++)
        {
            if (pole[i*10 + l])
            {
                cout << " ";
                cout << i*10 + l;
                cout << " ";
            }
            else{
                cout << 0;
            }
        }
        cout << endl;
    }
}

int main(){
    bool pole[100];
    PoleInit(pole);
    Sito(pole);
    PP(pole);
}