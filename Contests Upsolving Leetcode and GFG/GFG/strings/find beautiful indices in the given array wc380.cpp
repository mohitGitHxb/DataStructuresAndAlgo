#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Function to construct the Longest Prefix Suffix (LPS) array for the pattern string
    vector<int> constructLPS(const string &s)
    {
        vector<int> lps(s.size());
        for (int i = 1; i < s.size(); i++)
        {
            int prevIdx = lps.at(i - 1);
            // If the current character does not match with the character at the previous index,
            // then update the previous index to the index of the longest proper prefix which is also suffix.
            while (prevIdx > 0 && s.at(i) != s.at(prevIdx))
            {
                prevIdx = lps.at(prevIdx - 1);
            }
            // If the current character matches with the character at the previous index,
            // then increment the length of the longest proper prefix which is also suffix.
            lps.at(i) = prevIdx + (s.at(i) == s.at(prevIdx));
        }
        return lps;
    }

    vector<int> beautifulIndices(string s, string a, string b, int k)
    {
        // Append the pattern string to the main string with a delimiter
        string sa = a + '#' + s;
        string sb = b + '#' + s;
        vector<int> va, vb;

        // Construct the LPS array for the pattern string and the main string
        vector<int> v = constructLPS(sa);
        for (int i = a.size(); i < v.size(); i++)
        {
            int el = v[i];
            // If the length of the longest proper prefix which is also suffix is equal to the length of the pattern string,
            // then the pattern string is found in the main string.
            if (el == a.size())
            {
                int id = i - 2 * a.size();
                if (id >= 0)
                    va.push_back(id);
            }
        }

        v = constructLPS(sb);
        for (int i = b.size(); i < v.size(); i++)
        {
            int el = v[i];
            if (el == b.size())
            {
                int id = i - 2 * b.size();
                if (id >= 0)
                    vb.push_back(id);
            }
        }

        vector<int> ans;
        if (vb.size() == 0 || va.size() == 0)
            return ans;
        int bi = 0;
        for (int i = 0; i < va.size(); i++)
        {
            // Find the first index in vb that is greater than or equal to va[i]
            auto bi = lower_bound(vb.begin(), vb.end(), va[i]) - vb.begin();
            // If such an index exists and the difference between the indices is less than or equal to k,
            // then the index is beautiful.
            if (bi != vb.size() && abs(va[i] - vb[bi]) <= k)
            {
                ans.push_back(va[i]);
                continue;
            }
            // If the previous index exists and the difference between the indices is less than or equal to k,
            // then the index is beautiful.
            if (bi != 0 && abs(va[i] - vb[bi - 1]) <= k)
                ans.push_back(va[i]);
        }

        return ans;
    }
};

// Brief Explanation:
// The solution uses the Knuth-Morris-Pratt (KMP) algorithm to find all occurrences of the pattern strings a and b in the main string s. The KMP algorithm constructs a Longest Prefix Suffix (LPS) array for the pattern string and uses it to skip characters while matching the pattern string with the main string. The time complexity of the KMP algorithm is O(n), where n is the length of the main string. The space complexity is O(m), where m is the length of the pattern string. After finding all occurrences of the pattern strings, the solution checks if the difference between the indices of the occurrences is less than or equal to k. If it is, then the index is beautiful. The time complexity of this step is O(n log n), where n is the number of occurrences. The space complexity is O(n), where n is the number of occurrences.
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