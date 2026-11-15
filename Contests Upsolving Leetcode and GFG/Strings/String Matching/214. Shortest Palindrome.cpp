#include <bits/stdc++.h>
using namespace std;

class Solution
{
    /*




     */
public:
    vector<int> constructLPS(const string &s)
    {
        vector<int> lps(s.size());
        for (int i = 1; i < s.size(); i++)
        {
            int prevIdx = lps.at(i - 1);
            // If the current character does not match with the character at the
            // previous index, then update the previous index to the index of
            // the longest proper prefix which is also suffix.
            while (prevIdx > 0 && s.at(i) != s.at(prevIdx))
            {
                prevIdx = lps.at(prevIdx - 1);
            }
            // If the current character matches with the character at the
            // previous index, then increment the length of the longest proper
            // prefix which is also suffix.
            lps.at(i) = prevIdx + (s.at(i) == s.at(prevIdx));
        }
        return lps;
    }
    string longestPrefix(string &s)
    {
        // lps.back() gives us the length of the longest palindrome prefix
        vector<int> lps = constructLPS(s);
        return s.substr(0, lps.back());
    }
    string shortestPalindrome(string s)
    { // The characters to add are the part of the reverse of s that comes
        // after the palindrome prefix
        return longestPrefix(s) + s;
    }
};

int main()
{
    return 0;
}