#include <bits/stdc++.h>
using namespace std;
//* TWO pointers and Sliding Window Questions
/*
? Different patterns in sliding window / two pointers
@ Applicable where there is uniformity in the data to be processed
% Constant window size (size k)
% Longest subarray type of questions [shrink,expand]
% No. of subarrays with <Conditions/>
% Shorted/Minimum window <Conditions/>
 */

//^ 1 Maximum points you can obtain from cards.
class MaximumPoints
{
private:
    /*
    Input: cardPoints = [1,2,3,4,5,6,1], k = 3
    Output: 12
    Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

     */
public:
    int maxScore_extraSpace(vector<int> &cardPoints, int k)
    {
        int n = cardPoints.size();
        vector<int> temp;
        /*
        include first k elements in reverse order then last k elements in reverse order
        and simply use concept of sliding window on constant size
        * T.C O(2K) S.C O(2K)
         */
        for (int i = k - 1; i >= 0; i--)
        {
            temp.push_back(cardPoints[i]);
        }
        for (int i = n - 1; i >= n - k; i--)
        {
            temp.push_back(cardPoints[i]);
        }
        int sum = 0, maxSum = 0;
        int start = 0, end = 0;
        while (end < temp.size())
        {
            sum += temp.at(end);
            if (end - start + 1 == k)
            {
                maxSum = max(maxSum, sum);
                sum -= temp.at(start);
                start++;
            }
            end++;
        }
        return maxSum;
    }
    int maxScore(vector<int> &cardPoints, int k)
    {
        /*
         * T.C : O(2K) S.C : O(1)
         & Remove the extra space taken by vector and simply use two pointers
         */
        int n = cardPoints.size();
        int sum = 0, maxSum = 0;
        int start = n - k, end;
        for (end = start; end < n; end++)
        {
            sum += cardPoints.at(end);
        }
        maxSum = sum; // since all elements are positive hence sum always increases
        end = 0;
        while (end < k)
        {
            sum += cardPoints.at(end++);
            sum -= cardPoints.at(start++);
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }
};

//^ 2 Longest substring without repeating characters
class LongestSubstringWithoutRepeating
{
public:
    int lengthOfLongestSubstring(string &str)
    {
        unordered_map<char, int> freq; // using umap because of empty spaces symbols digits
        int start = 0, end = 0;
        int maxLen = 0;
        while (end < str.length())
        {
            freq[str[end]]++;
            while (freq[str[end]] > 1)
            {
                freq[str[start]]--;
                start++;
            }
            maxLen = max(maxLen, end - start + 1);
            end++;
        }
        return maxLen;
    }
    int lengthOfLongestSubstring_mostOptimal(string &str)
    {
        int n = str.size();
        int l = 0;
        int r = 0;
        int longest = 0;
        bitset<257> seen;
        while (r < n)
        {
            if (!seen[str[r]])
            {
                seen[str[r]] = 1;
                r++;
                longest = max(longest, r - l);
            }
            else
            {
                seen[str[l]] = 0;
                l++;
            }
        }
        return longest;
    }
};

//^ 3 Maximum consecutive ones 3
int longestOnes(vector<int> &nums, int k)
{ /*

 & Maintain zeroCount in a window and expand shrink accordingly.
 * Time Complexity: O(2N)
 * Space Complexity: O(1)
  */
    int start = 0, end = 0, maxLen = 0, zeroCount = 0;
    while (end < nums.size())
    {
        if (nums.at(end) == 0)
        {
            zeroCount++;
        }
        while (zeroCount > k)
        {
            if (nums.at(start) == 0)
            {
                zeroCount--;
            }
            start++;
        }
        maxLen = max(maxLen, end - start + 1);
        end++;
    }
    return maxLen;

    /*
    % More optimized version which takes O(N) T.C | O(1) S.C
        int start = 0, end = 0, maxLen = 0, zeroCount = 0;
        while (end < nums.size())
        {
            if (nums.at(end) == 0)
            {
                zeroCount++;
            }
            & Fix the window size to maxLen as even if we shrink window the answer won't be any better
            if(zeroCount > k){
                if(nums.at(start) == 0){
                    zeroCount--;
                }
                start++;
            }
            if(zeroCount <= k){
                maxLen = max(maxLen, end - start + 1);
            }
            end++;
        }
        return maxLen;

     */
}

//^ 4 Fruits and baskets
int totalFruit(vector<int> &fruits)
{
    unordered_map<int, int> mp;
    int ans = 0;
    for (int i = 0, j = 0; j < fruits.size(); j++)
    {
        mp[fruits[j]]++;
        if (mp.size() > 2)
        {
            mp[fruits[i]]--;
            if (mp[fruits[i]] == 0)
                mp.erase(fruits[i]);
            i++;
        }
        ans = max(ans, j - i + 1);
    }
    return ans;
}

//^ 5 Longest Repeating Character Replacement
class LongestRepeatingReplacement
{
public:
    int characterReplacement(string &s, int k)
    {
        /*
        & First mapping character to its frequency
        & Then using a set to maintain the max frequency and max character

        & if a string like AAABCCAAA has A:6 C:2 B:1 then the operations to convert this string into same characters would be (length of string - max freq);
        & in the above case it would be (9 - 6) = 3;

        % Now shrink and expand window according to the operations to convert the string into same characters.

         */
        set<pair<int, char>, greater<pair<int, char>>> st;
        vector<int> freq(26);
        int start = 0, end = 0, maxLength = 0;
        while (end < s.length())
        {
            st.erase({freq[s[end] - 'A'], s[end]});
            freq[s[end] - 'A']++;
            st.insert({freq[s[end] - 'A'], s[end]});

            auto [maxF, maxChar] = *st.begin();
            while ((end - start + 1) - maxF > k)
            {
                st.erase({freq[s[start] - 'A'], s[start]});
                freq[s[start] - 'A']--;
                st.insert({freq[s[start] - 'A'], s[start]});
                maxF = st.begin()->first;
                start++;
            }
            maxLength = max(maxLength, end - start + 1);
            end++;
        }
        return maxLength;
    }

    int characterReplacement_BetterSolution(string &s, int k)
    {
        /*
        & Instead of using sets to maintain maximum frequency and maximum character, we can use a vector of size 26 to maintain frequency of each character and maxFreq variable
         */
        vector<int> freq(26);
        int start = 0, end = 0, maxFreq = 0, maxLen = 0;
        while (end < s.size())
        {
            freq[s[end] - 'A']++;
            maxFreq = max(maxFreq, freq[s[end] - 'A']);
            while ((end - start + 1) - maxFreq > k)
            {
                freq[s[start] - 'A']--;
                maxFreq = *max_element(freq.begin(), freq.end());
                start++;
            }
            maxLen = max(maxLen, end - start + 1);
            end++;
        }
        return maxLen;
    }
};

//^ 6 Longest Substring with K Distinct Characters
int longestKSubstr(string s, int k)
{
    /*
     * Time complexity: O(2N)
     * Space complexity: O(26)
     */
    unordered_map<char, int> freq;
    int start = 0, end = 0, maxLen = -1;
    while (end < s.size())
    {
        freq[s[end]]++;
        while (freq.size() > k) // if(freq.size() >= k) use this to reduce T.C to O(N)
        {
            freq[s[start]]--;
            if (freq[s[start]] == 0)
            {
                freq.erase(s[start]);
            }
            start++;
        }
        if (freq.size() == k)
        {
            maxLen = max(maxLen, end - start + 1);
        }
        end++;
    }
    return maxLen;
}
//^ 7 Number of substrings containing all three characters
class NumberOfSubstrings
{
public:
    bool isFilled(vector<int> &freq)
    {
        return (freq[0] > 0 and freq[1] > 0 and freq[2] > 0);
    }
    int numberOfSubstrings(string s)
    {
        int start = 0, end = 0, substrings = 0;
        vector<int> freq(3);

        while (end < s.size())
        {
            freq[s[end] - 'a']++;
            while (isFilled(freq))
            {
                freq[s[start] - 'a']--;
                substrings += (s.size() - end); // for string abcabc [end] is at index 2 ("abc",abc)
                // since we already have the required characters even if we extend the string further it wouldn't change the condition(atleast one occurence of all chars)
                // hence we can directly add totalLength - end (these substrings are valid also)
                start++;
            }
            end++;
        }
        return substrings;
    }
};
//^ 8 Count number of nice subarrays
class CountNiceSubarrays
{
public:
    int numberOfSubarrays(vector<int> &nums, int k)
    {
        /**
         * Use a hashmap to count subarrays with exactly K odd elements
         * The key is the number of odd elements in the subarray starting from index 0
         * The value is the number of subarrays with that number of odd elements
         */
        unordered_map<int, int> mp;
        /**
         * Initialize the hashmap with key=0 and value=1
         * This is because there is only one subarray with 0 odd elements
         */
        mp[0] = 1;
        /**
         * Keep track of the number of odd elements in the prefix of the input array
         */
        int prefixOdd = 0;
        /**
         * Initialize the number of subarrays with exactly K odd elements to 0
         */
        int subarrays = 0;
        /**
         * Iterate over the input array
         */
        for (int i = 0; i < nums.size(); i++)
        {
            /**
             * Increment the number of odd elements in the prefix if the current element is odd
             */
            prefixOdd += (nums[i] & 1);
            /**
             * If the hashmap contains the key=number of odd elements in the prefix-K
             */
            if (mp.count(prefixOdd - k))
            {
                /**
                 * Add the number of subarrays with that key to the total number of subarrays
                 * This is because there are those many subarrays with prefixOdd-K odd elements
                 */
                subarrays += mp[prefixOdd - k];
            }
            /**
             * Increment the value for the key=number of odd elements in the prefix
             */
            mp[prefixOdd]++;
        }
        return subarrays;
    }
    /*
    & Instead of using prefix odd count to determine the subarrays, we can use the following approach:
    & First we try to find subarrays having atmost K odd elements.
    & Then we try to find subarrays having atmost K-1 odd elements.
    & and subtract the two subarrays to get the number of subarrays having atmost K odd elements.

    % This is a standard way to solve exactly K type problem in which we need to count subarrays/substrings.

    * Time complexity: O(N) (O(4N) to be exact)
    * Space complexity: O(1)

     */
    int atmostKsubarrays(vector<int> &nums, int k)
    {
        int start = 0, end = 0, subarrays = 0, oddCount = 0;
        while (end < nums.size())
        {
            oddCount += (nums[end] & 1);
            while (oddCount > k)
            {
                oddCount -= (nums[start++] & 1);
            }
            subarrays += (end - start + 1);
            end++;
        }
        return subarrays;
    }
    int numberOfSubarrays(vector<int> &nums, int k)
    {
        return atmostKsubarrays(nums, k) - atmostKsubarrays(nums, k - 1);
    }
};

//^ 9 Binary subarrays with sum K
class BinarySubarraysK
{
public:
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {

        unordered_map<int, int> mp;

        vector<int> prefix(nums.size() + 1);

        int subarrays = 0;

        mp[0] = 1;

        for (int i = 0; i < nums.size(); i++)
        {

            prefix[i + 1] = prefix[i] + nums[i];

            if (mp.count(prefix[i + 1] - goal))
            {

                subarrays += mp[prefix[i + 1] - goal];
            }

            mp[prefix[i + 1]]++;
        }

        return subarrays;
    }
    /*

Count number of subarrays with sum at most goal using the sliding window technique. Maintain a pointer to ensure that the window sum stays at most goal.
When sliding to position i:
    Add nums[i] to the window sum.
    Slide up the pointer prev to ensure that the current window sum does not exceed the goal.
    Update result with i - prev + 1 subarrays with sum at most goal and ending at i.
        Explain : sum[prev .. i] <= goal => sum[prev + 1 .. i] <= goal => .... => sum[i .. i] <= goal

* Time complexity: O(2N)
* Space complexity: O(1)
 */
    // % Same as atmost goal
    int subarraysWithSumLessThanEqualToGoal(vector<int> &nums, int goal)
    {
        if (goal < 0)
        {
            return 0;
        }
        int start = 0, end = 0, subarrays = 0, sum = 0;
        while (end < nums.size())
        {
            sum += nums[end];
            while (sum > goal)
            {
                sum -= nums[start++];
            }
            subarrays += (end - start + 1); // total subarrays ending at (end) given nums[end] is included;
            end++;
        }
        return subarrays;
    }
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {
        return subarraysWithSumLessThanEqualToGoal(nums, goal) - subarraysWithSumLessThanEqualToGoal(nums, goal - 1);
    }
};

//^ 9 Subarrays with K different distinct integers
class DistinctSubarrays
{
public:
    int atmostK(vector<int> &nums, int k)
    {
        unordered_map<int, int> m;
        int subarrays = 0;
        int start = 0;
        for (int end = 0; end < nums.size(); end++)
        {
            m[nums[end]]++;
            while (m.size() > k)
            {
                m[nums[start]]--;
                if (m[nums[start]] == 0)
                {
                    m.erase(nums[start]);
                }
                start++;
            }
            subarrays += (end - start + 1);
        }
        return subarrays;
    }
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        return atmostK(nums, k) - atmostK(nums, k - 1);
    }
};
int main()
{
    return 0;
}