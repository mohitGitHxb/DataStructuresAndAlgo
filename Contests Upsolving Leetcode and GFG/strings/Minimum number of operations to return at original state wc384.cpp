#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
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
        print1dVector<T>(i);
    }
    cout << "]\n";
}
template <class T = int, class U = int>
void printHashmap(const unordered_map<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int, class U = int>
void printMap(const map<T, U> &mp)
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
void printHashSet(const unordered_set<T> &mp)
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
template <class T = int, class U = int>
void printHashMultimap(const unordered_multimap<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int>
void printMultiHashSet(const unordered_multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
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

class DisjointSet
{
public:
    vector<int> rank, parent, size;
    DisjointSet(int n)
    {
        rank.resize(n + 1);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i < n + 1; i++)
        {
            parent.at(i) = i;
            size.at(i) = 1;
        }
    }

    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ultimateParentU = findUPar(u);
        int ultimateParentV = findUPar(v);
        if (ultimateParentU == ultimateParentV)
            return;
        if (rank.at(ultimateParentU) < rank.at(ultimateParentV))
        {
            parent.at(ultimateParentU) = ultimateParentV;
        }
        else if (rank.at(ultimateParentV) < rank.at(ultimateParentU))
        {
            parent.at(ultimateParentV) = ultimateParentU;
        }
        else
        {
            parent.at(ultimateParentV) = parent.at(ultimateParentU);
            rank.at(ultimateParentU)++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ultimateParentU = findUPar(u);
        int ultimateParentV = findUPar(v);
        if (ultimateParentU == ultimateParentV)
            return;
        if (size.at(ultimateParentU) < size.at(ultimateParentV))
        {
            parent.at(ultimateParentU) = ultimateParentV;
            size.at(ultimateParentV) += size.at(ultimateParentU);
        }
        else
        {
            parent.at(ultimateParentV) = ultimateParentU;
            size.at(ultimateParentU) += size.at(ultimateParentV);
        }
    }
};

class Solution
{
private:
    /*
        You are given a 0-indexed string word and an integer k.

At every second, you must perform the following operations:

    Remove the first k characters of word.
    Add any k characters to the end of word.

Note that you do not necessarily need to add the same characters that you removed. However, you must perform both operations at every second.

Return the minimum time greater than zero required for word to revert to its initial state.



Example 1:

Input: word = "abacaba", k = 3
Output: 2
Explanation: At the 1st second, we remove characters "aba" from the prefix of word, and add characters "bac" to the end of word. Thus, word becomes equal to "cababac".
At the 2nd second, we remove characters "cab" from the prefix of word, and add "aba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
It can be shown that 2 seconds is the minimum time greater than zero required for word to revert to its initial state.

Example 2:

Input: word = "abacaba", k = 4
Output: 1
Explanation: At the 1st second, we remove characters "abac" from the prefix of word, and add characters "caba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
It can be shown that 1 second is the minimum time greater than zero required for word to revert to its initial state.

Example 3:

Input: word = "abcbabcd", k = 2
Output: 4
Explanation: At every second, we will remove the first 2 characters of word, and add the same characters to the end of word.
After 4 seconds, word becomes equal to "abcbabcd" and reverts to its initial state.
It can be shown that 4 seconds is the minimum time greater than zero required for word to revert to its initial state.


     */
public:
    const int mod = 1e9 + 7;

    Solution()
    {
        fast_read();
    }
    int minimumTimeToInitialState_BruteForce(string word, int k)
    {
        // abacaba -> caba _ _ _
        //& now match abacaba with caba and see if whole caba matches with abacaba (ans is no here)
        //& caba_ _ _ --> a _ _ _ _ _ _ again perform matching
        //? _ _ _ _ _ _ _ (all blanks means yes it is possible now hence return ceil(n/k))

        //% Answer lies in the range [1,ceil(n/k)];  we are kind of matching a SUFFIX with a PREFIX (lps array intuition possible KMP)

        int n = word.size();
        string original = word;
        int pos = 0;
        for (int i = 1; i <= (n + k - 1) / k; i++)
        {
            if (pos >= word.length())
            {
                break;
            }
            pos = pos + k;
            int j = pos, k = 0;
            deb(j);
            while (j < word.size())
            {
                if (word[j] != original[k])
                {
                    break;
                }
                else
                {
                    j++;
                    k++;
                }
            }
            if (j == word.size())
            {
                return i;
            }
        }
        return (n + k - 1) / k;
    }

    /* 
    & LPS array optimization to match the pattern
    
     */
    vector<int> constructLPS(const string &s)
    {
        vector<int> lps(s.size());
        for (int i = 1; i < s.size(); i++)
        {
            int prevIdx = lps.at(i - 1);
            // If the current character does not match with the character at the previous index,
            // then update the previous index to the index of the longest proper prefix which is also suffix.
            while (prevIdx > 0 && s.at(i) != s.at(prevIdx))
            {
                prevIdx = lps.at(prevIdx - 1);
            }
            // If the current character matches with the character at the previous index,
            // then increment the length of the longest proper prefix which is also suffix.
            lps.at(i) = prevIdx + (s.at(i) == s.at(prevIdx));
        }
        return lps;
    }
    int minimumTimeToInitialState(string word, int k)
    {
        int n = word.size();
        vi lps = constructLPS(word);
        int maxLen = lps.back();
        while (maxLen > 0 && (n - maxLen) % k != 0)
        {
            maxLen = lps[maxLen - 1];
        }
        return (n - maxLen) % k == 0 ? (n - maxLen) / k : (n + k - 1) / k;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
