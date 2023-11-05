




//                                                             بسم الله الرحمن الرحيم
#include <bits/stdc++.h>

using namespace std;

map<string, int> phishingKeywords = {
    {"bank", 3},
    {"credit card", 3},
    {"password", 3},
    {"social security", 3},
    {"urgent", 2},
    {"emergency", 3},
    {"verify", 2},
    {"account", 2},
    {"suspicious", 2},
    {"login", 2},
    {"paypal", 3},
    {"ebay", 2},
    {"irs", 2},
    {"update", 2},
    {"security", 2},
    {"verify your account", 3},
    {"win an Iphone", 3},
    {"click here", 1},
    {"link", 1},
    {"limited offer", 2},
    {"Congratulations", 1},
    {"Account access alert", 2},
    {"ATM", 3},
    {"ID", 2},
    {"Click", 1},
    {"NASA", 2},
    {"quick and easy", 3}
};

map<string, pair<int, int>> foundTerms; 

void scanForPhishingTerms(const string& text) {
    for (const auto& entry : phishingKeywords) {
        const string& term = entry.first;
        int points = entry.second;
        regex pattern("\\b" + term + "\\b", regex_constants::icase);
        smatch matches;
        int occurrences = 0;

        auto textIter = text.cbegin();
        while (regex_search(textIter, text.cend(), matches, pattern)) {
            occurrences++;
            textIter = matches.suffix().first;
        }

        if (occurrences > 0) {
            foundTerms[term] = make_pair(occurrences, points * occurrences);
        }
    }
}

int main() {
    ifstream file("email.txt");

    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
    }
    else{
        string emailText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        scanForPhishingTerms(emailText);

        cout << "Phishing Keywords and Phrases Found:" << endl;
        for (const auto& entry : foundTerms) {
            const string& term = entry.first;
            int occurrences = entry.second.first;
            int points = entry.second.second;
            cout << term << "\tOccurrences: " << occurrences << "\tPoints: " << points << endl;
        }

        int totalPoints = 0;
        for (const auto& entry : foundTerms) {
            totalPoints += entry.second.second;
        }

        cout << "Total Points: " << totalPoints << endl;
    }
    return 0;
}
