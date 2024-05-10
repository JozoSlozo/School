/**
 * @file  utils.h
 * @brief Implementuje pomocné funkce.
*/
/**
* @fn std::vector<double> PolynomialMapToVector(std::unordered_map<double, double> polynom)
* @brief převod vyjádření polynomu unordered_map -> vector
* @param polynom polynom vyjádřen unordered_map<double, double>
* @return polynom vyjádřený vector<double>
*/
/**
* @fn std::string IntToSuperscriptChar(int number)
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
* @fn std::unordered_map<double, double> PolynomialVectorToMap(std::vector<double> polynom)
* @brief převod vyjádření polynomu vector -> unordered_map
* @param polynom polynom vyjádřen vector<double>
* @return polynom vyjádřený unordered_map<double, double>
*/
#include <vector>
#include <cmath>
#include <unordered_map>
std::string IntToSuperscriptChar(int number);
const char* SignAsChar(double num);
int SignAsInt(int val);
std::vector<double> PolynomialMapToVector(std::unordered_map<double, double> polynom);
std::unordered_map<double, double> PolynomialVectorToMap(std::vector<double> polynom);