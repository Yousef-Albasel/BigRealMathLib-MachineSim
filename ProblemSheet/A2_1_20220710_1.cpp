// by mohamed talaat hassan wali 20220710
// problem number 1
// correcting the sentence


#include <iostream>
#include "string"

using namespace std ;

int main() {
    string str ;
    getline(cin , str);
    if (islower(str[0])) {
        str[0] -= 32;
    }

    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' and str[i - 1] == ' ') {
            str.erase(str.begin() + i);
            i--;
        }
    }
    for (int i = 1; i < str.length(); ++i) {
        if (isupper(str[0]))
            str[i] = tolower(str[i]);

        else continue;
    }
    cout<<str;
}
