// File:  A2_S2_8.cpp
// Purpose: Solving Problem 8 about fractal pattern recursion.
// Author: Yousef Mohamed.
// Section: 2
// ID: 20220408
// TA: Maya Ahmed Kamal
// Date: 28 Oct 2023

#include <iostream>
#include <cmath>

using namespace std;

// Function to check if n is a power of two

bool isPowerOfTwo(int n) {
    if (n == 0)
        return false;

    return (ceil(log2(n)) == floor(log2(n)));
}


// Function to calculate number of spaces for each line

int calcSpaces(int n) {
    if (isPowerOfTwo(n))
        return 0;
    return (n - 1) / 2;
}
// Function to calculate number of stars for each line

int calcStar(int n) {
    int k = n;
    int cnt = 0;

    while (k % 2 == 0)
        k /= 2, cnt++;

    return pow(2, cnt);
}

void printpattern(int n) {
    for (int i = 1; i <= calcSpaces(n); i++)
        cout << " ";

    for (int i = 1; i <= calcStar(n); i++)
        cout << "*";
}

void pattern(int n) {
    int i, j, sp;
    for (i = 1; i <= n; i++)               //Upper Half
    {
        printpattern(i);
        cout << endl;
    }
    sp = n / 2;
    for (i = 1; i <= n - 1; i++)             //Lower Half
    {
        for (j = 1; j <= sp; j++)
            cout << " ";
        printpattern(i);
        cout << endl;
    }
}

int main() {
    int n = 16;
    pattern(n);
    return 0;
}
