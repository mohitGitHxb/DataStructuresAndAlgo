#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
static int init = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution
{
private:
    /*
A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:

    It is ().
    It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
    It can be written as (A), where A is a valid parentheses string.

You are given a parentheses string s and a string locked, both of length n. locked is a binary string consisting only of '0's and '1's. For each index i of locked,

    If locked[i] is '1', you cannot change s[i].
    But if locked[i] is '0', you can change s[i] to either '(' or ')'.

Return true if you can make s a valid parentheses string. Otherwise, return false.



Example 1:

Input: s = "))()))", locked = "010100"
Output: true
Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.

Example 2:

Input: s = "()()", locked = "0000"
Output: true
Explanation: We do not need to make any changes because s is already valid.

Example 3:

Input: s = ")", locked = "0"
Output: false
Explanation: locked permits us to change s[0].
Changing s[0] to either '(' or ')' will not make s valid.



    @ Approach:
    Intuition

The problem requires checking whether a given string of parentheses, along with locking constraints, can be valid. A valid sequence must have matching opening and closing parentheses in the correct order. Given the flexibility of certain positions (locked = '0'), this can be framed as a balancing problem. Using a greedy approach, we can track the minimum and maximum possible open parentheses at any point, ensuring that the string can still potentially form a valid sequence.
Approach

    Check Length:
    If the length of the string s is odd, return false, since a valid parentheses sequence requires an even number of characters.
    Define Counters (min and max):

    se two variables:
    min: Tracks the minimum number of open parentheses required.
    max: Tracks the maximum number of open parentheses allowed.
    Traverse the String:

    At each character:
    If it is '(' and locked, increase both min and max by 1.
    If it is ')' and locked, decrease both min and max by 1.
    If unlocked (locked = '0'), decrement min (treat it as a ) in one case) and increment max (treat it as a ( in the other case).
    Ensure min is non-negative (min = max(0, min)), as negative min means it's impossible to have enough open parentheses to match the closed ones so far.
    If max becomes negative at any point, return false, as this indicates too many closed parentheses compared to open parentheses.
    Final Validation:

    After processing all characters, check if min == 0. If min > 0, it means unmatched opening parentheses remain, making the sequence invalid.


     */
public:
    bool canBeValid(const string &s, const string &locked)
    {
        if (s.length() & 1)
            return false;
        const int n = s.length();
        int minOpenParens = 0, maxOpenParens = 0;
        for (int i = 0; i < n; i++)
        {
            if (locked[i] == '0')
            {
                minOpenParens--;
                maxOpenParens++;
            }
            else
            {
                minOpenParens += s[i] == '(' ? 1 : -1;
                maxOpenParens += s[i] == '(' ? 1 : -1;
            }
            minOpenParens = max(minOpenParens, 0);
            if (maxOpenParens < 0)
                return false;
        }
        return minOpenParens == 0;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    // Test cases for local testing
    string s = "001011";
    obj.minOperations(s);
    return 0;
}
#endif