#include <bits/stdc++.h>
using namespace std;
/* 
The problem requires finding the minimum number of operations to transform an array of non-negative powers of 2 (`nums`) into a subsequence whose elements sum to a given target (`target`). In each operation, you can choose an element `nums[i]` greater than 1, remove it, and add two occurrences of `nums[i] / 2` to the end of `nums`.

Here's a breakdown of the provided code:

1. **Initialization**:
   - `countBits`: This vector of size 31 is used to count the number of times each bit position (0 to 30) is set in the binary representation of the elements in `nums`.
   - `s`: This variable stores the sum of all elements in `nums`.

2. **Counting Bits and Calculating Total Sum**:
   - The code iterates through the elements of `nums`.
   - For each element `x`, it calculates its binary representation and increments the corresponding position in `countBits`.
   - It also updates the sum `s` by adding the current element `x`.

3. **Check for Impossibility**:
   - If the sum `s` is less than the target `m`, it returns -1 because it's impossible to obtain a subsequence whose elements sum to `m`.

4. **Main Loop**:
   - The code enters a loop where it tries to construct the subsequence.
   - It iterates through the bit positions from 0 to 29 (30 bits in total). The loop variable is `i`.
   - Within the loop:
     - It checks if the `i`-th bit is set in the binary representation of `m` using the bitwise AND operator `((1 << i) & m)`. If it's set, it means that `nums` should include an element with a bit set at position `i`.
     - If there are elements in `nums` that meet this condition (counted in `countBits[i]`), it simply decreases `countBits[i]` to indicate that one such element has been used.
     - If there are no elements in `nums` that meet this condition, it searches for the nearest available bit position that can be used (an unset bit after `i`). It increments `res` for each position it searches.
     - Once it finds an available position, it subtracts 1 from the `countBits` at the found position to indicate one such element has been used.
     - Then, it increments the `countBits` from the found position up to `i`, effectively adding the corresponding power of 2 back into `nums`.
     - It also updates `countBits[i+1]` by adding half of `countBits[i]` because, when a number is divided by 2, it contributes half of its count to the next bit position.
     - Finally, it increments `i` to check the next bit position.

5. **Result**:
   - The result is stored in the `res` variable, which holds the minimum number of operations required to construct the subsequence.
   - The code returns this result as the answer.

6. **Time Complexity**:
   - The code iterates through the `nums` array once to calculate `countBits` and the total sum `s`, resulting in O(n) operations.
   - The main loop has a complexity of O(30), which is a constant time operation.
   - So, the overall time complexity of the code is O(n).

7. **Space Complexity**:
   - The code uses a constant amount of space to store variables, except for the `countBits` vector, which requires O(31) = O(1) space.
   - Therefore, the space complexity is O(1).

8. **Hint**:
   - The code leverages the binary representation of numbers and bitwise operations to determine which elements in `nums` are used to construct the subsequence and efficiently update the counts.
 */
int minOperations(vector<int> &nums, int m)
{
    vector<int> countBits(31);
    long long s = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int x = nums.at(i);
        countBits[int(log2(x))]++;
        s += x;
    }
    if (s < m)
    {
        return -1;
    }
    int i = 0, res = 0;
    while (i < 30)
    {
        if ((1 << i) & m)
        {
            if (countBits.at(i) > 0)
            {
                countBits.at(i)--;
            }
            else
            {
                int j = i;
                while (j < 30 and countBits.at(j) == 0)
                {
                    j++;
                    res++;
                }
                countBits.at(j)--;
                while (j > i)
                {
                    countBits.at(--j)++;
                }
            }
        }

        countBits.at(i+1) += countBits.at(i)/2;
        i++;
    }
    return res;
}

//^ Alternative approach using priority queue
class Solution {
public:
    int minOperations(vector<int>& nums, int target) {
        priority_queue<int> pq;
        /*We keep a track of sum to decide whether to break the 
        element in consideration into two halves or not.*/
        long long sum=0;

        //Push elements into the max heap
        for(int i=nums.size()-1;i>=0;i--){
            pq.push(nums[i]);
            sum+=nums[i];
        }

        int ans=0;

        //While loop till the target is not achieved
        while(target>0){
            int front = pq.top();
            sum-=front;
            pq.pop();

            /*Case 1: If top element is less than target, then just 
            subtract the element. No need to divide it at this
            point.*/

            if(front<=target){
                target-=front;
            }

            /*Case 2: If top element is greater than target but sum
             upto top element is less than target. In this case, we 
            should split the top element to two halves.*/

            else if(front>target && sum<target){
                ans++;
                sum+=front;
                pq.push(front/2);
                pq.push(front/2);
            }

            /*Case 3: If our priority queue is empty and we have 
            yet not reached our target, then just return -1;*/

            if(pq.empty() && target!=0){
                return -1;
            }

        }
        //Finally we return our ans which we increment at every divide
        return ans;
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