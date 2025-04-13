#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target( \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
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
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
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

static const int MOD = 1e9 + 7;
static unordered_map<ll, unordered_map<ll, ll>> stored;

static ll binExpo(ll base, ll expo)
{
    if (stored.count(base) && stored[base].count(expo))
    {
        return stored[base][expo];
    }
    ll ans = 1;
    while (expo > 0)
    {
        if (expo & 1)
        {
            ans = (ans * base) % MOD;
            expo--;
        }
        else
        {
            base = (base * base) % MOD;
            expo >>= 1;
        }
    }
    return stored[base][expo] = ans;
}
class Solution
{
public:
    int countGoodNumbers(long long n)
    {
        const ll evenIndices = (n + 1) / 2;
        const ll oddIndices = n / 2;
        return (binExpo(5, evenIndices) % MOD * binExpo(4, oddIndices) % MOD) %
               MOD;
    }
};

/*
===========================
\U0001f9e0 ALGORITHM EXPLANATION:
===========================

1. A number is "good" if:
   - Every digit at an even index (0-based) is an EVEN digit → 5 choices: {0, 2,
4, 6, 8}
   - Every digit at an odd index is a PRIME digit → 4 choices: {2, 3, 5, 7}

2. For a number of length 'n':
   - Count of digits at even positions = ceil(n / 2) → (n + 1) / 2
   - Count of digits at odd positions  = floor(n / 2) → n / 2

3. Total combinations of such "good numbers":
   → total = 5^(even positions) * 4^(odd positions) mod 1e9+7

4. To avoid time limit exceeded and overflow, use modular exponentiation:
   - Use recursion to compute power efficiently in O(log n) time.

===========================
\U0001f9ea DRY RUN (Example: n = 4)
===========================

Step 1:
  even = (4 + 1) / 2 = 2
  odd  = 4 / 2 = 2

Step 2:
  modPow(5, 2) = 25
  modPow(4, 2) = 16

Step 3:
  result = (25 * 16) % MOD = 400

✅ So, countGoodNumbers(4) = 400
*/
