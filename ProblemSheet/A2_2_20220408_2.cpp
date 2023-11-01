// File:  A2_S2_2.cpp
// Purpose: Solving Problem 2 about converting male speech to inclusive speech.
// Author: Yousef Mohamed.
// Section: 2
// ID: 20220408
// TA: Maya Ahmed Kamal
// Date: 28 Oct 2023

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

unordered_map<string, string> dict = {{"he", "he or she"},
                                      {"He", "He or she"},
                                      {"him", "him or her"},
                                      {"Him", "Him or her"},
                                      {"his", "his or her"},
                                      {"His", "His or her"},
                                      {"himself", "himself or herself"},
                                      {"Himself", "Himself or herself"},
};


int main() {

    string input;
    getline(cin, input);
    stringstream reader(input);
    string word, output;
    while (reader >> word) {
        string punctuation;

        //separate word from punctuation
        while (!word.empty() && ispunct(word.back())) {
            punctuation += word.back();
            word.pop_back();
        }

        auto itr = dict.find(word);
        if (itr != dict.end()) {// Check if the word in dictionary
            output += itr->second += punctuation + " ";  // if yes add the value to the empty string
        } else {
            output += word + punctuation + " "; // else add the key
        }
    }

    cout << output;

}
