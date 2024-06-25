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
#pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC target("avx,avx2,fma")
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl
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
#define sz(x) ((ll)(x).size())
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

vpii dirs4 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vpii dirs8 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
template <class T = int>
void customPrint(const T &t)
{
    cerr << t << " ";
}

template <class T = int>
void customPrint(const vector<T> &vec)
{
    cerr << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const vector<vector<T>> &vec)
{
    cerr << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_map<T, U, custom_hash> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        cerr << "{" << i.first << ":";
        customPrint(i.second);
        cerr << "}\n";
    }
    cerr << "]\n";
}

template <class T = int, class U = int>
void customPrint(const map<T, U> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        cerr << "{" << i.first << ":";
        customPrint(i.second);
        cerr << "}\n";
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const multiset<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const set<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const unordered_set<T, custom_hash> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(priority_queue<T> pq)
{
    cerr << "[";
    while (!pq.empty())
    {
        customPrint(pq.top());
        pq.pop();
    }
    cerr << "]\n";
}
template <class T = int>
void customPrint(priority_queue<T, vector<T>, greater<T>> pq)
{
    cerr << "[";
    while (!pq.empty())
    {
        customPrint(pq.top());
        pq.pop();
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(stack<T> st)
{
    cerr << "[";
    while (!st.empty())
    {
        customPrint(st.top());
        st.pop();
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(queue<T> q)
{
    cerr << "[";
    while (!q.empty())
    {
        customPrint(q.front());
        q.pop();
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(deque<T> dq)
{
    cerr << "[";
    for (auto &i : dq)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_multimap<T, U> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        cerr << "{" << i.first << ":";
        customPrint(i.second);
        cerr << "}\n";
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const unordered_multiset<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}
void printBitRepresentation(long long n)
{
    string binary = bitset<64>(n).to_string(); // converts to binary
    cout << "Binary representation: " << binary << "\n";
}
bool isPrime_sqrt(ll n)
{
    if (n == 1)
        return false;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
long long binaryExponentiation(long long base, long long exponent, long long mod)
{
    long long res = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return res;
}
long long getModularMultiplicativeInverse(long long num, long long mod)
{
    // multiplicative inverse only exists if num and mod are relatively prime (coprime) i.e gcd(num, mod) = 1
    if (__gcd(num, mod) != 1)
    {
        return -1;
    }
    return binaryExponentiation(num, mod - 2, mod);
}
/*

Bodya and Sasha found a permutation p1,…,pn and an array a1,…,an

. They decided to play a well-known "Permutation game".

A permutation of length n
is an array consisting of n distinct integers from 1 to n in arbitrary order. For example, [2,3,1,5,4] is a permutation, but [1,2,2] is not a permutation (2 appears twice in the array), and [1,3,4] is also not a permutation (n=3 but there is 4

in the array).

Both of them chose a starting position in the permutation.

The game lasts k

turns. The players make moves simultaneously. On each turn, two things happen to each player:

    If the current position of the player is x

, his score increases by ax
.
Then the player either stays at his current position x
or moves from x to px

    .

The winner of the game is the player with the higher score after exactly k turns.

Knowing Bodya's starting position PB
and Sasha's starting position PS

, determine who wins the game if both players are trying to win.
Input

The first line contains a single integer t
(1≤t≤104

) — the number of testcases.

The first line of each testcase contains integers n
, k, PB, PS (1≤PB,PS≤n≤2⋅105, 1≤k≤109

) — length of the permutation, duration of the game, starting positions respectively.

The next line contains n
integers p1,…,pn (1≤pi≤n) — elements of the permutation p

.

The next line contains n
integers a1,…,an (1≤ai≤109) — elements of array a

.

It is guaranteed that the sum of values of n
over all test cases does not exceed 2⋅105

.
Output

For each testcase output:

    "Bodya" if Bodya wins the game.
    "Sasha" if Sasha wins the game.
    "Draw" if the players have the same score.

 */

ll getMaxScore(vl &perm, vl &a, ll k, ll startIdx)
{
    ll maximumMoves = min(k, sz(perm) - 1);
    ll move = 0;
    ll maxScore = a[startIdx] * (k - move);
    ll cumulativeSum = a[startIdx];
    while (move < maximumMoves)
    {
        startIdx = perm[startIdx];
        move++;
        maxScore = max(maxScore, cumulativeSum + a[startIdx] * (k - move));
        cumulativeSum += a[startIdx];
    }
    return maxScore;
}

void solve()
{
    ll n, k, pbd, ps;
    cin >> n >> k >> pbd >> ps;
    vl perm(n + 1), a(n + 1);
    forn(i, n) cin >> perm[i + 1];
    forn(i, n) cin >> a[i + 1];
    if (pbd == ps)
    {
        cout << "Draw" << endl;
        return;
    }
    /*
    @ Observations
    ! Wrong approach:
    & Try to reach the maximum element and then stay there for the remaining k - steps taken to reach the maximum element
    & This approach first of all is definitely pain in the ass to implement because you will be required to write DFS/BFS make graphs etc for a 1300 rated problem this is way too much
    & Secondly IT IS NOT EVEN CORRECT BECAUSE reaching maximum element doesn't guarantee best case answer

    ^ Correct approach:
    % After doing some observations we can see that initially the answer for starting position current would be a[current] * k
    % Now if we move to perm[i] (new index = perm[oldIndex])
    % first we have to take the previous element that would be now let's say a[prev1]
    % New answer would be a[prev1] + a[current] * (k - 1)
    % Similarly for 2 moves it would be a[prev1] + a[prev2] + a[current] * (k - 2)
    % similarly for 3 moves it would be a[prev1] + a[prev2] + a[prev3] + a[current] * (k - 3)

    & now do we keep doing this till (k - x) is greater than 0? NO!
    & We can see that since perm is a permutation traversing it like that way i = perrm[i] would result in a cycle
    & Hence at max we only need to go from 0 to till min(k,n);

    * Boom now just take maximum of all the possibilites and return the answer
    * O(N) Time complexity

     */
    ll bodyaScore = getMaxScore(perm, a, k, pbd);
    ll sashaScore = getMaxScore(perm, a, k, ps);
    if (bodyaScore > sashaScore)
    {
        cout << "Bodya" << endl;
    }
    else if (bodyaScore < sashaScore)
    {
        cout << "Sasha" << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fast_read();
    int t;
    cin >> t;
    forn(i, t)
    {
        cerr << "\nTestcase " << i + 1 << " started\n";
        solve();
    }

    return 0;
}