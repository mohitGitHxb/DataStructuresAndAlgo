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
class TrieNode
{
private:
    struct Node
    {
        Node *links[26];
        int cntEndWith = 0;
        int cntPrefix = 0;

        bool containsKey(char ch)
        {
            return (links[ch - 'a'] != nullptr);
        }

        Node *get(char ch)
        {
            return links[ch - 'a'];
        }

        void put(char ch, Node *node)
        {
            links[ch - 'a'] = node;
        }

        void increaseEnd()
        {
            cntEndWith++;
        }

        void increasePrefix()
        {
            cntPrefix++;
        }

        void deleteEnd()
        {
            cntEndWith--;
        }

        void reducePrefix()
        {
            cntPrefix--;
        }

        int getEnd()
        {
            return cntEndWith;
        }

        int getPrefix()
        {
            return cntPrefix;
        }
    };

    Node *root;

public:
    TrieNode()
    {
        root = new Node();
    }

    void insert(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    int countWordsEqualTo(string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
            }
            else
            {
                return 0;
            }
        }
        return node->getEnd();
    }

    int countWordsStartingWith(string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
            }
            else
            {
                return 0;
            }
        }
        return node->getPrefix();
    }

    void erase(string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
                node->reducePrefix();
            }
            else
            {
                return;
            }
        }
        node->deleteEnd();
    }
};
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
You are given an integer array nums of length n and a positive integer k.

The power of an array of integers is defined as the number of
subsequences
with their sum equal to k.

Return the sum of power of all subsequences of nums.

Since the answer may be very large, return it modulo 109 + 7.



Example 1:

Input: nums = [1,2,3], k = 3

Output: 6

Explanation:

There are 5 subsequences of nums with non-zero power:

    The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
    The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
    The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
    The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
    The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].

Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.

Example 2:

Input: nums = [2,3,3], k = 5

Output: 4

Explanation:

There are 3 subsequences of nums with non-zero power:

    The subsequence [2,3,3] has 2 subsequences with sum == 5: [2,3,3] and [2,3,3].
    The subsequence [2,3,3] has 1 subsequence with sum == 5: [2,3,3].
    The subsequence [2,3,3] has 1 subsequence with sum == 5: [2,3,3].

Hence the answer is 2 + 1 + 1 = 4.

Example 3:

Input: nums = [1,2,3], k = 7

Output: 0

Explanation: There exists no subsequence with sum 7. Hence all subsequences of nums have power = 0.

     */
public:
    const int mod = 1e9 + 7;
    vvl dp;
    vector<vvl> dpWithCount;
    Solution()
    {
        fast_read();
    }
    ll countSubsequenceWithSumK(vi &nums, int k, int idx)
    {
        if (k < 0)
            return 0;
        if (idx == nums.size())
        {
            return k == 0;
        }
        if (dp[idx][k] != -1)
            return dp[idx][k];
        ll take = countSubsequenceWithSumK(nums, k - nums[idx], idx + 1);
        ll notTake = countSubsequenceWithSumK(nums, k, idx + 1);
        return dp[idx][k] = (take + notTake) % mod;
    }
    void generateSubsequence(vector<int> &nums, int idx, vi &ds, vector<vi> &ans)
    {
        if (idx == nums.size())
        {
            ans.push_back(ds);
            return;
        }
        ds.push_back(nums[idx]);
        generateSubsequence(nums, idx + 1, ds, ans);
        ds.pop_back();
        generateSubsequence(nums, idx + 1, ds, ans);
    }
    int sumOfPower_BruteForce(vector<int> &nums, int k)
    {
        vector<vi> ans;
        vi ds;
        generateSubsequence(nums, 0, ds, ans);
        int sum = 0;
        for (auto v : ans)
        {
            sum += countSubsequenceWithSumK(v, k, 0);
        }
        return sum % mod;
    }
    int sumOfPower_better(vector<int> &nums, int k)
    {
        vvi ans;
        vi ds;
        generateSubsequence(nums, 0, ds, ans);
        int sum = 0;
        for (auto v : ans)
        {
            dp.clear();
            dp.resize(v.size() + 1, vl(k + 1, -1));
            sum += countSubsequenceWithSumK(v, k, 0);
        }
        return sum % mod;
    }

    //* Optimized approach T.C : O(N^2*k) * logN
    ll countSubsequenceWithSumK_withCount(vi &nums, int k, int count, int idx)
    {
        //% Count stores number of elements that are a part of current subsequence with sum == k
        if (k < 0)
            return 0;
        if (idx == nums.size())
        {
            if (k == 0)
                return binaryExponentiation(2, sz(nums) - count, mod);
            else
                return 0;
        }
        if (dpWithCount[idx][count][k] != -1)
            return dpWithCount[idx][count][k];
        ll take = countSubsequenceWithSumK_withCount(nums, k - nums[idx], count + 1, idx + 1);
        ll notTake = countSubsequenceWithSumK_withCount(nums, k, count, idx + 1);
        return dpWithCount[idx][count][k] = (take + notTake) % mod;
    }
    int sumOfPower_optimized(vector<int> &nums, int k)
    {
        //% We can eliminate the state(count) from the dp array by simply replacing below line
        //@ ll notTake = countSubsequenceWithSumK_withCount(nums, k, count, idx + 1); to ll notTake = 2 *  countSubsequenceWithSumK_withCount(nums, k, count, idx + 1);
        //& The reason why 2 * countSubsequenceWithSumK_withCount(nums, k, count, idx + 1) works because of two not take conditions
        //& This is a standard way to approach problems like subset of a subset of the original array
        //& Reason for 2 is: not taking into subset 1 + taking into subset 1 but not in subset 2;
        dpWithCount.resize(nums.size() + 1, vvl(k + 1, vl(k + 1, -1)));
        return countSubsequenceWithSumK_withCount(nums, k, 0, 0) % mod;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    return 0;
}
