// File:  A2_S2_11.cpp
// Purpose: Solving Problem 5 about file comparison.
// Author: Yousef Mohamed.
// Section: 2
// ID: 20220408
// TA: Maya Ahmed Kamal
// Date: 28 Oct 2023

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void read_line(ifstream &file, int target_line) {
    int curr_line = 1;
    string line;
    file.seekg(ios::beg);
    while (curr_line < target_line && getline(file, line)) {
        curr_line++;
    }
    if (curr_line == target_line && getline(file, line)) {
        cout << line << '\n';
    }

}

void cmp_char(ifstream &f_file, ifstream &s_file) {
    char c1, c2;
    int line_cnt = 1;
    bool notIdentical = false;
    int line_err = -1;
    while (true) {
        c1 = (char) f_file.get();
        c2 = (char) s_file.get();
        if (c1 != c2) {
            notIdentical = true;
            line_err = line_cnt;
            break;
        }

        if (c1 == '\n' || c2 == '\n') line_cnt++;

        if (c1 == EOF && c2 == EOF) break;
    }
    if (!notIdentical) cout << "Result: Files are Identical\n";
    else {
        cout << "Found contradiction at first file, line: " << line_err << " Content : \n";
        read_line(f_file, line_err);
        cout << "Found contradiction at second file, line: " << line_err << " Content : \n";
        read_line(s_file, line_err);
    }
    cout << "\n\n";
    f_file.close();
    s_file.close();
}

void cmp_word(ifstream &f_file, ifstream &s_file) {
    bool notIdentical = false;
    string f_word, s_word, f_line, s_line;
    int line_cnt = 0;
    while (getline(f_file, f_line) && getline(s_file, s_line) ) {
        ++line_cnt;
        stringstream f_stream(f_line), s_stream(s_line);
        while (f_stream >> f_word && s_stream >> s_word) {
            if (f_word != s_word) {
                cout << "Files are not identical.\nFirst difference found at word: " << f_word << " : " << s_word
                     << " At line : " << line_cnt << "\n\n";
                notIdentical = true;
                break;
            }
        }
    }


    if (!notIdentical) {
        cout << "Result : Files are identical." << endl;
    }
    f_file.close();
    s_file.close();
}

void open_files()

int main() {
    while (true) {
        printf("Welcome to File Comparator v1.0\n"
               " 1- Compare files character by character.\n"
               " 2- Compare files word by word.\n"
               " 3- Quit.\n");

        int opt;
        ifstream f_file, s_file;
        string f_file_loc, s_file_loc;
        cin >> opt;
        switch (opt) {
            case 1:
                printf("Please enter first file name (consider location): ");
                cin >> f_file_loc;
                f_file.open(f_file_loc, ios::in);

                // Error handling

                if (!f_file.is_open()) {
                    printf("Invalid File Name, try again.\n");
                    break;  // Exit the case if the first file is invalid
                }

                printf("Please enter second file name (consider location): ");
                cin >> s_file_loc;
                s_file.open(s_file_loc, ios::in);

                // Error handling
                if (!s_file.is_open()) {
                    printf("Invalid File Name, try again.\n");
                    f_file.close();
                    break;
                }

                cmp_char(f_file, s_file);  // Compare the two opened files

                break;

            case 2:
                printf("Please enter first file name (consider location): ");
                cin >> f_file_loc;
                f_file.open(f_file_loc, ios::in);

                // Error handling

                if (!f_file.is_open()) {
                    printf("Invalid File Name, try again.\n");
                    break;  // Exit the case if the first file is invalid
                }

                printf("Please enter second file name (consider location): ");
                cin >> s_file_loc;
                s_file.open(s_file_loc, ios::in);

                // Error handling
                if (!s_file.is_open()) {
                    printf("Invalid File Name, try again.\n");
                    f_file.close();
                    break;
                }
                cmp_word(f_file, s_file);
                break;
            case 3:
                return 0;
            default:
                printf("Please enter a valid answer!\n");
        }
    }

}
