#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define deb(x) cout << #x << "=" << x << endl
using mset = tree<long long, null_type, less_equal<long long>, rb_tree_tag,
                  tree_order_statistics_node_update>;
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
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return the nth ugly number.



Example 1:

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.

Example 2:

Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.



     */
public:
    Solution()
    {
        fast_read();
    }

    int nthUglyNumber(int n)
    {
        int a = 0, b = 0, c = 0;
        vector<int> arr(n);
        arr[0] = 1;
        for (int i = 1; i < n; i++)
        {
            arr[i] = min({2 * arr[a], 3 * arr[b], 5 * arr[c]});
            if (arr[i] == 2 * arr[a])
                a++;
            if (arr[i] == 3 * arr[b])
                b++;
            if (arr[i] == 5 * arr[c])
                c++;
        }
        return arr[n - 1];
    }
};