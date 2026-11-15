#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define gc getchar_unlocked
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define all(x) x.begin(), x.end()
#define endl "\n"
#define sortall(x) sort(all(x))
#define forv(it, a) for (auto &it : a)
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
#define sz(x) ((ll)(x).size())

void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

class Solution
{
private:
    /*
You are given a string target, an array of strings words, and an integer array costs, both arrays of the same length.

Imagine an empty string s.

You can perform the following operation any number of times (including zero):

    Choose an index i in the range [0, words.length - 1].
    Append words[i] to s.
    The cost of operation is costs[i].

Return the minimum cost to make s equal to target. If it's not possible, return -1.



Example 1:

Input: target = "abcdef", words = ["abdef","abc","d","def","ef"], costs = [100,1,1,10,5]

Output: 7

Explanation:

The minimum cost can be achieved by performing the following operations:

    Select index 1 and append "abc" to s at a cost of 1, resulting in s = "abc".
    Select index 2 and append "d" to s at a cost of 1, resulting in s = "abcd".
    Select index 4 and append "ef" to s at a cost of 5, resulting in s = "abcdef".

Example 2:

Input: target = "aaaa", words = ["z","zz","zzz"], costs = [1,10,100]

Output: -1

Explanation:

It is impossible to make s equal to target, so we return -1.


     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    int minimumCost(string target, vsr &words, vector<int> &costs)
    {
        /*

        ! TLE
        ! first of all string comparisons in the hashmap is O(string length)
        ! then we are running two loops and inside checking again in the hashmap so due to string comparison it can go O(N^2 * maxLength of string)

         */
        unordered_map<string, int> mp;
        for (int i = 0; i < words.size(); i++)
        {
            if (mp.count(words[i]))
            {
                mp[words[i]] = min(costs[i], mp[words[i]]);
            }
            else
            {
                mp[words[i]] = costs[i];
            }
        }
        vi dp(target.size() + 1, 1e9);
        dp[target.size()] = 0;
        rforn(i, target.size() - 1)
        {
            string lookFor = "";
            for (int j = i; j <= target.size(); j++)
            {
                lookFor += target[j];
                if (mp.count(lookFor))
                {
                    dp[i] = min(dp[i], mp[lookFor] + dp[j + 1]);
                }
            }
        }
        return (dp[0] == 1e9) ? -1 : dp[0];
    }

    struct TrieNode
    {
        unordered_map<char, TrieNode *> children;
        bool isEnd;
        int cost; // this will be the minimum cost for the word
        TrieNode()
        {
            isEnd = false;
            cost = INT_MAX;
        }
        bool containsKey(char ch) { return children.count(ch); }
        void put(char ch) { children[ch] = new TrieNode(); }
        TrieNode *get(char ch) { return children[ch]; }
    };
    class TrieSolution
    {
    public:
        TrieNode *root;
        /* 
        @ Insertion with minimum cost [simple trie insertion]
        
         */
        void insert(string &word, int cost)
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
            node->cost = min(node->cost, cost);
        }
        /* 
        @ Search whether the word exist and return its cost 
        ! IMPORTANT NOTE:
        & We can't use this actually because the string length may go upto 5x1e4 which will throw TLE if we call this function in a nested for loop
         */
        int search(string &word)
        {
            TrieNode *node = root;
            for (char ch : word)
            {
                if (!node->containsKey(ch))
                {
                    return 1e9;
                }
                else
                {
                    node = node->get(ch);
                }
            }
            return node->cost;
        }
        int minimumCost(string target, vector<string> &words, vector<int> &costs)
        {
            root = new TrieNode();
            for (int i = 0; i < words.size(); i++)
            {
                insert(words[i], costs[i]);
            }

            vector<long long> dp(target.size() + 1, INT_MAX);
            dp[0] = 0;
            /* 
            @ Core Idea:
            & We will traverse the target and for each character we will find the cost for the word and then we will update the dp array
            & But instead of first making the substring like lookFor in the brute force method
            & We will search simultaneously while building the substring that way we can eliminate the extra O(string) factor
            % Note that the constraints said sum of lengths would be under 5 x 1e4 if we apply some basic maths for testcase [a,aa,aaa,aaaa,...k]
            % We will get the value of k as root(2n) 
            * Overall time complexity is O(Nroot(n))
            
             */
            for (int i = 0; i < target.size(); i++)
            {
                if (dp[i] == INT_MAX)
                    continue;
                TrieNode *node = root;
                for (int j = i; j < target.size(); j++)
                {
                    char ch = target[j];
                    if (!node->containsKey(ch))
                    {
                        break;
                    }
                    node = node->get(ch);
                    if (node->cost != INT_MAX)
                    {
                        dp[j + 1] = min(dp[j + 1], node->cost + dp[i]);
                    }
                }
            }
            return (dp[target.size()] == INT_MAX) ? -1 : dp[target.size()];
        }
    };
};

int main(int argc, char const *argv[])
{
    Solution obj;
    return 0;
}
