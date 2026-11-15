#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl
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
Alice and Bob are playing a game on an array a of n

positive integers. Alice and Bob make alternating moves with Alice going first.

In his/her turn, the player makes the following move:

    If a1=0

, the player loses the game, otherwise:
Player chooses some i
with 2≤i≤n. Then player decreases the value of a1 by 1 and swaps a1 with ai

    .

Determine the winner of the game if both players play optimally.
Input

The input consists of multiple test cases. The first line contains a single integer t
(1≤t≤2⋅104)

 — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer n
(2≤n≤105)  — the length of the array a

.

The second line of each test case contains n
integers a1,a2…an (1≤ai≤109)  — the elements of the array a

.

It is guaranteed that sum of n
over all test cases does not exceed 2⋅105

.
Output

For each test case, if Alice will win the game, output "Alice". Otherwise, output "Bob".

You can output each letter in any case. For example, "alIcE", "Alice", "alice" will all be considered identical.
Example
Input


3
2
1 1
2
2 1
3
5 4 4

Output

Bob
Alice
Alice

Note

In the first testcase, in her turn, Alice can only choose i=2
, making the array equal [1,0]. Then Bob, in his turn, will also choose i=2 and make the array equal [0,0]. As a1=0

, Alice loses.

In the second testcase, once again, players can only choose i=2
. Then the array will change as follows: [2,1]→[1,1]→[1,0]→[0,0]

, and Bob loses.

In the third testcase, we can show that Alice has a winning strategy.
 */

void TLE_Solution()
{
    int n;
    cin >> n;
    vi v(n);
    forn(i, n)
    {
        cin >> v[i];
    }
    string ans;
    bool turn = false;
    // whoever gets 0 first gets to lose or win according to minimum element available to swap with. if that minimum element is 0 you win else you lose
    priority_queue<int, vi, greater<int>> pq(v.begin() + 1, v.end());
    int front = v.front();

    while (!pq.empty())
    {
        front--;
        int ele = pq.top();
        pq.pop();
        if (front == 0)
        {
            if (ele == 0)
            {
                ans = (turn) ? "bob" : "alice";
                break;
            }
            else
            {
                ans = (turn) ? "alice" : "bob";
                break;
            }
        }
        pq.push(front);
        turn = !turn;
        front = ele;
    }
    cout << ans << "\n";
}

void solve()
{
    int n;
    cin >> n;
    vi v(n);
    forn(i, n)
    {
        cin >> v[i];
    }
    /*
    Case 1: a1>min(a)

Alice
can force the Bob to always decrease the minimum element by always choosing minimum element of a in her turn. Where as Bob can not do much, all other elements he would swap with would be greater than or equal to min(a). Even if there exists multiple minimums in a, In first move Alice would decrease from a1, hence in this case Alice

would always win.

Case 2: a1=min(a)

In this case optimal startegy for Bob
would be to always chhose minimum element of the array, which is a1. Alice would always be swapping the element greater than a1 in her turn, hence in the case Bob would always win

     */
    string ans;
    if (v.front() == *min_element(v.begin(), v.end()))
    {
        ans = "bob";
    }
    else
    {
        ans = "alice";
    }
    cout << ans << "\n";
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

    while (t--)
    {
        cerr << "\n<-----------TESTCASE STARTED!!!-----------------/>\n\n";
        solve();
    }

    return 0;
}