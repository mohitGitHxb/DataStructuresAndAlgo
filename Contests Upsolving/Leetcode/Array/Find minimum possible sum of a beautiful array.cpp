#include <bits/stdc++.h>
using namespace std;

/* 
You are given positive integers n and target.

An array nums is beautiful if it meets the following conditions:

    nums.length == n.
    nums consists of pairwise distinct positive integers.
    There doesn't exist two distinct indices, i and j, in the range [0, n - 1], such that nums[i] + nums[j] == target.

Return the minimum possible sum that a beautiful array could have.

 

Example 1:

Input: n = 2, target = 3
Output: 4
Explanation: We can see that nums = [1,3] is beautiful.
- The array nums has length n = 2.
- The array nums consists of pairwise distinct positive integers.
- There doesn't exist two distinct indices, i and j, with nums[i] + nums[j] == 3.
It can be proven that 4 is the minimum possible sum that a beautiful array could have.

Example 2:

Input: n = 3, target = 3
Output: 8
Explanation: We can see that nums = [1,3,4] is beautiful.
- The array nums has length n = 3.
- The array nums consists of pairwise distinct positive integers.
- There doesn't exist two distinct indices, i and j, with nums[i] + nums[j] == 3.
It can be proven that 8 is the minimum possible sum that a beautiful array could have.

Example 3:

Input: n = 1, target = 1
Output: 1
Explanation: We can see, that nums = [1] is beautiful.

 */


/* 
The provided code aims to find the minimum possible sum of a "beautiful" array. A beautiful array is an array of distinct positive integers where no two elements sum up to a specific target.

Here's the breakdown of the code:

1. **Intuition**:
   - To create a beautiful array, the code starts with the smallest positive integer (1) and iteratively adds the next positive integers as long as the sum of any two elements in the array is not equal to the given target value `k`.
   - To ensure distinctness of elements, a `unordered_set` named `hs` is used to keep track of the numbers added to the array.
   - The process continues until the array has `n` elements, as specified by the input.

2. **Code Explanation**:
   - The code initializes an empty set `hs` to keep track of numbers that have been added to the beautiful array.
   - It initializes `sum` to 0, which will store the sum of the beautiful array.
   - It starts a loop to add numbers to the array until it reaches the desired length `n`.
   - Within the loop:
     - It checks if `k - num` is already present in the set `hs`. If it is not, it means that adding `num` will not result in a sum of `k`. In this case, it adds `num` to the `sum` and inserts it into the set `hs`.
     - If `k - num` is already present in `hs`, it decrements `i` by 1. This effectively repeats the addition of the current `num` to the array in the next iteration.

3. **Time Complexity**:
   - The code runs in O(n) time, where `n` is the length of the beautiful array. In the worst case, it will loop through all `n` elements to construct the array.

4. **Space Complexity**:
   - The space complexity is determined by the `unordered_set` `hs`, which can store at most `n` elements (all distinct positive integers up to `n`). Therefore, the space complexity is O(n).

5. **Hint**:
   - The code iteratively adds positive integers to the beautiful array, starting from 1. It checks if the current integer and its complement (to reach `k`) have already been added to the array. If not, it adds the integer; otherwise, it repeats the addition in the next iteration.
   - The loop continues until the beautiful array has `n` elements.

The code effectively constructs a beautiful array by adding distinct positive integers to it while ensuring that no two elements sum up to the given target `k`. It returns the minimum possible sum of such an array.
 */

    long long minimumPossibleSum(int n, int k) {
        unordered_set<long long> hs;
        long long sum = 0,num=1;
        for(int i = 0; i < n; i++){
            if(!hs.count(k - num)){
                sum += num;
                hs.insert(num);
            }
            else{
                i--;
            }
            num+=1;
        }
        return sum;
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
        //write code here
    }
    return 0;
}