using namespace std;
#include <iostream>
#include <vector>
#include <cmath>

string IntToSuperscriptChar(int number) {
    static const string superscripts[] = {
        "", "", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹",
        "¹⁰", "¹¹", "¹²", "¹³", "¹⁴", "¹⁵", "¹⁶", "¹⁷", "¹⁸", "¹⁹",
        "²⁰", "²¹", "²²", "²³", "²⁴", "²⁵", "²⁶", "²⁷", "²⁸", "²⁹",
        "³⁰", "³¹", "³²", "³³", "³⁴", "³⁵", "³⁶", "³⁷", "³⁸", "³⁹",
        "⁴⁰", "⁴¹", "⁴²", "⁴³", "⁴⁴", "⁴⁵", "⁴⁶", "⁴⁷", "⁴⁸", "⁴⁹",
        "⁵⁰", "⁵¹", "⁵²", "⁵³", "⁵⁴", "⁵⁵", "⁵⁶", "⁵⁷", "⁵⁸", "⁵⁹",
        "⁶⁰", "⁶¹", "⁶²", "⁶³", "⁶⁴", "⁶⁵", "⁶⁶", "⁶⁷", "⁶⁸", "⁶⁹",
        "⁷⁰", "⁷¹", "⁷²", "⁷³", "⁷⁴", "⁷⁵", "⁷⁶", "⁷⁷", "⁷⁸", "⁷⁹",
        "⁸⁰", "⁸¹", "⁸²", "⁸³", "⁸⁴", "⁸⁵", "⁸⁶", "⁸⁷", "⁸⁸", "⁸⁹",
        "⁹⁰", "⁹¹", "⁹²", "⁹³", "⁹⁴", "⁹⁵", "⁹⁶", "⁹⁷", "⁹⁸", "⁹⁹",
        "¹⁰⁰"
    };

    if (number > 1 && number <= 100) {
        return superscripts[number];
    } else {
        return "";
    }
}

const char* SignAsChar(double num){
    if (signbit(num))
    {
        return "-";
    }
    return "+";
}

int SignAsInt(int val) {
    return (0 < val) - (val < 0);//if greater than zero 1 - 0, if less than zero 0 - 1
}

int PrintPolynom(vector<double> polynom){
    for (int i = polynom.size()-1; i >= 0 ; i--)
    {
        if(polynom[i] != 0){
            if(i == 0){
                cout << SignAsChar(polynom[i]) << abs(polynom[i]);//no x no superscript
            }
            else if(abs(polynom[i]) == 1){
                cout << SignAsChar(polynom[i]) << "x" << IntToSuperscriptChar(i);//no a
            }
            else{
                cout << SignAsChar(polynom[i]) << abs(polynom[i]) << "x" << IntToSuperscriptChar(i);//full format
            }
        }
    }
    cout << endl;
    return 0;
}

double StupenPolynom(vector<double> polynom){
    //check for 0 polynom, if all nums in polynom are 0
    double temp = 0;
    for (double i : polynom) temp += i;
    if (temp == 0) return -INFINITY;

    //get the degree, get the reverse index of first non zero number in the vector
    for (int i = polynom.size()-1; i >= 0; i--)
    {
        if(polynom[i] > 0){
            return i;
        }
    }
    return 0;
}

double HodnotaPolynomuVX(vector<double> polynom, int x){
    double temp = 0;
    for (int i = polynom.size()-1; i >= 0; i--)
    {
        temp += SignAsInt(polynom[i]) * (abs(polynom[i]) * pow(x, i));
    }
    return temp;
}

int main(){

    vector<double> temp = {4,5,-1,7,0,3};
    PrintPolynom(temp);
    cout << StupenPolynom(temp) << endl;
    cout << HodnotaPolynomuVX(temp, 1) << endl;
    return 0;
}