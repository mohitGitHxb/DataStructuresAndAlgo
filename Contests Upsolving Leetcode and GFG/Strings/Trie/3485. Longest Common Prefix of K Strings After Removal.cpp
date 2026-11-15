#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
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
static int init = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

struct TrieNode
{
    TrieNode *children[26] = {nullptr};
    bool isEnd = false;
    int count = 0;
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
};

class Solution
{
private:
    /*
You are given an array of strings words and an integer k.

For each index i in the range [0, words.length - 1], find the length of the longest common

among any k strings (selected at distinct indices) from the remaining array after removing the ith element.

Return an array answer, where answer[i] is the answer for ith element. If removing the ith element leaves the array with fewer than k strings, answer[i] is 0.



Example 1:

Input: words = ["jump","run","run","jump","run"], k = 2

Output: [3,4,4,3,4]

Explanation:

    Removing index 0 ("jump"):
        words becomes: ["run", "run", "jump", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
    Removing index 1 ("run"):
        words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
    Removing index 2 ("run"):
        words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
    Removing index 3 ("jump"):
        words becomes: ["jump", "run", "run", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
    Removing index 4 ("run"):
        words becomes: ["jump", "run", "run", "jump"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).

    @ Approach
    Insert each string into the Trie while counting the occurrences of each prefix length.
    Use a multiset (prefixLengths) to keep track of valid prefix lengths that appear in at least k strings.
    Remove each string temporarily, check the maximum prefix length in st, and then reinsert the string.

     */
public:
    TrieNode *root;
    multiset<int> prefixLengths;
    int minOccurrences;
    void insert(const string &word)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            const char ch = word[i];
            if (!node->containsKey(ch))
            {
                node->putKey(ch);
            }
            node = node->get(ch);
            node->count++;
            if (node->count == minOccurrences)
            {
                prefixLengths.insert(i + 1);
            }
        }
    }
    void erase(const string &word)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            const char ch = word[i];
            node = node->get(ch);

            // remove prefix length if it was stored in the multiset
            if (node->count == minOccurrences)
            {
                prefixLengths.erase(prefixLengths.find(i + 1));
            }
            node->count--;
        }
    }
    vector<int> longestCommonPrefix(vector<string> &words, int k)
    {
        root = new TrieNode();
        minOccurrences = k;
        const int n = words.size();
        vector<int> result(n);
        for (int i = 0; i < n; i++)
        {
            insert(words[i]);
        }
        for (int i = 0; i < n; i++)
        {
            erase(words[i]);
            result[i] = (!prefixLengths.empty()) ? *prefixLengths.rbegin() : 0;
            insert(words[i]);
        }
        return result;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    vector<string> words = {"aba", "bcb", "ece", "aa", "e"};
    vector<vector<int>> queries = {{0, 2}, {1, 4}, {1, 1}};
    obj.vowelStrings(words, queries);
    // Test cases for local testing
    return 0;
}
#endif