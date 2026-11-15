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
You are given an array arr of size n consisting of non-empty strings.

Find a string array answer of size n such that:

    answer[i] is the shortest
    substring
    of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the
    lexicographically smallest
    . And if no such substring exists, answer[i] should be an empty string.

Return the array answer.



Example 1:

Input: arr = ["cab","ad","bad","c"]
Output: ["ab","","ba",""]
Explanation: We have the following:
- For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
- For the string "ad", there is no substring that does not occur in any other string.
- For the string "bad", the shortest substring that does not occur in any other string is "ba".
- For the string "c", there is no substring that does not occur in any other string.

Example 2:

Input: arr = ["abc","bcd","abcd"]
Output: ["","","abcd"]
Explanation: We have the following:
- For the string "abc", there is no substring that does not occur in any other string.
- For the string "bcd", there is no substring that does not occur in any other string.
- For the string "abcd", the shortest substring that does not occur in any other string is "abcd".



     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    static bool cmp(string a, string b)
    {
        if (a.size() != b.size())
        {
            return a.size() < b.size();
        }
        return a < b;
    }
    vsr shortestSubstrings(vsr &arr)
    {
        vsr ans(arr.size(), "");
        vector<vsr> substrings(arr.size());
        vector<unordered_set<string>> sets(arr.size());
        forn(i, sz(arr))
        {
            forn(j, sz(arr[i]))
            {
                string temp;
                forsn(k, j, sz(arr[i]))
                {
                    temp.pb(arr[i][k]);
                    substrings[i].pb(temp);
                    sets[i].insert(temp);
                }
            }
            sort(all(substrings[i]), cmp);
        }
        // customPrint<string>(substrings);
        forn(i, sz(substrings))
        {
            forn(j, sz(substrings[i]))
            {
                bool flag = true;
                forn(k, sz(substrings))
                {
                    if (k == i)
                        continue;
                    if (sets[k].count(substrings[i][j]))
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    ans[i] = substrings[i][j];
                    break;
                }
            }
        }
        return ans;
    }
};

//* TRIE SOLUTION OPTIMIZED APPROACH
/*
class Solution {
public:
    class Node {
        public:
            Node* child[26];
            int count = 0;

    };

    void add(Node* head, string s, int ind){
        Node* ptr = head;
        for(int i = ind; i < s.size(); ++i){
            int c = s[i] - 'a';
            if(ptr->child[c] == NULL) ptr->child[c] = new Node();
            ptr = ptr->child[c];
            ptr->count++;
        }
    }

    void remove(Node* head, string s, int ind){
        Node* ptr = head;
        for(int i = ind; i < s.size(); ++i){
            ptr = ptr->child[s[i] - 'a'];
            ptr->count--;
        }
    }

    string check(Node* head, string s, int ind){
        Node* ptr = head;
        string ans = "";
        for(int i = ind; i < s.size(); ++i){
            int c = s[i] - 'a';
            if(ptr->child[c] == NULL) return ans;
            ans += s[i];
            ptr = ptr->child[c];
            if(ptr->count < 1) return ans;
        }
        return s + s;
    }

    vector<string> shortestSubstrings(vector<string>& arr) {
        vector<string> ans;
        Node* head = new Node();
        for(auto s: arr){             // Add all the strings to the trie
            for(int i = 0; i < s.size(); ++i) add(head, s, i);
        }
        for(auto s: arr){
            string res = s + s;
            for(int i = 0; i < s.size(); ++i) remove(head, s, i);  // remove the current string from trie
            for(int i = 0; i < s.size(); ++i){                     // iterate over each substring starting at i th and check for the uncommon string length
                string t = check(head, s, i);
                if(t.size() < res.size() || (t.size() == res.size() && t < res) ) res = t;  // store it in result if length is less or lexicographically smaller if equal
            }
            ans.push_back((res.size() <= s.size())?res: "");        // add res to final answer
            for(int i = 0; i < s.size(); ++i) add(head, s, i);      // add back the current string to the trie
        }
        return ans;
    }
};
 */
class Solution
{
public:
    class Node
    {
    public:
        Node *child[26];
        int count = 0;
    };

    void add(Node *head, string s, int ind)
    {
        Node *ptr = head;
        for (int i = ind; i < s.size(); ++i)
        {
            int c = s[i] - 'a';
            if (ptr->child[c] == NULL)
                ptr->child[c] = new Node();
            ptr = ptr->child[c];
            ptr->count++;
        }
    }

    void remove(Node *head, string s, int ind)
    {
        Node *ptr = head;
        for (int i = ind; i < s.size(); ++i)
        {
            ptr = ptr->child[s[i] - 'a'];
            ptr->count--;
        }
    }

    string check(Node *head, string s, int ind)
    {
        Node *ptr = head;
        string ans = "";
        for (int i = ind; i < s.size(); ++i)
        {
            int c = s[i] - 'a';
            if (ptr->child[c] == NULL)
                return ans;
            ans += s[i];
            ptr = ptr->child[c];
            if (ptr->count < 1)
                return ans;
        }
        return s + s;
    }

    vector<string> shortestSubstrings(vector<string> &arr)
    {
        vector<string> ans;
        Node *head = new Node();
        for (auto s : arr)
        { // Add all the strings to the trie
            for (int i = 0; i < s.size(); ++i)
                add(head, s, i);
        }
        for (auto s : arr)
        {
            string res = s + s;
            for (int i = 0; i < s.size(); ++i)
                remove(head, s, i); // remove the current string from trie
            for (int i = 0; i < s.size(); ++i)
            { // iterate over each substring starting at i th and check for the uncommon string length
                string t = check(head, s, i);
                if (t.size() < res.size() || (t.size() == res.size() && t < res))
                    res = t; // store it in result if length is less or lexicographically smaller if equal
            }
            ans.push_back((res.size() <= s.size()) ? res : ""); // add res to final answer
            for (int i = 0; i < s.size(); ++i)
                add(head, s, i); // add back the current string to the trie
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
