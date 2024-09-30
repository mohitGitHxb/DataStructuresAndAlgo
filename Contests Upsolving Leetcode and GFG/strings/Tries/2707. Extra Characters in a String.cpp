#include <bits/stdc++.h>
using namespace std;
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
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
static int init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

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
    void put(char ch)
    {
        children[ch - 'a'] = new TrieNode();
    }
};

class Solution
{
private:
    /*
    You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary. There may be some extra characters in s which are not present in any of the substrings.

    Return the minimum number of extra characters left over if you break up s optimally.



    Example 1:

    Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
    Output: 1
    Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8. There is only 1 unused character (at index 4), so we return 1.

    Example 2:

    Input: s = "sayhelloworld", dictionary = ["hello","world"]
    Output: 3
    Explanation: We can break s in two substrings: "hello" from index 3 to 7 and "world" from index 8 to 12. The characters at indices 0, 1, 2 are not used in any substring and thus are considered as extra characters. Hence, we return 3.



     */
public:
    static constexpr int mod = 1e9 + 7;
    TrieNode *root;
    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (!node->containsKey(ch))
            {
                node->put(ch);
            }
            node = node->get(ch);
        }
        node->isEnd = true;
    }
    int minExtraChar(string s, vector<string> &dictionary)
    {
        // unordered_set<string> dict(dictionary.begin(), dictionary.end());
        // using tries instead of set
        root = new TrieNode();
        for (string &word : dictionary)
        {
            insert(word);
        }
        int n = s.size();
        vector<int> dp(n + 1, 0);
        //&- Solved using unordered_set
        // for (int i = 1; i <= n; i++)
        // {
        //     dp[i] = dp[i - 1] + 1;
        //     for (int j = 0; j < i; j++)
        //     {
        //         if (dict.count(s.substr(j, i - j)))
        //         {
        //             dp[i] = min(dp[i], dp[j]);
        //         }
        //     }
        // }

        //&- Trie method for optimal checking
        for (int i = n - 1; i >= 0; i--)
        {
            dp[i] = dp[i + 1] + 1;
            TrieNode *node = root;
            for (int j = i; j < n; j++)
            {
                if (node->containsKey(s[j]))
                {
                    node = node->get(s[j]);
                    if (node->isEnd)
                    {
                        dp[i] = min(dp[i], dp[j + 1]);
                    }
                }
                else
                    break;
            }
        }

        return dp[0];
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
