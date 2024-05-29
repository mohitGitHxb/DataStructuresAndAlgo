#include <bits/stdc++.h>
using namespace std;
/*

* THIS THING IS GANGSTA!!!
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
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
#define forv(i, v) for (auto i : v)
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
#define sz(x) ((ll)(x).size())

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
void customPrint(const unordered_map<T, U> &mp)
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
void customPrint(const unordered_set<T> &mp)
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
ou are given a number n and an array b1,b2,…,bn+2

, obtained according to the following algorithm:

    some array a1,a2,…,an

was guessed;
array a
was written to array b, i.e. bi=ai (1≤i≤n
);
The (n+1)
-th element of the array b is the sum of the numbers in the array a, i.e. bn+1=a1+a2+…+an
;
The (n+2)
-th element of the array b was written some number x (1≤x≤109), i.e. bn+2=x
; The
array b

    was shuffled.

For example, the array b=[2,3,7,12,2]

it could be obtained in the following ways:

    a=[2,2,3]

and x=12
;
a=[3,2,7]
and x=2

    .

For the given array b
, find any array a that could have been guessed initially.

& Whole sum of array B contains the sum of array A and all elements of array A + some random value

& SUM(B) = SUM(A) + SUM(A) + x;
& WE HAVE SUM(B) now we can assume every element to be 'x' and try removing it and check whether (SUM(B) - x) = NewSum
& NewSum = 2 * SUM(A) hence NewSum/2 should also exists in the array b
& if we can find a number in the array b such that NewSum/2 = SUM(A) then we can find the array a easily

% Important condition NewSum has to be even and it should be less than equal 2e9 as per the constraints
@ Core observation of the simple formula SUM(B) = SUM(A) + SUM(A) + x
 */

void solve()
{

    int n;
    cin >> n;
    vi b(n + 2);
    unordered_multiset<int, custom_hash> st;
    ll sum = 0;
    forn(i, sz(b))
    {
        cin >> b[i];
        st.insert(b[i]);
        sum += b[i];
    }
    forv(x, b)
    {
        st.erase(st.find(x));
        sum -= x;
        if (sum % 2 == 0 and sum <= 2e9 and st.count(sum / 2) > 0)
        {
            st.erase(st.find(sum / 2));
            forv(element, st)
            {
                cout << element << " ";
            }
            cout << "\n";
            return;
        }
        sum += x;
        st.insert(x);
    }
    cout << "-1\n";
}
//* EASIER WAY TO IMPLEMENT THE ABOVE PROBLEM
void solve()
{

    int n;
    cin >> n;
    vi b(n + 2);
    ll sum = 0;
    forn(i, sz(b))
    {
        cin >> b[i];
        sum += b[i];
    }

    //@ Alternate solution [more intuitive]
    //% SUM(A) can be one of the two largest element in the array
    sortall(b);
    bool found = false;
    int index = -1;
    forn(i, sz(b) - 1)
    {
        if (sum - b[i] == 2 * b.back())
        { //& last element is the SUM(A)
            found = true;
            index = i;
            break;
        }
    }

    if (found)
    {
        forn(i, sz(b) - 1)
        {
            if (i != index)
            {
                cout << b[i] << " ";
            }
        }
        cout << "\n";
    }
    else if (sum - b.back() == 2 * b[n])
    { //& second last element is the SUM(A)
        forn(i, n)
        {
            cout << b[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "-1\n";
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