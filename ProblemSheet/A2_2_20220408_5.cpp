// File:  A2_S2_5.cpp
// Purpose: Solving Problem 5 about top 10 players leaderboard.
// Author: Yousef Mohamed.
// Section: 2
// ID: 20220408
// TA: Maya Ahmed Kamal
// Date: 28 Oct 2023

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Vector of pairs for storing the players data
vector<pair<string, int>> list;

// Compare function to use it in the sort function
bool cmp(pair<string, int> &a,
         pair<string, int> &b) {
    return a.second > b.second; // to sort it by value
}

void add_player(const string &p_name, int score) {
    list.emplace_back(p_name, score); // add the player to the vector
    sort(list.begin(), list.end(), cmp); // sort it by val using the custom function we created
    printf("Player has been added successfully!\n");
}

void print_top_players(const vector<pair<string, int>> &v) {
    cout << "Top 10 Players: \n ";

    // First case: if the vector isn't empty, and has more than 10 entries, print first 10 entries.
    if (!v.empty() && v.size() >= 10) {
        for (int i = 0; i < 10; i++) {
            cout << i + 1 << "- " << v[i].first << " : " << v[i].second << "\n ";
        }
    }
    // Second case: if the vector isn't empty, and has less than 10 entries, print all.
    else if (!v.empty() && v.size() < 10) {
        for (int i = 0; i < v.size(); i++) {
            cout << i + 1 << "- " << v[i].first << " : " << v[i].second << "\n ";
        }
    }
    // if it's empty, print error message
    else {
        printf("Leaderboard is Empty, please add some data first.\n");
    }
}

void search_for_player(const string &name, vector<pair<string, int>> v) {
    bool isFound = false;
    for (int i = 0; i < 10; i++) { // search for the player in top 10 list
        if (v[i].first == name) {
            isFound = true;
            cout << "Player #" << i+1 << " " << v[i].first << " : " << v[i].second << "\n";
        }
    }
    if(!isFound) cout << "Player doesn't exist in the top 10 list!\n";
}

int main() {

    // ======= Main Menu =======//

    while (true) {
        printf("Main Menu:\n"
               " 1- Add new player.\n"
               " 2- Top 10 players.\n"
               " 3- Info about a player.\n"
               " 4- Quit.\n");
        int opt;
        cin >> opt;
        string p_name, a_name;
        int score;
        switch (opt) {
            case 1:
                printf("  Enter Player name: ");
                cin.ignore();
                getline(cin, p_name);
                printf(" Enter Player Score: ");
                cin >> score;
                add_player(p_name, score);
                break;
            case 2:
                print_top_players(list);
                break;
            case 3:
                printf(" Enter Player name: ");
                cin >> a_name;
                search_for_player(a_name,list);
                break;
            case 4:
                return 0;
            default:
                cout << "Please Enter a valid input!\n";
        }
    }
}
