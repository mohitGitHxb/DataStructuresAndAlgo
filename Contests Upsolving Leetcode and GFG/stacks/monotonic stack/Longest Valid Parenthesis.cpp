#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
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
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

class Solution
{
private:
    /*
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses
substring
.



Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Example 3:

Input: s = ""
Output: 0



     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    int longestValidParentheses(string &s)
    {
        int n = s.size();
        stack<int> st;
        vector<int> dp(n, 0);
        // treat the ( ) as 0 and 1
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                st.push(i);
            }
            else
            {
                if (!st.empty())
                {
                    int top = st.top();
                    st.pop();
                    dp[i] = 1;
                    dp[top] = 1;
                }
                else
                {
                    dp[i] = 0;
                }
            }
        }

        // find longest chain of 1s
        int ans = 0, streak = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[i] == 1)
            {
                streak++;
                ans = max(ans, streak);
            }
            else
            {
                streak = 0;
            }
        }
        return ans;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
