#include <bits/stdc++.h>
using namespace std;
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
#define gc getchar_unlocked
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define forv(it, a) for (auto it : a)
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
typedef unordered_map<int, int, custom_hash> hmpi;
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
        In a mystic dungeon, n magicians are standing in a line. Each magician has an attribute that gives you energy. Some magicians can give you negative energy, which means taking energy from you.

You have been cursed in such a way that after absorbing energy from magician i, you will be instantly transported to magician (i + k). This process will be repeated until you reach the magician where (i + k) does not exist.

In other words, you will choose a starting point and then teleport with k jumps until you reach the end of the magicians' sequence, absorbing all the energy during the journey.

You are given an array energy and an integer k. Return the maximum possible energy you can gain.



Example 1:

Input: energy = [5,2,-10,-5,1], k = 3

Output: 3

Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.

Example 2:

Input: energy = [-2,-3,-1], k = 2

Output: -1

Explanation: We can gain a total energy of -1 by starting from magician 2.

     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }

    int maximumEnergy(vi &energy, int k)
    {
        vi dp(sz(energy));
        forn(i, sz(energy))
        {
            if (i - k >= 0)
            {
                dp[i] = max(dp[i - k] + energy[i], energy[i]); // at each point we have two options
                //& greedy approach
                //& either we take the previous energy and jump at current location and add the current energy
                //& or maybe start the jump from here itself 

                //% out of these two options we take the maximum of them
            }
            else
            {
                dp[i] = energy[i];
            }
        }
        int ans = INT_MIN;
        int start = max((int)energy.size() - k, 0);
        //& as we can notice energies in range [n-k,n] can only be taken once as after jumping we will reach the end
        //& so we just need to maximise the answer
        //& basically find the maximum value in dp[n-k...n] and energy[n-k...n]
        forsn(i, start, sz(energy))
        {
            ans = max({ans, dp[i], energy[i]});
        }
        return static_cast<int>(ans);
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\n\n\tProgram ended\n\n";
    return 0;
}
