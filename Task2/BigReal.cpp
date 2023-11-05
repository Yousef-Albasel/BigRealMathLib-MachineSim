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
            if (dot_index == 0) {
                integerPart = "0";
                fractionPart = realString.substr(1);
            } else {
                if (isdigit(realString[0])) {
                    integerPart = realString.substr(0, dot_index);
                    fractionPart = realString.substr(dot_index + 1);
                } else if (!isdigit(realString[0]) && realString[0] != '.') {
                    integerPart = realString.substr(1, dot_index - 1);
                    fractionPart = realString.substr(dot_index + 1);
                }
            }
        } else {
            if (!isdigit(realString[0]) && realString[0] != '.') {
                // No dot found, and the first character is + or -
                integerPart = realString.substr(1);
                fractionPart = "0";
            } else {
                // No dot found, and the first character is a digit
                integerPart = realString;
                fractionPart = "0";
            }
        }


    };
    removeZeros(integerPart, fractionPart);
}

BigReal BigReal::operator+(BigReal &r) {
    BigReal result;
    string integerSum = "";
    string fractionSum = "";
    int carry = 0;

    //  padding with zeros to get same length for both reals.
    while (integerPart.length() < r.integerPart.length()) integerPart = '0' + integerPart;
    while (integerPart.length() > r.integerPart.length()) r.integerPart = '0' + r.integerPart;
    while (fractionPart.length() < r.fractionPart.length()) fractionPart += '0';
    while (fractionPart.length() > r.fractionPart.length()) r.fractionPart += '0';

    // Add the fractional parts
    for (int i = fractionPart.size() - 1; i >= 0; --i) {
        int digit1 = fractionPart[i] - '0';
        int digit2 = r.fractionPart[i] - '0';
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        fractionSum += to_string(sum % 10);
    }

    // Add the integer parts
    for (int i = integerPart.size() - 1; i >= 0; --i) {
        int digit1 = integerPart[i] - '0';
        int digit2 = r.integerPart[i] - '0';
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        integerSum += to_string(sum % 10);
    }

    // Handle any carry left
    if (carry > 0) {
        integerSum = to_string(carry) + integerSum;
    }
    // reversing to get the right form
    reverse(integerSum.begin(), integerSum.end());
    reverse(fractionSum.begin(), fractionSum.end());

    result.integerPart = integerSum;
    result.fractionPart = fractionSum;

    return result;
}


BigReal BigReal::operator-(BigReal &r) {
    // Implement subtraction here
}

bool BigReal::operator==(BigReal &r) {
    if (sign == r.sign && integerPart == r.integerPart && fractionPart == r.fractionPart) {
        return true;
    } else {
        return false;
    }
}

bool BigReal::operator<(BigReal &r) {
    if (sign == '-' && r.sign == '-') {
        // Both numbers are negative, send to the other operator
        BigReal absThis = *this;
        BigReal absOther = r;
        absThis.sign = absOther.sign = '+';
        return absThis > absOther;
    }

    if (sign == '-' && r.sign == '+') {
        return true;
    } else if (r.sign == '-' && sign == '+') {
        return false;
    } else if (r.sign == sign) {
        // Compare integer parts
        if (integerPart.length() < r.integerPart.length()) {
            return true;
        } else if (integerPart.length() > r.integerPart.length()) {
            return false;
        }

        for (int i = 0; i < integerPart.length(); ++i) {
            int f_real = integerPart[i] - '0';
            int s_real = r.integerPart[i] - '0';

            if (f_real < s_real) {
                return true;
            } else if (f_real > s_real) {
                return false;
            }
        }

        // Compare fraction parts
        for (int i = 0; i < fractionPart.length(); ++i) {
            int f_real = fractionPart[i] - '0';
            int s_real = r.fractionPart[i] - '0';

            if (f_real < s_real) {
                return true;
            } else if (f_real > s_real) {
                return false;
            }
        }
    }

    return false;
}

bool BigReal::operator>(BigReal &r) {
    if (sign == '-' && r.sign == '-') {
        // Both numbers are negative, send to the other operator
        BigReal absThis = *this;
        BigReal absOther = r;
        absThis.sign = absOther.sign = '+';
        return absThis < absOther;
    }

    if (sign == '-' && r.sign == '+') {
        return false;
    } else if (r.sign == '-' && sign == '+') {
        return true;
    } else if ((r.sign == sign) && (sign == '+')) {
        // Compare integer parts
        if (integerPart.length() > r.integerPart.length()) {
            return true;
        } else if (integerPart.length() < r.integerPart.length()) {
            return false;
        }

        for (int i = 0; i < integerPart.length(); ++i) {
            int f_real = integerPart[i] - '0';
            int s_real = r.integerPart[i] - '0';

            if (f_real > s_real) {
                return true;
            } else if (f_real < s_real) {
                return false;
            }
        }

        // Compare fraction parts
        for (int i = 0; i < fractionPart.length(); ++i) {
            int f_real = fractionPart[i] - '0';
            int s_real = r.fractionPart[i] - '0';

            if (f_real > s_real) {
                return true;
            } else if (f_real < s_real) {
                return false;
            }
        }
    }

    return false;
}

ostream& operator << (ostream& out, BigReal num){
    out << num.sign << num.integerPart<<"."<<num.fractionPart;
    return out;
}

BigReal::~BigReal() {}

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

void BigReal::removeZeros(string &Integer, string &Fraction) {
    int i; // 00000000.
    for (i = 0; i < Integer.size() - 1; ++i) {
        if (Integer[i] != '0')
            break;
    }
    Integer.erase(0, i);
    // 2.00000
    for (size_t j = Fraction.size() - 1; j > 0; j--) {
        if (Fraction[j] == '0')
            Fraction.pop_back();
        else
            break;
    }
}

// fix fraction default