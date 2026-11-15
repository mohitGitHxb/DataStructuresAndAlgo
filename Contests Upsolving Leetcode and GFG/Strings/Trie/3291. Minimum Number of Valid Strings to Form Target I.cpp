#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define bigInt __int128_t
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
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

struct TrieNode
{
    TrieNode *children[26] = {nullptr};
    bool isEnd = false;
    bool containsKey(char ch)
    {
        return children[ch - 'a'] != nullptr;
    }
    TrieNode *get(char ch)
    {
        return children[ch - 'a'];
    }
    bool putKey(char ch)
    {
        return children[ch - 'a'] = new TrieNode();
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
You are given an array of strings words and a string target.

A string x is called valid if x is a
prefix
of any string in words.

Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.

A prefix of a string is a substring that starts from the beginning of the string and extends to any point within it.



Example 1:

Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"

Output: 3

Explanation:

The target string can be formed by concatenating:

    Prefix of length 2 of words[1], i.e. "aa".
    Prefix of length 3 of words[2], i.e. "bcd".
    Prefix of length 3 of words[0], i.e. "abc".

Example 2:

Input: words = ["abababab","ab"], target = "ababaababa"

Output: 2

Explanation:

The target string can be formed by concatenating:

    Prefix of length 5 of words[0], i.e. "ababa".
    Prefix of length 5 of words[0], i.e. "ababa".

@ Approach
&-> maintain a trie to efficiently look for prefixes quickly
&-> DO NOT create another search function for the trie to look for prefixes
&-> This has to be done while we are traversing the target string to optimize time complexity

~ Create trie using TrieNode* children[] not unordered_map<char,TrieNode*> children
~ Arrays are way faster than unordered_map

%-> For DP part it is simply try to partition it at every possible index (valid only if there exists a prefix of it)
     */
public:
    const uint32_t MOD = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    TrieNode *root;
    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (!node->containsKey(ch))
            {
                node->putKey(ch);
            }
            node = node->get(ch);
        }
        node->setEnd();
    }
    int minValidStrings(vector<string> &words, string &target)
    {
        root = new TrieNode();
        for (string &word : words)
            insert(word);
        vector<ll> dp(target.length() + 1, 1e9);
        dp[target.length()] = 0;
        for (int idx = target.length() - 1; idx >= 0; idx--)
        {
            TrieNode *node = root;
            for (int i = idx; i < target.length(); i++)
            {
                if (!node->containsKey(target[i]))
                    break;
                node = node->get(target[i]);
                dp[idx] = min<ll>(dp[idx], 1 + dp[i + 1]);
            }
        }
        return dp[0] == 1e9 ? -1 : dp[0];
    }
};

int main()
{
    Solution obj;
    return 0;
}