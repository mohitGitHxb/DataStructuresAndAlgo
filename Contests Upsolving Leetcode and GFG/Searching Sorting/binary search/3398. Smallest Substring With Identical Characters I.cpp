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
        You are given a binary string s of length n and an integer numOps.

You are allowed to perform the following operation on s at most numOps times:

    Select any index i (where 0 <= i < n) and flip s[i]. If s[i] == '1', change s[i] to '0' and vice versa.

You need to minimize the length of the longest
substring
of s such that all the characters in the substring are identical.

Return the minimum length after the operations.



Example 1:

Input: s = "000001", numOps = 1

Output: 2

Explanation:

By changing s[2] to '1', s becomes "001001". The longest substrings with identical characters are s[0..1] and s[3..4].

Example 2:

Input: s = "0000", numOps = 2

Output: 1

Explanation:

By changing s[0] and s[2] to '1', s becomes "1010".

Example 3:

Input: s = "0101", numOps = 0

Output: 1

    @ Approach:
    &- Minimize the longest substring should automatically clicks the binary search on answer algorithm
    &- For a particular mid length can we make the string within the given numOps
    &- Special case : 1001 or 0110 --> i.e for mid = 1
    &- for mid = 1 the string has to be an alternating string so check for this as an edge case or base case
    %- finally return the ans (minimized according to the predicate function isValid)

    * Time complexity : O(nlogn)
    * Space complexity : O(1)

     */
public:
    bool isValid(const string &s, const int &numOps, const int &mxLen)
    {
        const int n = s.length();
        int operations = 0;
        int i = 0;
        while (i < n)
        {
            const char c = s[i];
            int streak = 0;
            while (i < n && s[i] == c)
            {
                streak++;
                i++;
            }
            // we want to divide the streak by (mxLen + 1) and add the result to the operations
            // this is because we want to know how many times we can divide the streak of identical characters
            // by the maximum length of the substring, and round down
            // for example, if the streak is 5 and mxLen is 2, then we can divide the streak by mxLen + 1
            // and get 2, which means we need 2 operations to make the substring alternating
            operations += streak / (mxLen + 1);
        }
        return operations <= numOps;
    }
    bool canBecomeAlternating(const string &s, const int &numOps)
    {
        int operations = 0, n = s.length();
        for (int i = 0; i < n; i++)
        {
            // we want to check if the current character is equal to the parity of the current index
            // i.e. if the index is even, then the character should be '0', and if the index is odd, then the character should be '1'
            // if this condition is not met, then it means that the current character is not equal to the parity of the current index
            // so we need to increment the operations counter to account for the flip operation needed to make them equal.
            if ((s[i] - '0') != (i % 2))
                operations++;
        }
        operations = min(operations, n - operations);
        return operations <= numOps;
    }
    int minLength(const string &s, const int numOps)
    {
        if (canBecomeAlternating(s, numOps))
        {
            return 1;
        }
        int low = 2, high = s.size();
        int ans = s.size();
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(s, numOps, mid))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    // Test cases for local testing
    return 0;
}
#endif