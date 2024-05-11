/**
 * @file  main.cpp
 * @brief Implementuje použití třídy polynomial
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include "polynomial.h"
/**
* @fn int main()
* @brief tiskne výsledky funkcí třídy polynomial na testovacích vektorech
*/
int main()
{
    std::vector<double> temp = {4,5,-1,7,0,3};
    polynomial polynom1(temp);
    std::unordered_map<double, double> temp2 = {{8,4}, {1,9}, {4,2}};
    polynomial polynom2(temp2);
    std::cout << "Polynom a: ";
    polynom1.prettyPrintPolynomial();
    std::cout << "Polynom b: ";
    polynom2.prettyPrintPolynomial();
    std::cout << "Stupeň a: " << polynom1.getPolynomialDegree() << ", stupeň b: " << polynom2.getPolynomialDegree() << std::endl;
    std::cout << "Hodnota a v x = 5: " << polynom1.getPolynomialValueInX(5) << ", hodnota b v x = 2: " << polynom2.getPolynomialValueInX(2) << std::endl;
    std::cout << "Soucet a + b: ";
    polynom1.polynomialAddition(polynom2).prettyPrintPolynomial();
    std::cout << "Rozdil a - b: ";
    polynom1.polynomialSubtraction(polynom2).prettyPrintPolynomial();
    std::cout << "Soucin a * b: ";
    polynom1.polynomialAddition(polynom2).prettyPrintPolynomial();
    std::cout << "Derivace a: ";
    polynom1.getPolynomialDerivation().prettyPrintPolynomial();
    std::cout << "Derivace b: ";
    polynom2.getPolynomialDerivation().prettyPrintPolynomial();
    std::cout << "Integrace a: ";
    polynom1.getPolynmomialAntiderivative().prettyPrintPolynomial();
    std::cout << "Integrace b: ";
    polynom2.getPolynmomialAntiderivative().prettyPrintPolynomial();
    return 0;

}