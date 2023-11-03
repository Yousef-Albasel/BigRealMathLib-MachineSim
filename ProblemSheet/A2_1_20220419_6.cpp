#include <bits/stdc++.h>
using namespace std;

static void binaryPrint(int n){
    if (n > 0) {
        binaryPrint(n / 2);
        cout << n % 2;
    }
    else
        cout << 0;
}


static void numbers(string prefix, int k){
    if (k == 0){
        cout << prefix << endl;
    }
    else{
        numbers(prefix + '0' , k - 1);
        numbers(prefix + '1' , k - 1);
    }
}


int main(){
    int n;
    cin >> n;
    binaryPrint(n);
    numbers("00101", 2);
    return 0;
}