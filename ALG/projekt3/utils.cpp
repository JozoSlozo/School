#include <vector>
#include <unordered_map>
#include <string>
#include "utils.h"

std::string IntToSuperscriptChar(int number)
{
    // array stringu byl vygenerovan ChatGPT
    static const std::string superscripts[] = {
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
    if (std::signbit(num))
    {
        return "-";
    }
    return "+";
}

int SignAsInt(int val) 
{
    return (0 < val) - (val < 0); // if greater then zero 1 - 0, if less then zero 0 - 1
}

std::vector<double> PolynomialMapToVector(std::unordered_map<double, double> polynom)
{
    int maxPow = 0;
    for (auto [power, number] : polynom)
    {
        if (power > maxPow)
        {
            maxPow = power;
        }
    }
    std::vector<double> fin(maxPow + 1, 0);
    for (auto [power, number] : polynom)
    {
        fin[power] = number;
    }
    return fin;
}

std::unordered_map<double, double> PolynomialVectorToMap(std::vector<double> polynom)
{
    std::unordered_map<double, double> temp;
    for (int i = 0; i < polynom.size(); i++)
    {
        if (polynom[i] != 0)
        {
            temp[i] = polynom[i];
        }
    }
    return temp;
}