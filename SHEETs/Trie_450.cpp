#include <bits/stdc++.h>
using namespace std;

//^ Implementation of trie data structure

// class Trie
// {

// public:
//     // N is number of possible characters in a string
//     const static int N = 26;

//     // baseChar defines the base character for possible characters
//     // like '0' for '0','1','2'... as possible characters in string
//     const static char baseChar = 'a';

//     struct TrieNode
//     {
//         int next[N];
//         // if isEnd is set to true , a string ended here
//         bool isEnd;
//         // freq is how many times this prefix occurs
//         int freq;

//         TrieNode()
//         {
//             for (int i = 0; i < N; i++)
//                 next[i] = -1;
//             isEnd = false;
//             freq = 0;
//         }
//     };

//     // the implementation is via vector and each position in this vector
//     // is similar as new pointer in pointer type implementation
//     vector<TrieNode> tree;

//     // Base Constructor
//     Trie()
//     {
//         tree.push_back(TrieNode());
//     }

//     // inserting a string in trie
//     void insert(const string &s)
//     {
//         int p = 0;
//         tree[p].freq++;
//         for (int i = 0; i < s.size(); i++)
//         {
//             // tree[]
//             if (tree[p].next[s[i] - baseChar] == -1)
//             {
//                 tree.push_back(TrieNode());
//                 tree[p].next[s[i] - baseChar] = tree.size() - 1;
//             }

//             p = tree[p].next[s[i] - baseChar];
//             tree[p].freq++;
//         }
//         tree[p].isEnd = true;
//     }

//     // check if a string exists as prefix
//     bool checkPrefix(const string &s)
//     {
//         int p = 0;
//         for (int i = 0; i < s.size(); i++)
//         {
//             if (tree[p].next[s[i] - baseChar] == -1)
//                 return false;

//             p = tree[p].next[s[i] - baseChar];
//         }
//         return true;
//     }

//     // check is string exists
//     bool checkString(const string &s)
//     {
//         int p = 0;
//         for (int i = 0; i < s.size(); i++)
//         {
//             if (tree[p].next[s[i] - baseChar] == -1)
//                 return false;

//             p = tree[p].next[s[i] - baseChar];
//         }

//         return tree[p].isEnd;
//     }

//     // persistent insert
//     // returns location of new head
//     int persistentInsert(int head, const string &s)
//     {
//         int old = head;

//         tree.push_back(TrieNode());
//         int now = tree.size() - 1;
//         int newHead = now;

//         int i, j;

//         for (i = 0; i < s.size(); i++)
//         {
//             if (old == -1)
//             {
//                 tree.push_back(TrieNode());
//                 tree[now].next[s[i] - baseChar] = tree.size() - 1;
//                 tree[now].freq++;
//                 now = tree[now].next[s[i] - baseChar];
//                 continue;
//             }
//             for (j = 0; j < N; j++)
//                 tree[now].next[j] = tree[old].next[j];
//             tree[now].freq = tree[old].freq;
//             tree[now].isEnd = tree[old].isEnd;

//             tree[now].freq++;

//             tree.push_back(TrieNode());
//             tree[now].next[s[i] - baseChar] = tree.size() - 1;

//             old = tree[old].next[s[i] - baseChar];
//             now = tree[now].next[s[i] - baseChar];
//         }

//         tree[now].freq++;
//         tree[now].isEnd = true;

//         return newHead;
//     }

//     // persistent check prefix
//     bool persistentCheckPrefix(int head, const string &s)
//     {
//         int p = head;
//         for (int i = 0; i < s.size(); i++)
//         {
//             if (tree[p].next[s[i] - baseChar] == -1)
//                 return false;

//             p = tree[p].next[s[i] - baseChar];
//         }
//         return true;
//     }

//     // persistent check string
//     bool persistentCheckString(int head, const string &s)
//     {
//         int p = head;
//         for (int i = 0; i < s.size(); i++)
//         {
//             if (tree[p].next[s[i] - baseChar] == -1)
//                 return false;

//             p = tree[p].next[s[i] - baseChar];
//         }
//         return tree[p].isEnd;
//     }
//     int countWordsStartingWith(const string &prefix)
//     {
//         int p = 0;
//         for (int i = 0; i < prefix.size(); i++)
//         {
//             if (tree[p].next[prefix[i] - baseChar] == -1)
//                 return 0; // no words with this prefix
//             p = tree[p].next[prefix[i] - baseChar];
//         }
//         return tree[p].freq; // return the frequency of this prefix
//     }

//     // count words equal to a given string
//     int countWordsEqualTo(const string &s)
//     {
//         int p = 0;
//         for (int i = 0; i < s.size(); i++)
//         {
//             if (tree[p].next[s[i] - baseChar] == -1)
//                 return 0; // no words equal to this string
//             p = tree[p].next[s[i] - baseChar];
//         }
//         return tree[p].isEnd ? tree[p].freq : 0; // return the frequency if this string is a word end
//     }

//     void erase(const string &s)
//     {
//         if (!checkString(s))
//         {
//             throw std::runtime_error("Word not found in Trie");
//         }
//         int p = 0;
//         tree[p].freq--;
//         for (int i = 0; i < s.size(); i++)
//         {
//             int nextNode = tree[p].next[s[i] - baseChar];
//             tree[nextNode].freq--;
//             if (tree[nextNode].freq == 0)
//             {
//                 tree[p].next[s[i] - baseChar] = -1;
//             }
//             p = nextNode;
//         }
//         tree[p].isEnd = false;
//     }
// };

//^ Implementation of trie data structure [striver]
// class TrieNode
// {
// private:
//     struct Node
//     {
//         Node *links[26];
//         int cntEndWith = 0;
//         int cntPrefix = 0;

//         bool containsKey(char ch)
//         {
//             return (links[ch - 'a'] != nullptr);
//         }

//         Node *get(char ch)
//         {
//             return links[ch - 'a'];
//         }

//         void put(char ch, Node *node)
//         {
//             links[ch - 'a'] = node;
//         }

//         void increaseEnd()
//         {
//             cntEndWith++;
//         }

//         void increasePrefix()
//         {
//             cntPrefix++;
//         }

//         void deleteEnd()
//         {
//             cntEndWith--;
//         }

//         void reducePrefix()
//         {
//             cntPrefix--;
//         }

//         int getEnd()
//         {
//             return cntEndWith;
//         }

//         int getPrefix()
//         {
//             return cntPrefix;
//         }
//     };

//     Node *root;

// public:
//     TrieNode()
//     {
//         root = new Node();
//     }

//     void insert(string word)
//     {
//         Node *node = root;
//         for (int i = 0; i < word.length(); i++)
//         {
//             if (!node->containsKey(word[i]))
//             {
//                 node->put(word[i], new Node());
//             }
//             node = node->get(word[i]);
//             node->increasePrefix();
//         }
//         node->increaseEnd();
//     }

//     int countWordsEqualTo(string &word)
//     {
//         Node *node = root;
//         for (int i = 0; i < word.length(); i++)
//         {
//             if (node->containsKey(word[i]))
//             {
//                 node = node->get(word[i]);
//             }
//             else
//             {
//                 return 0;
//             }
//         }
//         return node->getEnd();
//     }

//     int countWordsStartingWith(string &word)
//     {
//         Node *node = root;
//         for (int i = 0; i < word.length(); i++)
//         {
//             if (node->containsKey(word[i]))
//             {
//                 node = node->get(word[i]);
//             }
//             else
//             {
//                 return 0;
//             }
//         }
//         return node->getPrefix();
//     }

//     void erase(string &word)
//     {
//         Node *node = root;
//         for (int i = 0; i < word.length(); i++)
//         {
//             if (node->containsKey(word[i]))
//             {
//                 node = node->get(word[i]);
//                 node->reducePrefix();
//             }
//             else
//             {
//                 return;
//             }
//         }
//         node->deleteEnd();
//     }
// };

//^ 1 Longest Common Prefix in an Array

class LongestCommonPrefix
{
private:
    struct Node
    {
        Node *links[26];
        bool flag = false;
        int cp = 0;

        void insert(char a, Node *tmp)
        {
            links[a - 'a'] = tmp;
        }

        bool containKey(char a)
        {
            return links[a - 'a'] != NULL;
        }

        Node *get(char a)
        {
            return links[a - 'a'];
        }

        void setEnd()
        {
            this->flag = true;
        }

        bool isEnd()
        {
            return flag;
        }

        void increaseP()
        {
            this->cp++;
        }
    };

    class Trie
    {
    private:
        Node *root;

    public:
        Trie()
        {
            root = new Node();
        }

        void insert(string s)
        {
            Node *node = root;
            for (int i = 0; i < s.length(); i++)
            {
                if (!node->containKey(s[i]))
                {
                    node->insert(s[i], new Node());
                }

                node = node->get(s[i]);
                node->increaseP();
            }

            node->setEnd();
        }

        int pre_len(string s)
        {
            Node *node = root;

            for (int i = 0; i < s.length(); i++)
            {
                if (!node->containKey(s[i]))
                    return 0;

                node = node->get(s[i]);
            }
            return node->cp;
        }
    };

public:
    string longestCommonPrefix(vector<string> &strs)
    {
        // string small;
        int len = 1e9;
        Trie *trie = new Trie();
        int n = strs.size();
        for (int i = 0; i < strs.size(); i++)
        {
            if (strs[i].length() < len)
            {
                len = strs[i].length();
                // small = strs[i];
            }
            trie->insert(strs[i]);
        }

        string t;

        for (int i = 0; i < len; i++)
        {
            t += strs[0][i];

            if (trie->pre_len(t) != n)
            {
                t.pop_back();
                return t;
            }
        }

        return t;
    }
};

//^ 2 Count distinct substrings of a given string
class CountDistinct
{

public:
    /*
    ! Brute Force Approach
    Consider all substrings of the given string and insert them in a set
    Return the size of the set

    !Time Complexity: O(n^2)
    !Space Complexity: O(n*m) if all substrings are distinct
     */
    int countDistinctSubstring(string s)
    {
        // Your code here
        unordered_set<string> hs;
        for (int i = 0; i < s.length(); i++)
        {
            string temp = "";
            for (int j = i; j < s.length(); j++)
            {
                temp.push_back(s[j]);
                hs.insert(temp);
            }
        }
        return hs.size() + 1;
    }

    /*
    & Optimized approach using Trie
    * Time Complexity: O(n^2)
     */
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

    /*You are required to complete this method */
    int countDistinctSubstring(string s)
    {
        int count = 0;           // Initialize the count of distinct substrings
        Node *root = new Node(); // Create a new root node for the trie

        // Iterate through each character in the string
        for (int i = 0; i < s.length(); i++)
        {
            string temp = "";  // Create a temporary string to store substrings
            Node *node = root; // Start from the root node

            // Iterate through each character from current position to end of string
            for (int j = i; j < s.length(); j++)
            {
                temp.push_back(s[j]); // Add the current character to the temporary string

                // If the current character is not present in the trie, add it and increment the count
                if (!node->containsKey(s[j]))
                {
                    count++;
                    node->put(s[j], new Node());
                }

                node = node->get(s[j]); // Move to the next node
            }
        }

        return count + 1; // Return the count of distinct substrings
    }
};

//^ 4 Maximum XOR of two numbers in an array
/*
Problem Overview:

The problem requires finding the maximum result of XOR between any two elements in an array. To solve this problem efficiently, the code implements a Trie (Prefix Tree) data structure. The Trie is used to store the binary representation of the array elements and to find the maximum XOR.
Trie Implementation:

The Trie is implemented using a structure called Node, which has an array of two pointers (links) to represent the two possible bits (0 or 1). The Trie class has methods for inserting an integer into the Trie and finding the maximum XOR for a given integer.
Algorithm:

    Create a Trie object.
    Iterate through the array nums and insert each element into the Trie.
    For each element in nums, find the maximum XOR by traversing the Trie.
    Update the maximum XOR if a higher value is found.
    Return the maximum XOR as the result.

Trie Insertion:

    For each integer, iterate through its binary representation from the most significant bit to the least significant bit.
    Create nodes in the Trie as needed to represent the binary representation of the integer.

Trie FindMax:

    For each bit of the given integer, traverse the Trie to find the bit that, when XORed with the current bit, produces the maximum XOR.
    Update the result accordingly.

Time Complexity:

    The time complexity of inserting each element into the Trie is O(32 * n) since each integer has a maximum of 32 bits.
    The time complexity of finding the maximum XOR for each element is also O(32 * n).
    Therefore, the overall time complexity is O(n), where n is the size of the input array.

Space Complexity:

    The space complexity is O(n) for storing the Trie nodes.

Summary:

The code efficiently utilizes the Trie data structure to find the maximum XOR for any two elements in the given array. The time and space complexities are reasonable for the given problem size. The algorithm is based on bitwise manipulation and Trie traversal, making it an effective solution for the problem.

 */

//^ 5 Maximum XOR from an element in an array (offline query + trie)
class MaximumXORQueries
{
private:
    struct Node
    {
        Node *links[2];

        bool containsKey(int ind)
        {
            return (links[ind] != NULL);
        }
        Node *get(int ind)
        {
            return links[ind];
        }
        void put(int ind, Node *node)
        {
            links[ind] = node;
        }
    };
    class Trie
    {
    private:
        Node *root;

    public:
        Trie()
        {
            root = new Node();
        }

        void insert(int num)
        {
            Node *node = root;
            // cout << num << endl;
            for (int i = 31; i >= 0; i--)
            {
                int bit = (num >> i) & 1;
                if (!node->containsKey(bit))
                {
                    node->put(bit, new Node());
                }
                node = node->get(bit);
            }
        }

        int findMax(int num)
        {
            Node *node = root;
            int maxNum = 0;
            for (int i = 31; i >= 0; i--)
            {
                int bit = (num >> i) & 1;
                if (node->containsKey(!bit))
                {
                    maxNum = maxNum | (1 << i);
                    node = node->get(!bit);
                }
                else
                {
                    node = node->get(bit);
                }
            }
            return maxNum;
        }
    };

public:
    vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size(), m = queries.size();
        sort(nums.begin(), nums.end());
        vector<int> ans(m);
        vector<pair<int, pair<int, int>>> offlineQueries(m);
        for (int i = 0; i < m; i++)
        {
            offlineQueries[i] = {queries[i][1], {queries[i][0], i}};
        }
        sort(offlineQueries.begin(), offlineQueries.end());
        Trie trie;
        int index = 0;
        for (int i = 0; i < m; i++)
        {
            while (index < n && nums[index] <= offlineQueries[i].first)
            {
                trie.insert(nums[index]);
                index++;
            }
            if (index == 0)
            {
                ans[offlineQueries[i].second.second] = -1;
            }
            else
            {
                ans[offlineQueries[i].second.second] = trie.findMax(offlineQueries[i].second.first);
            }
        }
        return ans;
    }
};

//^ 6 Maximum Strong pair XOR - 2
class MaxStrongXOR
{
private:
    // Define a Trie node
    class T
    {
    public:
        T *ch[2]; // Pointers to the child nodes
        int freq; // Frequency of the node
        T()
        {
            // Initialize the child nodes to NULL and frequency to 1
            for (int i = 0; i < 2; i++)
                ch[i] = NULL;
            freq = 1;
        }
    };

    // Define the Trie
    class trie
    {
    public:
        T *root; // Root of the Trie
        trie()
        {
            // Initialize the root node
            root = new T();
        }

        // Function to add a number to the Trie
        void add(int x)
        {
            bitset<32> w(x); // Convert the number to binary
            T *r = root;
            for (int i = 31; i >= 0; i--) // Traverse the binary representation from left to right
            {
                if (r->ch[w[i]] != NULL) // If the child node exists
                {
                    r = r->ch[w[i]]; // Move to the child node
                    r->freq += 1;    // Increase the frequency
                }
                else
                {
                    // If the child node does not exist, create a new node
                    r->ch[w[i]] = new T();
                    r = r->ch[w[i]];
                }
            }
        }

        // Function to delete a number from the Trie
        void del(int x)
        {
            bitset<32> w(x); // Convert the number to binary
            T *r = root;
            for (int i = 31; i >= 0; i--) // Traverse the binary representation from left to right
            {
                r = r->ch[w[i]]; // Move to the child node
                r->freq -= 1;    // Decrease the frequency
            }
        }

        // Function to get the maximum XOR of a number with numbers in the Trie
        int get(int x)
        {
            T *r = root;
            bitset<32> w(x); // Convert the number to binary
            int maxNum = 0;
            for (int i = 31; i >= 0; i--) // Traverse the binary representation from left to right
            {
                if (r->ch[!w[i]] && r->ch[!w[i]]->freq) // If the opposite bit exists and its frequency is non-zero
                {
                    maxNum = maxNum | (1 << i); // Update the maximum number
                    r = r->ch[!w[i]];           // Move to the child node with the opposite bit
                }
                else
                {
                    r = r->ch[w[i]]; // Otherwise, move to the child node with the same bit
                }
            }
            return maxNum; // Return the maximum number
        }
    };

public:
    int maximumStrongPairXor(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());    // Sort the array in ascending order
        int ans = INT_MIN;                 // Initialize the answer to the minimum integer
        int i = 0, j = 0, n = nums.size(); // Initialize the pointers and get the size of the array
        trie *r = new trie();              // Create a new Trie
        while (j < n)                      // While the end of the array is not reached
        {
            r->add(nums[j]);                       // Add the current number to the Trie
            while (i < j && nums[j] > 2 * nums[i]) // While the current number is more than twice the number at the i-th position
            {
                r->del(nums[i]); // Delete the number at the i-th position from the Trie
                i++;             // Move the i-th position to the right
            }
            int k = r->get(nums[j]); // Get the maximum XOR of the current number with numbers in the Trie
            ans = max(ans, k);       // Update the answer
            j++;                     // Move to the next number
        }
        return ans; // Return the answer
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