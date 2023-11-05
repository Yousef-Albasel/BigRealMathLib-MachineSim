#include <bits/stdc++.h>
#include "BigReaL.cpp"

using namespace std;

int main() {
    string real, real2;
    cin >> real >> real2;
    BigReal a(real);
    BigReal b(real2);
    BigReal c = a + b;

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
    if (a > b) cout << "big";
    else if (a < b) cout << "less";
    else cout << "equal";


    return 0;
}

// 30 + .2