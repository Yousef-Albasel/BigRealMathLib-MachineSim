#ifndef BIGREAL_H
#define BIGREAL_H

#include <bits/stdc++.h>
using namespace std;

#pragma once

class BigReal
{
public:
    BigReal(string real);
    BigReal operator+ (BigReal& r);
    BigReal operator- (BigReal& r);
    BigReal operator== (BigReal& r);
    void print();
    ~BigReal();

private:
    char sign = '+';
    string integer = "", fraction = "";
};

#endif