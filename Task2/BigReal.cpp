#include "BigReal.h"

BigReal::BigReal(string real)
{
    string digits = "0123456789";
    string non_digits = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()'^$%!@#=_|/<>?";
    bool valid = 1;

    for (int i = 0; i<real.size() ; i++){
        if (find(non_digits.begin(), non_digits.end(), real[i]) != non_digits.end()){
            valid = 0;
            break;
        }
    }
     

    if(!valid || find(digits.begin(), digits.end(), real[0]) == digits.end() && real[0] != '+' && real[0] != '-' && real[0] != '.' || count(real.begin(), real.end(), '.') > 1){
        cout << "NaN";
    }
    else{
        if(real[0] == '-' || real[0] == '+'){
            sign = real[0];
            real = real.substr(1, real.size() - 2);   ///////////////////////
        }
        integer = real.substr(0, find(real.begin(), real.end(), '.') - real.begin());
        fraction = real.substr(find(real.begin(), real.end(), '.') - real.begin() + 1, real.size() - (find(real.begin(), real.end(), '.') - real.begin()) - 2);
    }
}

BigReal BigReal::operator+ (BigReal& r){

}

BigReal BigReal::operator- (BigReal& r){

}

BigReal BigReal::operator== (BigReal& r){

}

void BigReal::print(){
    // if (fraction.empty())
    //     cout << sign << integer<< endl;
    // else
        cout << sign << integer << "." << fraction << endl;
}

BigReal::~BigReal()
{

}