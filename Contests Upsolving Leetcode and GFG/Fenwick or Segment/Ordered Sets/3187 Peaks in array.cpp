#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/*
 * CUSTOM hash function which avoids collisions and hence makes unordered maps / sets faster
 */
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
#define gc getchar_unlocked
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(x) memset(x, false, sizeof(x))
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define SUM(v) accumulate(all(v), 0LL)
#define endl "\n"
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define forv(it, a) for (auto &it : a)
#define PI 3.1415926535897932384626
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef unordered_map<int, int, custom_hash> hmpi;
typedef unordered_map<ll, ll, custom_hash> hmpll;
typedef unordered_map<int, pii> hmppi;
typedef unordered_map<int, vi> hmpvi;
typedef unordered_set<int, custom_hash> hsi;
typedef unordered_set<ll, custom_hash> hsll;
typedef unordered_set<pii> hspi;
typedef unordered_set<pl> hspl;
typedef map<int, int> mpi;
typedef map<ll, ll> mpll;
typedef map<int, pii> mppi;
typedef map<int, vi> mpvi;
typedef set<int> si;
typedef set<ll> sll;
typedef set<pii> spi;
typedef set<pl> spl;
template <class T = pii>
using oset =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T = pii>
using mset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
#define sz(x) ((ll)(x).size())

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
A peak in an array arr is an element that is greater than its previous and next element in arr.

You are given an integer array nums and a 2D integer array queries.

You have to process queries of two types:

    queries[i] = [1, li, ri], determine the count of peak elements in the
    subarray
    nums[li..ri].
    queries[i] = [2, indexi, vali], change nums[indexi] to vali.

Return an array answer containing the results of the queries of the first type in order.

Notes:

    The first and the last element of an array or a subarray cannot be a peak.



Example 1:

Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]

Output: [0]

Explanation:

First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].

Second query: The number of peaks in the [3,1,4,4,5] is 0.

Example 2:

Input: nums = [4,1,4,2,1,5], queries = [[2,2,4],[1,0,2],[1,0,4]]

Output: [0,1]

Explanation:

First query: nums[2] should become 4, but it is already set to 4.

Second query: The number of peaks in the [4,1,4] is 0.

Third query: The second 4 is a peak in the [4,1,4,2,1].

    @ Use PBDS like ordered set to maintain peaks and update values effieciently
    @ It can be solved using segment tree or fenwick tree as well
    @ as it only has point update

     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    vi countOfPeaks(vi &nums, vector<vi> &queries)
    {
        oset<ll> peaksIndices;
        forsn(i, 1, sz(nums) - 1)
        {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
            {
                peaksIndices.insert(i); //& store all peaks;
            }
        }
        vi ans;
        forn(i, sz(queries))
        {
            int type = queries[i][0];
            ll index = queries[i][1];
            if (type == 1)
            {
                ll rightMost = queries[i][2];
                int right = peaksIndices.order_of_key(rightMost);
                int left = peaksIndices.order_of_key(index + 1);
                // deb(right);
                // deb(left);
                ans.pb(max(0, right - left));
            }
            else
            {
                int valueToChange = queries[i][2];
                nums[index] = valueToChange;

                /*
             & Just observe one thing that if an element is affected jth index then the only affected peak values (possible) will be j-1 && j + 1
             & hence we can run loop for only 3 values (-1 to +1) [make sure it is in bounds of array]
             ! peaks can never happen at extreme hands;
             ^ Erase all keys and then insert the one which remains peak even after performing point update

              */
                for (int j = max(1ll, index - 1); j <= min(sz(nums) - 2, index + 1); j++)
                {
                    peaksIndices.erase(j);
                    if (nums[j] > nums.at(j - 1) && nums[j] > nums.at(j + 1))
                    {
                        // customPrint(nums);
                        peaksIndices.insert(j);
                    }
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
