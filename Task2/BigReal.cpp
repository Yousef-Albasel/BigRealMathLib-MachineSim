#include "BigReal.h"
#include <cctype>

BigReal::BigReal(const string &realString) {
    isValid = validateInput(realString);
    if (!isValid) { cout << "[ERROR]: Not a real number."; }
    else {
        // First : Extract Sign
        if (!isdigit(realString[0]) && realString[0] != '.') {
            sign = realString[0];
            realString.substr(1);
        } else {
            sign = '+';
        }

        // Second : Extract Integer part

        int dot_index = (int) realString.find('.');
        if (dot_index != string::npos) {
            if (isdigit(realString[0])) {
                integerPart = realString.substr(0, dot_index);
                fractionPart = realString.substr(dot_index + 1); // extracting fraction part if no sign was given
            } else if (!isdigit(realString[0]) && realString[0] != '.') {
                integerPart = realString.substr(1, dot_index - 1);
                fractionPart = realString.substr(dot_index + 1); // extracting fraction part if a sign was gives

            } else {
                integerPart = "0";
                fractionPart = realString.substr(dot_index + 1); // extracting fraction part if no sign and a dot given
            }
        }



    };

}

BigReal BigReal::operator+(BigReal &r) {
    // Implement addition here
}

BigReal BigReal::operator-(BigReal &r) {
    // Implement subtraction here
}

bool BigReal::operator==(BigReal &r) {
    // Implement equality comparison here
}

void BigReal::print() {
    if(isValid){
        if (fractionPart.empty())fractionPart = "0";
        if (integerPart.empty())integerPart = "0";
        cout << sign << integerPart << "." << fractionPart << endl;
    }
}

BigReal::~BigReal() {
    // Destructor code, if needed
}

bool BigReal::validateInput(const string &input) {
    string invalidChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()'^$%!@#=_|/<>?";
    int dotCount = 0;
    bool isValid = true;

    for (int i = 0; i < input.size(); i++) {
        if (invalidChars.find(input[i]) != string::npos) {
            isValid = false;
            break;  // If an invalid character is found
        }
        if (i == 0) {
            if (input[i] != '+' && input[i] != '-' && input[i] != '.' && !isdigit(input[i])) {
                isValid = false;
                break;  // If the first character is invalid
            }
        }
        if (input[i] == '.') {
            dotCount++;
            if (dotCount > 1) {
                isValid = false;
                break;  // More than one decimal point
            }
        }
    }

    return isValid;
}

