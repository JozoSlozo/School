/**
 * @file  main.cpp
 * @brief Implementuje třídu polynom.
*/
/**
* @fn vector<double> PolynomialMapToVector(unordered_map<double, double> polynom)
* @brief převod vyjádření polynomu unordered_map -> vector
* @param polynom polynom vyjádřen unordered_map<double, double>
* @return polynom vyjádřený vector<double>
*/
/**
* @fn string IntToSuperscriptChar(int number)
* @brief převádí číslo na charakter horního indexu
* @param number int číslo, musí být v rozmezí 2-100
* @return horní index daného čísla, prázdný charakter když je číslo mimo meze
*/
/**
* @fn const char* SignAsChar(double num)
* @brief znaménko čísla jako charakter
* @param num jakékoliv číslo
* @return znaménko daného čísla jako charakter
*/
/**
* @fn int SignAsInt(int val)
* @brief znaménko jako číslo
* @param val jakékoliv číslo
* @return -1 pokud je číslo záporne, 1 pokud je kladne, 0 pokud je 0
*/
/**
* @fn unordered_map<double, double> PolynomialVectorToMap(vector<double> polynom)
* @brief převod vyjádření polynomu vector -> unordered_map
* @param polynom polynom vyjádřen vector<double>
* @return polynom vyjádřený unordered_map<double, double>
*/
/**
* @fn int main()
* @brief tiskne do konzole výsledky funckí na testovacích polynomech
*/
using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

#pragma region util
string IntToSuperscriptChar(int number)
{
    //array stringu byl vygenerovan ChatGPT
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

    if (number > 1 && number <= 100) 
    {
        return superscripts[number];
    } 
    else 
    {
        return "";
    }
}

const char* SignAsChar(double num)
{
    if (signbit(num))
    {
        return "-";
    }
    return "+";
}

int SignAsInt(int val) 
{
    return (0 < val) - (val < 0);//if greater then zero 1 - 0, if less then zero 0 - 1
}
vector<double> PolynomialMapToVector(unordered_map<double, double> polynom)
{
    int maxPow = 0;
    for (auto [power, number] : polynom)
    {
        if (power > maxPow)
        {
            maxPow = power;
        }
    }
    vector<double> fin(maxPow+1, 0);
    for (auto [power, number] : polynom)
    {
        fin[power] = number;
    }
    return fin;
}
unordered_map<double, double> PolynomialVectorToMap(vector<double> polynom){
    unordered_map<double, double> temp;
    for (int i = 0; i < polynom.size(); i++)
    {
        if (polynom[i] != 0)
        {
            temp[i] = polynom[i];
        }
    }
    return temp;
}
#pragma endregion
/**
* @brief Třída Polynom.
*
* Tato třída zpracovává základní operace s polynomy.
*/
class polynomial
{
private:
    /**
    * @brief Vektorové vyjádření polynomu.
    *
    * polynom lze vyjádřit pomocí vectoru<double>, kde index jednotlivé hodnoty vyjadřuje její stupeň x
    */
    vector<double> polynomialVector;
    /**
    * @brief Unorderet_map vyjádření polynomu.
    *
    *  polynom lze vyjádřit pomocí unordered_map<double, double>, kde první číslo pairu je stupeň x a druhé číslo hodnota a.
    */
    unordered_map<double, double> polynomialMap;
public:
    /**
    * @brief Konstruktor třídy polynom.
    *
    * @param polynomialVector vektorové vyjádření polynomu
    */
    polynomial(vector<double> polynomialVector);
    /**
    * @brief Konstruktor třídy polynom.
    * 
    * @param polynomialMap vyjádření polynomu pomoci unordered_map
    */
    polynomial(unordered_map<double, double> polynomialMap);
    /**
    * @brief Konstruktor třídy polynom.
    * 
    * @param x vyjádření polynomu pomocí čísla, nultý polynom
    */
    polynomial(int x);
    /**
    * @brief Stupeň polynomu.
    * 
    * @return Stupeň polynomu, -INFINITY když je polynom nulový
    */
    double getPolynomialDegree();
    /**
    * @brief Vytiskne polynom do terminálu.
    * 
    * @return 1 když je polynom nulový, 0 když není
    */
    int prettyPrintPolynomial();
    double getPolynomialValueInX(double x);
    /**
    * @brief Hodnota polynomu v X.
    * @param x číslo x podle které se počítá hodnota polynomu
    * @return hodnotu polynomu v x
    */
    polynomial polynomialAddition(polynomial secondPolynomial);
    /**
    * @brief Součet dvou polynomů.
    * @param secondPolynomial druhý sčítanec
    * @return výsledný polynom po sčítání
    */
    polynomial polynomialSubtraction(polynomial secondPolynomial);
    /**
    * @brief Rozdíl dvou polynomů.
    * @param secondPolynomial menšitel rozdílu
    * @return výsledný polynom po rozdílu
    */
    polynomial polynomialMultiplication(polynomial secondPolynomial);
    /**
    * @brief Součin dvou polynomů.
    * @param secondPolynomial druhý činitel
    * @return výsledný polynom po součinu
    */
    polynomial getPolynomialDerivation();
    /**
    * @brief Derivace polynomu.
    * @return první derivaci polynomu
    */
};
polynomial::polynomial(vector<double> pV)
{
    this->polynomialVector = pV;
    this->polynomialMap = PolynomialVectorToMap(pV);
}
polynomial::polynomial(unordered_map<double, double> pM)
{
    this->polynomialMap = pM;
    this->polynomialVector = PolynomialMapToVector(pM);
}
polynomial::polynomial(int x){
    this->polynomialVector = vector<double>(1, x);
    this->polynomialMap[0] = x;
}
double polynomial::getPolynomialDegree()
{
    //check for 0 polynom, if all nums in polynom are 0
    double temp = 0;
    for (double i : this->polynomialVector) temp += i;
    if (temp == 0) return -INFINITY;

    //get the degree, get the reverse index of first non zero number in the vector
    for (int i = this->polynomialVector.size()-1; i >= 0; i--){
        if(this->polynomialVector[i] > 0){
            return i;
        }
    }
    return 0;
}
int polynomial::prettyPrintPolynomial()
{
    if (this->getPolynomialDegree() == -INFINITY)
    {
        cout << 0 << endl;
        return 1;
    }
    
    for (int i = this->polynomialVector.size()-1; i >= 0 ; i--)
    {
        if(this->polynomialVector[i] != 0){
            if(i == 0){
                cout << SignAsChar(this->polynomialVector[i]) << abs(this->polynomialVector[i]);//no x no superscript
            }
            else if(abs(this->polynomialVector[i]) == 1){
                cout << SignAsChar(this->polynomialVector[i]) << "x" << IntToSuperscriptChar(i);//no a
            }
            else{
                cout << SignAsChar(this->polynomialVector[i]) << abs(this->polynomialVector[i]) << "x" << IntToSuperscriptChar(i);//full format
            }
        }
    }
    cout << endl;  
    return 0;
}
double polynomial::getPolynomialValueInX(double x)
{
    double temp = 0;
    for (int i = this->polynomialVector.size()-1; i >= 0; i--)
    {
        temp += SignAsInt(this->polynomialVector[i]) * (abs(this->polynomialVector[i]) * pow(x, i));
    }   
    return temp;    
}
polynomial polynomial::polynomialAddition(polynomial secondPolynomial)
{
    vector<double> fin(max(this->getPolynomialDegree(), secondPolynomial.getPolynomialDegree())+1, 0);
    for (int i = 0; i < this->polynomialVector.size(); i++)
    {
        fin[i] = this->polynomialVector[i];
    }
    for (int i = 0; i < secondPolynomial.polynomialVector.size(); i++)
    {
        fin[i] += secondPolynomial.polynomialVector[i];
    }
    return polynomial(fin);    
}
polynomial polynomial::polynomialSubtraction(polynomial secondPolynomial)
{
    vector<double> fin(max(this->getPolynomialDegree(), secondPolynomial.getPolynomialDegree())+1, 0);
    for (int i = 0; i < this->polynomialVector.size(); i++)
    {
        fin[i] = this->polynomialVector[i];
    }
    for (int i = 0; i < secondPolynomial.polynomialVector.size(); i++)
    {
        fin[i] -= secondPolynomial.polynomialVector[i];
    }
    return polynomial(fin);   
}
polynomial polynomial::polynomialMultiplication(polynomial secondPolynomial)
{
    unordered_map<double, double> fin;
    for (auto [stpower, stnumber] : this->polynomialMap)
    {
        for (auto [ndpower, ndnumber] : secondPolynomial.polynomialMap)
        {
            fin[ndpower+stpower] += ndnumber*stnumber;
        }
    }
    return polynomial(fin);
}
polynomial polynomial::getPolynomialDerivation()
{
    vector<double> fin(this->polynomialVector.size(), 0);
    for (int i = 1; i < this->polynomialVector.size(); i++)
    {
        if(this->polynomialVector[i] != 0){
            fin[i-1] = this->polynomialVector[i]*i;
        }
    }
    return polynomial(fin);    
}
int main()
{
    vector<double> temp = {4,5,-1,7,0,3};
    polynomial polynom1(temp);
    unordered_map<double, double> temp2 = {{8,4}, {1,9}, {4,2}};
    polynomial polynom2(temp2);
    cout << "Polynom a: ";
    polynom1.prettyPrintPolynomial();
    cout << "Polynom b: ";
    polynom2.prettyPrintPolynomial();
    cout << "Stupeň a: " << polynom1.getPolynomialDegree() << ", stupeň b: " << polynom2.getPolynomialDegree() << endl;
    cout << "Hodnota a v x = 5: " << polynom1.getPolynomialValueInX(5) << ", hodnota b v x = 2: " << polynom2.getPolynomialValueInX(2) << endl;
    cout << "Soucet a + b: ";
    polynom1.polynomialAddition(polynom2).prettyPrintPolynomial();
    cout << "Rozdil a - b: ";
    polynom1.polynomialSubtraction(polynom2).prettyPrintPolynomial();
    cout << "Soucin a * b: ";
    polynom1.polynomialAddition(polynom2).prettyPrintPolynomial();
    cout << "Derivace a: ";
    polynom1.getPolynomialDerivation().prettyPrintPolynomial();
    cout << "Derivace b: ";
    polynom2.getPolynomialDerivation().prettyPrintPolynomial();
    return 0;

}