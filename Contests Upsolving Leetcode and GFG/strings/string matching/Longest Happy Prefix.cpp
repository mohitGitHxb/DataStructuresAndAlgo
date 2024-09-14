#include <bits/stdc++.h>
using namespace std;
/* 
A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s, return the longest happy prefix of s. Return an empty string "" if no such prefix exists.

 

Example 1:

Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".

Example 2:

Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.




 */
class Solution
{
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
        vector<int> lps = constructLPS(s);
        return s.substr(0, lps.back());
    }
};
int main()
{
    return 0;
}