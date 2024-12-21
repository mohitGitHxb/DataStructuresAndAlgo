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
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl

static bool isPrimeNumber[100001];
static void sieve()
{
    isPrimeNumber[0] = isPrimeNumber[1] = true;
    for (int i = 2; i < 100001; i++)
    {
        if (!isPrimeNumber[i])
        {
            for (ll j = i * 1ll * i; j < 100001; j += i)
            {
                isPrimeNumber[j] = true;
            }
        }
    }
}
static int init = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    sieve();
    return 0;
}();

class Solution
{
private:
    /*
3377. Digit Operations to Make Two Integers Equal
You are given two integers n and m that consist of the same number of digits.

You can perform the following operations any number of times:

    Choose any digit from n that is not 9 and increase it by 1.
    Choose any digit from n that is not 0 and decrease it by 1.

The integer n must not be a prime number at any point, including its original value and after each operation.

The cost of a transformation is the sum of all values that n takes throughout the operations performed.

Return the minimum cost to transform n into m. If it is impossible, return -1.

A prime number is a natural number greater than 1 with only two factors, 1 and itself.



Example 1:

Input: n = 10, m = 12

Output: 85

Explanation:

We perform the following operations:

    Increase the first digit, now n = 20.
    Increase the second digit, now n = 21.
    Increase the second digit, now n = 22.
    Decrease the first digit, now n = 12.

Example 2:

Input: n = 4, m = 8

Output: -1

Explanation:

It is impossible to make n equal to m.

Example 3:

Input: n = 6, m = 2

Output: -1

Explanation:

Since 2 is already a prime, we can't make n equal to m.



Constraints:

    1 <= n, m < 104
    n and m consist of the same number of digits.


     */
public:
    const int mod = 1e9 + 7;
    int minOperations(int n, int m)
    {
        if (!isPrimeNumber[m] || !isPrimeNumber[n])
            return -1;
        set<pair<ll, ll>> st;
        st.emplace(n, n);
        bitset<100001> visited;
        visited.set(n);
        while (!st.empty())
        {
            auto [cost, curr] = *st.begin();
            st.erase(st.begin());
            if (curr == m)
                return cost;
            string currStr = to_string(curr);

            for (int i = 0; i < currStr.size(); i++)
            {
                int digit = currStr[i] - '0';

                // Increment the digit if it's less than 9
                if (digit < 9)
                {
                    string nextStr = currStr;
                    nextStr[i] = currStr[i] + 1;
                    int nextNum = stoll(nextStr);
                    if (!visited[nextNum] && isPrimeNumber[nextNum])
                    {
                        st.emplace(cost + nextNum, nextNum);
                        visited.set(nextNum);
                    }
                }

                // Decrement the digit if it's greater than 0
                if (digit > 0)
                {
                    string nextStr = currStr;
                    nextStr[i] = currStr[i] - 1;
                    // Ensure no leading zeros in the transformed number
                    if (nextStr[0] != '0')
                    {
                        int nextNum = stoll(nextStr);
                        if (!visited[nextNum] && isPrimeNumber[nextNum])
                        {
                            st.emplace(cost + nextNum, nextNum);
                            visited.set(nextNum);
                        }
                    }
                }
            }
        }
        return -1;
    }
};
