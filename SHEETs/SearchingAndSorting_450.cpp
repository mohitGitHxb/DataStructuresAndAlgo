#include <bits/stdc++.h>
using namespace std;

//^1 First occurrence and last occurrence of a element in the sorted array
//* O(logN) T.C | O(1) space
vector<int> findOccurrences(int arr[], int n, int x)
{
    int firstOccur = -1, lastOccur = -1;
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if (arr[mid] == x)
        {
            if (arr[mid - 1] != arr[mid])
            {
                firstOccur = mid;
                break;
            }
            else
            {
                high = mid - 1;
            }
        }
        else if (arr[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if (arr[mid] == x)
        {
            if (arr[mid + 1] != arr[mid])
            {
                lastOccur = mid;
                break;
            }
            else
            {
                low = mid + 1;
            }
        }
        else if (arr[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return {firstOccur, lastOccur};
    /*
    @ Using lower and upper bound
     */
    int first = lower_bound(arr, arr + n, x) - arr;
    int last = upper_bound(arr, arr + n, x) - arr - 1;
    if (first >= n || arr[first] != x)
        return {-1, -1};
    else
        return {first, last};
}

//^2 Value equal to the index in Unsorted array
//* O(N) T.C | O(1) S.C

vector<int> valueEqualToIndex(int arr[], int n)
{
    // code here
    vector<int> res;
    for (int i = 0; i < n; i++)
        if (i + 1 == arr[i])
            res.push_back(arr[i]);
    return res;
}

//^3 Search in a rotated sorted array
int searchInRotatedArray(vector<int> &nums, int target)
{
    int low = 0, high = nums.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (target == nums[mid])
            return mid;
        //? there exists rotation; the middle element is in the left part of the array
        if (nums[mid] > nums[high])
        {
            if (target < nums[mid] && target >= nums[low])
                high = mid - 1;
            else
                low = mid + 1;
        }
        //? there exists rotation; the middle element is in the right part of the array
        else if (nums[mid] < nums[low])
        {
            if (target > nums[mid] && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
        //? there is no rotation; just like normal binary search
        else
        {
            if (target < nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
    }

    return -1;
}

//^4 Count squares less than N
//* O(sqrt(N)) T.C | O(1) S.C
int countSquares(int N)
{
    int squares = 0;
    for (int i = 1; i * i < N; i++)
        squares++;
    return squares;
}

//^5 Find missing and repeating element in an array of N+1 integers
int *findTwoElement(int *arr, int n)
{
    //! O(N) T.C | O(N) S.C
    /*         bool visited[n+1] = {false}; //? Auxillary array to keep track of visited elements in the array
            int *ans = new int[2];
            for(int i = 0; i < n; i++){
                if(visited[arr[i]]){ //? if already visited that means this element is repeating itself.
                    ans[0] = arr[i];
                    continue;
                }
                else{
                    visited[arr[i]] = true;
                }
            }
            for(int i = 1; i <= n; i++)
                if(visited[i] == false)
                    {ans[1] = i; return ans;}
            return ans; */

    /*
    & Idea is to use individual value as index. And the one with repetition will try to access same index twice and will get caught. The catch is that there will be one  element in the array which hasn't been accessed and BOOM this is the one who's corresponding value is missing in the array
    * O(N) T.C | O(1) S.C
     */
    int *answer = new int[2]{-1};
    int i = 0;
    int value = 0;
    int element = 0;

    for (i = 0; i < n; i++)
    {
        value = abs(arr[i]);
        element = arr[value - 1];
        if (element > 0)
            arr[value - 1] = -element;
        else
            answer[0] = value;
    }
    for (i = 0; i < n; i++)
    {
        if (arr[i] > 0)
        {
            answer[1] = i + 1;
            break;
        }
    }
    return answer;
}

//^ 6 Count inversions
class CountInversions
{
public:
    /*
    & method - 1: Brute force --> Fix one element and find elements smaller than this element in the remaining array and update the inversionCount accordingly.

    ! O(N^2) T.C | O(1) S.C

  &  method - 2: Using Merge sort...
  &   Whenever we are merging two sorted arrays, check for the case when arr[i]>arr[j] and update the inversionCount accordingly.

  * O(NlogN) T.C | O(N) S.C
     */
    // arr[]: Input Array
    // N : Size of the Array arr[]
    // Function to count inversions in the array.
    void mergeSort(long long arr[], long long lo, long long hi, long long &ans)
    {
        if (lo < hi)
        {
            long long mid = lo + (hi - lo) / 2;
            mergeSort(arr, lo, mid, ans);
            mergeSort(arr, mid + 1, hi, ans);
            merge(arr, lo, mid, hi, ans);
        }
    }

    void merge(long long arr[], long long lo, long long mid, long long hi, long long &ans)
    {
        long long n1 = mid - lo + 1, n2 = hi - mid;
        long long arr1[n1], arr2[n2];
        for (long i = 0; i < n1; i++)
            arr1[i] = arr[lo + i];
        for (long i = 0; i < n2; i++)
            arr2[i] = arr[mid + i + 1];
        long long i = 0, j = 0, k = lo;
        while (i < n1 && j < n2)
        {
            if (arr1[i] <= arr2[j])
                arr[k++] = arr1[i++];
            else
            {
                ans += n1 - i; //? We are not doing ans++; because if J becomes equal to n2, We won't be able to tell whether there are more inversions possible here. To avert this, Rather than adding '1' we add the difference 'n1-i' This ensures that we don't miss on any element as if let's say a element in j is smaller than i that means every element in arr1 after 'i' must be greater than arr2[j].
                arr[k++] = arr2[j++];
            }
        }
        while (i < n1)
            arr[k++] = arr1[i++];
        while (j < n2)
            arr[k++] = arr2[j++];
    }
    long long int inversionCount(long long arr[], long long N)
    {
        // Your Code Here
        if (N == 0)
            return 0;
        long long inversions = 0;
        mergeSort(arr, 0, N - 1, inversions);
        return inversions;
    }
};

//^ 7 Searching in an array where adjacent differ by at most k
/*
& Instead of directly using linear search and searching each element, we need to use the given information and modify it to search elements where we have maximum probability of finding the required element.

& To do this, while traversing the array, if the current element is not the required element:

&     Calculate absolute difference between element at current index and required element. This will give an idea of how far the required element can be from the current element.
&    Now, assuming that the difference between adjacent elements is exactly k, we can find the least number of jumps required to reach required element from current element by dividing the calculated difference by k.
&    Incase the difference between current element and required element is smaller than k, its division will result in 0, it means that we need to increment the iterator by 1, thus we take maximum of 1 or least jumps calculated and increment iterator by that.
 */
int search_in_adjacent(int arr[], int n, int x, int k)
{
    for (int i = 0; i < n;)
    {
        if (x == arr[i])
            return i;
        else
        {
            i += max(1, abs(x - arr[i]) / k);
            continue;
        }
        i++;
    }
    return -1;
}

//^ 8 Find pair with given difference
bool find_pair(vector<int> &arr, int difference)
{

    /*
   ! method - 1 : Brute force O(N^2) T.C
   * method - 2: Two pointers technique and sorting O(NlogN) T.C | O(1) S.C
   & Maintain two pointers i and j , increment i when the difference between arr[i] and arr[j] becomes more than given difference, otherwise increment j when the difference between arr[i] and arr[j] becomes less than given difference.

   & if arr[j] - arr[i] becomes the given difference check if i and j are not pointing to the same element then return true
     */
    int size = arr.size();
    sort(arr.begin(), arr.begin() + size);
    int i = 0, j = 1;
    while (i <= j && j < size)
    {
        if (abs(arr[i] - arr[j]) == difference && i != j)
            return true;
        else if (abs(arr[j] - arr[i]) > difference)
            i++;
        else
            j++;
    }

    return false;
}

//^ 9 Find All four sum numbers
/*
& Basically this problem is an extension of the 3 sum problem but we need to print every unique possible combination of 4 elements.
& To solve this, first fix two numbers then this problem is reduced to two sum problem which is solved by using two pointers technique. So, we store the combination in a set (to avoid duplicates) and print them

* O(N^3) T.C | O(N^2) S.C
 */
vector<vector<int>> fourSum(vector<int> &arr, int sum)
{

    vector<vector<int>> ans;
    set<vector<int>> s;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size() - 3; i++)
    {
        for (int j = i + 1; j < arr.size() - 2; j++)
        {
            int left = j + 1;
            int right = arr.size() - 1;
            while (left < right)
            {
                if (arr[left] + arr[right] + arr[i] + arr[j] == sum)
                {
                    s.insert({arr[i], arr[j], arr[left], arr[right]});
                    left++;
                    right--;
                }
                else if (arr[left] + arr[right] + arr[i] + arr[j] < sum)
                    left++;
                else
                    right--;
            }
        }
    }
    for (auto &i : s)
        ans.push_back(i);
    return ans;
}

//^ 10 Stickler thief problem
int maxHouseLooted(vector<int> &arr)
{
    if (arr.size() < 2)
        return arr[arr.size() - 1];
    //? storing sum up to current element including and
    //? excluding it in respective variables.
    int ans = max(arr[0], arr[1]);
    int previousItem = arr[0];
    for (int i = 2; i < arr.size(); i++)
    {
        int temp = previousItem;
        //? updating sum up to current element excluding it as maximum
        //? of sum upto previous element excluding and including it
        ans = max(previousItem + arr[i], ans);
        previousItem = temp;
    }
    return ans;
}

//^ 11 Count triplets having sum less than given sum

/*
& We need three elements right, obviously we want a triplet so we wanna leave three two elements at the end for triplets. So we traverse this from i=0 to i<n-2
& Now we use two pointers, j=i+1 and k=n-1,
& We will run a while loop for pointers till j<k  and we will check the sum
~ let sum=arr[i]+arr[j]+arr[k]
& and if the sum is less than the target, we increment our result with ans+=(k-j), WHY??? , IF YOUR LARGEST NUMBER K IS ADDED TO SOME ELEMENT IN YOUR RANGE J TO K AND IT IS LESS THAN TARGET…IT MEANS ALL NUMBERS BETWEEN IT WILL FOR SURE MAKE TRIPLETS AND THAT TRIPLET COUNT WILL BE THE DIFFERENCE BETWEEN THE POINTER J AND K WHEN THE SUM IS LESS THAN TARGET…

& If the sum is less than target , increment res and increment j++, since we have can still increment it because its lower than target.
& If found sum is greater than target, lower end pointer.



* O(N^2) T.C | O(1) S.C
 */
long long countTriplets(vector<int> &arr, int sum)
{
    int n = arr.size();
    if (n < 3)
        return -1;
    sort(arr.begin(), arr.end());
    long long ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int low = i + 1;
        int high = n - 1;
        while (low < high)
        {
            if (arr[i] + arr[low] + arr[high] < sum)
            {
                ans += (high - low);
                low++;
            }
            else
            {
                high--;
            }
        }
    }
    return ans;
}

//^ 11 Count the number of sub arrays having sum zero
long long int findSubarray(vector<long long int> &arr, int n)
{
    /*
~ Method - 1
&    If subarray [l,r] sum is 0 then prefixSum[l-1] = prefixSum[r] which is easy to prove
&    Now for each r we can calculate the l indices with same sum and we can keep track of the count of l indices using map while looping through.
&    Using map we can count the frequency of the prefix sums until r and add (frequency[sum] - 1) which is ( count of  l indices = Subarrays with sum 0 ending at index r)
&    After calculating for each r i.e. 0 to n-1 we return the sum of all values as result

% O(NlogN) T.C | O(N) S.C

~ Method - 2

&    calculate the prefixSum for every element
&    now check how many times the particular prefixSum is repeat (let's say x times repeat), then our answer is the summation of whole these (x*(x-1))/2
&    example      {0,0,5, 5,  0,  0}
&    prefix sum = 0 0 5 10 10 10
&    particular prefixSum                   it's cnt / repetition (x)
@           0                                           2
@           5                                           1
@          10                                           3
&   answer = ( (2*1)/2 + (1*0)/2 +(3*2)/2 )
&       for =>    0(x = 2)    5(x = 1)   10(x = 3)
&    hence answer = 1 + 0 + 3 = 4
&    But wait we should also have to add 2 in our answer, as that's the special conditions which we've to always remembered that how many times we get 0 in our prefixSum==> so 0 count is 2
&    Hence our final answer will be,
&    Answer = 4 + 2 = 6

* O(N) T.C and S.C


     */
    unordered_map<long long, int> mp;
    long long prefixSum = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        prefixSum += arr[i];
        mp[prefixSum]++;
    }
    int add = 0;
    for (auto &it : mp)
    {
        if (it.first == 0)
            add += it.second;
        ans += (it.second) * (it.second - 1) / 2;
    }
    return ans + add;
}

//^ 12 Missing number in an Arithmetic Progression
/*
& A : first term, C: common difference , B: element needed to be found
& Simple class 10th Ap eqn An = A + (n - 1)d
* O(1) T.C | O(1) S.C
 */
int inSequence(int A, int B, int C)
{
    if (C == 0 && A == B)
        return 1;
    else if (C == 0)
        return 0;
    int n = 1 + (B - A) / C;
    return ((B - A) % C == 0 && n > 0);
}
//^ 13 Product Puzzle Array
vector<long long int> productExceptSelf(vector<long long int> &nums, int n)
{
    // code here
    /*
    & Fix one element at a time and find the product of whole array excluding
    & this element.

    ! O(N^2) T.C | O(N) S.C
     */
    /*         vector<long long> ans;
            long long prod=1;
            for(int i = 0; i < nums.size(); i++){
                int curr = nums[i];
                bool flag = true; //? To handle duplicates
                for(int j = 0; j < nums.size(); j++){
                    if(prod!=0 && (nums[j]!=curr || flag))
                        prod*=nums[j];
                    else if(prod == 0)
                        break;
                }
                ans.push_back(prod);
                prod=1;
            }
            return ans; */

    // * O(N) T.C | O(N) S.C
    vector<long long> ans(nums.size());
    long long prod = nums[0];
    ans[0] = 1;
    for (int i = 1; i < nums.size(); i++)
    {
        ans[i] = prod;
        prod *= nums[i];
    }
    prod = nums.back();
    for (int i = nums.size() - 2; i >= 0; i--)
    {
        ans[i] *= prod;
        prod *= nums[i];
    }
    return ans;
}

//^ 14 Sort according to set bits
class SortBits
{
    //* O(NlogN) T.C | O(1) S.C
public:
    static bool comp(int a, int b)
    {
        //? this is a inbuilt function in c++ which finds the count of set bits.
        return __builtin_popcount(a) > __builtin_popcount(b);
    }
    void sortBySetBitCount(int arr[], int n)
    {
        stable_sort(arr, arr + n, comp);
    }
};

//^ 15 Minimum number of swaps to sort the array
/*
& Given array has no duplicates!
& had there been duplicates we would've used stable_sort instead of sort

* O(NlogN) T.C | O(N) S.C
*/
int minSwaps(vector<int> &nums)
{
    vector<pair<int, int>> temp; //? creating temporary [sorted] array which stores element and index
    for (int i = 0; i < nums.size(); i++)
    {
        temp.push_back(make_pair(nums[i], i));
    }
    int swapCount = 0;
    sort(temp.begin(), temp.end());
    for (int i = 0; i < nums.size(); i++)
    {
        if (i != temp.at(i).second) //? If index of current element is different than the index of current element in sorted temp array,
                                    //? then we can safely say there is a swapping between these two elements
        {
            swapCount++;
            swap(temp.at(i), temp.at(temp.at(i).second)); //? making the sorted array same as the nums array (the swap count will remain the same)
            i--;
        }
    }
    return swapCount;
}

//^ 16 Allocate minimum number of pages
class AllocatePage
{
private:
    /*
    ~ Method - 1: Recursive Approach
    & We need to make cuts in the books array. let there be books from X0 to Xn-1
    & then we cut this array such that (k-1) students read books from X0 to Xi-1(i books)
    &then we calculate the sum of pages from Xi to Xn-1 and these books are allocated to the first person.
    & Recursively call the function for left half and for k - 1 student

    ! O(N!) T.C



    ~ Method - 2: Binary Search
    & Compute maximum element in the array and the total sum of the elements in the array this [low,high] is the range of possible answer.
    & calculate the middle value (say mid). Check if this mid is a valid answer by
    & calculating the students such that each student can read maximum 'mid' pages
    & if this students value is greater than K then it is not a valid answer. Just do low = mid + 1;
    & if this students value is smaller or equal than K then it is a valid answer then do high = mid - 1
    & because every value from mid to high would be the possible ans but here we need to minimize it.
    & keep doing the same till low<=high and then return the answer.

    *O(NlogN) T.C | O(1) S.C
     */
protected:
public:
    int sumRange(vector<int> &arr, int start, int end)
    {
        int sum = 0;
        for (int i = start; i < end; i++)
        {
            sum += arr[i];
        }
        return sum;
    }
    int minimumPages(vector<int> &books, int n, int k)
    {
        /*     if(k == 1)
                return sumRange(books,0,books.size()-1);
            if(books.size() == 1)
                return books.front();
            int res = INT_MAX;
            for(int i=1; i<n;i++){
                res = min(res,max(minimumPages(books,i,k-1),sumRange(books,i,n-1)));
            }
            return res; */

        if (n < k)
            return -1;
        int end = 0, start = 0;
        for (int i = 0; i < n; i++)
        {
            end += books[i];
            start = max(start, books[i]);
        }

        int res = -1;
        while (start <= end)
        {
            int mid = (start + end) / 2;
            if (isValid(books, mid, k))
            {
                res = mid;
                end = mid - 1;
            }
            else
                start = mid + 1;
        }
        return res;
    }

    bool isValid(vector<int> &arr, int mid, int k)
    {
        int student = 1;
        int sum = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            sum = sum + arr[i];
            if (sum > mid)
            {
                student++;
                sum = arr[i];
            }
            if (student > k)
                return false;
        }
        return true;
    }
};

//^ 17 Aggressive cows
class AggressiveCows
{
private:
    /*
~    Sort the array:

& Since the minimum distance between two stalls will be distance between the consecutive stalls.

~Set the Search Space:

& It means take a range in which answer could lie, here i have taken range (0, maxElement - minElement). Since answer could not be less than '0' and could not more than 'maxElement - minElement'.

~ Calculate Mid and check if its valid or not :

~ Calculate mid = low+(high-low)/2; (we are considering, mid is the minimum distance between the cows, which is maximum)

& checking if its the valid distance between the cows or not:

&   If Valid: we will increase mid value by moving in right half as we have to maximise the minimum distance i.e. low = mid+1;

& If Not Valid: It means with 'mid' as minimum distance we can not accommodate cows(there must be cows left to accommodate in stalls), hence if we decrease the 'mid' which is minimum distance we considered, then we can accommodate all cows. Therefore decrease the mid by moving in left half. i.e. high = mid-1

~ Valid Function: It will check if with mid distance, cow can be accomodated or not?

& increase cows count if distance between two consecutive stalls is greater than or equals to mid (that means we are placing a cow in above situation).

& As soon as cows count equals to number of cows given, it means with 'mid' as minimum distance, we have placed all the cows, hence return true

& In other situation the cows count will be less than given cows, thats means we can not accomodate given number of cows with 'mid' minimum distance. (i.e. we need to decrease the the mid(distance between cows) value so, all cow will be accomodated)
     */
public:
    bool isPossible(vector<int> &arr, int mid, int k)
    {
        int cowCount = 1;
        int lastPos = arr[0];
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] - lastPos >= mid)
            {
                cowCount++;
                if (cowCount == k)
                {
                    return true;
                }
                lastPos = arr[i];
            }
        }
        return false;
    }
    int solve(vector<int> &stalls, int k)
    {
        sort(stalls.begin(), stalls.end());
        int start = 0;
        int end = stalls.back() - stalls.front();
        int ans = -1;
        while (start <= end)
        {
            int mid = (start + end) / 2;
            if (isPossible(stalls, mid, k))
            {
                ans = max(ans, mid);
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
        return ans;
    }
};

//^ 18 Bishu and Soldiers
/*
& Sort the array and simply apply binary search to find the count of elements that
& are less than the given power. pre compute the sum of the elements in a prefixSum array

* O(NlogN) T.C | O(N) S.C
 */
pair<int, int> soldiersDefeated(vector<int> &powerLevels, int power)
{
    sort(powerLevels.begin(), powerLevels.end());
    vector<int> prefixSum(powerLevels.size() + 1);
    for (int i = 1; i < powerLevels.size(); i++)
    {
        prefixSum[i] = prefixSum[i - 1] + powerLevels[i - 1];
    }
    auto idx = upper_bound(powerLevels.begin(), powerLevels.end(), power) - powerLevels.begin();

    return {idx, prefixSum[idx]};
}

//^ 19 Kth smallest element in a range
class kthSmallestElementAgain
{
private:
    /*
    & 1. Sort the intervals array and merge the intervals to avoid overlapping
    & 2. Check if the Kth smallest element can be present in the range as the difference between elements is only '1' we can use this formula: second - first + 1
    & 3. IF it is there in the range then update the answer and break the loop
    & 4. else update the K by reducing it to the K - (second-first+1)

    * O(NlogN) T.C | O(N) S.C
     */
public:
    vector<pair<int, int>> mergeIntervals(vector<pair<int, int>> &intervals)
    {
        vector<pair<int, int>> merged;
        for (auto &&interval : intervals)
        {
            if (merged.empty() || merged.back().second < interval.second)
            {
                merged.push_back(interval);
            }
            else
            {
                merged.back().second = max(merged.back().second, interval.second);
            }
        }
        return merged;
    }
    int kthSmallest(vector<pair<int, int>> &intervals, int K)
    {
        sort(intervals.begin(), intervals.end());
        vector<pair<int, int>> arr = mergeIntervals(intervals);
        int ans = -1;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i].second - arr[i].first + 1 >= K)
            {
                ans = arr[i].first + K - 1;
                break;
            }
            else
            {
                K = K - (arr[i].second - arr[i].first + 1);
            }
        }
        return ans;
    }
};

//^ 20 EKO-SPOJ
class EkoSPOJ
{
private:
    /*
        & Use Search Space method (similar to allocate minimum no. of pages / painter's partition algorithm)
     */
public:
    bool isValid(vector<int> &arr, int mid, int k)
    {
        int sum = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] - mid > 0)
                sum += (arr[i] - mid);
            else
                sum += 0;
        }
        return sum >= k;
    }
    int maxLevel(vector<int> &arr, int k)
    {
        int low = *min_element(arr.begin(), arr.end());
        int high = *max_element(arr.begin(), arr.end());
        int ans = -1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (isValid(arr, mid, k))
            {
                ans = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return ans;
    }
};

//^ 21 Roti-Prata SPOJ
class RotiPrata
{
private:
public:
    bool isFeasible(vector<int> &cooks, unsigned int mid, int k)
    {
        unsigned int time = 0;
        unsigned int prata = 0;
        for (int i = 0; i < cooks.size(); i++)
        {
            time = cooks[i];
            int j = 2;
            while (time <= mid)
            {
                prata++;
                time += (cooks[i] * j);
                j++;
            }
            if (prata >= k)
            {
                return true;
            }
        }
        return false;
    }
    int minimumTime(vector<int> &cooks, int k)
    {
        unsigned int low = 0;
        unsigned int high = 10e8;
        unsigned int ans = 0;
        while (low <= high)
        {
            unsigned int mid = (low + high) / 2;
            if (isFeasible(cooks, mid, k))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};

//^ 22 Double-Helix SPOJ
/*
~ Two Pointer Approach.
& let the two sequence be a0 a1 a2 ... an & b0 , b1 b2 ... bn
& suppose a3 and b3 are common points, to choose the path with maximum sum
& we need to calculate the sum from a0 to a2(sumA) and b0 to b2(sumB)
& ans = ans + max(sumA,sumB) + a[i] or B[i]
& kind of same as merging two arrays
* O(N) T.C and S.C
 */
int pathWithMaxSum(vector<int> &A, vector<int> &B)
{
    int sumA = 0;
    int sumB = 0;
    int i = 0, j = 0;
    int ans = 0;
    while (i < A.size() && j < B.size())
    {
        if (A[i] < B[j])
        {
            sumA += A[i++];
        }
        else if (A[i] > B[j])
        {
            sumB += B[j++];
        }
        else
        {
            ans += max(sumA, sumB) + A[i];
            i++;
            j++;
            sumA = sumB = 0;
        }
    }

    while (i < A.size())
    {
        sumA += A[i++];
    }
    while (j < A.size())
    {
        sumB += B[j++];
    }
    ans += max(sumA, sumB);
    return ans;
}

//^ 23 Kth element in two sorted arrays
/*
~ Method - 1: Two pointer / Divide and Conquer
& We will keep two pointers, say p1 and p2, each in two arrays. A counter to keep track of whether we have reached the kth position. Start iterating through both arrays. If array1[p1] < array2[p2], move p1 pointer ahead and increase counter value. If array2[p2] <array1[p1], move p2 pointer ahead and increase counter. When the count is equal to k, return the element in which condition makes the counter value equal to k.

!O(K) T.C | O(1) S.C

~ Method - 2: BINARY SEARCH
& Apply binary search in an array with a small size. Start iterating with two pointers, say left and right. Find the middle of the range. Take elements from low to middle of array1 and the remaining elements from the second array. Then using the condition mentioned above, check if the left half is valid. If valid, print the maximum of both array’s last element. If not, move the range towards the right if l2 > r1, else move the range towards the left if l1 > r2.

* O(min( log(min(m,n)) ) T.C | O(1) S.C

 */
int kthElement(int arr1[], int arr2[], int n, int m, int k)
{
    if (m > n)
    {
        return kthElement(arr2, arr1, m, n, k);
    }

    int low = max(0, k - m);
    int high = min(k, n);
    while (low <= high)
    {
        int cut1 = (low + high) / 2;
        int cut2 = (k - cut1);
        int left1 = cut1 == 0 ? INT_MIN : arr1[cut1 - 1];
        int left2 = cut2 == 0 ? INT_MIN : arr2[cut2 - 1];
        int right1 = cut1 == n ? INT_MAX : arr1[cut1];
        int right2 = cut2 == m ? INT_MAX : arr2[cut2];

        if (left1 <= right2 && left2 <= right1)
        {
            return max(left1, left2);
        }
        else if (left1 > right2)
            high = cut1 - 1;
        else
            low = cut1 + 1;
    }
    return 1;
}

//^ 24 Subset Sum SPOJ
class subsetSum
{
private:
    /*
   & v1,v2 stores the subsequence sum  of 1st and 2nd half respectively.
   & sort both the subset sums
   & Now, lets say X(from v1) and Y(from v2) is taken such that
   & 1. X + Y = A; ==> Y = A - X <--- find y using lower bound
   & 2. X + Y = B; ==> Y = B - X <--- find y using upper bound
   & Now our count is high - low;

   *O(NlogN) T.C | O(N) S.C
     */
    vector<int> v1, v2;

public:
    void subsetSumGenerator(vector<int> &arr, int low, int high)
    {
        int start = 0;
        int n = high - low + 1;
        for (int i = 0; i < (1 << n); i++)
        { //? 1 << n is same as 2^n
            start = 0;
            int j = start;
            int x = i;
            while (x)
            {
                int lo = x & 1;
                if (lo)
                    start += arr[j];
                j++;
                x >>= 1;
            }
            v1.push_back(start);
        }
    }
    int getCount(vector<int> &arr, int a, int b)
    {
        int count = 0;
        for (int i = 0; i < v1.size(); i++)
        {
            int low = lower_bound(v2.begin(), v2.end(), a - v1[i]) - v2.begin();
            int high = upper_bound(v2.begin(), v2.end(), b - v1[i]) - v2.begin();
            count += high - low;
        }
        return count;
    }
};

//^ -------------------------------------------------------------------------------
//? Additional questions from striver SDE sheet [BINARY SEARCH]

//^ 25 Search in a rotated sorted array with duplicates
/*
    Initialize low and high as the starting and ending indices of the array, respectively.

    Use a while loop to perform binary search until low is less than or equal to high.

    Calculate the mid index as the average of low and high.

    Compare the element at mid with the target. If they are equal, return true as the target is found in the array.

    Check if arr[low] is equal to arr[high]. This condition is used to handle duplicate elements in the array.

    If arr[low] is equal to arr[high], and target is equal to arr[low], return true as the target is found.

    Otherwise, increment low and decrement high to skip the duplicate elements at both ends of the array.

    Check if the left half of the array is sorted (i.e., arr[low] <= arr[mid]).

    If the left half is sorted and the target lies between arr[low] and arr[mid], then update high to mid - 1 to search in the left half.

    If the target does not lie in the left half, update low to mid + 1 to search in the right half.

    If the right half of the array is sorted (i.e., arr[mid] <= arr[high]).

    If the right half is sorted and the target lies between arr[mid] and arr[high], then update low to mid + 1 to search in the right half.

    If the target does not lie in the right half, update high to mid - 1 to search in the left half.

    Repeat steps 3 to 13 until the target is found or low becomes greater than high.

    If the target is not found after the while loop, return false.

~   The intuition behind this code is to use binary search to efficiently find the target element in the rotated sorted array. The code handles cases of duplicates by incrementing low and decrementing high when they are equal to skip the duplicate elements.

*   The time complexity of the code is O(log n) as it uses binary search, where n is the number of elements in the array. The space complexity is O(1) as it uses only a constant amount of extra space for variables.

 */

bool search(vector<int> &arr, int target)
{
    int low = 0, high = arr.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == target)
            return true;
        if (arr[low] == arr[high])
        {
            if (target == arr[low])
                return true;
            low++;
            high--;
        }
        else if (arr[low] <= arr[mid])
        {
            if (target < arr[mid] && target >= arr[low])
            {
                high = mid - 1;
            }
            else
                low = mid + 1;
        }
        else if (arr[high] >= arr[mid])
        {
            if (target > arr[mid] && target <= arr[high])
            {
                low = mid + 1;
            }
            else
                high = mid - 1;
        }
    }
    return false;
}

//^ 26 Find minimum in a rotated sorted array using binary search
/*
&- Initialize low and high as the starting and ending indices of the array, respectively.

&- Check if the array is already sorted in non-decreasing order by comparing the first and last elements. If it is, return the first element as it is the minimum.

&- Set ans to a large value (1e9) to keep track of the minimum element found so far.

&- Use a while loop to perform binary search until low is less than or equal to high.

&- Calculate the mid index as the average of low and high.

&- Compare the element at low with the element at high. If the subarray from low to high is already sorted in non-decreasing order, then the minimum element is arr[low]. Update ans to min(ans, arr[low]) and return ans.

&- Otherwise, check if the left half of the array is sorted (i.e., arr[low] <= arr[mid]). If it is, update ans to min(ans, arr[low]) and narrow the search to the right half of the array by updating low to mid + 1.

&- If the left half is not sorted, then the right half must be sorted. Update ans to min(ans, arr[mid]) and narrow the search to the left half of the array by updating high to mid - 1.

&- Repeat steps 4 to 7 until the minimum element is found or low becomes greater than high.

&- If the minimum element is not found after the while loop, return ans.

~   The intuition behind this code is to use binary search to efficiently find the minimum element in the rotated sorted array. The code handles cases of duplicates by updating ans whenever it encounters a new potential minimum element.

*   Time Complexity: The code uses binary search, so the time complexity is O(log n), where n is the number of elements in the array.

*   Space Complexity: The code uses only a constant amount of extra space for variables, so the space complexity is O(1).
 */
int findMin_bs(int arr[], int n)
{
    // complete the function here
    int low = 0, high = n - 1;
    if (arr[low] <= arr[high])
        return arr[low];
    int ans = 1e9;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[low] <= arr[high])
        {
            ans = min(ans, arr[low]);
            return ans;
        }
        else if (arr[low] <= arr[mid])
        {
            ans = min(ans, arr[low]);
            low = mid + 1;
        }
        else if (arr[high] >= arr[mid])
        {
            ans = min(ans, arr[mid]);
            high = mid - 1;
        }
    }
    return ans;
}

//^ 27 Find how many times the array is rotated.
/*
&- The given code aims to find the number of times a sorted array has been rotated. It uses a modified binary search to efficiently find the rotation count.

&- The algorithm initializes low and high as the starting and ending indices of the array, respectively. It also sets ans to a large value (1e9) and minIndex to 0 to keep track of the minimum element and its index found so far.

&- Use a while loop to perform binary search until low is less than or equal to high.

&- Calculate the mid index as the average of low and high.

&- Check if the subarray from low to high is already sorted in non-decreasing order by comparing the elements at low and high. If it is, update ans and minIndex to arr[low] and low, respectively, and break the loop.

&- If the left half of the array is sorted (i.e., arr[low] <= arr[mid]), update ans and minIndex to arr[low] and low, respectively, and narrow the search to the right half of the array by updating low to mid + 1.

&- If the left half is not sorted, then the right half must be sorted. Update ans and minIndex to arr[mid] and mid, respectively, and narrow the search to the left half of the array by updating high to mid - 1.

&- Repeat steps 4 to 7 until the minimum element is found or low becomes greater than high.

&- After the while loop, return minIndex, which represents the number of times the sorted array has been rotated.

~ Intuition: The code performs a modified binary search to efficiently find the rotation count. The binary search narrows down the search space to locate the minimum element, which corresponds to the number of rotations. The algorithm keeps track of the minimum element and its index during the search process.

*- Time Complexity: The code uses binary search, so the time complexity is O(log n), where n is the number of elements in the array.

*- Space Complexity: The code uses only a constant amount of extra space for variables, so the space complexity is O(1).

*- Hints: The given array was initially sorted, so it is still mostly sorted after the rotation. Therefore, binary search can be a suitable approach to find the rotation count efficiently. Keep track of the minimum element and its index during the search to determine the rotation count.
 */
int findKRotation(int arr[], int n)
{
    // code here
    int low = 0, high = n - 1;
    int ans = 1e9, minIndex = 0;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[low] <= arr[high])
        {
            if (arr[low] < ans)
            {
                ans = arr[low];
                minIndex = low;
            }
            break;
        }
        else if (arr[low] <= arr[mid])
        {
            if (arr[low] < ans)
            {
                ans = arr[low];
                minIndex = low;
            }
            low = mid + 1;
        }
        else
        {
            if (arr[mid] < ans)
            {
                ans = arr[mid];
                minIndex = mid;
            }
            high = mid - 1;
        }
    }
    return minIndex;
}

///^ 28 Find the single element in a rotated sorted array
class SingleElement
{
public:
    /*
    @ Using Xor operator
    ? Works even for non sorted arrays
    ! O(N) T.C | O(1) S.C
     */
    int singleNonDuplicate(vector<int> &nums)
    {
        int ans = nums.front();
        for (int i = 1; i < nums.size(); i++)
        {
            ans = ans ^ nums.at(i);
        }
        return ans;
    }
    /*
    @ Binary search
    &- The given code aims to find the element in a sorted array that occurs only once (with a frequency of 1), while all other elements occur exactly twice.

&- The algorithm first handles base cases for arrays of size less than 2, where the single element is the result.

&- Then, it checks if the first and second elements are different. If so, the first element is the result.

&- Similarly, it checks if the last and second-to-last elements are different. If so, the last element is the result.

&- After these checks, a binary search is performed to find the element with frequency 1. The search space is narrowed down by updating `low` and `high` pointers in each iteration.

&- In each iteration, the middle element `mid` is calculated using bitwise right shift (`>> 1`) for better performance.

&- If the middle element is not equal to its adjacent elements, it means the middle element has a frequency of 1, and it is returned as the result.

&- Otherwise, it checks the parity of `mid`. If it is odd, then the left half has even elements, and the right half has odd elements. So, if `mid` is equal to its left adjacent element, the element with frequency 1 is in the right half, and the search space is narrowed to the right half by updating `low` to `mid + 1`.

&- Otherwise, if `mid` is equal to its right adjacent element, the element with frequency 1 is in the left half, and the search space is narrowed to the left half by updating `high` to `mid - 1`.

&- The binary search continues until the element with frequency 1 is found or until `low` becomes greater than `high`.

&- If the element is found, it is returned as the result; otherwise, -1 is returned.

~- Intuition: The code exploits the sorted property of the array to perform a binary search and efficiently find the element with frequency 1. By comparing the middle element with its adjacent elements and analyzing their parity, the search space is intelligently narrowed down.

*- Time Complexity: The binary search reduces the search space in each iteration by half, so the time complexity is O(log n), where n is the number of elements in the array.

*- Space Complexity: The code uses only a constant amount of extra space for variables, so the space complexity is O(1).

*- Hints: Since the array is sorted, consider using binary search to efficiently locate the element with frequency 1. Pay attention to the adjacent elements and their parity to narrow down the search space effectively.

? Basically all pairs of same elements on left side will have indexes in order (even,odd) and the right side will have indexes in order (odd,even) (left sorted array, single element , right sorted array)
     */
    int singleNonDuplicate_optimized(vector<int> &nums)
    {
        if (nums.size() < 2)
            return nums.front();
        if (nums.at(0) != nums.at(1))
            return nums.at(0);
        if (nums.at(nums.size() - 1) != nums.at(nums.size() - 2))
            return nums.at(nums.size() - 1);
        int low = 1, high = nums.size() - 2;
        while (low <= high)
        {
            int mid = (low + high) >> 1;
            if (nums.at(mid) != nums.at(mid - 1) && nums.at(mid) != nums.at(mid + 1))
            {
                return nums.at(mid);
            }
            else if (mid % 2 == 1 && nums.at(mid) == nums.at(mid - 1) || mid % 2 == 0 && nums.at(mid) == nums.at(mid + 1))
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return -1;
    }
};

//^ 29 Peak element in a array
class PeakElement
{
public:
    /*
    @ Binary search algorithm
    &- The given code is used to find a peak element in an array. A peak element is defined as an element that is greater than its neighbors.

&- The algorithm first handles the base cases where the array has 0 or 1 elements. In such cases, the only element is a peak, and its index is returned as the result.

&- Next, it checks if the first element is greater than the second element. If so, the first element is a peak, and its index (0) is returned as the result.

&- Similarly, it checks if the last element is greater than its second-to-last element. If so, the last element is a peak, and its index (`n - 1`) is returned as the result.

&- After these checks, a binary search is performed to find a peak element in the middle part of the array (excluding the first and last elements).

&- In each iteration, the middle index `mid` is calculated using `(low + high) / 2`. To avoid potential overflow, `low` and `high` are updated differently in the binary search.

&- If the middle element `nums[mid]` is greater than its adjacent elements (`nums[mid - 1]` and `nums[mid + 1]`), it is a peak element, and its index `mid` is returned as the result.

&- Otherwise, the binary search narrows down the search space based on the comparison between `nums[mid]` and its neighbors.

&- If `nums[mid]` is greater than or equal to `nums[low]` and `nums[mid - 1]`, it means the peak element is likely to be on the right side of the array. So, the search space is narrowed down to the right half by updating `low` to `mid + 1`.

&- Otherwise, the peak element is likely to be on the left side of the array, and the search space is narrowed down to the left half by updating `high` to `mid - 1`.

&- The binary search continues until a peak element is found or until `low` becomes greater than `high`.

&- If a peak element is found, its index is returned as the result; otherwise, -1 is returned.

~- Intuition: The code efficiently uses binary search to locate a peak element by comparing elements and intelligently narrowing down the search space based on their relationships.

*- Time Complexity: The binary search reduces the search space in each iteration by half, so the time complexity is O(log n), where n is the number of elements in the array.

*- Space Complexity: The code uses only a constant amount of extra space for variables, so the space complexity is O(1).

*- Hints: Consider using binary search to efficiently find a peak element in the array. Pay attention to the comparisons between elements and use them to narrow down the search space effectively. Keep in mind the different cases of peak elements based on their relationships with neighbors.
     */
    int findPeakElement(vector<int> &nums)
    {
        const int n = nums.size();
        if (n <= 1)
            return 0;
        if (nums.front() > nums.at(1))
            return 0;
        if (nums.back() > nums.at(n - 2))
            return n - 1;
        int low = 1, high = n - 2;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (nums.at(mid) > nums.at(mid - 1) && nums.at(mid) > nums.at(mid + 1))
            {
                return mid;
            }
            else if (nums.at(mid) >= nums.at(low) && nums.at(mid) >= nums.at(mid - 1))
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return -1;
    }
};

//^ 30 Nth root of a number
class NthRoot
{
private:
    /*
        &- The customPow function calculates the power of a number mid raised to the nth power and checks if the result exceeds m.
        &- The NthRoot_Bs function is used to find the nth root of a number m using binary search.
        &- If the value of m is 1, it means that the 1st root of any number is 1, so the function returns 1.
        &- If n is greater than m, it is not possible to find the nth root of m, so the function returns -1.
        &- The low variable is initialized to 1, and the high variable is set to m / n since the nth root of a number cannot be greater than m / n.
        &- The function performs a binary search to find the nth root of m within the range [1, m / n].
        &- In each iteration of the binary search, the middle value mid is calculated as (low + high) / 2.
        &- The customPow function is called with mid, n, and m as arguments to check whether mid raised to the nth power is equal to m, less than m, or greater than m.
        &- If customPow returns 1, it means mid is the nth root of m, and the function returns mid.
        &- If customPow returns 0, it means mid raised to the nth power is less than m, so the search range is shifted to the right by setting low = mid + 1.
        &- If customPow returns 2, it means mid raised to the nth power is greater than m, so the search range is shifted to the left by setting high = mid - 1.
        &- If no nth root is found within the range [1, m / n], the function returns -1.
        *- The time complexity of the code is O(log(m / n)) due to the binary search, where m / n represents the search range for the nth root.
        *- The space complexity of the code is O(1) as it uses a constant amount of extra space.

    Hints:

        *- The customPow function is used to calculate the power of a number without using the standard power function to avoid overflow issues.
        *- Binary search is employed to efficiently find the nth root of a given number within a specific range.
        *- Be cautious with the boundary conditions of the binary search to ensure a correct result.
     */
public:
    long long customPow(int mid, int n, int m)
    {
        long long ans = 1;
        for (int i = 1; i <= n; i++)
        {
            ans = ans * mid;
            if (ans > m)
            {
                return 2;
            }
        }
        if (ans == m)
        {
            return 1;
        }
        return 0;
    }
    int NthRoot_Bs(int n, int m)
    {
        // Code here.
        if (m == 1)
            return 1;
        if (n > m)
        {
            return -1;
        }
        int low = 1, high = m / n;
        int ans = -1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            long long calc = customPow(mid, n, m);
            // cout << mid << ", "<<calc<< "\n";
            if (calc == 1)
            {
                return mid;
            }
            else if (calc == 0)
            {
                low = mid + 1;
            }
            else
                high = mid - 1;
        }
        return ans;
    }
};
//~ Search space problems
//^ 31 Koko eating bananas
class Koko
{
public:
    class Solution
    {
    private:
        /*

     &- The `isValid` function checks if it is possible for Koko to eat all bananas in the given `piles` of bananas within `h` hours when eating at a rate of `mid` bananas per hour.
     &- The `hoursTaken` variable keeps track of the total hours taken by Koko to eat all bananas.
     &- For each pile of bananas in the `piles` vector, the function calculates how many hours it would take Koko to eat that pile using the formula `ceil((double)i / mid)`, where `i` is the number of bananas in the pile. The `ceil` function is used to ensure that Koko spends enough time to eat all the bananas in the pile.
     &- If the total hours taken exceed `h`, it means Koko cannot eat all bananas within `h` hours at the current rate `mid`, so the function returns false.
     &- If Koko can eat all bananas within `h` hours, the function returns true.
     &- The `minEatingSpeed` function uses binary search to find the minimum eating speed `k` at which Koko can eat all bananas within `h` hours.
     &- The `high` variable is set to the maximum number of bananas in any pile, and the `low` variable is set to 1 as the minimum possible eating speed.
     &- The function performs a binary search to find the minimum eating speed `k` within the range [1, max(piles)].
     &- In each iteration of the binary search, the middle value `mid` is calculated as `low + (high - low) / 2`.
     &- The `isValid` function is called with `mid`, `piles`, and `h` as arguments to check if Koko can eat all bananas at the eating speed `mid` within `h` hours.
     &- If `isValid` returns true, it means Koko can eat all bananas at the current eating speed, and the function updates the value of `k` as the minimum of `k` and `mid`.
     &- If `isValid` returns false, it means Koko cannot eat all bananas at the current eating speed, so the search range is shifted to the right by setting `low = mid + 1`.
     &- If Koko can eat all bananas at a certain eating speed `k`, then Koko can also eat all bananas at any eating speed greater than `k`, so the search range is shifted to the left by setting `high = mid - 1` when `isValid` returns true.
     &- The function returns `k`, which represents the minimum eating speed at which Koko can eat all bananas within `h` hours.
     *- The time complexity of the code is O(n * log(max(piles))) due to the binary search, where `n` is the number of piles of bananas, and `max(piles)` is the maximum number of bananas in any pile.
     *- The space complexity of the code is O(1) as it uses a constant amount of extra space.

    Hints:
     *- The problem requires finding the minimum eating speed `k` such that Koko can eat all bananas within `h` hours. This can be done using binary search as the eating speed can be considered as the search space.
     *- The `isValid` function is used to check if Koko can eat all bananas within `h` hours at a given eating speed `mid`. It is essential to use the `ceil` function to calculate the number of hours required to eat a particular pile of bananas.
     *- By performing binary search within the range [1, max(piles)], we can efficiently find the minimum eating speed `k` that satisfies the condition of eating all bananas within `h` hours.
         */
    public:
        bool isValid(int mid, vector<int> &piles, int h)
        {
            int hoursTaken = 0;
            for (int &i : piles)
            {
                int res = hoursTaken + ceil((double)i / mid);

                if (res > h)
                {
                    return false;
                }
                hoursTaken = res;
                // cout << "hoursTaken: "<<hoursTaken<<"\n";
            }
            // cout << "hoursTaken: "<<hoursTaken<<"\n";
            return hoursTaken <= h;
        }
        int minEatingSpeed(vector<int> &piles, int h)
        {
            int high = *max_element(piles.begin(), piles.end());
            int low = 1;
            int k = 1e9;
            while (low <= high)
            {
                int mid = low + (high - low) / 2;
                // cout << "mid: "<<mid<<"\n";
                if (isValid(mid, piles, h))
                {
                    k = min(k, mid);
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            return k;
        }
    };
};

//^ 32 Minimum days to make m bouquets
class MinimumDays
{
private:
    /*
        &- The isValid function checks if it is possible to make m bouquets with at least k flowers in each bouquet using the given bloomDay array and a maximum waiting time mid.
        &- The function uses two variables, bouquets and counter, to keep track of the number of bouquets made and the number of consecutive flowers that have bloomed within the waiting time mid.
        &- The function iterates through the bloomDay array and counts the number of consecutive flowers that have bloomed within mid. If the bloom day of a flower is less than or equal to mid, it increments the counter.
        &- When the bloom day of a flower is greater than mid, it means the consecutive sequence of bloomed flowers is broken, and the function calculates how many bouquets can be made from the current sequence of consecutive flowers (using counter) and adds it to the bouquets.
        &- After processing all the flowers, if there are any remaining consecutive flowers (with counter greater than zero), the function calculates how many additional bouquets can be made and adds it to the bouquets.
        &- Finally, the function returns true if the total number of bouquets (bouquets) is greater than or equal to m, indicating that it is possible to make m bouquets with at least k flowers each within the waiting time mid.
        &- The minDays function uses binary search to find the minimum waiting time ans required to make m bouquets with at least k flowers each.
        &- The function first checks if it is possible to make m bouquets with at least k flowers each within the given bloomDay array. If not, it returns -1 as it is impossible to make the required number of bouquets.
        &- The function then finds the minimum and maximum bloom days in the bloomDay array using minmax_element and sets the search range for the binary search as [min, max].
        &- The function performs a binary search to find the minimum waiting time ans within the search range [min, max].
        &- In each iteration of the binary search, the middle value mid is calculated as low + (high - low) / 2.
        &- The isValid function is called with mid, m, k, and the bloomDay array as arguments to check if it is possible to make m bouquets with at least k flowers each within the waiting time mid.
        &- If isValid returns true, it means it is possible to make m bouquets within mid days, so the function updates the value of ans as the minimum of ans and mid and adjusts the search range by setting high = mid - 1.
        &- If isValid returns false, it means it is not possible to make m bouquets within mid days, so the function adjusts the search range by setting low = mid + 1.
        &- The function returns ans, which represents the minimum waiting time required to make m bouquets with at least k flowers each.
        *- The time complexity of the code is O(n * log(max(bloomDay))) due to the binary search, where n is the size of the bloomDay array and max(bloomDay) is the maximum bloom day in the array.
        *- The space complexity of the code is O(1) as it uses a constant amount of extra space.

    Hints:

        *- The problem requires finding the minimum waiting time ans required to make m bouquets with at least k flowers each from the given bloomDay array.
        *- Binary search can be used to efficiently find the minimum waiting time within the range of bloom days.
        *- The isValid function checks if it is possible to make m bouquets with at least k flowers each within a given waiting time mid. It counts the number of consecutive flowers that have bloomed within mid and calculates how many bouquets can be made from this sequence of consecutive flowers.
        *- By performing binary search within the range of minimum and maximum bloom days, we can efficiently find the minimum waiting time ans required to make m bouquets with at least k flowers each.
     */
public:
    bool isValid(int mid, int m, int k, vector<int> &bloomDay)
    {
        int bouquets = 0;
        int counter = 0;
        for (int &i : bloomDay)
        {
            if (i <= mid)
            {
                counter++;
            }
            else
            {
                bouquets += (counter / k);
                counter = 0;
            }
        }
        bouquets += (counter / k);
        return bouquets >= m;
    }
    int minDays(vector<int> &bloomDay, int m, int k)
    {
        if ((long long)m * k > bloomDay.size())
            return -1;
        auto range = minmax_element(bloomDay.begin(), bloomDay.end());
        int low = *range.first, high = *range.second;
        int ans = 1e9;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(mid, m, k, bloomDay))
            {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};

//^ 33 Find a smallest divisor given a threshold
class SmallestDivisor
{
public:
    bool isValid(int mid, vector<int> &nums, int threshold)
    {
        int result = 0;
        for (int &i : nums)
        {
            result += ceil((double)i / mid);
            if (result > threshold)
            {
                break;
            }
        }
        return result <= threshold;
    }
    int smallestDivisor(vector<int> &nums, int threshold)
    {
        int high = *max_element(nums.begin(), nums.end());
        int low = 1;
        int ans = 1e9;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(mid, nums, threshold))
            {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};

//^ 34 Capacity To Ship Packages Within D Days

class ShipCapacity
{
public:
    bool isValid(int mid, vector<int> &weights, int days)
    {
        int dayCounter = 1, capacity = 0;
        for (int &i : weights)
        {
            capacity += i;
            if (capacity > mid)
            {
                dayCounter++;
                capacity = i;
            }
            if (dayCounter > days)
            {
                break;
            }
        }
        return dayCounter <= days;
    }
    int shipWithinDays(vector<int> &weights, int days)
    {
        int high = accumulate(weights.begin(), weights.end(), 0);
        int low = *max_element(weights.begin(), weights.end());
        int ans = high;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(mid, weights, days))
            {
                ans = min(mid, ans);
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};

//^ 35 Kth missing positive number
class KthMissing
{
public:
    /*
    @ Linear search
    ! O(N) T.C | O(1) S.C
     */
    int findKthPositive(vector<int> &arr, int k)
    {
        for (int &i : arr)
        {
            if (i <= k)
                k++;
            else
                break;
        }
        return k;
    }
    /*
    @ Leetcode solution
     */
    int KthMissingElement(int a[], int n, int k)
    {
        int low = 0, high = n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int missing = a[mid] - (mid + 1); //* counting missing numbers ex: (2 3 4 7 11) <-> (1 1 1 3 6)
            if (missing < k)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        //? high is pointing at the location of the starting point of the answer's range ex:7;
        //? low is pointing at the location of the ending point of the answer's range ex:11;
        //~ missing number = a[high] + (more numbers) but more numbers = k - (a[high] - (high + 1))
        //~ solving above we get = high + 1 + k or (low) + k as high + 1 == low
        return low + k;
    }
    /*
    @ GFG solution
     */
    int KthMissingElement(int a[], int n, int k)
    {
        // Consider starting element as the first element of the array.
        int low = 0, high = n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int missing = a[mid] - (mid + a[0]);
            if (missing < k)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        if (low + k + a[0] - 1 < a[n - 1])
            return low + k + a[0] - 1;

        return -1;
    }
};

//^ 36 Magnetic force between two BALLS :-p
class MagneticForce
{
public:
    /*
    @ Same as aggressive cows
     */
    bool isValid(unsigned mid, vector<int> &position, int m)
    {
        unsigned balls = 1, lastPos = position.front();
        for (unsigned i = 0; i < position.size(); i++)
        {
            if (position.at(i) - lastPos >= mid)
            {
                balls++;
                lastPos = position.at(i);
            }
            if (balls >= m)
            {
                return true;
            }
        }
        return balls >= m;
    }
    int maxDistance(vector<int> &position, int m)
    {
        sort(position.begin(), position.end());
        unsigned low = 1;
        unsigned high = position.back() - position.front();
        unsigned ans = 0;
        while (low <= high)
        {
            unsigned mid = low + (high - low) / 2;
            if (isValid(mid, position, m))
            {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return ans;
    }
};

//^ 37 Split array largest sum [Allocation of min number of pages / painter's partition]
class SplitArray
{
public:
    bool isValid(int mid, int k, vector<int> &nums)
    {
        int subarrays = 1, currSum = nums.front();
        for (int i = 1; i < nums.size(); i++)
        {
            currSum += nums.at(i);
            if (currSum > mid)
            {
                subarrays++;
                currSum = nums.at(i);
            }
            if (subarrays > k)
            {
                return false;
            }
        }
        return true;
    }
    int splitArray(vector<int> &nums, int k)
    {
        int high = accumulate(nums.begin(), nums.end(), 0);
        int low = *max_element(nums.begin(), nums.end());

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(mid, k, nums))
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return low;
    }
};

//^ 38 Minimize the maximum distance between two gas stations
class MinimizeDistance
{
public:
    /*
    @ Brute force
    if((arr[i] - arr[i-1]) == (dist * numberInBetween)) {
      numberInBetween--;
}

    &- The minimizeMaxDistance function aims to minimize the maximum distance between two gas stations by optimally placing k additional gas stations between the existing n gas stations represented by the stations vector.
    &- The function starts by creating a vector howMany of size n - 1 to store the number of additional gas stations that will be placed between each pair of existing gas stations. Initially, all elements in howMany are set to 0.
    &- The function then iterates k times to place the additional gas stations. In each iteration, it calculates the length of each section between two existing gas stations and determines which section requires an additional gas station to minimize the maximum distance. The section with the largest length is selected, and an additional gas station is added to it by incrementing the corresponding element in the howMany vector.
    &- After all additional gas stations have been placed, the function calculates the maximum distance between two gas stations. This is done by iterating through all sections between existing gas stations and calculating the length of each section with respect to the number of additional gas stations placed between them.
    &- Finally, the function returns the maximum distance found, which represents the minimum maximum distance achievable after optimally placing k additional gas stations.
    !- The time complexity of the code is O(n * k), where n is the size of the stations vector and k is the number of additional gas stations to be placed. The function iterates k times, and in each iteration, it goes through all n - 1 sections between existing gas stations.
    !- The space complexity of the code is O(n), which is used to store the howMany vector to keep track of additional gas stations placed between each pair of existing gas stations.

Hints:

    &- The problem requires optimizing the placement of k additional gas stations between the existing n gas stations to minimize the maximum distance between two gas stations.
    &- The given stations vector represents the positions of existing gas stations along a line.
    &- To solve the problem, you need to iteratively place additional gas stations between existing gas stations in a way that minimizes the maximum distance between them.
    &- You can use a binary search approach to efficiently find the optimal positions to place the additional gas stations.
    &- Initially, you can set up a range for the possible positions of the additional gas stations between two existing gas stations. The range can be set from the minimum distance between two existing gas stations to the maximum distance between them.
    &- Then, you can use binary search within this range to find the optimal position to place the additional gas stations such that the maximum distance between two gas stations is minimized.
    &- By repeating this process k times, you can iteratively optimize the placement of k additional gas stations and find the minimum maximum distance achievable.
     */
    long double minimizeMaxDistance(vector<int> &stations, int k)
    {
        const unsigned n = stations.size();
        vector<int> howMany(n - 1);
        for (int gasStations = 1; gasStations <= k; gasStations++)
        {
            long double maxSection = -1;
            int maxInd = -1;
            for (int i = 0; i < n - 1; i++)
            {
                long double diff = stations.at(i + 1) - stations.at(i);
                long double sectionLength = (long double)diff / (long double)(howMany.at(i) + 1);

                if (sectionLength > maxSection)
                {
                    maxSection = sectionLength;
                    maxInd = i;
                }
            }
            howMany.at(maxInd)++;
        }

        long double maxAns = -1;
        for (int i = 0; i < n - 1; i++)
        {
            long double diff = (stations.at(i + 1) - stations.at(i));
            long double sectionLength = diff / (long double)(howMany.at(i) + 1);

            maxAns = max(maxAns, sectionLength);
        }
        return maxAns;
    }
    /*
    @ Using priority queue (max-heap)
        &- The minimizeMaxDistance_v2 function aims to minimize the maximum distance between two gas stations by optimally placing k additional gas stations between the existing n gas stations represented by the stations vector.
    &- The function starts by creating a priority queue pq to store the lengths of all sections between existing gas stations. Each element in the priority queue is a pair containing the length of the section and the index of the corresponding section in the stations vector.
    &- The priority queue is initialized by calculating the length of each section between adjacent gas stations and inserting them into the queue. The priority queue automatically arranges the sections in descending order of length, so the section with the largest length will be at the top of the queue.
    &- The function then iterates k times to place the additional gas stations. In each iteration, it pops the section with the largest length from the top of the priority queue. It then increments the number of additional gas stations placed between the corresponding existing gas stations and calculates the new length of the section with the additional gas station.
    &- After all additional gas stations have been placed, the function returns the length of the section with the largest length, which represents the minimum maximum distance achievable after optimally placing k additional gas stations.
    *- The time complexity of the code is O(n * log n + k * log n), where n is the size of the stations vector. The n * log n part comes from initializing the priority queue with all n - 1 sections, and the k * log n part comes from the k iterations to place additional gas stations.
    *- The space complexity of the code is O(n), which is used to store the howMany vector and the priority queue.

Hints:

    &- The problem requires optimizing the placement of k additional gas stations between the existing n gas stations to minimize the maximum distance between them.
    &- The given stations vector represents the positions of existing gas stations along a line.
    &- To solve the problem, you need to iteratively place additional gas stations between existing gas stations in a way that minimizes the maximum distance between them.
    &- You can use a priority queue to efficiently find the section with the largest length between existing gas stations and place an additional gas station in that section.
    &- By repeating this process k times, you can iteratively optimize the placement of k additional gas stations and find the minimum maximum distance achievable.
     */
    long double minimizeMaxDistance_v2(vector<int> &stations, int k)
    {
        const uint32_t n = stations.size();
        vector<int> howMany(n - 1);
        priority_queue<pair<long double, int>> pq;
        for (int i = 0; i < n - 1; i++)
        {
            pq.push({stations.at(i + 1) - stations.at(i), i});
        }
        for (int gasStations = 1; gasStations <= k; gasStations++)
        {
            auto p = pq.top();
            pq.pop();
            howMany.at(p.second)++;
            long double initialDifference = stations.at(p.second + 1) - stations.at(p.second);

            long double newSectionLength = initialDifference / (long double)(howMany.at(p.second) + 1);

            pq.push({newSectionLength, p.second});
        }

        return pq.top().first;
    }
    /*
    @ Binary search
     */
    bool isValid(long double dist, vector<int> &arr, int k)
    {
        int count = 0;
        for (int i = 1; i < arr.size(); i++)
        {
            int numberInBetween = (arr[i] - arr[i - 1]) / dist;
            if ((arr[i] - arr[i - 1]) / dist == numberInBetween * dist)
            {
                numberInBetween--;
            }
            count += numberInBetween;
        }
        return count > k;
    }

    long double minimizeMaxDistance_v3(vector<int> &stations, int k)
    {
        const unsigned int n = stations.size();
        long double low = 0;
        long double high = 0;
        for (int i = 0; i < n - 1; i++)
        {
            high = max(high, (long double)(stations.at(i + 1) - stations.at(i)));
        }
        long double diff = 1e-6;
        while (high - low > diff)
        {
            long double mid = low + (high - low) / 2.0;
            if (isValid(mid, stations, k))
            {
                low = mid;
            }
            else
            {
                high = mid;
            }
        }
        return high;
    }
};

//^ 39 Number of pairs
/*
    Intuition:
        The inequality x^y > y^x can be rewritten as y * log(x) > x * log(y), where log denotes the natural logarithm.
        To compare the two sides of the inequality, we can calculate y / log(y) and x / log(x) for all elements of arrays X[] and Y[], respectively.
        Then, we sort these values to simplify the counting process.

    Code Explanation:
        The code first calculates lnx[i] for each element X[i] in the X[] array, and similarly, calculates lny[i] for each element Y[i] in the Y[] array.
        Then, it sorts the arrays lnx and lny.
        The code uses two pointers technique to count the pairs (x, y) that satisfy the condition. For each logy in lny, it finds the count of lnx elements that are smaller than logy and adds this count to the total number of pairs.
        The final count of such pairs is returned.

    Time Complexity:
        The code involves sorting two arrays, lnx and lny, which takes O(m * log m + n * log n) time.
        The loop that calculates the count of valid pairs takes O(m + n) time, as it processes each element of lny and performs a binary search on lnx.
        Thus, the overall time complexity is O(m * log m + n * log n + m + n), which is effectively O(max(m * log m, n * log n)).

    Space Complexity:
        The code uses two arrays, lnx and lny, to store the transformed values, which require O(m + n) space.

    Hints:
        The comparison x^y > y^x can be simplified using logarithms to y * log(x) > x * log(y).
        Transform the values in both arrays X[] and Y[] using x / log(x) and y / log(y) respectively.
        Sort the transformed arrays to simplify the comparison process.
        Utilize a two pointers approach to count the number of valid pairs.
 */
long long countPairs(int X[], int Y[], int m, int n)
{
    // code here
    vector<double> lnx(m), lny(n);
    for (int i = 0; i < m; i++)
    {
        lnx[i] = (double)X[i] / (log(X[i]));
    }
    for (int i = 0; i < n; i++)
    {
        lny[i] = (double)Y[i] / (log(Y[i]));
    }
    sort(lnx.begin(), lnx.end());
    sort(lny.begin(), lny.end());
    long long pairs = 0;
    for (auto &logy : lny)
    {

        long long logxSmallerThanlogy = lower_bound(lnx.begin(), lnx.end(), logy) - lnx.begin();
        // cout<<t<<" ";
        pairs += (logxSmallerThanlogy);
    }
    return pairs;
}

//^ 40 Base equivalence
/*
    It iterates through a loop with i ranging from 2 to 31 (base 2 to base 32).
    For each i, it calculates the number of digits required to represent n in base i using the formula (log(n) / log(i)) + 1.
    If the number of digits calculated is equal to m, it returns "Yes" to indicate that n can be represented with m digits in base i.
    If none of the iterations result in a match, it returns "No," indicating that there is no base in which n can be represented with m digits.

Here's a breakdown of the code's logic:

    It checks different bases from 2 to 31.
    For each base, it calculates the number of digits needed to represent n.
    If it finds a base where the number of digits matches m, it returns "Yes."
    If no such base is found, it returns "No."

This code snippet can be used to determine if there exists a base in which n can be represented with exactly m digits. If such a base exists, it returns "Yes"; otherwise, it returns "No."

For example, if n is 15 and m is 4, the code will return "Yes" because 15 can be represented as "1111" in binary, which has 4 digits.

Keep in mind that this code assumes that n and m are positive integers. */
string baseEquiv(int n, int m)
{
    // code here
    for (int i = 2; i < 32; i++)
    {
        int number = ((log(n) / log(i))) + 1;
        if (number == m)
            return "Yes";
    }
    return "No";
}

//^ 41 Median of 2 sorted arrays
/*
We are going to use the Binary Search algorithm to optimize the approach.

The primary objective of the Binary Search algorithm is to efficiently determine the appropriate half to eliminate, thereby reducing the search space by half. It does this by determining a specific condition that ensures that the target is not present in that half.

Now, let’s learn through the following observations how we can apply binary search to this problem. First, we will try to solve this problem where n1+n2 is even and then we will consider the odd scenario.
Observations:

Assume, n = n1+n2 i.e. the total length of the final merged array.

    Median creates a partition on the final merged array: Upon closer observation, we can easily show that the median divides the final merged array into two halves. For example,

    Characteristics of each half:
        Each half contains (n/2) elements.
        Each half also contains x elements from the first array i.e. arr1[] and (n/2)-x elements from the second array i.e. arr2[]. The value of x might be different for the two halves. For example, in the above array, the left half contains 3 elements from arr1[] and 2 elements from arr2[].
    The unique configuration of halves: Considering different values of x, we can get different left and right halves(x = the number of elements taken from arr1[] for a particular half). Some different configurations for the above example are shown below:

How to solve the problem using the above observations:

    Try to form the unique left half:
        For a valid merged array, the configurations of the two halves are unique. So, we can try to form the halves with different values of x, where x = the number of elements taken from arr1[] for a particular half.
        There’s no need to construct both halves. Once we have the correct left half, the right half is automatically determined, consisting of the remaining elements not yet considered. Therefore, our focus will solely be on creating the unique left half.
        How to form all configurations of the left half: We know that the left half will surely contain x elements from arr1[] and (n/2)-x elements from arr2[]. Here the only variable is x. The minimum possible value of x is 0 and the maximum possible value is n1(i.e. The length of the considered array).
        For all the values,[0, n1] of x, we will try to form the left half and then we will check if that half’s configuration is valid.
    Check if the formed left half is valid: For a valid left half, the merged array will always be sorted. So, if the merged array containing the formed left half is sorted, the formation is valid.
        How to check if the merged array is sorted without forming the array:
        In order to check we will consider 4 elements, i.e. l1, l2, r1, r2.
            l1 = the maximum element belonging to arr1[] of the left half.
            l2 = the maximum element belonging to arr2[] of the left half.
            r1 = the minimum element belonging to arr1[] of the right half.
            r1 = the minimum element belonging to arr2[] of the right half.

For example,

How to apply Binary search to form the left half:

    We will check the formation of the left half for all possible values of x. Now, we know that the minimum possible value of x is 0 and the maximum is n1(i.e. The length of the considered array). Now the range is sorted. So, we will apply the binary search on the possible values of x i.e. [0, n1].
    How to eliminate the halves based on the values of x: Binary search works by eliminating the halves in each step. Upon closer observation, we can eliminate the halves based on the following conditions:
        If l1 > r2: This implies that we have considered more elements from arr1[] than necessary. So, we have to take less elements from arr1[] and more from arr2[]. In such a scenario, we should try smaller values of x. To achieve this, we will eliminate the right half (high = mid-1).
        If l2 > r1: This implies that we have considered more elements from arr2[] than necessary. So, we have to take less elements from arr2[] and more from arr1[]. In such a scenario, we should try bigger values of x. To achieve this, we will eliminate the left half (low = mid+1).

Until now, we have learned how to use binary search but with the assumption that (n1+n2) is even. Let’s generalize this.

If (n1+n2) is odd: In the case of even, we have considered the length of the left half as
(n1+n2) / 2. In this case, that length will be (n1 + n2 + 1) / 2. This much change is enough to handle the case of odd. The rest of the things will be completely the same.
As in the code, division refers to integer division, this modified formula (n1+n2+1) / 2 will be valid for both cases of odd and even.

What will be the answer i.e. the median:

    If l1 <= r2 && l2 <= r1: This condition assures that we have found the correct elements.
        If (n1+n2) is odd: The median will be max(l1, l2).
        Otherwise, median = (max(l1, l2) + min(r1, r2)) / 2.0

Note: We are applying binary search on the possible values of x i.e. [0, n1]. Here n1 is the length of arr1[]. Now, to further optimize it, we will consider the smaller array as arr1[]. So, the actual range will be [0, min(n1, n2)].
Algorithm:

    First, we have to make sure that the arr1[] is the smaller array. If not by default, we will just swap the arrays. Our main goal is to consider the smaller array as arr1[].
    Calculate the length of the left half: left = (n1+n2+1) / 2.
    Place the 2 pointers i.e. low and high: Initially, we will place the pointers. The pointer low will point to 0 and the high will point to n1(i.e. The size of arr1[]).
    Calculate the ‘mid1’ i.e. x and ‘mid2’ i.e. left-x: Now, inside the loop, we will calculate the value of ‘mid1’ using the following formula:
    mid1 = (low+high) // 2 ( ‘//’ refers to integer division)
    mid2 = left-mid1
    Calculate l1, l2, r1, and r2: Generally,
        l1 = arr1[mid1-1]
        l2 = arr2[mid2-1]
        r1 = arr1[mid1]
        r2 = arr2[mid2]
        The possible values of ‘mid1’ and ‘mid2’ might be 0 and n1 and n2 respectively. So, to handle these cases, we need to store some default values for these four variables. The default value for l1 and l2 will be INT_MIN and for r1 and r2, it will be INT_MAX.
    Eliminate the halves based on the following conditions:
        If l1 <= r2 && l2 <= r1: We have found the answer.
            If (n1+n2) is odd: Return the median = max(l1, l2).
            Otherwise: Return median = (max(l1, l2)+min(r1, r2)) / 2.0
        If l1 > r2: This implies that we have considered more elements from arr1[] than necessary. So, we have to take less elements from arr1[] and more from arr2[]. In such a scenario, we should try smaller values of x. To achieve this, we will eliminate the right half (high = mid1-1).
        If l2 > r1: This implies that we have considered more elements from arr2[] than necessary. So, we have to take less elements from arr2[] and more from arr1[]. In such a scenario, we should try bigger values of x. To achieve this, we will eliminate the left half (low = mid1+1).
    Finally, outside the loop, we will include a dummy return statement just to avoid warnings or errors.

The steps from 4-6 will be inside a loop and the loop will continue until low crosses high.
 */
double median(vector<int> &a, vector<int> &b)
{

    int n1 = a.size();
    int n2 = b.size();
    if (n1 > n2)
        return median(b, a);

    int n = n1 + n2;              // total length
    int left = (n1 + n2 + 1) / 2; // length of left half
    // apply binary search:
    // l1 = the maximum element belonging to arr1[] of the left half.
    // l2 = the maximum element belonging to arr2[] of the left half.
    // r1 = the minimum element belonging to arr1[] of the right half.
    // r1 = the minimum element belonging to arr2[] of the right half.
    int low = 0, high = n1;
    while (low <= high)
    {
        int mid1 = (low + high) / 2;
        int mid2 = left - mid1;
        int l1 = (mid1 == 0) ? INT_MIN : a[mid1 - 1];
        int l2 = (mid2 == 0) ? INT_MIN : b[mid2 - 1];
        int r1 = (mid1 == n1) ? INT_MAX : a[mid1];
        int r2 = (mid2 == n2) ? INT_MAX : b[mid2];
        if (l1 <= r2 && l2 <= r1)
        {
            if (n % 2 == 0)
                return (max(l1, l2) + min(r1, r2)) / 2.0;
            else
                return max(l1, l2);
        }
        else if (l1 > r2)
            high = mid1 - 1;
        else
            low = mid1 + 1;
    }
    return 0.0;
}

//^ 42 Row with maximum 1s
class RowMax1s
{
public:
    // int rowWithMax1s(vector<vector<int>> arr, int n, int m)
    // {
    //     int j = m - 1, max_row_index = 0;
    //     for (int i = 0; i < n; i++)
    //     {
    //         bool flag = false;
    //         while (j >= 0 && arr[i][j] == 1)
    //         {
    //             j--;
    //             flag = true;
    //         }
    //         if (flag)
    //         {
    //             max_row_index = i;
    //         }
    //     }
    //     if (max_row_index == 0 && arr[0][m - 1] == 0)
    //         return -1;
    //     return max_row_index;
    // }

    int rowWithMax1s(vector<vector<int>> &matrix, int n, int m)
    {
        int cnt_max = 0;
        int index = -1;

        // traverse the rows:
        for (int i = 0; i < n; i++)
        {
            // get the number of 1's:
            int cnt_ones = m - (lower_bound(matrix[i].begin(), matrix[i].end(), 1) - matrix[i].begin());
            if (cnt_ones > cnt_max)
            {
                cnt_max = cnt_ones;
                index = i;
            }
        }
        return index;
    }
};

//^ 43 Search in a 2D sorted Matrix
/*
Algorithm:

    Place the 2 pointers i.e. low and high: Initially, we will place the pointers. The pointer low will point to 0 and the high will point to (NxM)-1.
    Calculate the ‘mid’: Now, inside the loop, we will calculate the value of ‘mid’ using the following formula:
    mid = (low+high) // 2 ( ‘//’ refers to integer division)
    Eliminate the halves based on the element at index mid: To get the element, we will convert index ‘mid’ to the corresponding cell using the above formula. Here no. of columns of the matrix = M.
    row = mid / M, col = mid % M.
        If matrix[row][col] == target: We should return true here, as we have found the ‘target’.
        If matrix[row][col] < target: In this case, we need bigger elements. So, we will eliminate the left half and consider the right half (low = mid+1).
        If matrix[row][col] > target: In this case, we need smaller elements. So, we will eliminate the right half and consider the left half (high = mid-1).
    Steps 2-3 will be inside a while loop and the loop will end once low crosses high
    (i.e. low > high). If we are out of the loop, we can say the target does not exist in the matrix. So, we will return false.

 */
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    int m = matrix[0].size();

    // apply binary search:
    int low = 0, high = n * m - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        int row = mid / m, col = mid % m;
        if (matrix[row][col] == target)
            return true;
        else if (matrix[row][col] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}

//^ 44 Find peak element 2 [matrix version]
class PeakElement2
{
public:
    int getMaxElementRowNumber(vector<vector<int>> &mat, int mid)
    {
        int m = mat.size();
        int n = mat.front().size();

        int row = 0, maxi = INT_MIN;
        for (int i = 0; i < m; i++)
        {
            if (mat[i][mid] > maxi)
            {
                maxi = mat[i][mid];
                row = i;
            }
        }
        return row;
    }
    // Finds the peak element in a 2D grid.

    // Parameters:
    // - mat: The input 2D grid.
    // Returns:
    // - A vector containing the row and column indices of the peak element.
    //   If no peak element is found, returns {-1, -1}.
    vector<int> findPeakGrid(vector<vector<int>> &mat)
    {
        int m = mat.size();
        int n = mat.front().size();

        // Binary search to find the peak element.
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = (left + right) >> 1;
            int maxElementRowNumber = getMaxElementRowNumber(mat, mid);
            int _left = (mid - 1) >= 0 ? mat[maxElementRowNumber][mid - 1] : -1;
            int _right = (mid + 1) < n ? mat[maxElementRowNumber][mid + 1] : -1;

            if (mat[maxElementRowNumber][mid] > _left && mat[maxElementRowNumber][mid] > _right)
            {
                // Peak element found.
                return {maxElementRowNumber, mid};
            }
            else if (_left < mat[maxElementRowNumber][mid])
            {
                // Peak element lies in the right half.
                left = mid + 1;
            }
            else
            {
                // Peak element lies in the left half.
                right = mid - 1;
            }
        }

        // No peak element found.
        return {-1, -1};
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}
