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
You are given a 0-indexed integer array nums of size n, and a 0-indexed integer array pattern of size m consisting of integers -1, 0, and 1.

A subarray nums[i..j] of size m + 1 is said to match the pattern if the following conditions hold for each element pattern[k]:

    nums[i + k + 1] > nums[i + k] if pattern[k] == 1.
    nums[i + k + 1] == nums[i + k] if pattern[k] == 0.
    nums[i + k + 1] < nums[i + k] if pattern[k] == -1.

Return the count of subarrays in nums that match the pattern.



Example 1:

Input: nums = [1,2,3,4,5,6], pattern = [1,1]
Output: 4
Explanation: The pattern [1,1] indicates that we are looking for strictly increasing subarrays of size 3. In the array nums, the subarrays [1,2,3], [2,3,4], [3,4,5], and [4,5,6] match this pattern.
Hence, there are 4 subarrays in nums that match the pattern.

Example 2:

Input: nums = [1,4,4,1,3,5,5,3], pattern = [1,0,-1]
Output: 2
Explanation: Here, the pattern [1,0,-1] indicates that we are looking for a sequence where the first number is smaller than the second, the second is equal to the third, and the third is greater than the fourth. In the array nums, the subarrays [1,4,4,1], and [3,5,5,3] match this pattern.
Hence, there are 2 subarrays in nums that match the pattern.


     */
public:
    Solution()
    {
        fast_read();
    }
    int allocateDiff(int a, int b)
    {
        if (a > b)
        {
            return 1;
        }
        else if (a < b)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    /*
    & Brute force O(N^3) not going to mention this as it is just pure implementation

    & The below solution is slightly optimized brute force however it is O(N^2) means TLE but the thing is this solution requires a lot of observation so added it as this concept might me useful in future

     */
    int countMatchingSubarrays(vector<int> &nums, vector<int> &pattern)
    {
        int n = sz(nums);
        int m = sz(pattern);
        int subarraySize = m + 1;
        vi diff(m);
        forsn(i, 1, m + 1)
        {
            diff[i - 1] = allocateDiff(nums[i], nums[i - 1]);
        }
        // print1dVector(diff);
        int count = 0;
        int j = m + 1;
        while (j < n)
        {
            int i = j - m;
            if (diff == pattern)
            {
                count++;
            }
            // anti clockwise rotating
            rotate(diff.begin(), diff.begin() + 1, diff.end());
            diff.back() = allocateDiff(nums[j], nums[j - 1]);
            // print1dVector(diff);
            j++;
        }
        if (diff == pattern)
        {
            count++;
        }
        return count;
    }
};

/* 
& KMP and Z-algo are the new trends in lc contests so don't missout on these
& converting the pattern array and the given nums to their string equivalent
& then simply running KMP algorithm to match the string (literally no efforts copy paste the snippet)


 */
class OPTIMAL_KMP_ALGO
{
public:
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
    char allocateDiff(int a, int b)
    {
        if (a > b)
        {
            return 'a';
        }
        else if (a < b)
        {
            return 'd';
        }
        else
        {
            return 's';
        }
    }
    int countMatchingSubarrays(vector<int> &nums, vector<int> &pattern)
    {
        string pString, nString;
        int n = nums.size(), m = pattern.size();
        for (int i = 0; i < m; i++)
        {
            if (pattern[i] == 1)
                pString.push_back('a');
            else if (pattern[i] == -1)
                pString.push_back('d');
            else
                pString.push_back('s');
        }

        for (int i = 1; i < n; i++)
        {
            nString.push_back(allocateDiff(nums[i], nums[i - 1]));
        }
        cout << nString;

        string joined = pString + '#' + nString;
        vector<int> lps = constructLPS(joined);
        int count = 0;

        // matching the lps array of the string not the pattern
        // at i = m there will be a '#' which divides the pattern and string that needs to be matched.
        for (int i = m; i < lps.size(); i++)
        {
            if (lps.at(i) == m)
                count++;
        }
        return count;
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}
