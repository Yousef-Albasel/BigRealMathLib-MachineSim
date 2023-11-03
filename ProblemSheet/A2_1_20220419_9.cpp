#include <bits/stdc++.h>
using namespace std;

bool bears(int n){
    if (n == 42){
        return 1;
    }
    if (n < 42){
        return 0;
    }
    if (n % 2 == 0){
        bears(n/2);
    }
    else if (n % 3 == 0 || n % 4 == 0){
        bears((n % 10) * ((n % 100) / 10));
    }
    else if (n % 5 == 0){
        bears(42);
    }
    else{
        return 0;
    }
}

int main(){
    cout << bears(250) << endl;
    cout << bears(42) << endl;
    cout << bears(84) << endl;
    cout << bears(53) << endl;
    cout << bears(41) << endl;
    return 0;
}