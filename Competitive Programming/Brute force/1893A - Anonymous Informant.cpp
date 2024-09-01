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
#define deb(x) cerr << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
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
#define forv(it, a) for (auto &it : a)
#define PI 3.1415926535897932384626
ll MOD = 998244353;
double eps = 1e-12;
#define forsn(i, s, e) for (ll i = s; i < e; i++)
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
	ios::sync_with_stdio(false);
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

You are given an array b1,b2,…,bn

.

An anonymous informant has told you that the array b
was obtained as follows: initially, there existed an array a1,a2,…,an, after which the following two-component operation was performed k

times:

	A fixed point†

x of the array a
was chosen.
Then, the array a
was cyclically shifted to the left‡ exactly x

	times.

As a result of k
such operations, the array b1,b2,…,bn

was obtained. You want to check if the words of the anonymous informant can be true or if they are guaranteed to be false.

†
A number x is called a fixed point of the array a1,a2,…,an if 1≤x≤n and ax=x

.

‡
A cyclic left shift of the array a1,a2,…,an is the array a2,…,an,a1.

@ Important concept:
The key idea is that after applying an operation with the number x, the last element of the resulting array will be equal to x. Since after x cyclic shifts, the array [a1,a2,…,an] will become [ax+1,…,an,a1,…,ax], and ax=x, as x was a fixed point of the array a

.

From this idea, we can deduce that the operation can always be undone in at most one way: we need to look at the last element (an
), and if an>n, it is not possible to undo the operation. Otherwise, we need to cyclically shift the array to the right an

times.

Therefore, the solution to the problem will be to undo the operation on the array by 1
step k

times. If at any point it becomes impossible to undo the operation, the answer is "No". Otherwise, the answer is "Yes".

To avoid explicitly shifting the array, we can store a variable s
representing the index of the initial element, indicating that the current array is equal to [as,as+1,…,an,a1,…,as−1]. When cyclically shifting the array to the right by x, s decreases by x, initially s=1

.

Also, since k
in the problem can be up to 109, simulating k undo operations would be very time-consuming. However, we can notice that if we manage to undo the operation n times without breaking anything, we have entered a cycle. Therefore, if we successfully undo the operation n times, the answer is definitely "Yes". In other words, it was sufficient to do k = min(k, n).
 */

constexpr inline void printAns(bool result)
{
	puts(result ? "Yes" : "No");
}

void solve()
{
	ll n,k;
	cin >> n >> k;
	vl a(n);
	forsn(i, 0, n)
	{
		cin >> a[i];
	}
	// as at maximum there can be n unique rotations
	ll LIMIT = min(n,k);
	ll start = 0;
	forsn(i,0,LIMIT){
		ll endPosition = (start + n - 1) % n;
		ll endVal = a[endPosition];
		if(endVal > n){
			printAns(false);
			return;
		}
		start = (start - endVal + n) % n;
	}

	printAns(true);
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
	forsn(i, 0, t)
	{
		cerr << "\nTestcase " << i + 1 << " started\n";
		solve();
	}

	return 0;
}