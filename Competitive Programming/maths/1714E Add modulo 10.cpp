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

You are given an array of n integers a1,a2,…,an

You can apply the following operation an arbitrary number of times:

	select an index i

(1≤i≤n) and replace the value of the element ai with the value ai+(aimod10), where aimod10 is the remainder of the integer dividing ai by 10

	.

For a single index (value i
), this operation can be applied multiple times. If the operation is applied repeatedly to the same index, then the current value of ai is taken into account each time. For example, if ai=47 then after the first operation we get ai=47+7=54, and after the second operation we get ai=54+4=58

.

Check if it is possible to make all array elements equal by applying multiple (possibly zero) operations.

For example, you have an array [6,11]

.

	Let's apply this operation to the first element of the array. Let's replace a1=6

with a1+(a1mod10)=6+(6mod10)=6+6=12. We get the array [12,11]
.
Then apply this operation to the second element of the array. Let's replace a2=11
with a2+(a2mod10)=11+(11mod10)=11+1=12. We get the array [12,12]

	.

Thus, by applying 2
operations, you can make all elements of an array equal.
 */
bool isSame(vl &arr){
	return MAX(arr) == MIN(arr);
}
void solve()
{

	int n;
	cin >> n;
	vl arr(n);
	forsn(i, 0, n)
	{
		cin >> arr[i];
	}
	// first check whether all elements are equal or not
	if (isSame(arr))
	{
		cout << "YES" << "\n";
		return;
	}
	// if there are elements multiple of 5 then at max you can perform single operation
	bool flag_5 = false;
	forv(num, arr)
	{
		if (num % 5 == 0)
		{
			flag_5 = true;
			num = (num + (num % 10));
		}
	}
	if (flag_5)
	{
		cout << (isSame(arr) ? "YES" : "NO") << "\n";
		return;
	}
	/*
	The remaining odd balances (1,3,7,9) immediately turn into even ones. The even remainders (2,4,6,8) change in a cycle, while the array element increases by 20 in 4 operations. Thus, we will apply the operation to each element of the array until its remainder modulo 10 becomes, for example, 2, and then check that the array does not contain both remainders 2 and 12 modulo 20.

	 */
	bool flag_2 = false, flag_12 = false;
	forv(num, arr)
	{
		ll temp = num;
		while (temp % 10 != 2)
		{
			temp = (temp + (temp % 10));
		}
		if(temp%20 == 2){
			flag_2 = true;
		}
		else{
			flag_12 = true;
		}
	}
	// this means that not all elements are equal
	if (flag_2 && flag_12)
	{
		cout << "NO" << "\n";
		return;
	}

	cout << "YES" << "\n";
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