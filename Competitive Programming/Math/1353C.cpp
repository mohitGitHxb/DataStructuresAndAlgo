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
// #define mod 1000000007
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

template <class T = int>
void print1dVector(const vector<T> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void print2dVector(const vector<vector<T>> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        print1dVector(i);
    }
    cout << "]\n";
}
template <class T = int>
void printHashmap(const unordered_map<T, T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int>
void printMap(const map<T, T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int>
void printMultiSet(const multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void printSet(const set<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void printPriorityQueue(priority_queue<T> pq)
{
    cout << "[";
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "]\n";
}
template <class T = int>
void printStack(stack<T> st)
{
    cout << "[";
    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "]\n";
}
template <class T = int>
void printQueue(queue<T> q)
{
    cout << "[";
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "]\n";
}
template <class T = int>
void printDeque(deque<T> dq)
{
    cout << "[";
    for (auto &i : dq)
    {
        cout << i << " ";
    }
    cout << "]\n";
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
It is intuitive (and provable) that the best strategy is to move each figure to the center cell (n+12,n+12). Now, with some paperwork or easy observations, we can notice that we have exactly 8 cells with the shortest distance 1, 16 cells with the shortest distance 2, 24 cells with the shortest distance 3 and so on. So we have 8i cells with the shortest distance i. So the answer is 1⋅8+2⋅16+3⋅24+⋯+(n−12)2⋅8. It can be rewritten as 8(1+4+9+⋯+(n−12)2) so we can just calculate the sum of squares of all integers from 1 to n−12 using loop (or formula n(n+1)(2n+1)6) and multiply the answer by 8

.

Time complexity: O(n)
or O(1).

 */
void solve()
{
    ll n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    ll start = 0, end = 0, bCount = 0, wCount = 0, operations = 0;
    for (end = 0; end < k; end++)
    {
        if (str[end] == 'B')
        {
            bCount++;
        }
        else
        {
            wCount++;
        }
    }
    if (bCount == k)
    {
        cout << 0 << endl;
        return;
    }
    operations = wCount;
    // deb(bCount);
    // deb(wCount);
    while (end < n)
    {
        if (str[start] == 'B')
        {
            bCount--;
        }
        else
        {
            wCount--;
        }
        if (str[end] == 'B')
        {
            bCount++;
        }
        else
        {
            wCount++;
        }
        // cout << bCount << " : " << wCount << "\t{" << start << " : " << end << "}" << endl;
        operations = min(operations, wCount);
        start++;
        end++;
    }
    cout << operations << endl;
}

void preCompute(hmpll &mp)
{
    const int lim = 6e5 + 5;
    mp[1] = 0;
    ll sum = 0;
    ll multiplier = 1, factor = 8;
    for (int i = 3; i < lim; i += 2)
    {
        sum = sum + factor * multiplier;
        mp[i] = sum;
        factor += 8;
        multiplier++;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    hmpll mp;
    preCompute(mp);
    while (t--)
    {
        ll n;
        cin >> n;
        cout << mp[n] << endl;
    }

    return 0;
}
