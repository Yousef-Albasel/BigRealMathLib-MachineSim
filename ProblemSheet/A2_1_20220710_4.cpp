// by mohamed talaat hassan wali 20220710
// problem number 4
// Prime numbers


#include <iostream>
#include "vector"

using namespace std ;

int main() {

    int n;
    cin >> n;
    vector<int> nums;
    for (int i = 2; i < n + 1; ++i) {
        nums.push_back(i);

    }
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[j] % nums[i] == 0) {
                    nums[j] = 0;
                }
            }
        }
    }


    for (int i = 0; i < n + 1; ++i) {
        if (nums[i] != 0) {
            cout << nums[i]<< ", ";
        }
    }
}








