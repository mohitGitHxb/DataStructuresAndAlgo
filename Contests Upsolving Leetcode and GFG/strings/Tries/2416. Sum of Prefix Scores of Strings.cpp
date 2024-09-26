#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
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

static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

struct TrieNode
{
    TrieNode *children[26] = {NULL};
    int countPrefix = 0;
    constexpr bool containsKey(char ch)
    {
        return children[ch - 'a'] != NULL;
    }
    void increaseCountPrefix()
    {
        countPrefix++;
    }
    constexpr int getCountPrefix()
    {
        return countPrefix;
    }
    TrieNode *get(char ch)
    {
        return children[ch - 'a'];
    }
    void putKey(char ch)
    {
        children[ch - 'a'] = new TrieNode();
    }
};

class Solution
{
private:
    /*
Example 1:

Input: words = ["abc","ab","bc","b"]
Output: [5,4,3,2]
Explanation: The answer for each string is the following:
- "abc" has 3 prefixes: "a", "ab", and "abc".
- There are 2 strings with the prefix "a", 2 strings with the prefix "ab", and 1 string with the prefix "abc".
The total is answer[0] = 2 + 2 + 1 = 5.
- "ab" has 2 prefixes: "a" and "ab".
- There are 2 strings with the prefix "a", and 2 strings with the prefix "ab".
The total is answer[1] = 2 + 2 = 4.
- "bc" has 2 prefixes: "b" and "bc".
- There are 2 strings with the prefix "b", and 1 string with the prefix "bc".
The total is answer[2] = 2 + 1 = 3.
- "b" has 1 prefix: "b".
- There are 2 strings with the prefix "b".
The total is answer[3] = 2.

Example 2:

Input: words = ["abcd"]
Output: [4]
Explanation:
"abcd" has 4 prefixes: "a", "ab", "abc", and "abcd".
Each prefix has a score of one, so the total is answer[0] = 1 + 1 + 1 + 1 = 4.

@Observations
&- USE Trie to optimally check prefixes
&- Store the count of words ending with each prefix (replace bool isEnd by int countPrefix)

     */
public:
    TrieNode *root;
    void insert(string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (!node->containsKey(ch))
            {
                node->putKey(ch);
            }
            node = node->get(ch);
            node->increaseCountPrefix();
        }
    }
    int getCountPrefixMatch(const string &word)
    {
        TrieNode *node = root;
        int sum = 0;
        for (char ch : word)
        {
            if (node->containsKey(ch))
            {
                node = node->get(ch);
                sum += node->getCountPrefix();
            }
            else
                break;
        }
        return sum;
    }
    vector<int> sumPrefixScores(vector<string> &words)
    {
        vector<int> ans(words.size());
        root = new TrieNode();
        for (string word : words)
        {
            insert(word);
        }
        for (int i = 0; i < words.size(); i++)
        {
            ans[i] = getCountPrefixMatch(words[i]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
