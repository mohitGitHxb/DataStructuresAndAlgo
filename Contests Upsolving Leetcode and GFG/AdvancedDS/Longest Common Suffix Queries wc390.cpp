#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl

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
        //&- arr is of size n + 1 (1 based indexed);
        for (long long i = 1; i <= n; i++)
        {
            update(i, arr.at(i));
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
    };
    void update(long long idx, long long val)
    {
        while (idx <= n)
        {
            bit.at(idx) += val;
            idx += idx & (-idx); // sets the last unset bit to 1
        }
    };
    void replace(long long idx, long long val)
    {
        update(idx, -a.at(idx) + val);
        a.at(idx) = val;
    };
};
/*
% Use unordered_map instead of Node* links[26]; because it is much better for wider range of characters.

 */
struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    bool isEnd = false;
    int minIdx = -1;
    int minLen = INT_MAX;
    bool containsKey(char ch)
    {
        return children.count(ch);
    }
    TrieNode(int minIdx, int minLen)
    {
        this->minIdx = minIdx;
        this->minLen = minLen;
    }
    TrieNode *get(char ch)
    {
        return children[ch];
    }
    void put(char ch, TrieNode *node)
    {
        children[ch] = node;
    }
    void setEnd()
    {
        isEnd = true;
    }
};

class Solution
{
private:
    /*
You are given two arrays of strings wordsContainer and wordsQuery.

For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.

Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].



Example 1:

Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]

Output: [1,1,1]

Explanation:

Let's look at each wordsQuery[i] separately:

    For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
    For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
    For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.

Example 2:

Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]

Output: [2,0,2]

Explanation:

Let's look at each wordsQuery[i] separately:

    For wordsQuery[0] = "gh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
    For wordsQuery[1] = "acbfgh", only the string at index 0 shares the longest common suffix "fgh". Hence it is the answer, even though the string at index 2 is shorter.
    For wordsQuery[2] = "acbfegh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.


     */
public:
    TrieNode *root;
    Solution()
    {
        root = new TrieNode(-1, INT_MAX);
    }
    void insert(string &word, int idx)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                node->put(word[i], new TrieNode(idx, word.size()));
                node = node->get(word[i]);
            }
            else
            {
                node = node->get(word[i]);
                if (node->minLen > word.size())
                {
                    node->minIdx = idx;
                    node->minLen = word.size();
                }
            }
        }
    }
    int search(string &word)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
            }
            else
            {
                break;
            }
        }
        return node->minIdx;
    }
    vector<int> stringIndices(vector<string> &wordsContainer, vector<string> &wordsQuery)
    {
        vector<int> ans;
        /*
        & Maintain trie ds with minLen and minIdx if a word has same prefix(suffix here because we'll reverse all the words before hand) check if it has smaller length if yes then update the minLen as well as minIdx

        & Insert all the words from wordsContainer before hand to to compute the suffix for queries.

        & Search according to the longest common suffix and return the minimum index.

        * Overall time complexity is roughly O(N + M);
         */
        for (auto &it : wordsContainer)
        {
            reverse(it.begin(), it.end());
        }
        for (auto &it : wordsQuery)
        {
            reverse(it.begin(), it.end());
        }
        for (int i = 0; i < wordsContainer.size(); i++)
        {
            if (wordsContainer[i].length() < root->minLen)
            {
                root->minLen = wordsContainer[i].length();
                root->minIdx = i;
            }
            insert(wordsContainer[i], i);
        }
        for (int i = 0; i < wordsQuery.size(); i++)
        {
            ans.push_back(search(wordsQuery[i]));
        }
        return ans;
    }
};
