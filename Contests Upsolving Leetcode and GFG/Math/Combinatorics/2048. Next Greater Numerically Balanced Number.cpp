#include <bits/stdc++.h>
using namespace std;
/*
An integer x is numerically balanced if for every digit d in the number x, there are exactly d occurrences of that digit in x.

Given an integer n, return the smallest numerically balanced number strictly greater than n.



Example 1:

Input: n = 1
Output: 22
Explanation:
22 is numerically balanced since:
- The digit 2 occurs 2 times.
It is also the smallest numerically balanced number strictly greater than 1.

Example 2:

Input: n = 1000
Output: 1333
Explanation:
1333 is numerically balanced since:
- The digit 1 occurs 1 time.
- The digit 3 occurs 3 times.
It is also the smallest numerically balanced number strictly greater than 1000.
Note that 1022 cannot be the answer because 0 appeared more than 0 times.

Example 3:

Input: n = 3000
Output: 3133
Explanation:
3133 is numerically balanced since:
- The digit 1 occurs 1 time.
- The digit 3 occurs 3 times.
It is also the smallest numerically balanced number strictly greater than 3000.


*/

const int MAX_POSSIBLE_NUMBER = 1224444;
static vector<int> allNumericallyBalancedNumbers;
static auto init = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<string> possible = {"1", "22", "122", "333", "1333",
                               "4444", "22333", "55555", "666666", "155555",
                               "224444", "14444", "122333", "1224444"};
    set<int>
        uniqueNumbers; // Use set to automatically handle duplicates and sorting
    for (const string &s : possible)
    {
        string temp = s;
        do
        {
            if (stoi(temp) > MAX_POSSIBLE_NUMBER)
            {
                break;
            }
            uniqueNumbers.insert(stoi(temp));
        } while (next_permutation(temp.begin(), temp.end()));
    }
    // Copy from set to vector
    allNumericallyBalancedNumbers.assign(uniqueNumbers.begin(),
                                         uniqueNumbers.end());
    return 0;
}();

class Solution
{
public:
    int nextBeautifulNumber(int n)
    {
        // Find the first number strictly greater than n
        auto it = upper_bound(allNumericallyBalancedNumbers.begin(),
                              allNumericallyBalancedNumbers.end(), n);
        return *it;
    }
};
int main()
{
    return 0;
}