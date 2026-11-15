#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target( \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl

const int MOD = 1e9 + 7;
const int MAX_N = 1e5 + 10;

static vector<ll> fact(MAX_N + 1, 1), invFact(MAX_N + 1, 1);
static ll binaryExponentiation(ll base, ll exponent)
{
    long long res = 1;
    base %= MOD;
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent >>= 1;
    }
    return res;
}
static const int precompute = []()
{
    for (int i = 2; i <= MAX_N; ++i)
    {
        fact[i] = (fact[i - 1] * 1LL * i) % MOD;
    }
    // Fermat's Little Theorem
    invFact[MAX_N] = binaryExponentiation(fact[MAX_N], MOD - 2);
    for (int i = MAX_N - 1; i >= 1; --i)
    {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
    return 0;
}();

static const int init = []
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
        You are given three integers n, m, k. A good array arr of size n is defined as follows:

        Each element in arr is in the inclusive range [1, m].
        Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].

    Return the number of good arrays that can be formed.

    Since the answer may be very large, return it modulo 109 + 7.



    Example 1:

    Input: n = 3, m = 2, k = 1

    Output: 4

    Explanation:

        There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
        Hence, the answer is 4.

    Example 2:

    Input: n = 4, m = 2, k = 2

    Output: 6

    Explanation:

        The good arrays are [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 1, 1, 1], [2, 2, 1, 1] and [2, 2, 2, 1].
        Hence, the answer is 6.

    Example 3:

    Input: n = 5, m = 2, k = 0

    Output: 2

    Explanation:

        The good arrays are [1, 2, 1, 2, 1] and [2, 1, 2, 1, 2]. Hence, the answer is 2.



         */
    public:
        /*
        Intuition

        Looks too hard to code some nice dp or dfs or something
        Maybe there’s a nice formula
        Approach

        We can view the array as runs of consecutive numbers

        So something like [1, 1, 2, 2, 2, 3] -> [1, 1],[2, 2, 2],[3]
        Suppose there are r runs in the list
        Then there are r-1 pairs of indices that are not the same (when the run changes)

        So since there a total of n-1 pairs of indices in the whole array
        There are (n-1) - (r-1) = n-r pairs of indices that are the same

        We want this equal to k, so n-r=k

        How many ways are there to split the array of length n into r non-empty runs?
        We can just choose r-1 “bars” to place in the n-1 gaps between the elements
        Then each subarray between bars is a run

        There are (n-1 choose r-1) ways to do this
        Which is the same as (n-1 choose (n-1) - (r-1)) = (n-1 choose n-r)
        But remember we showed above that n-r=k
        So we have (n-1 choose k) which is very nice for our problem

        Then the first run can be any of m elements, but each run after must be different than the previous run or else the runs would merge
        There are (m-1)^(r-1) = (m-1)^(n-k-1) to do this

        Thus, our answer is (n-1 choose k) * m * (m-1)^(n-k-1)

         */
        ll nCr(ll n, ll r)
        {
            if (r > n or r < 0)
                return 0;
            return (fact[n] % MOD * invFact[r] % MOD) % MOD * 1LL * invFact[n - r] % MOD;
    }
    int countGoodArrays(const int n, const int m, const int k)
    {
        if (k >= n)
            return 0;
        // (n - 1 choose k * m) * (m-1)^(n-k-1)
        return (((nCr(n - 1, k) % MOD) * 1LL * (m % MOD)) % MOD * 1LL *
                binaryExponentiation(m - 1, n - k - 1)) %
               MOD;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
