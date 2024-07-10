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
#pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC target("avx,avx2,fma")
#define gc getchar_unlocked
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define mp make_pair
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
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define forv(it, a) for (auto &it : a)
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
typedef unordered_map<int, int, custom_hash> hmpii;
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
void customPrint(const unordered_map<T, U> &mp)
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
void customPrint(const unordered_set<T> &mp)
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

class Fenwick
{
private:
    vector<long long> bit, a;
    long long n;

public:
    Fenwick(long long n)
    {
        this->n = n;
        bit.resize(n + 1);
    }
    Fenwick(vector<long long> &arr)
    {
        n = arr.size();
        bit.resize(n + 1);
        this->a = arr;
        build(a);
    }
    void build(vector<long long> &arr)
    {
        for (long long i = 0; i < n; i++)
        {
            update(i + 1, arr.at(i));
        }
    }
    long long query(long long idx)
    {
        long long sum = 0;
        while (idx > 0)
        {
            sum += bit.at(idx);
            idx -= idx & (-idx); // sets the last set bit to 0
        }
        return sum;
    }
    void update(long long idx, long long val)
    {
        while (idx <= n)
        {
            bit.at(idx) += val;
            idx += idx & (-idx); // sets the last unset bit to 1
        }
    }
    void replace(long long idx, long long val)
    {
        update(idx + 1, -a.at(idx) + val);
        a.at(idx) = val;
    }
    void printBitVector()
    {
        for (long long i = 1; i <= n; i++)
        {
            cout << bit.at(i) << " ";
        }
        cout << "\n";
    }
    void rangeUpdate(long long l, long long r, long long val)
    {
        update(l, val);
        update(r + 1, -val);
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
        There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.

You are given a 2D array queries, which contains two types of queries:

    For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
    For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.

Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.
     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    vector<bool> getResults(vvi &queries)
    {
        mpi space;           // <coordinate or distance(from origin), size of maximum block that can be fit till that coordinate>
        space.emplace(0, 0); // initial point of the number line;
        space.emplace(INT_MAX, INT_MAX);
        vector<bool> res;
        forv(query, queries)
        {
            int type = query[0];
            int coord = query[1];
            if (type == 1)
            {
                // insert the coordinate and update the maximum gap/size of block that can be fit till that coordinate for all coordinates > coord
                auto it = space.emplace(coord, INT_MIN).first;
                auto justPrevious = prev(it);
                // space[coord] = max(justPrevious->second, coord - justPrevious->first);

                /*
                % Update all the coordinates > coord
                % if gap between two consecutive coordinates become same break the loop because it'll not affect the answer even if we update till infinity

                 */
                while (it != space.end() && justPrevious->second != it->second)
                {
                    it->second = max(justPrevious->second, it->first - justPrevious->first);
                    justPrevious = it++;
                }
            }
            else
            {
                /*
                @ TYPE-2 query handling
                & Get the coordinate just smaller than given coord (say c)
                & Get the maximum gap stored at that coordinate c
                & check if the gap is >= sz OR coord - c >= sz

                 */
                auto it = space.upper_bound(coord);
                advance(it, -1);
                int gap = coord - it->first;
                int sz = query[2];
                res.push_back(gap >= sz || it->second >= sz);
            }
        }
        return res;
    }

    //@ Fenwick Tree solution

    class FenwickMaximum
    {
    private:
        vector<int> bit, a;
        int n;

    public:
        FenwickMaximum(int n)
        {
            this->n = n;
            bit.resize(n + 1);
        }
        int query(int idx)
        {
            int maxAns = 0;
            while (idx > 0)
            {
                maxAns = max(maxAns, bit.at(idx));
                idx -= idx & (-idx); // sets the last set bit to 0
            }
            return maxAns;
        }
        void update(int idx, int val)
        {
            while (idx <= n)
            {
                bit.at(idx) = max(bit.at(idx), val); // max query
                idx += idx & (-idx);                 // sets the last unset bit to 1
            }
        }
    };
    vector<bool> getResults(vvi &queries)
    {
        /*
        @ Fenwick tree approach
        & first we have seen already that we need to perform updates at every points (maximum available gap) whenever we insert a new element
        & However doing this will require range updates like segment tree with lazy propagation
        & Now since we are kind of finding maximum in a range we can make use of fenwick tree but instead of going left to right
        & we go backwards from right to left because inserting new element will decrease the gap between two points
        % so we instead place all the obstacles first then try to remove them (going backwards) and make point query updates

        ^ Also see the constraints
        Constraints:

    1 <= queries.length <= 15 * 104
    2 <= queries[i].length <= 3
    1 <= queries[i][0] <= 2
    1 <= x, sz <= min(5 * 1e4, 3 * queries.length)
         */
        int n = min(5 * 10000, 3 * (int)queries.size()) + 1;
        si obstaclePoints;
        obstaclePoints.emplace(0);
        obstaclePoints.emplace(n);
        FenwickMaximum ft(n);
        vector<bool> results;
        //? place all obstacles as we'll be moving backwards
        forv(query, queries)
        {
            int type = query[0];
            int coord = query[1];
            if (type == 1)
            {
                obstaclePoints.emplace(coord);
            }
        }
        tr(it, obstaclePoints)
        {
            if (it == obstaclePoints.begin())
                continue;
            auto prevIterator = prev(it);
            int gapSize = *it - *prevIterator;
            int location = *it;
            ft.update(location, gapSize);
        }
        rforn(queryIdx, sz(queries) - 1)
        {
            auto query = queries[queryIdx];
            int type = query[0];
            int coord = query[1];
            if (type == 1)
            {
                auto it = obstaclePoints.find(coord);
                auto prevIt = prev(it);
                auto nextIt = next(it);
                obstaclePoints.erase(it);
                ft.update(*nextIt, *nextIt - *prevIt); //^ update the maximum gap for next iterator because we are removing the current block at current coordinate coord
                //^ We are doing this as we are going backwards means we have placed all the obstacles
            }
            else
            {
                int sz = query[2];
                auto it = obstaclePoints.upper_bound(coord);
                auto prevIt = prev(it);
                int gapSize1 = coord - *prevIt;
                int gapSize2 = ft.query(*prevIt);
                results.push_back(gapSize1 >= sz || gapSize2 >= sz);
            }
        }
        reverse(all(results)); // ^ we are going backwards so we need to reverse the results
        return results;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\n\n\tProgram ended\n\n";
    return 0;
}
