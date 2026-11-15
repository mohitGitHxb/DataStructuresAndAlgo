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
void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

class Solution
{
private:
    /*
A positive integer is magical if it is divisible by either a or b.

Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.



Example 1:

Input: n = 1, a = 2, b = 3
Output: 2

Example 2:

Input: n = 4, a = 2, b = 3
Output: 6

  @Intuition

we need to find the nth number that is divible by a or b.so we simply check for some arbuitry number what is it's rank on the secuence.
Approach

* to check a number from 1 to x how many number is divisible by a is x/a,for b is x/b and if we add both the value we get the repeated counting of number that is dibisible by both a and b to remove that we use x/a+x/b-x/lcm(a,b).
* now we use binary seach and check the rank of mid in the sequence is less than n if we get that at the end we simple increase ans+1 because we get the last number that may or may not divisible by a or b ans stricily less than n.
     */
public:
    const int mod = 1e9 + 7;
    ll lcm(ll a, ll b)
    {
        return (a * b) / __gcd(a, b);
    }
    Solution()
    {
        fast_read();
    }
    int nthMagicalNumber(int n, int a, int b)
    {
        ll low = 1, high = n * min(a, b);
        while (low <= high)
        {
            ll mid = (low + high) / 2;
            ll x = mid / a;
            ll y = mid / b;
            ll z = mid / lcm(a, b);
            if (x + y - z >= n)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return low % mod;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
