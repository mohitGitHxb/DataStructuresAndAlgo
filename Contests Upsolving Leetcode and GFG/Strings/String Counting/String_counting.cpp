#include <bits/stdc++.h>
using namespace std;

/*
@ problem
Given a string s, you choose some substring s[l...r] (1 ≤ l ≤ r ≤ |s|) exactly once and reverse it. For example, in the string geeks, select the substring s[2...4], after performing the mentioned operation, the new string will be gkees.

Count the number of unique strings that can be obtained by doing this operation exactly once.

Example 1:
Input:
s = "abaaa"
Output:
5
Explanation:
Take every possible substring and operate on it.
Possible strings after doing the operation are:
"baaaa", "abaaa", "aabaa", "aaaba" and "aaaab".

Example 2:
Input:
s = "aaaaaa"
Output:
1
Explanation:
Take any substring and reverse it, the resultant string will be same as the given string.

 */

/*

? hint: count the number of substrings where s[start] != s[end]
Intuition:

To solve this problem, we need to count the number of unique strings that can be obtained by performing the reverse operation on any substring exactly once. Since the reverse operation on a substring doesn't depend on the order of characters within the substring, we can consider each character in the original string as the center of the substring to be reversed.

Algorithm / Code Explanation:

    Create an unordered map, mp, to store the frequency of characters in the string s.
    Initialize ans to 1, as the original string itself is a unique string.
    Iterate over each character of the string s starting from the second character (index 1).
    For each character s[i], increment its frequency in the map mp.
    Update the answer ans by adding the count of possible substrings that can be formed using the current character as the center. The count is calculated as (i - mp[s[i]] + 1), where i is the current index and mp[s[i]] is the frequency of character s[i].
    Repeat steps 4 and 5 for each character in the string.
    Return the final value of ans.

Time Complexity:

The time complexity of this algorithm is O(n), where n is the length of the input string s. We iterate through the string once, and each operation inside the loop takes constant time.

Space Complexity:

The space complexity is O(n) due to the map mp, which can store at most n unique characters in the worst case.

Dry Run:

Let's dry run the given example "abaaa":

    Initialize mp and ans as empty and 1, respectively.
    Start iterating over the characters of the string:
        For character 'b':
            mp: {'b': 1}
            ans: 1
        For character 'a':
            mp: {'b': 1, 'a': 1}
            ans: 1 + (1 - 1 + 1) = 2
        For character 'a':
            mp: {'b': 1, 'a': 2}
            ans: 2 + (2 - 2 + 1) = 3
        For character 'a':
            mp: {'b': 1, 'a': 3}
            ans: 3 + (3 - 3 + 1) = 4
        For character 'a':
            mp: {'b': 1, 'a': 4}
            ans: 4 + (4 - 4 + 1) = 5
    Return ans as 5, which is the correct output.
 */
long long int countStrings(string s)
{
    unordered_map<char, long long int> mp;
    mp[s[0]] = 1;
    long long int ans = 1;
    for (long long int i = 1; i < s.length(); i++)
    {
        mp[s[i]]++;
        ans += (i - mp[s[i]] + 1);
    }
    return ans;
}

/*
The idea is as we can observe that if we reverse the substring with different beginning and ending characters then it would be a unique string. So we calculate the total number of possible combinations for all characters of the string and then remove the combinations which are formed by the repeating characters. So we get all the unique strings.
 */

long long int countStrings(string s)
{
    long long int ans = 1, n = s.length();
    vector<int> hash(26);
    for (int i = 0; i < n; i++)
    {
        hash[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            ans += hash[i] * hash[j];
        }
    }
    return ans;
}
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