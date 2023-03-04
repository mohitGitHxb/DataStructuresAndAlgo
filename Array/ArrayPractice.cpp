#include <bits/stdc++.h>
using namespace std;

void showArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int duplicate(vector<int> &arr)
{

    for (int i = 0; i < arr.size(); i++)
    {
        int currentElement = arr[i];
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] == arr[i])
            {
                return 1;
            }
        }
    }
    return -1;
}

// bool uniqueOccureneces(vector<int> &arr)
// {
//     unordered_map<int,int> mp;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         mp[arr[i]]++;
//     }
//     vector<int> freq;
//     for (auto &x : mp)
//     {
//         freq.push_back(x.second);
//     }
//     mp.clear();
//     sort(freq.begin(),freq.end());
//     for (int i = 1; i < freq.size(); i++)
//     {
//         if(freq[i] == freq[i-1]){
//             return false;
//         }
//     }
//     return true;

// }

// int sumBetween(vector<int> &arr, int k1, int k2)
// {
//     vector<int> temp = arr;
//     sort(temp.begin(), temp.end());
//     int k1thSmallestElement = temp[k1 - 1];
//     int k2thSmallestElement = temp[k2 - 1];
//     int sum = 0;
//     for (int i = k1; i < k2 - 1; i++)
//     {
//         sum += temp[i];
//     }

//     return sum;
// }

// vector<int> duplicates(int arr[], int n)
// {
//     unordered_map<int, int> mp;
//     vector<int> vec;
//     for (int i = 0; i < n; i++)
//     {
//         mp[arr[i]]++;
//     }
//     unsigned cnt = 0;
//     for (auto &x : mp)
//     {
//         if (x.second != 1)
//         {
//             vec.push_back(x.first);
//             cnt++;
//         }
//     }
//     mp.clear();

//     if (cnt != 0)
//     {
//         sort(vec.begin(), vec.end());
//         return vec;
//     }
//     return vector<int>{-1};
// }

/* running sum of 1d array aka prefix sum */
// vector<int> runningSum(vector<int> &nums){
//     vector<int> prefixSum;
//     int sum = 0;
//     for (int i = 0; i < nums.size(); i++)
//     {
//         sum+=nums[i];
//         prefixSum.push_back(sum);
//     }
//     return prefixSum;

// }

/* concatenate arrays */
vector<int> getConcatenation(vector<int> &nums)
{
    vector<int> temp = nums;
    nums.insert(nums.end(), temp.begin(), temp.end());
    temp.clear();
    return nums;
}

int immediateSmaller(int arr[], int n, int x)
{
    int minDifference = INT_MAX, minElementIndex = -1;

    for (int i = 0; i < n; i++)
    {
        int currentDifference = x - arr[i];
        if (arr[i] < x && currentDifference > 0)
        {
            if (minDifference > currentDifference)
            {
                minElementIndex = i;
            }
            minDifference = min(currentDifference, minDifference);
        }
    }
    if (minElementIndex == -1)
        return -1;
    return arr[minElementIndex];
}
void leftRotateByD(int arr[], int size, int d)
{
    if (d <= size)
    {
        queue<int> q;
        for (int i = 0; i < size; i++)
        {
            if (i < d)
            {
                q.push(arr[i]);
                arr[i] = arr[i + d];
                continue;
            }
            else if (i + d < size)
            {
                arr[i] = arr[i + d];
            }
            else
            {
                break;
            }
        }
        for (int i = size - d; i < size; i++)
        {
            arr[i] = q.front();
            q.pop();
        }
    }
}

vector<int> largestAndSecondLargest(int sizeOfArray, int arr[])
{
    vector<int> result;
    int max1 = INT_MIN, max2 = INT_MIN;
    int minDiff = INT_MIN;
    for (int i = 0; i < sizeOfArray; i++)
    {
        max1 = max(max1, arr[i]);
    }
    result.push_back(max1);
    for (int i = 0; i < sizeOfArray; i++)
    {
        int currentDifference = max1 - arr[i];
        if (currentDifference > 0 && currentDifference < minDiff)
        {
            minDiff = min(currentDifference, minDiff);
            max2 = arr[i];
        }
    }

    if (max2 == INT_MIN)
    {
        result.push_back(-1);
        return result;
    }
    result.push_back(max2);
    return result;
}

void maximumAdjacent(int sizeOfArray, int arr[])
{

    /*******************************************
     * Your code here
     * Function should print max adjacents for all pairs
     ********************************************/
    // pair<int,int> p;
    for (int i = 1; i < sizeOfArray; i++)
    {
        cout << max(arr[i], arr[i - 1]) << " ";
    }
}

int minAdjDiff(int arr[], int n)
{
    int minDiff = INT_MAX;
    for (int i = 1; i < n; i++)
    {
        if (i == n - 1)
        {
            minDiff = min(minDiff, abs(arr[0] - arr[i]));
            break;
        }
        minDiff = min(minDiff, abs(arr[i - 1] - arr[i]));
    }
    return minDiff;
}


 int maxOccured(int L[], int R[], int n, int maxx){
    
        // Your code here
        int res[maxx+1] ={0}; //? hashmap two store frequency of elements from a specific range , the element with highest frequency shall be returned
        int ans=INT_MIN;
        int idx=0;
        
        
        for(int i=0;i<n;i++){
            
            int counter = L[i];
            
            while(counter<=R[i]){
            res[counter]++;
            counter++;
            }
        }
        
        for(int i=0; i<=maxx;i++){
            if(ans<res[i]){
                ans=res[i];
                idx = i;
            }
        }
        return idx;
        
    }
void convertToWave(int n, vector<int> &arr)
{

    if (arr.size() % 2 == 0)
    {
        for (int i = 1; i < arr.size(); i += 2)
        {
            swap(arr[i], arr[i - 1]);
        }
        return;
    }
    for (int i = 1; i < arr.size() - 1; i += 2)
    {
        swap(arr[i], arr[i - 1]);
    }
}

void frequencyCount(vector<int> &arr, int N, int P)
{
    unordered_map<int, int> m;
    for (int i = 0; i < arr.size(); i++)
    {
        m[arr[i]]++;
    }
    for (int i = 1; i <= N; i++)
    {
        if (m.find(i) != m.end())
        {
            arr[i - 1] = m[i];
            continue;
        }
        arr[i - 1] = 0;
    }
}

int equilibriumPoint(long long a[], int n)
{

    // Your code here
    if (n == 1)
        return 1;
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += a[i];
    }
    int chk = s / 2;
    int j = -1, sum = 0;
    while (sum <= chk)
    {
        sum += a[++j];
    }
    sum = sum - a[j];
    int s3 = 0;
    for (int i = j + 1; i < n; i++)
    {
        s3 += a[i];
    }
    if (s3 == sum)
        return j + 1;
    else
        return -1;
}
vector<int> leaders(int a[], int n)
{
    if (n == 0)
        return vector<int>{0};
    else if (n == 1)
        return vector<int>{a[n - 1]};
    vector<int> ans;
    int currentMax = a[n - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        currentMax = max(currentMax, a[i]);
        if (a[i] == currentMax)
            ans.push_back(a[i]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int missingNumber(int arr[], int n)
{
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }
    int positive = 1;
    for (int i = 0; i < n; i++)
    {
        if (mp.find(positive) == mp.end())
        {
            return positive;
        }
        positive++;
    }
}

/* extra space solution */
// void rearrange(long long *arr, int n)
// {
//     vector<long> temp;
//     int low = 0 , high = n-1;
//     while (low<=high)
//     {
//         if(arr[low] == arr[low+1]){
//             continue;
//         }
//         temp.push_back(arr[high]);
//         temp.push_back(arr[low]);
//         low++;
//         high--;
//     }
//     for (int i = 0; i < n; i++)
//     {
//         arr[i] = temp[i];
//     }
//     temp.clear();

// }

// const space
void rearrange_v2(long long arr[], int n)
{
    long maxElement = arr[n - 1] + 1;
    int max = n - 1;
    int min = 0;

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            arr[i] = arr[i] + (arr[max] % maxElement) * maxElement;
            max--;
        }
        else
        {
            arr[i] = arr[i] + (arr[min] % maxElement) * maxElement;
            min++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr[i] / maxElement;
    }
}
/* Rearrange an array with O(1) extra space elements from 1 to n-1 */
void arrange(long long arr[], int n)
{
    // Your code here
    for (int i = 0; i < n; i++)
        arr[i] = arr[i] + (arr[arr[i]] % n) * n;
    for (int i = 0; i < n; i++)
        arr[i] = arr[i] / n;
}

int maxIndexDiff(int a[], int n)
{
    vector<int> diff;
    for (int i = 0; i < n; i++)
    {
        int j = n - 1;
        while (a[i] > a[j])
        {
            j--;
        }
        diff.push_back(j - i);
    }
    return *max_element(diff.begin(), diff.end());
}

/* Given a sorted array arr[] of size N without duplicates,
and given a value x. Floor of x is defined as the largest element K in arr[] such that K is smaller than or equal to x.
 Find the index of K(0-based indexing). */
int findFloor(long long int arr[], int N, long long int x)
{

    long long low = 0, high = N - 1;
    long long currentMaxFloor = INT_MIN;
    long long index = -1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] <= x)
        {
            currentMaxFloor = max(arr[mid], currentMaxFloor);
            index = mid;
            low = mid + 1;
        }
        else if (arr[mid] > x)
        {
            high = mid - 1;
        }
    }
    return index;
}

/* Given an array of distinct elements which was initially sorted. This array is rotated at some unknown point. The task is to find the minimum element in the given sorted and rotated array.  */
int minNumber(int arr[], int low, int high)
{
    int minElement = arr[0];
    if (arr[high - 1] < arr[high - 2])
        return high - 1;
    if (arr[low] > arr[low + 1])
        return low + 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] < arr[mid - 1])
            return mid;
        if (arr[mid + 1] < arr[mid])
            return mid + 1;
        low++;
        high--;
    }
    return -1;
}

/* You are given an array of N+2 integer elements. All elements of the array are in range 1 to N. Also, all elements occur once except two numbers which occur twice. Find the two repeating numbers. */

// random order
vector<int> twoRepeated(int arr[], int N)
{
    unordered_map<int, int> ump;
    vector<int> ans;
    for (int i = 0; i < N; i++)
    {
        ump[arr[i]]++;
    }
    for (const auto &m : ump)
    {
        if (m.second > 1)
            ans.push_back(m.first);
    }
    return ans;
    // fixed order w/ O(1) space
    /*
        vector<int>v;
            for(int i=0; i<N+2; i++)
            {
                if(arr[abs(arr[i])] > 0)
                {
                    arr[abs(arr[i])] = -arr[abs(arr[i])];
                }
                else
                {
                    v.push_back(abs(arr[i]));
                }
            }
            return v;
     */
}

/*
You are given heights of consecutive buildings. You can move from the roof of a building to the roof of next adjacent building. You need to find the maximum number of consecutive steps you can put forward such that you gain an increase in altitude with each step.
 */
int maxStep(int A[], int N)
{
    // Your code here
    int maxJumps = 0;
    int jumpStep = 0;
    for (int i = 1; i < N; i++)
    {
        if (A[i] > A[i - 1])
        {
            jumpStep++;
            maxJumps = max(maxJumps, jumpStep);
            continue;
        }
        jumpStep = 0;
    }
    return maxJumps;
}

/* Maximum Water Between Two Buildings  */
int maxWater(int height[], int n)
{
    int low = 0, high = n - 1;
    int maxArea = INT_MIN;
    while (low <= high)
    {
        int gap = high - low - 1;
        if (height[low] < height[high])
        {
            maxArea = max(maxArea, gap * min(height[low], height[high]));
            low++;
            continue;
        }
        else
        {
            maxArea = max(maxArea, gap * min(height[low], height[high]));
            high--;
        }
    }
    return maxArea;
}

/* find repeating element in consecutive sorted array of size n w/ elements from 1 to N */
// best solution
pair<int, int> findRepeating(int *arr, int len)
{
    pair<int, int> ans;
    int start = 0, end = len - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if ((mid > 0 && arr[mid] == arr[mid - 1]) || (mid < len - 1 && arr[mid] == arr[mid + 1]))
        {
            ans.first = arr[mid];
            ans.second = upper_bound(arr, arr + len, arr[mid]) - lower_bound(arr, arr + len, arr[mid]);
            return ans;
        }
        else if (arr[mid] - arr[start] != mid - start)
            end = mid - 1;
        else
            start = mid + 1;
    }
    ans.first = -1;
    ans.second = -1;
    return ans;
}

/* ount More than n/k Occurences  */
int countOccurence(int arr[], int n, int k)
{
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }
    int occurence = 0;
    for (auto &x : mp)
    {
        if (x.second > n / k)
        {
            occurence++;
        }
    }
    return occurence;
}

    vector<int> printClosest(int arr[], int brr[], int n, int m, int x) {
       vector<int> ans;
            int low=0,high=m-1;
            int diff=INT_MAX;
            while(low<n&&high>=0){
                int sum=arr[low]+brr[high];
                if(diff>abs(sum-x)){
                    diff=abs(sum-x);
                    ans={arr[low],brr[high]};
                }
                if(sum>=x)high--;
                else low++;
            }
            return ans;
    }

/* triplet sum */
   bool find3Numbers(int A[], int n, int X)
    {
        //Your Code Here
        for (int i = 0; i < n-1; i++)
        {
            int twoSum=X-A[i];
            unordered_set<int> s;
            for (int j = i+1; j < n; j++)
            {
                if(s.find(twoSum-A[j])!=s.end())return true;
                else s.insert(A[j]);
            }
            
        }
        return false;


        //w/ constant space
        /*     int low = 0, high = n-1;
       sort(A, A+n);
       for(int i=0; i<n-2; ++i){
           low = i+1;
           high = n-1;
           while(low < high){
               if(A[low] + A[high] + A[i] == X)
                   return true;
               else if(A[low] + A[high] + A[i] < X)
                   ++low;
               else
                   --high;
           }
       }
       return false; */
        
        
    }



//^ Count number of subarrays such that the number of subarrays having value strictly greater than K. where 'value' means maximum element in that particular subarray..

long long countSubarray(vector<int> &arr , int K){

    //* Method 1:  O(N) time and O(1) approach
    int n = arr.size();
    long long ans = 0;
    long long last = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > K)
        {
            ans+=i + 1; //~ all possible subarrays which can be formed using this element excluding those which contains element which comes after this arr[i] basically , selecting arrays where the last element is this ...
            last = i + 1;
        }
        else
        {
            ans += last;
        }   
    }

     /*  
     * Method - 2 :
*  Step 1 :- We know total possible Subarrayof length n is (n*(n+1))/2.

*  Step 2 :- Now,Just think reverse of the problem, i.e find count of total subarray *   whose value is less than or equal to k. and then subtract this count from our   total possible subarray.

*  Step 3 :- This count can be easily find by considering the total maximum length of *  subarray in which value is less then or equal to k
     */
    // long long totalSubarrays = (n*(n+1))/2;
    // long long less = 0;
    // for(int i=0;i<n;i++){
    //     if(arr[i]<=K){
    //         less++;
    //     }
    //     else
    //     {
    //         totalSubarrays -= (less*(less+1))/2;
    //         less = 0;
    //     }
        

    // }
          
    // totalSubarrays -= (less*(less+1))/2;
    // return totalSubarrays;

    //! Brute force O(N^2) on worst case...
/*      int left = 0;
	    long long ans = 0;
	    for (int i = 0 ; i < n ; i++){
	        for (int j = left ; j < n ; j++){
	            if (arr[j] > k) {
	                ans += (n - j);
	                break;
	            }
	        }
	        left++;
	    }
	    return ans; */

}


int main()
{
    int arr[] = {1, 4, 45, 6 ,10 ,8};
    int brr[]={10, 20, 30, 40} ;
    vector<int> temp = {1, 2, 3, 4, 5};
    // vector<int> result = leaders(arr,6);
    // convertToWave(6, temp);
    // maximumAdjacent(6,arr);
    // leftRotateByD_v3(arr, 5, 2);
    // missingNumber(arr, 5);
    // rearrange_v2(arr, 13);
    // cout<<maxIndexDiff(arr,9);
    // cout<<findFloor(arr,7,13);
    // cout << minNumber(arr, 0, 13);
    // findRepeating(arr, 5);
    // printClosest(arr,brr,4,4,32);
    cout<<find3Numbers(arr,6,13);
    // for (auto &c : arr)
    // {
    //     cout << c << " ";
    // }

} // } Driver Code Ends