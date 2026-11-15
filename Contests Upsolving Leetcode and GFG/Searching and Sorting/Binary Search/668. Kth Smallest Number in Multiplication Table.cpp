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
Nearly everyone has used the Multiplication Table. The multiplication table of size m x n is an integer matrix mat where mat[i][j] == i * j (1-indexed).

Given three integers m, n, and k, return the kth smallest element in the m x n multiplication table.



Example 1:

Input: m = 3, n = 3, k = 5
Output: 3
Explanation: The 5th smallest number is 3.

@ Approach:
We can use binary search to find the kth smallest number in the multiplication table. The idea is
to count how many numbers are less than or equal to a mid value in the multiplication table,
and adjust our search range based on that count.
Time Complexity: O(m * log(m * n))
Space Complexity: O(1)

     */
public:
    int findKthNumber(int m, int n, int k)
    {
        long long minProduct = 1, maxProduct = m * n;

        while (minProduct <= maxProduct)
        {
            long long midProduct = (minProduct + maxProduct) >> 1;

            long long countOfSmaller = 0;
            for (int i = 1; i <= m; i++)
                countOfSmaller += min<long long>(midProduct / i, n);

            if (countOfSmaller < k)
            {
                minProduct = midProduct + 1;
            }
            else
            {
                maxProduct = midProduct - 1;
            }
        }
        return minProduct;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    vector<string> words = {"aba", "bcb", "ece", "aa", "e"};
    vector<vector<int>> queries = {{0, 2}, {1, 4}, {1, 1}};
    obj.vowelStrings(words, queries);
    // Test cases for local testing
    return 0;
}
#endif