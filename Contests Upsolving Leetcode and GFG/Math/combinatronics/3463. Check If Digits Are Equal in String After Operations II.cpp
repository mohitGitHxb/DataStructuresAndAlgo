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
    You are given a string s consisting of digits. Perform the following operation repeatedly until the string has exactly two digits:

        For each pair of consecutive digits in s, starting from the first digit, calculate a new digit as the sum of the two digits modulo 10.
        Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.

    Return true if the final two digits in s are the same; otherwise, return false.

    Example 1:

    Input: s = "3902"

    Output: true

    Explanation:

        Initially, s = "3902"
        First operation:
            (s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
            (s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
            (s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
            s becomes "292"
        Second operation:
            (s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
            (s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
            s becomes "11"
        Since the digits in "11" are the same, the output is true.

    Example 2:

    Input: s = "34789"

    Output: false

    Explanation:

        Initially, s = "34789".
        After the first operation, s = "7157".
        After the second operation, s = "862".
        After the third operation, s = "48".
        Since '4' != '8', the output is false.

    @ Observations:
    &- Important thing to remember: (a + b) % 10 = ((a % 10) + (b % 10)) % 10 and vice versa
    &- If we visualize the tree a little bit we can notice that the term's coefficients follows pascal's triangle
    &- nCk = value of pascal triangle grid at row n and column k

    &- We need to find nCr % 10 however we can't find inverse modulo of non prime number (Fermat's little theorem)
    &- Hence we will need to find some way to calculate inverse modulo properly.
    ~ nCr % 2 = x, nCr % 5 = y: now try for all values 0-9 to get the nCr % 10 which satisfies the first two conditions
    ? Alternate sol: Use chinese remainder theorem


    ! Hard problem to solve

     */
public:
    int binaryExponentiation(int n, int p, int mod)
    {
        int res = 1;
        while (p)
        {
            if (p & 1)
            {
                res = res * n % mod;
            }
            n = n * n % mod;
            p >>= 1;
        }
        return res;
    }

    pair<int, int> decompose(int x, int mod)
    {
        // decompose x into x = y * pow(mod, ct). so that we can calc mod inv of y (cannot directly calculate on x)
        int ct = 0;
        while (x % mod == 0)
        {
            x /= mod;
            ++ct;
        }
        return {x % mod, ct};
    }

    bool check(vector<int> &a, int mod)
    {
        int res = 0;
        int n = a.size();
        int ncr = 1; // maintains c(n - 1, i)
        int ct = 0;  // maintains the exponent part of mod
        for (int i = 0; i != n; ++i)
        {
            if (ct == 0)
            { // ct >= 0
                res = (res + a[i] * ncr) % mod;
            }
            // update ncr = ncr * (n - 1 - i) / (i + 1)
            if (i == n - 1)
            {
                continue;
            } // guarantee the x fed to decompose() is pos.
            pair<int, int> p1 = decompose(n - 1 - i, mod);
            ncr = ncr * p1.first % mod;
            ct += p1.second;
            pair<int, int> p2 = decompose(i + 1, mod);
            ncr = ncr * binaryExponentiation(p2.first, mod - 2, mod) % mod;
            ct -= p2.second;
        }
        return res == 0;
    }

    bool hasSameDigits(string s)
    {
        int n = s.size();
        vector<int> a(n - 1);
        for (int i = 0; i != n - 1; ++i)
        {
            a[i] = (s[i] - '0') - (s[i + 1] - '0');
            a[i] = (a[i] + 10) % 10;
        }
        return check(a, 2) && check(a, 5);
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