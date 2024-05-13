/**
 * @file  polynomial.h
 * @brief Implementuje třídu polynomial.
*/

#include <vector>
#include <cmath>
#include <unordered_map>


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
    * polynom lze vyjádřit pomocí std::vector<double>, kde index jednotlivé hodnoty vyjadřuje její stupeň x
    */
    std::vector<double> polynomialVector;
    /**
    * @brief Unorderet_map vyjádření polynomu.
    *
    *  polynom lze vyjádřit pomocí std::unordered_map<double, double>, kde první číslo pairu je stupeň x a druhé číslo hodnota a.
    */
    std::unordered_map<double, double> polynomialMap;
public:
    /**
    * @brief Konstruktor třídy polynom.
    *
    * @param polynomialVector vektorové vyjádření polynomu
    */
    polynomial(std::vector<double> polynomialVector);
    /**
    * @brief Konstruktor třídy polynom.
    * 
    * @param polynomialMap vyjádření polynomu pomoci unordered_map
    */
    polynomial(std::unordered_map<double, double> polynomialMap);
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
    /**
    * @brief Hodnota polynomu v X.
    * @param x číslo x podle které se počítá hodnota polynomu
    * @return hodnotu polynomu v x
    */
    double getPolynomialValueInX(double x);
    /**
    * @brief Součet dvou polynomů.
    * @param secondPolynomial druhý sčítanec
    * @return výsledný polynom po sčítání
    */
    polynomial polynomialAddition(polynomial secondPolynomial);
    /**
    * @brief Rozdíl dvou polynomů.
    * @param secondPolynomial menšitel rozdílu
    * @return výsledný polynom po rozdílu
    */
    polynomial polynomialSubtraction(polynomial secondPolynomial);
    /**
    * @brief Součin dvou polynomů.
    * @param secondPolynomial druhý činitel
    * @return výsledný polynom po součinu
    */
    polynomial polynomialMultiplication(polynomial secondPolynomial);
    /**
    * @brief Derivace polynomu.
    * @return první derivaci polynomu
    */
    polynomial getPolynomialDerivation();
    /**
    * @brief Primitivní funkce, integrace polynomu.
    * @return integraci polynomu
    */
    polynomial getPolynmomialAntiderivative();   
};
