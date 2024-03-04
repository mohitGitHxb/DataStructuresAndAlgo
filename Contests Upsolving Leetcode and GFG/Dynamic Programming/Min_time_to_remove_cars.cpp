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
@ Problem
You are given a 0-indexed binary string s which represents a sequence of train cars. s[i] = '0' denotes that the ith car does not contain illegal goods and s[i] = '1' denotes that the ith car does contain illegal goods.

As the train conductor, you would like to get rid of all the cars containing illegal goods. You can do any of the following three operations any number of times:

    Remove a train car from the left end (i.e., remove s[0]) which takes 1 unit of time.
    Remove a train car from the right end (i.e., remove s[s.length - 1]) which takes 1 unit of time.
    Remove a train car from anywhere in the sequence which takes 2 units of time.

Return the minimum time to remove all the cars containing illegal goods.

Note that an empty sequence of cars is considered to have no cars containing illegal goods.



Example 1:

Input: s = "1100101"
Output: 5
Explanation:
One way to remove all the cars containing illegal goods from the sequence is to
- remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
- remove a car from the right end. Time taken is 1.
- remove the car containing illegal goods found in the middle. Time taken is 2.
This obtains a total time of 2 + 1 + 2 = 5.

An alternative way is to
- remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
- remove a car from the right end 3 times. Time taken is 3 * 1 = 3.
This also obtains a total time of 2 + 3 = 5.

5 is the minimum time taken to remove all the cars containing illegal goods.
There are no other ways to remove them with less time.

Example 2:

Input: s = "0010"
Output: 2
Explanation:
One way to remove all the cars containing illegal goods from the sequence is to
- remove a car from the left end 3 times. Time taken is 3 * 1 = 3.
This obtains a total time of 3.

Another way to remove all the cars containing illegal goods from the sequence is to
- remove the car containing illegal goods found in the middle. Time taken is 2.
This obtains a total time of 2.

Another way to remove all the cars containing illegal goods from the sequence is to
- remove a car from the right end 2 times. Time taken is 2 * 1 = 2.
This obtains a total time of 2.

2 is the minimum time taken to remove all the cars containing illegal goods.
There are no other ways to remove them with less time.
 */

/*
@ Explanation
As the problem states we need to remove illegal car from either:
1. left [cost = 1]
2. right [cost = 1]
3. anywhere in between [cost = 2]

So, we will create two arrays which will store the cost from left-to-right[0...i] and right-to-left[i+1....n-1] traversal in two different pass.

For left-to-right array:
1. Initialise the cost of array to 0.
2. If s[0] == '1' means we can directly remove it from the left end which would be minimum cost = 1.
3.for (i = 1 to n - 1)// we have 2 choices
a. Either remove all the elements from left upto i which would cost = i + 1
b. Consider the previous cost + remove current element by cost = 2

    i.e left_to_right[i] = min(left_to_right[i - 1] + 2, i + 1)


Do similar thing for right-to-left array in reverse way

At the end, take the

    min of(left_to_right[n - 1], right_to_left[0])
    for (i = 0 to n - 2)
    min of (left_to_right[i] + right_to_left[i+1])

Example:

index          0  1  2  3  4  5  6
string         1  1  0  0  1  0  1
left_to_right  1  2  2  2  4  4  6
                \  \  \  \  \  \
right_to_left  7  5  3  3  3  1  1
 */
int minimumTime(string s)
{
    int n = s.length();
    vector<int> L2R(n), R2L(n);
    if (s.front() == '1')
    {
        L2R.front() = 1;
    }
    for (int i = 1; i < n; i++)
    {
        if (s[i] == '1')
        {
            L2R[i] = min(L2R[i - 1] + 2, i + 1);
        }
        else
            L2R[i] = L2R[i - 1];
    }

    if (s.back() == '1')
    {
        R2L.back() = 1;
    }
    for (int i = n - 2; i >= 0; i--)
    {
        if (s[i] == '1')
        {
            R2L[i] = min(R2L[i + 1] + 2, n - i);
        }
        else
        {
            R2L[i] = R2L[i + 1];
        }
    }

    int ans = -1e9;
    ans = min(L2R.back(), R2L.front());
    for (int i = 0; i < n - 1; i++)
    {
        ans = min(ans, L2R[i] + R2L[i + 1]);
    }

    return ans;
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