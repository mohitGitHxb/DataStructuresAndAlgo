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
static const int N = 1e4 + 1;
static const ll MOD = 1e9 + 7;
static ll factorial[N];
static ll invFactorial[N];

long long __binaryExponentiation(long long base, long long exponent)
{
    long long res = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent >>= 1;
    }
    return res;
}
long long __ncr(int n, int r)
{
    if (r < 0 || r > n)
        return 0;
    return (factorial[n] * invFactorial[r] % MOD) * invFactorial[n - r] % MOD;
}
void __precompute()
{
    if (factorial[0] == 0)
    {
        factorial[0] = 1;
        invFactorial[0] = 1;
        for (int i = 1; i < N; i++)
        {
            factorial[i] = (factorial[i - 1] * i) % MOD;
            invFactorial[i] = __binaryExponentiation(factorial[i], MOD - 2);
        }
    }
}

static int init = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    __precompute();
    return 0;
}();

class Solution
{
private:
    /*
    You are given two integers n and maxValue, which are used to describe an ideal array.

    A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:

        Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
        Every arr[i] is divisible by arr[i - 1], for 0 < i < n.

    Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.



    Example 1:

    Input: n = 2, maxValue = 5
    Output: 10
    Explanation: The following are the possible ideal arrays:
    - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
    - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
    - Arrays starting with the value 3 (1 array): [3,3]
    - Arrays starting with the value 4 (1 array): [4,4]
    - Arrays starting with the value 5 (1 array): [5,5]
    There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.

    Example 2:

    Input: n = 5, maxValue = 3
    Output: 11
    Explanation: The following are the possible ideal arrays:
    - Arrays starting with the value 1 (9 arrays):
    - With no other distinct values (1 array): [1,1,1,1,1]
    - With 2nd distinct value 2 (4 arrays): [1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
    - With 2nd distinct value 3 (4 arrays): [1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
    - Arrays starting with the value 2 (1 array): [2,2,2,2,2]
    - Arrays starting with the value 3 (1 array): [3,3,3,3,3]
    There are a total of 9 + 1 + 1 = 11 distinct ideal arrays.


    @approach:
    ✅ GOAL:
You need to count how many arrays of length n are possible, such that:

Each element is between 1 and maxValue

Each element is divisible by the one before it
→ i.e., arr[i] % arr[i-1] == 0

✅ Step-by-Step in Words:
🧠 Step 1: Understand the type of sequences we want
We are only interested in multiplicative sequences like:

[1, 2, 4] → each value is a multiple of the one before

[3, 6, 12] is valid

[4, 5, 6] is not valid because 5 is not divisible by 4

So we are looking for chains of numbers where each is divisible by the previous one.

🏗️ Step 2: Precompute all possible chains
We precompute all such chains by length:

All chains of length 1
(Just single numbers: [1], [2], [3], … up to maxValue)

All chains of length 2
For example: [1,2], [1,3], [2,4], [3,6]

All chains of length 3
For example: [1,2,4], [2,4,8], etc.

We build up these chain counts using dynamic programming:

Start from length 1

For each value, go through its multiples to form the next value in the chain

Repeat until the value exceeds maxValue

In the end, we have a list STRICT_COUNTS[k][v], which tells:

How many chains of length k+1 end with a number ≤ v + base - 1

🧮 Step 3: Stretch each chain into a full-length array
Let’s say we found a valid chain of distinct values:
[1, 2, 4] → 3 values

But we want arrays of length n (maybe n=5)

So, we stretch this chain like:

[1,1,2,2,4]

[1,2,2,4,4]

[1,1,1,2,4]

These are all valid!
We’re just repeating some values, keeping them in order.

How many ways can we stretch a chain of k values to length n?

The answer is combinations:
C(n-1, k-1)
This comes from "stars and bars" (a combinatorics trick).

🔄 Step 4: Go through each chain length and calculate total arrays
We go through all possible chain lengths:

For each chain length k:

Look up how many chains of length k we found (STRICT_COUNTS[k-1])

Multiply it by C(n-1, k-1) (ways to stretch into length n)

Add that to the final answer

We keep doing this until:

The chain base (smallest number in the chain) exceeds maxValue, or

We’ve tried all valid lengths up to n

🔚 Step 5: Return the final count modulo 1e9+7
Because the number of arrays can be huge, we use modulo 1_000_000_007 to keep the number within bounds.

✅ Example (in Words):
Say n = 3, maxValue = 5

Possible valid chains:

Length 1: [1], [2], [3], [4], [5] → 5 total
Stretch to length 3: only 1 way each → 5 total arrays

Length 2: [1,2], [1,3], [1,4], [1,5], [2,4] → 5 total
Each stretched to length 3 in C(2,1) = 2 ways → 5 × 2 = 10 arrays

Length 3: [1,2,4] → 1 total
Stretched to length 3 in C(2,2) = 1 way → 1 array

Total arrays = 5 + 10 + 1 = 16

     */
public:
    int idealArrays(int n, int maxValue)
    {
        vector<ll> dp(maxValue + 1, 1);
        ll totalAns = maxValue;
        dp[0] = 0;
        const int uniquePrimes = min(n, 16);

        for (int k = 2; k <= uniquePrimes; k++)
        {
            vector<ll> next_dp(maxValue + 1);
            for (int j = 1; j <= maxValue; j++)
            {
                if (dp[j] == 0)
                    continue;
                for (ll i = 2LL * j; i <= maxValue; i += j)
                {
                    next_dp[(int)i] = (next_dp[(int)i] + dp[j]) % MOD;
                }
            }

            ll count = 0;
            for (int i = 1; i <= maxValue; i++)
            {
                count = (count + next_dp[i]) % MOD;
            }

            if (count == 0)
                break;

            ll factor = __ncr(n - 1, k - 1);
            totalAns = (totalAns + count * factor % MOD) % MOD;

            dp = next_dp;
        }

        return (int)totalAns % MOD;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    cout << obj.minimizeXor(4214, 5) << endl;
    return 0;
}
#endif