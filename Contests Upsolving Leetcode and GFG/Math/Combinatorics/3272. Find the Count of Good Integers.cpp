#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target(                                                            \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ull unsigned long long
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

static auto init = [] {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

/* 

Intuition

After looking the constraints, it is evident that we cant iterate through all valid numbers. But if iterate through the k-palindromes, it is feasible.

i.e
Number of Palindromes below 10^10 can be found in O(10^5)
Approach

Using a Queue, We will first of all find all the palindromes less than 10^n. This can be done by starting with 1 digit (for odd) and 2 digits (for even) and appending numbers from 0 to 9 on both sides of the string.

Ex:

for n=3
q: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
q: 1, 2, 3, 4, 5, 6, 7, 8, 9, 000, 101, 202, 303, ...
q: 2, 3, 4, 5, 6, 7, 8, 9, 000, 101, 202, 303, ..., 010, 111, 212, ...

Now that we have the palindromes, if a palindrome if n-sized, then we check if it is valid (a valid palindrom should be k-palindromic and should not have leading zero).

For each valid palindrome, we calculate the count of good integers. And we mark the sorted palindrome as visited (as there can be duplicates ex: 24042 and 42024 yield same good integers so should not be double counted).

 */



static ll factorial[11] = {0};
class Solution {
public:
    Solution() {
        if (factorial[0] == 0) {
            factorial[0] = 1;
            for (int i = 1; i <= 10; i++) {
                factorial[i] = i * 1ll * factorial[i - 1];
                ;
            }
        }
    }
    inline bool isValid(string& str, int k) {
        return (str.front() == '0') ? false : stoull(str) % k == 0;
    }
    // Count all permutations of the string
    ll countgood(string& x, bool withLeadingZeros = false) {
        ll res = factorial[(x.size() - withLeadingZeros)];
        unordered_map<char, int> u;
        for (auto c : x)
            u[c]++;
        if (u['0'] == 0 && withLeadingZeros)
            return 0;
        u['0'] -= withLeadingZeros;
        for (auto& [key, val] : u) {
            res /= factorial[val];
        }
        return res;
    }
    long long countGoodIntegers(int n, int k) {
        ll ans = 0;
        unordered_map<string, bool> mp;
        queue<string> q;
        if (n % 2)
            for (int i = 0; i < 10; i++)
                q.push(to_string(i));
        else
            for (int i = 0; i < 10; i++)
                q.push(to_string(i) + to_string(i));
        int len = n / 2;
        while (!q.empty()) {
            string s = q.front();
            string scopy = s;
            sort(scopy.begin(), scopy.end());
            q.pop();
            if (s.size() != n)
                for (int i = 0; i < 10; i++) 
                    q.push(to_string(i) + s + to_string(i));
            else
                if(isValid(s,k) && !mp[scopy]){
                    mp[scopy] = true;
                    ans += countgood(s) - countgood(s,true);
                }
        }
        return ans;
    }
};