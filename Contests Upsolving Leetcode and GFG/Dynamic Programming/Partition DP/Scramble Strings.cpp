#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

class Solution
{
private:
    /*
We can scramble a string s to get a string t using the following algorithm:

    If the length of the string is 1, stop.
    If the length of the string is > 1, do the following:
        Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
        Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
        Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.



Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at random index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now, and the result string is "rgeat" which is s2.
As one possible scenario led s1 to be scrambled to s2, we return true.

Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false

Example 3:

Input: s1 = "a", s2 = "a"
Output: true

    & Take care of the cases of swappping and not swapping
     */
public:
    Solution()
    {
        fast_read();
    }
    // unordered_map<string, unordered_map<string, bool>> dp; // 2D dp
    unordered_map<string, bool> reducedDP;
    bool isScramble(string s1, string s2)
    {
        if (s1 == s2)
        {
            return true;
        }
        else if (s1.length() != s2.length())
        {
            return false;
        }
        string key = s1 + '#' + s2;
        if (reducedDP.count(key))
        {
            return reducedDP[key];
        }
        int n = s1.length();
        bool flag = false;
        for (int i = 1; i < s1.length(); i++)
        {
            // not swapped
            // gr eat   gr ate
            flag |= isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i));
            if (flag)
            {
                break;
            }

            // swapped
            // gr eat   eat gr
            flag |= isScramble(s1.substr(i, n - i), s2.substr(0, n - i)) && isScramble(s1.substr(0, i), s2.substr(n - i, i));

            if (flag)
            {
                break;
            }
        }
        return reducedDP[key] = flag;
    }
};

int main()
{
    return 0;
}