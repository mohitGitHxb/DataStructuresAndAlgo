#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:

/* 

A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).

You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.

Return the minimum number of flips to make s monotone increasing.

 

Example 1:

Input: s = "00110"
Output: 1
Explanation: We flip the last digit to get 00111.

Example 2:

Input: s = "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.





Did dry run of a test case and figured out we need to count the number of one's and when we encounter a 0 in the string increase the count of variable countFlip and find the minimum of the two values.

Finding minimum value on encountering a 0 because we are asked to make the string monotonically increasing.
If asked to make monotonically decreasing we find minimum when we encounter a 1 in the string.

    String s = "00110"
    After 1st iteration -> countOne = 0, countFlips = 1
    Find minimum of two, countFlips = 0
    After 2nd iteration -> countOne = 0, countFlips = 1
    Find minimum of two, countFlips = 0
    After 3rd iteration -> countOne = 1, countFlips = 0
    After 4th iteration -> countOne = 2, countFlips = 0
    After 5th iteration -> countOne = 2, countFlips = 1
    Find minimum of two, countFlips = 1

Return the value of countFlips after iterating through the string
Approach

MONTONICALLY INCREASING - 0's appear first then the 1's

Take 2 variables - countOne - to store the counts of character '1' in the string,
and countFlip - this decides the numbers of flips required to make string monotonically increasing and increases when we encounter the character '0' in the string. We then compare this value with countOne's to find the minimum of two.

Use a loop to iterate through the string character-wise.

    When '1' comes, no flip is done since 1's are to be present at the end of the strings .
    When '0' comes, we have to flip it place 0's at the beginning of the string. So, we have to find the minimum of cnt1 and cntFlips.

Complexity

    Time complexity:

O(n) - iterating throughout the string once

    Space complexity:

O(1) - no additional space used just some variables created

 */
public:
    int minFlipsMonoIncr(string s)
    {
        int n = s.length();

        if (n == 0)
        {
            return 0;
        }

        int cntFlips = 0, cnt1 = 0;
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
            {
                cnt1++;
            }
            else if (s[i] == '0')
            {
                cntFlips++;
                // finding minimum bcz we want minimum number of flips
                cntFlips = min(cnt1, cntFlips);
            }
        }
        return cntFlips;
    }
};
int main()
{
    return 0;
}