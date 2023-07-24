#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
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
#define fi first
#define se second
#define sz(x) ((ll)(x).size())

/*

@ The problem statement describes a scenario where you are given an array of n numbers, a number k, and a target mean value x. You need to determine if it is possible to multiply two distinct values in the array by k such that the mean of the resulting array is equal to x.

&   The provided solution uses a hash set to solve this problem. The function IsMean takes as input the number of elements in the array n, the value of k, the target mean value x, and a vector of integers representing the array.

&   First, it checks if there is only one element in the array, in which case it returns false since it is not possible to select two distinct indices. Then, it sorts the array and calculates its total sum. It also calculates the value of z, which represents the difference between the target sum (x * arr.size()) and the current sum of the array.

&   The function then iterates over all elements in the array. For each element, it calculates the value of first, which represents the difference between the value of the element multiplied by k and its original value. It then checks if there is a value in the hash set that, when added to first, equals z. If such a value exists, it means that it is possible to perform the operation and achieve the target mean, so it returns true. Otherwise, it inserts first into the hash set and continues to the next iteration.

&   If no pair of values is found that can achieve the target mean, the function returns false.

&   The time complexity of this solution is O(n log n), where n is the number of elements in the array, since it sorts the array. The space complexity is O(n), since it uses a hash set to store up to n values.

Here’s a step-by-step explanation of how the code works:

&- The function IsMean takes as input the number of elements in the array n, the value of k, the target mean value x, and a vector of integers representing the array.

&- If there is only one element in the array, it returns false since it is not possible to select two distinct indices.

&- It then sorts the array and calculates its total sum.

&- It also calculates the value of z, which represents the difference between the target sum (x * arr.size()) and the current sum of the array.

&- The function then iterates over all elements in the array.

&- For each element, it calculates the value of first, which represents the difference between the value of the element multiplied by k and its original value.

&- It then checks if there is a value in the hash set that, when added to first, equals z.

&- If such a value exists, it means that it is possible to perform the operation and achieve the target mean, so it returns true.

&- Otherwise, it inserts first into the hash set and continues to the next iteration.

&- If no pair of values is found that can achieve the target mean, the function returns false.

 */

bool IsMean(int n, int k, int x, vector<int> &arr)
{
    if (n == 1)
    {
        return false;
    }
    sort(arr.begin(), arr.end());
    int totalSum = accumulate(arr.begin(), arr.end(), 0);
    int z = x * arr.size() - totalSum; //? use you braincells to get this formula (totalsum + extra needed) / number of elements = given mean (not actual mean)
    unordered_set<int> hs;
    for (int i = 0; i < n; i++)
    {
        int first = arr[i] * k - arr[i];
        if (hs.count(z - first))
        {
            return true;
        }
        else
        {
            hs.insert(first);
        }
    }
    return false;
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