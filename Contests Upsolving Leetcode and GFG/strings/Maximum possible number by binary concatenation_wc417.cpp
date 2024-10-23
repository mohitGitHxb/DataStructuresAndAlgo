#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ull unsigned long long
#define ll long long
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

static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution
{
private:
    /*
        You are given an array of integers nums of size 3.

        Return the maximum possible number whose binary representation can be formed by concatenating the binary representation of all elements in nums in some order.

        Note that the binary representation of any number does not contain leading zeros.

     */
public:
    string removeLeadingZeros(int num)
    {
        string copy = bitset<10>(num).to_string();
        copy.erase(copy.begin(), find_if(copy.begin(), copy.end(), [](int ch)
                                         { return ch != '0'; }));
        return copy;
    }
    int maxGoodNumber(vector<int> &nums)
    {
        //& Use custom comparator a + b > b + a to sort numbers optimally
        sort(nums.begin(), nums.end(), [&](int a, int b)
             { return removeLeadingZeros(a) + removeLeadingZeros(b) > removeLeadingZeros(b) + removeLeadingZeros(a); });
        string s;
        for (int i = 0; i < nums.size(); i++)
        {
            s.append(removeLeadingZeros(nums[i]));
        }
        return stoull(s, nullptr, 2);
    }
};
