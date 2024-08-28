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
#define deb(x) cout << #x << "=" << x << endl
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
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vvl> vvvl;
template <class T = pii>
using oset =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T = pii>
using mset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
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
    cout << t << " ";
}

template <class T = int>
void customPrint(const vector<T> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const vector<vector<T>> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int, class U = int>
void customPrint(const pair<T, U> &p)
{
    cout << "{" << customPrint(p.first) << ":";
    customPrint(p.second);
    cout << "}\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_map<T, U, custom_hash> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":";
        customPrint(i.second);
        cout << "}\n";
    }
    cout << "]\n";
}

template <class T = int, class U = int>
void customPrint(const map<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":";
        customPrint(i.second);
        cout << "}\n";
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const set<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const unordered_set<T, custom_hash> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(priority_queue<T> pq)
{
    cout << "[";
    while (!pq.empty())
    {
        customPrint(pq.top());
        pq.pop();
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(stack<T> st)
{
    cout << "[";
    while (!st.empty())
    {
        customPrint(st.top());
        st.pop();
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(queue<T> q)
{
    cout << "[";
    while (!q.empty())
    {
        customPrint(q.front());
        q.pop();
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(deque<T> dq)
{
    cout << "[";
    for (auto &i : dq)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_multimap<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":";
        customPrint(i.second);
        cout << "}\n";
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const unordered_multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
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

class Solution
{
private:
    /*
You are given an m x n binary matrix grid.

A row or column is considered palindromic if its values read the same forward and backward.

You can flip any number of cells in grid from 0 to 1, or from 1 to 0.

Return the minimum number of cells that need to be flipped to make all rows and columns palindromic, and the total number of 1's in grid divisible by 4.



Example 1:

Input: grid = [[1,0,0],[0,1,0],[0,0,1]]

Output: 3

Explanation:

Example 2:

Input: grid = [[0,1],[0,1],[0,0]]

Output: 2

Explanation:

Example 3:

Input: grid = [[1],[1]]

Output: 2

Identify Symmetry: The goal is to make the grid palindromic, meaning each row and column should read the same forwards and backwards. To do this, focus on pairs of cells that are symmetrically opposite relative to the center of the grid.

Count and Compare Symmetric Cells: For each cell in the top-left quadrant, find its three symmetric counterparts in the other quadrants (top-right, bottom-left, and bottom-right). Count the number of 1's among these four cells.

Calculate Minimum Flips: Based on the count of 1's, determine the minimum number of flips required to make all four cells the same (either all 0's or all 1's). This is done by choosing the smaller of the number of 1's or the number of 0's to flip.

Handle Edge and Center Cases: Separate logic is used for the center row, center column, and the very center element (if the grid dimensions are odd) to ensure they also become palindromic.

Adjust for Odd 1-Pairs: If there's an odd number of symmetrical 1-pairs across the middle row or column, an additional flip might be necessary to make the total number of 1's divisible by 4.
     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    int minFlips(vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid.front().size();
        int requiredMoves = 0;
        int count1pairs = 0;
        int zeroOnePairs = 0;
        // Loop to handle the four corners (general cases)
        for (int i = 0; i < rows / 2; i++)
        {
            for (int j = 0; j < cols / 2; j++)
            {
                int a = grid[i][j];
                int b = grid[rows - i - 1][j];
                int c = grid[i][cols - j - 1];
                int d = grid[rows - i - 1][cols - j - 1];
                int sum = a + b + c + d;
                requiredMoves += min(4 - sum, sum);
            }
        }
        // Loop to handle the middle row if the number of rows is odd
        if (rows % 2 == 1)
        {
            int middleRow = rows / 2;
            for (int j = 0; j < cols / 2; j++)
            {
                if (grid[middleRow][j] != grid[middleRow][cols - j - 1])
                {
                    requiredMoves++;
                    zeroOnePairs++;
                }
                else if (grid[middleRow][j] == 1)
                {
                    count1pairs++;
                }
            }
        }
        // Loop to handle the middle column if the number of columns is odd
        if (cols % 2 == 1)
        {
            int middleCol = cols / 2;
            for (int i = 0; i < rows / 2; i++)
            {
                if (grid[i][middleCol] != grid[rows - i - 1][middleCol])
                {
                    requiredMoves++;
                    zeroOnePairs++;
                }
                else if (grid[i][middleCol] == 1)
                {
                    count1pairs++;
                }
            }
        }
        // Center element case (for odd-sized grids)
        if (rows % 2 == 1 && cols % 2 == 1)
        {
            int centerRow = rows / 2;
            int centerCol = cols / 2;
            if (grid[centerRow][centerCol] == 1)
            {
                requiredMoves++;
            }
        }
        // If there are an odd number of 1-pairs, adjust required moves
        if (count1pairs % 2 > zeroOnePairs)
        {
            requiredMoves += 2;
        }

        return requiredMoves;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;

    cout << "\nProgram Started\n\n";
    return 0;
}
