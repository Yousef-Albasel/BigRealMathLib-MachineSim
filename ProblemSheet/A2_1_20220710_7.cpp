// by mohamed talaat hassan wali 20220710
// problem number 1
// domino game

#include <iostream>
#include <vector>
using namespace std;

bool FormsDominoChain(vector<vector<int>>& dominos) {
    for(int i = 0; i < dominos.size() - 1; ++i) {
        if(dominos[i][1] != dominos[i + 1][0]) {
            return false;
        }
    }
    return true;
}

int main() {
   int n;
   cout<<"enter the num of domino pieces";
   cin>>n;
    vector<vector<int>> dominos(n, vector<int>(2)); // إنشاء مصفوفة 2D بحجم 4x2


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
        cout<<"enter the domino";
            cin >> dominos[i][j];
        }}
    if(FormsDominoChain(dominos)) {
        cout << "yes" << endl;
    } else {
        cout<<"no" << endl;
    }

    for(int i = 0; i < dominos.size() ; ++i) {
        cout<<dominos[i][0]<<"|"<<dominos[i][1]<<" "<<"_";
    }
    return 0;
}