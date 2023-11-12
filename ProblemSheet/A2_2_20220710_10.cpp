#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
using namespace std;

unordered_map<string, string> dictionary;

// Function to replace words in a line based on the dictionary
string replace_words(const string &line, const unordered_map<string, string> &dict) {
    string result = line;
    for (const auto &entry : dict) {
        size_t start_pos = 0;
        while ((start_pos = result.find(entry.first, start_pos)) != string::npos) {
            result.replace(start_pos, entry.first.length(), entry.second);
            start_pos += entry.second.length();
        }
    }
    return result;
}

int main() {
    string dict_name;
    cout << "Please enter dictionary file name (e.g., '../folder/file.txt'): \n";
    cin >> dict_name;
    string line;
    ifstream dict_input(dict_name);
    if (dict_input.is_open()) {
        while (getline(dict_input, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                dictionary[key] = value;
            }
        }
        dict_input.close();
    } else {
        cout << "Error: Dictionary file is not opened, make sure you are typing the name and directory correctly." << endl;
        return 1;
    }

    ifstream file_input;
    string f_name;
    cout << "Please enter file name for filtering (e.g., '../folder/content.txt'): \n";
    cin >> f_name;
    file_input.open(f_name);
    if (file_input.is_open()) {
        ofstream file_output("filtered_content.txt"); // Output file
        if (!file_output.is_open()) {
            cout << "Error: Could not create output file." << endl;
            return 1;
        }
        while (getline(file_input, line)) {
            string replaced_line = replace_words(line, dictionary);
            file_output << replaced_line << endl; // Write to output file
        }
        file_input.close();
        file_output.close();
    } else {
        cout << "Error: Content file is not opened, make sure you are typing the name and directory correctly." << endl;
        return 1;
    }

    return 0;
}
