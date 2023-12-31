#include <bits/stdc++.h>
using namespace std;

//^ Implementation of trie data structure

class Trie
{

public:
    // N is number of possible characters in a string
    const static int N = 26;

    // baseChar defines the base character for possible characters
    // like '0' for '0','1','2'... as possible characters in string
    const static char baseChar = 'a';

    struct TrieNode
    {
        int next[N];
        // if isEnd is set to true , a string ended here
        bool isEnd;
        // freq is how many times this prefix occurs
        int freq;

        TrieNode()
        {
            for (int i = 0; i < N; i++)
                next[i] = -1;
            isEnd = false;
            freq = 0;
        }
    };

    // the implementation is via vector and each position in this vector
    // is similar as new pointer in pointer type implementation
    vector<TrieNode> tree;

    // Base Constructor
    Trie()
    {
        tree.push_back(TrieNode());
    }

    // inserting a string in trie
    void insert(const string &s)
    {
        int p = 0;
        tree[p].freq++;
        for (int i = 0; i < s.size(); i++)
        {
            // tree[]
            if (tree[p].next[s[i] - baseChar] == -1)
            {
                tree.push_back(TrieNode());
                tree[p].next[s[i] - baseChar] = tree.size() - 1;
            }

            p = tree[p].next[s[i] - baseChar];
            tree[p].freq++;
        }
        tree[p].isEnd = true;
    }

    // check if a string exists as prefix
    bool checkPrefix(const string &s)
    {
        int p = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (tree[p].next[s[i] - baseChar] == -1)
                return false;

            p = tree[p].next[s[i] - baseChar];
        }
        return true;
    }

    // check is string exists
    bool checkString(const string &s)
    {
        int p = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (tree[p].next[s[i] - baseChar] == -1)
                return false;

            p = tree[p].next[s[i] - baseChar];
        }

        return tree[p].isEnd;
    }

    // persistent insert
    // returns location of new head
    int persistentInsert(int head, const string &s)
    {
        int old = head;

        tree.push_back(TrieNode());
        int now = tree.size() - 1;
        int newHead = now;

        int i, j;

        for (i = 0; i < s.size(); i++)
        {
            if (old == -1)
            {
                tree.push_back(TrieNode());
                tree[now].next[s[i] - baseChar] = tree.size() - 1;
                tree[now].freq++;
                now = tree[now].next[s[i] - baseChar];
                continue;
            }
            for (j = 0; j < N; j++)
                tree[now].next[j] = tree[old].next[j];
            tree[now].freq = tree[old].freq;
            tree[now].isEnd = tree[old].isEnd;

            tree[now].freq++;

            tree.push_back(TrieNode());
            tree[now].next[s[i] - baseChar] = tree.size() - 1;

            old = tree[old].next[s[i] - baseChar];
            now = tree[now].next[s[i] - baseChar];
        }

        tree[now].freq++;
        tree[now].isEnd = true;

        return newHead;
    }

    // persistent check prefix
    bool persistentCheckPrefix(int head, const string &s)
    {
        int p = head;
        for (int i = 0; i < s.size(); i++)
        {
            if (tree[p].next[s[i] - baseChar] == -1)
                return false;

            p = tree[p].next[s[i] - baseChar];
        }
        return true;
    }

    // persistent check string
    bool persistentCheckString(int head, const string &s)
    {
        int p = head;
        for (int i = 0; i < s.size(); i++)
        {
            if (tree[p].next[s[i] - baseChar] == -1)
                return false;

            p = tree[p].next[s[i] - baseChar];
        }
        return tree[p].isEnd;
    }
    int countWordsStartingWith(const string &prefix)
    {
        int p = 0;
        for (int i = 0; i < prefix.size(); i++)
        {
            if (tree[p].next[prefix[i] - baseChar] == -1)
                return 0; // no words with this prefix
            p = tree[p].next[prefix[i] - baseChar];
        }
        return tree[p].freq; // return the frequency of this prefix
    }

    // count words equal to a given string
    int countWordsEqualTo(const string &s)
    {
        int p = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (tree[p].next[s[i] - baseChar] == -1)
                return 0; // no words equal to this string
            p = tree[p].next[s[i] - baseChar];
        }
        return tree[p].isEnd ? tree[p].freq : 0; // return the frequency if this string is a word end
    }

    void erase(const string &s)
    {
        if (!checkString(s))
        {
            throw std::runtime_error("Word not found in Trie");
        }
        int p = 0;
        tree[p].freq--;
        for (int i = 0; i < s.size(); i++)
        {
            int nextNode = tree[p].next[s[i] - baseChar];
            tree[nextNode].freq--;
            if (tree[nextNode].freq == 0)
            {
                tree[p].next[s[i] - baseChar] = -1;
            }
            p = nextNode;
        }
        tree[p].isEnd = false;
    }
};

//^ Implementation of trie data structure [striver]
#include <string>
using namespace std;

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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}