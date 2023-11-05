#ifndef BIGREAL_H
#define BIGREAL_H

#include <bits/stdc++.h>

using namespace std;

#pragma once

class BigReal {
private:

    string realString;
    char sign;
    string integerPart;
    string fractionPart;
    bool isValid=true;

    // function for input validation
    static bool validateInput(const string &input);
    static void removeZeros( string &Integer, string& Fraction);

public:
    // Constructors
    BigReal() {
        sign = '+';
        integerPart="0";
        fractionPart="0";
    }

    BigReal(const string& input);

    // Operator overloading
    BigReal operator+(BigReal &other);

    BigReal operator-(BigReal &other);

    bool operator==(BigReal &other);
    bool operator>(BigReal &other);
    bool operator<(BigReal &other);

    // Getter methods
    char getSign() const { return sign; }

    string getIntegerPart() const { return integerPart; }

    string getFractionPart() const { return fractionPart; }

    // Print method
    friend ostream& operator << (ostream& out, BigReal num);
    // Destructor
    ~BigReal();
};

#endif