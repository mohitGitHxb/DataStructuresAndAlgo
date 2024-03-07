#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
#define mod 1000000007
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
typedef unordered_map<int, int> hmpi;
typedef unordered_map<ll, ll> hmpll;
typedef unordered_map<int, pii> hmppi;
typedef unordered_map<int, vi> hmpvi;
typedef unordered_set<int> hsi;
typedef unordered_set<ll> hsll;
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
#define sz(x) ((ll)(x).size())
/*
The given code is an implementation of an algorithm to solve the problem of finding the maximum elegance of a subsequence of items with size exactly `k`. The elegance of a subsequence is defined as the sum of all profits in the subsequence plus the square of the number of distinct categories in the subsequence.

The main function `findMaximumElegance` takes as input a reference to the 2D vector `items` and an integer `k`. It returns the maximum elegance of a subsequence of items with size exactly `k`.

First, the function sorts `items` in non-increasing order based on their profits. It then reverses `items` to obtain a non-decreasing order. This is done to ensure that the most profitable items are considered first.

Next, it initializes the result `res` to 0 and a variable `curr` to keep track of the current total profit. It also calculates the size of `items` and creates two additional data structures: a vector `dup` to store duplicate categories and an unordered set `seen` to keep track of distinct categories.

The function then enters a for loop that iterates over all items. For each item, it checks if its index is less than `k`. If it is, it adds its profit to `curr` and checks if its category has already been seen. If it has, it adds its profit to `dup`. Otherwise, it checks if its category has not been seen yet. If it has not, it checks if `dup` is empty. If it is, it breaks out of the loop. Otherwise, it adds its profit to `curr`, subtracts the last element in `dup` from `curr`, and pops the last element from `dup`.

After processing each item, it inserts its category into `seen` and updates `res` with the maximum between its current value and the current total profit plus the square of the size of `seen`.

Finally, after processing all items, it returns `res`, which represents the maximum elegance of a subsequence of items with size exactly `k`.

In terms of time complexity, since the function sorts `items`, its time complexity is dominated by the sorting operation, which takes `O(n log n)` time, where `n` is the number of items. In terms of space complexity, since the function uses additional data structures such as a vector and an unordered set, its space complexity is `O(n)`.


The intuition behind the code is to first sort the items in non-increasing order based on their profits and then consider the most profitable items first. The code uses a greedy approach to select the first k items and then tries to improve the result by replacing any duplicate categories with distinct categories from the remaining items.

The code uses a vector dup to store duplicate categories and an unordered set seen to keep track of distinct categories. It iterates over all items and adds their profits to a variable curr that keeps track of the current total profit. If it encounters a duplicate category, it adds its profit to dup. If it encounters a distinct category, it checks if dup is empty. If it is not, it replaces the least profitable duplicate category with the current distinct category by adding its profit to curr, subtracting the least profitable duplicate category from curr, and popping it from dup.

After processing each item, the code updates the result with the maximum between its current value and the current total profit plus the square of the number of distinct categories.
 */

ll findMaximumElegance(vvi &items, int k)
{
    sortall(items);
    reverse(all(items));
    ll res = 0, curr = 0, size = sz(items);
    vi dup;
    hsi seen;
    forn(i, size)
    {
        if (i < k)
        {
            if (seen.count(items[i][1]))
            {
                dup.pb(items[i][0]);
            }
            curr += items[i][0];
        }
        else if (seen.count(items[i][1]) == 0)
        {
            if (dup.empty())
                break;
            curr += items[i][0] - dup.back();
            dup.pop_back();
        }
        seen.insert(items[i][1]);
        res = fmax(res, curr + (ll)seen.size() * seen.size());
    }
    return res;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}