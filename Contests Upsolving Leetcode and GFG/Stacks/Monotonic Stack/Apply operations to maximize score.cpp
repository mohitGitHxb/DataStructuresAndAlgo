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

    Intuition:
        The goal is to maximize the score by choosing subarrays and elements as per the described rules.
        The code calculates the maximum possible score using a combination of prime factors and dynamic programming.

    Code Explanation:
        The function maximumScore takes a vector of positive integers nums and an integer k as input.
        It calculates the upper limit of the values in nums and initializes a vector prime to mark prime numbers and another vector primeScore to store prime scores.
        It uses the Sieve of Eratosthenes algorithm to calculate prime numbers and their scores.
        Two stacks (nextGreaterElement and prevGreaterOrEqualElement) are used to track the nearest greater and previous greater or equal elements for each element in the array.
        The tuples vector is created to store pairs of values and their indices. It is sorted in reverse order based on values and indices.
        The code iterates through the sorted tuples and calculates the operations needed for each element using the prevGreaterOrEqualElement and nextGreaterElement stacks.
        The score is updated based on the chosen element and operations, and the k value is decremented accordingly.
        The algorithm uses the pow function to calculate the power of an element modulo 10^9 + 7.
        The maximum score is returned.

    Time Complexity:
        The code involves several iterations, but the main time-consuming part is the sorting step, which takes O(n * log n) time.

    Space Complexity:
        The algorithm uses several vectors and stacks to store information, resulting in a space complexity of O(n).

    Hints:
        Calculate prime numbers and their scores using the Sieve of Eratosthenes.
        Use stacks to track nearest greater and previous greater or equal elements for each element.
        Sort the elements based on values and indices to prioritize element selection.
        Use the pow function to calculate powers modulo 10^9 + 7.

The code efficiently maximizes the score based on the given rules by considering prime scores and choosing the best elements from the array. It's a combination of mathematical calculations, prime factorization, and dynamic programming.
 */

int maximumScore(vector<int> &nums, int k)
{
    int n = nums.size();

    int upper = *max_element(nums.begin(), nums.end()) + 1;

    vector<bool> prime(upper, true);
    prime[0] = prime[1] = false;
    vector<int> primeScore(upper, 0);
    for (int i = 2; i < upper; i++)
    {
        if (prime[i])
        {
            for (int j = i; j < upper; j += i)
            {
                primeScore[j]++;
                prime[j] = false;
            }
        }
    }

    vector<int> nextGreaterElement(n, n);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && primeScore[nums[i]] >= primeScore[nums[s.top()]])
        {
            s.pop();
        }
        nextGreaterElement[i] = s.empty() ? n : s.top();
        s.push(i);
    }

    vector<int> prevGreaterOrEqualElement(n, -1);
    s = stack<int>();
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && primeScore[nums[i]] > primeScore[nums[s.top()]])
        {
            s.pop();
        }
        prevGreaterOrEqualElement[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }

    int res = 1;
    vector<pair<int, int>> tuples(n);
    for (int i = 0; i < n; i++)
    {
        tuples[i].first = nums[i];
        tuples[i].second = i;
    }
    sort(tuples.rbegin(), tuples.rend());
    for (const auto &[num, i] : tuples)
    {
        int operations = min((i - prevGreaterOrEqualElement[i]) * (nextGreaterElement[i] - i), k);
        res = (int)((1L * res * pow(num, operations)) % MOD);
        k -= operations;
        if (k == 0)
        {
            return res;
        }
    }

    return res;
}

int pow(int x, int n)
{
    int res = 1;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            res = (int)((1L * res * x) % MOD);
        }
        x = (int)((1L * x * x) % MOD);
        n /= 2;
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