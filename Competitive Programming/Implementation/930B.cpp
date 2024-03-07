#include <bits/stdc++.h>
using namespace std;
/*
You are given a 2×n grid filled with zeros and ones. Let the number at the intersection of the i-th row and the j-th column be aij

.

There is a grasshopper at the top-left cell (1,1)
that can only jump one cell right or downwards. It wants to reach the bottom-right cell (2,n). Consider the binary string of length n+1

consisting of numbers written in cells of the path without changing their order.

Your goal is to:

    Find the lexicographically smallest†

    string you can attain by choosing any available path;
    Find the number of paths that yield this lexicographically smallest string.

†
If two strings s and t have the same length, then s is lexicographically smaller than t if and only if in the first position where s and t differ, the string s has a smaller element than the corresponding element in t.


& Logic/explanation
?- get the lexicographically smallest string using greedy approach
?- count the occurrences of this lexicographically smallest string
 */
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        string s1, s2;
        cin >> s1 >> s2;
        string s;
        int l = 0;
        int f = 0;
        while (l < n)
        {
            if (f == 0)
            {
                s += s1[l];
                //& switching row 0 to row 1 as bottom char is smaller than right car [lexicographically]
                if (l + 1 < n && s2[l] < s1[l + 1])
                {
                    f = 1;
                }
                //& we are at the bottom row so the remaining string is added as it is
                else if (l + 1 == n)
                {
                    s += s2[l];
                    break;
                }
                //& we are at the top row so keep moving forward
                else
                {
                    l++;
                }
            }
            //& flag is 1 means currently we have switched to row 1
            else
            {
                s += s2[l];
                l++;
            }
        }
        cout << s << endl;
        long long ans = 1;
        for (int i = 1; i < n; i++)
        {
            //& if both chars (bottom and right) are same then there are 2 possible paths (moving top or switching to row 1 then moving ahead)
            if (s1[i] == s2[i - 1])
                ans++;
            //& top char is smaller hence ans is 1
            else if (s1[i] == '0' and s2[i - 1] == '1')
                ans = 1;
            else
                break;
        }
        cout << ans << endl;
    }
    return 0;
}