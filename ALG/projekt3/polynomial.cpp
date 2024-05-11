#include <vector>
#include <cmath>
#include <unordered_map>
#include <string>
#include <iostream>
#include "polynomial.h"
#include "utils.h"

polynomial::polynomial(std::vector<double> pV)
{
    this->polynomialVector = pV;
    this->polynomialMap = PolynomialVectorToMap(pV);
}
polynomial::polynomial(std::unordered_map<double, double> pM)
{
    this->polynomialMap = pM;
    this->polynomialVector = PolynomialMapToVector(pM);
}
polynomial::polynomial(int x){
    this->polynomialVector = std::vector<double>(1, x);
    this->polynomialMap[0] = x;
}
double polynomial::getPolynomialDegree()
{
    // check for 0 polynom, if all nums in polynom are 0
    double temp = 0;
    for (double i : this->polynomialVector) temp += i;
    if (temp == 0) return -INFINITY;

    // get the degree, get the reverse index of first non zero number in the vector
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
        std::cout << 0 << std::endl;
        return 1;
    }
    
    for (int i = this->polynomialVector.size()-1; i >= 0 ; i--)
    {
        if(this->polynomialVector[i] != 0){
            if(i == 0){
                std::cout << SignAsChar(this->polynomialVector[i]) << std::abs(this->polynomialVector[i]);//no x no superscript
            }
            else if(std::abs(this->polynomialVector[i]) == 1){
                std::cout << SignAsChar(this->polynomialVector[i]) << "x" << IntToSuperscriptChar(i);//no a
            }
            else{
                std::cout << SignAsChar(this->polynomialVector[i]) << std::abs(this->polynomialVector[i]) << "x" << IntToSuperscriptChar(i);//full format
            }
        }
    }
    std::cout << std::endl;  
    return 0;
}
double polynomial::getPolynomialValueInX(double x)
{
    double temp = 0;
    for (int i = this->polynomialVector.size()-1; i >= 0; i--)
    {
        temp += SignAsInt(this->polynomialVector[i]) * (std::abs(this->polynomialVector[i]) * std::pow(x, i));
    }   
    return temp;    
}
polynomial polynomial::polynomialAddition(polynomial secondPolynomial)
{
    std::vector<double> fin(std::max(this->getPolynomialDegree(), secondPolynomial.getPolynomialDegree())+1, 0);
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
    std::vector<double> fin(std::max(this->getPolynomialDegree(), secondPolynomial.getPolynomialDegree())+1, 0);
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
    std::unordered_map<double, double> fin;
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
    std::vector<double> fin(this->polynomialVector.size(), 0);
    for (int i = 1; i < this->polynomialVector.size(); i++)
    {
        if(this->polynomialVector[i] != 0){
            fin[i-1] = this->polynomialVector[i]*i;
        }
    }
    return polynomial(fin);    
}
polynomial polynomial::getPolynmomialAntiderivative()
{
    std::vector<double> fin(this->polynomialVector.size()+1, 0);
    fin[0] = 0;//konstanta C bude vyjadrena nulou, protoze vyjadreni neznamou by rozbilo scitani atd. 
    for (int i = 1; i < this->polynomialVector.size()+1; i++)
    {
        if(this->polynomialVector[i-1] != 0){
            fin[i] = this->polynomialVector[i-1] / i;
        }
    }
    return polynomial(fin);
}