#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector <string> split(string target, string delimiter){
    vector <string> s;
    string tmp = "";
    for (int i = 0; i<target.size(); i++){
        if (target[i] != delimiter[0]){
            tmp += target[i];
        }
        else{
            s.push_back(tmp);
            tmp = "";
        }
    }
    s.push_back(tmp);
    return s;
}

int main(){
    string t;
    string d;
    getline(cin, t);
    getline(cin, d);
    vector <string> a = split(t, d);
    for (int i = 0; i<a.size(); i++){
        cout << a[i] << " ";
    }
}