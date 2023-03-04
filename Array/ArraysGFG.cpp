#include <bits/stdc++.h>
using namespace std;

// Linear search O(n)✅
// template <class T = int>
// int search_in(T arr[], int size, T x)
// {
//     for (int i = 0; i < size; i++)
//     {
//         if (arr[i] == x)
//         {
//             return 1;
//         }
//     }
//     return -1;
// }

// Insertion in array O(n)✅
//  template <class T = int>
//  int insert(T arr[] , int size , T element , int capacity , int index){
//      if (size == capacity)
//      {
//          return size;
//      }
//      for (int i = size - 1; i >= index; i--)
//      {
//          arr[i+1] = arr[i];
//      }
//      arr[index] = x;
//      return (size+1);

// }

// Deletion in arrays O(n)✅

// template <class T = int>
// int deleteFromArray(T arr[], int size, T element)
// {
//     int* i = new int;
//     for (*i = 0; *i < size; (*i)++)
//     {
//         if (arr[*i] == element)
//         {
//             break;
//         }
//     }
//     if (*i == size)
//     {
//         return size;
//     }
//     for (int j = *i; j < size - 1; j++)
//     {
//         arr[j] = arr[j + 1];
//     }
//     delete i;
//     return size - 1;
// }

// Largest element in array O(n^2)✅
// int getLargest(int arr[], int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         bool flag = true;
//         for (int j = i; j < size; j++)
//         {
//             if (arr[j] > arr[i])
//             {
//                 flag = false;
//                 break;
//             }
//         }
//         if (flag == true)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// Largest number in an array O(n) ✅
// int getLargest_v2(int arr[], int size)
// {
//     int res = 0;
//     for (int i = 1; i < size; i++)
//     {
//         if (arr[i] > arr[res])
//         {
//             res = i;
//         }
//     }
//     return res;
// }

// Second Largest element in an array O(n) 🙃🙃✅
//  int secondLargest(int arr[],int size){
//      int res = 0 , min_diff = INT_FAST16_MAX;
//      int max2; bool flag = false;
//      for (int i = 0; i < size; i++)
//      {
//          if (arr[i]>arr[res])
//          {
//              res = i;
//          }
//      }
        // for (int i = 0; i < size; ++i)
        // {
        //     int differ = arr[res] - arr[i];
        //     if (differ < min_diff && differ > 0)
        //     {
        //         min_diff = differ;
        //         flag = true;
        //         max2 = i;
        //     }
        // }
//      if (flag == true)
//      {
//          return max2;
//      }
//      else
//      {
//          return -1;
//      }

// }

// Simpler form of second largest✅
//  int secondLargest(int arr[],int n){
//      int largest = getLargest_v2(arr,n);
//      int res = -1;
//      for (int i = 0; i < n; i++)
//      {
//          if (arr[i] != arr[largest])
//          {
//              if (res == -1)
//              {
//                  res = i
//              }
//              else if(arr[i] > arr[res])
//              {
//                  res = i;
//              }

//         }

//     }
//     return res

// }

// Second largest optimized approach 😎😎😎
// int secondLargest_v2(int arr[], int size)
// {
//     int res = -1, largest = 0;
//     for (int i = 0; i < size; i++)
//     {
//         if (arr[i] > arr[largest])
//         {
//             res = largest;
//             largest = i;
//         }
//         else if (arr[i] != arr[largest])
//         {
//             if (res == -1 || arr[i] > arr[res])
//             {
//                 res = i;
//             }
//         }
//     }
//     return res;
// }

// Array is sorted or not? O(n^2)
//  bool isSorted(int arr[] , int size){
//      for (int i = 0; i < size; i++)
//      {
//          for (int j = i+1; j < size; j++)
//          {
//              if (arr[j]<arr[i])
//              {
//                  return false;
//              }

//         }

//     }
//     return true;

// }

// isSorted O(n)
//  bool isSorted_v2(int arr[] , int size){
//      for (int i = 0; i < size; i++)
//      {
//          if (arr[i+1]<arr[i])
//          {
//              return false;
//          }

//     }
//     return true;

// }

// reverse of an array O(n)
// void reverse(int arr[] , int n){
//     int* low = new int(0);
//     int* high = new int(n-1);
//     while (*low < *high)
//     {
//         int temp = arr[*low];
//         arr[*low] = arr[*high];
//         arr[*high] = temp;
//         (*low)++;
//         (*high)--;
//     }
//     delete low , high;

// }

// remove duplicates O(n)
// int removeDuplicate(int arr[], int size)
// {
//     int temp[size];
//     temp[0] = arr[0];
//     int res = 1;
//     for (int i = 1; i < size; i++)
//     {
//         if (temp[res - 1] != arr[i])
//         {
//             temp[res] = arr[i];
//             res++;
//         }
//     }
//     for (int j = 0; j < size; j++)
//     {
//         arr[j] = temp[j];
//     }
//     return res;
// }

// remove duplicates w/ O(1) space
//  int removeDup_v2(int arr[] , int size){
//      uint_fast16_t res = 1;
//      for (int i = 1; i < size; i++)
//      {
//          if (arr[i] != arr[res-1])
//          {
//              arr[res]=arr[i];
//              ++res;
//          }

//     }
//     return res;
// }

// Move all zeroes to end O(n^2)

// void moveZeroes(int arr[], int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         if (arr[i] == 0)
//         {
//             for (int j = i + 1; j < size; j++)
//             {
//                 if (arr[j] != arr[i])
//                 {
//                     swap(arr[i], arr[j]);
//                     break;
//                 }
//             }
//         }
//     }
// }

// move zeroes to end O(n)😶😑
void moveZeroes_v2(int arr[], int size)
{
    uint_fast16_t countNonZero = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != 0)
        {
            swap(arr[i], arr[countNonZero]);
            countNonZero++;
        }
    }
}

// left rotate an array by 1 O(n)
 void leftRotateBy1(int arr[] , int size){
     int_fast16_t temp = arr[0];
     for (int i = 0; i < size; i++)
     {
         arr[i] = arr[i+1];
     }
     arr[size-1] = temp;

}

// left rotate array by d places 😎
// void leftRotateByD(int arr[], int size, int d)
// {
//     if (d <= size)
//     {   
//         queue<int> q;
//         for (int i = 0; i < size; i++)
//         {
//             if(i < d){
//             q.push(arr[i]);
//             arr[i] = arr[i+d];
//             continue;
//             }
//             else if(i+d<size){
//                 arr[i] = arr[i+d];
//             }
//             else{break;}
//         }
//         for (int i = size - d; i < size; i++)
//         {
//             arr[i] = q.front();
//             q.pop();
//         }
        
        
        
//     }
// }

// left rotate array O(nd)
//  void leftRotate(int arr[] , int size , int d){
//      for (int i = 0; i < d; i++)
//      {
//          leftRotateBy1(arr,size);
//      }
//  }

// void leftRotate_v2(int arr[], int size, int d)
// {
//     int temp[d];
//     for (int i = 0; i < d; i++)
//     {
//         temp[i] = arr[i];
//     }
//     for (int i = d; i < size; i++)
//     {
//         arr[i - d] = arr[i];
//     }
//     for (int i = 0; i < d; i++)
//     {
//         arr[size - d + i] = temp[i];
//     }
// }

//left rotate an array by d places O(n) time and const space
void leftRotateByD_v3(int arr[] , int n , int d){
    d=d%n;
    reverse(arr,arr+d);
    reverse(arr+d,arr+n);
    reverse(arr,arr+n);
}


// get leaders in an array O(n^2)
// void getLeaders(int arr[], int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         bool flag = false;
//         for (int j = i + 1; j < size; j++)
//         {
//             if (arr[i] <= arr[j])
//             {
//                 flag = true;
//                 break;
//             }
//         }
//         if (flag == false)
//         {
//             cout << arr[i] << " ";
//         }
//     }
// }

// get leader O(n)
 void getLeader_v2(int arr[] , int size){
     int arr_ldr = arr[size-1];
     cout<<arr_ldr<<" ";
     for (int i = size - 2; i >= 0; i--)
     {
         if (arr_ldr < arr[i])
         {
             arr_ldr = arr[i];
             cout<<arr_ldr<<" ";
         }

    }

}
// max difference problem O(n^2)
// int maxDiff(int arr[], int n)
// {
//     int res = arr[1] - arr[0];
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             res = max(res, arr[j] - arr[i]);
//         }
//     }
//     return res;
// }

// max difference problem O(n)
int maxDiff(int arr[], int n)
{
    int res = arr[1] - arr[0];
    int minVal = arr[0];
    for (int i = 1; i < n; i++)
    {
        res = max(res, arr[i] - minVal);
        minVal = min(minVal, arr[i]);
    }
    return res;
}

// stock buy and sell o(n^2)
// int maxProfit(int arr[], int start, int end)
// {
//     if (end <= start)
//     {
//         return NULL;
//     }
//     unsigned int profit = 0;
//     for (int i = start; i < end; i++)
//     {
//         for (int j = i + 1; j <= end; j++)
//         {
//             if (arr[j] > arr[i])
//             {
//                 uint_fast32_t curr_profit = arr[j] - arr[i] + maxProfit(arr, start, i - 1) + maxProfit(arr, j + 1, end);
//                 profit = max(profit, curr_profit);
//             }
//         }
//     }
//     return profit;
// }
//

// stock buy and sell O(n)
int maxProfit_v2(int price[], int size)
{
    uint_fast32_t profit = 0;
    for (int i = 1; i < size; i++)
    {
        if (price[i] > price[i - 1])
        {
            profit += price[i] - price[i - 1];
        }
    }
    return profit;
}

// frequencies in a sorted array
void frequency(int arr[], int size)
{
    unordered_multiset<int> ums;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        ums.insert(arr[i]);
    }

    for (int i = 1; i <= size; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            count = ums.count(arr[i]);
            cout << arr[i] << " -> " << ums.count(arr[i]) << endl;
            i += count - 1;
        }
        else if (arr[i] > arr[i - 1])
        {
            cout << arr[i - 1] << " -> " << ums.count(arr[i - 1]) << endl;
        }
        else
        {
            continue;
        }
    }
}

// Frequency in an array(sorted)
void frequency_v2(int arr[], int size)
{
    int freq = 1, i = 1;
    while (i < size)
    {
        while (i < size && arr[i] == arr[i - 1])
        {
            freq++;
            i++;
        }
        cout << arr[i - 1] << " -> " << freq << endl;
        i++;
        freq = 1;
    }
    if (size == 1 || arr[size - 1] != arr[size - 2])
    {
        cout << arr[size - 1] << " -> " << 1 << endl;
    }
}

// Trapping rain water O(n^2)
//  int getWater(int arr[] , int size){
//      uint_fast16_t res = 0;
//      for (int i = 1; i < size - 1; i++)
//      {
//          int left_max = arr[i];
//          for (int j = 0; j < i; j++)
//          {
//              left_max = max(left_max,arr[j]);
//          }
//          int right_max = arr[i];
//          for (int k = i+1; k < size; k++)
//          {
//              right_max = max(right_max , arr[k]);
//          }

//         res = res + (min(left_max , right_max) - arr[i]);
//     }
//     return res;

// }

// trapping water O(n) 🤨
int getWater_v2(int arr[], int size)
{
    uint_fast16_t res = 0;
    int left_max[size], right_max[size];
    left_max[0] = arr[0];
    for (int i = 1; i < size; i++)
    {
        left_max[i] = max(arr[i], left_max[i - 1]);
    }
    right_max[size - 1] = arr[size - 1];
    for (int i = size - 2; i >= 0; i--)
    {
        right_max[i] = max(arr[i], right_max[i + 1]);
    }
    for (int i = 0; i < size - 1; i++)
    {
        res += min(right_max[i], left_max[i]) - arr[i];
    }
    return res;
}

// Maximum consecutive 1's in a binary array O(n)
// int maxConsecutive1s(bool arr[], int size)
// {
//     set<int> s;
//     uint_fast16_t count = 1;
//     for (int i = 0; i < size; i++)
//     {
//         if (arr[i] == arr[i+1] && arr[i] == 1)
//         {
//             count++;
//         }
//         else
//         {
//             s.insert(count);
//             count = 1;
//         }
//     }
//     return *s.crbegin();
//     s.clear();
// }

// maximum consecutive 1s in a binary arr O(n)

int maxConsecutive1s(bool arr[], int size)
{
    uint_fast16_t res = 0;
    {
        uint_fast16_t curr = 0;
        for (int i = 0; i < size; i++)
            if (arr[i] == 0)
            {
                curr = 0;
            }
            else
            {
                curr++;
                res = max(res, curr);
            }
    }
    return res;
}

// maximum sum subarray O(n^2)
 int maxSum(int arr[] , int size){
     int_fast16_t res = arr[0];
     for (int i = 0; i < size; i++)
     {
         int_fast16_t curr = 0;
         for (int j = i; j < size; j++)
         {
             curr+=arr[j];
             res = max(res,curr);
         }

    }
    return res;

}

// maximum sum subarray O(n) kadanes algo 🤔
int maxSum_v2(int arr[], int size)
{
    int_fast16_t res = arr[0], maxEnding = arr[0];
    for (int i = 1; i < size; i++)
    {
        maxEnding = max(maxEnding + arr[i], arr[i]);
        res = max(res, maxEnding);
    }
    return res;
}

// longest even odd subarray O(n)
int maxEvenOdd(int arr[], int size)
{
    int res = 1, length = 1;
    for (int i = 1; i < size; i++)
    {
        if ((arr[i] % 2 != 0 && arr[i - 1] % 2 == 0) || (arr[i] % 2 == 0 && arr[i - 1] % 2 != 0))
        {
            res++;
            // length++;
        }
        else
        {
            res = 1;
        }
        length = max(res,length);

    }
    return length;
}

// Maximum circular subarray sum O(n^2)
// int maxSumCircular(int arr[], int size)
// {
//     int_fast16_t res = arr[0];
//     for (int_fast16_t i = 0; i < size; i++)
//     {
//         int_fast16_t curr_max = arr[i];
//         int_fast16_t curr_sum = arr[i];
//         for (int_fast16_t j = 1; j < size; j++)
//         {
//             uint_fast16_t index = (i + j) % size;
//             curr_sum += arr[index];
//             curr_max = max(curr_max, curr_sum);
//         }
//         res = max(curr_max, res);
//     }
//     return res;
// }

// kadanes method max sum of circular sum O(n)
int maxSumCircular_v2(int arr[], int size)
{
    int_fast32_t max_normal = maxSum_v2(arr, size);
    if (max_normal < 0)
    {
        return max_normal;
    }
    int_fast32_t arr_sum = 0;
    for (int i = 0; i < size; i++)
    {
        arr_sum += arr[i];
        arr[i] = -arr[i];
    }
    int_fast32_t max_circular = arr_sum + maxSum_v2(arr, size);
    return max(max_normal, max_circular);
}

// finding majority in an array O(n) 😎😎
int findMajority(int arr[], int size)
{
    unordered_map<int, int> ump;
    for (int i = 0; i < size; i++)
    {
        ump[arr[i]]++;
    }
    for (auto &y : ump)
    {
        if (y.second > size / 2)
        {
            return y.first;
        }
    }
    ump.clear();
    return -1;
}

// finding majority in array O(n^2) [returns index]
// int findMajority_v2(int arr[], int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         uint16_t count = 1;
//         for (int j = i + 1; j < size; j++)
//         {
//             if (arr[i] == arr[j])
//             {
//                 count++;
//             }
//         }
//         if (count > size / 2)
//             return i;
//     }
//     return -1;
// }

//^ finding majority in an array O(n) [returns index]
/* 
&    Loop through each element and maintains a count of the majority element, and a majority index, maj_index
&    If the next element is the same then increment the count if the next element is not the same then decrement the count.
&    if the count reaches 0 then change the maj_index to the current element and set the count again to 1.
&    Now again traverse through the array and find the count of the majority element found.
&   If the count is greater than half the size of the array, print the element
&    Else print that there is no majority element
 */
int findMajority_v3(int arr[], int size)
{
    uint_fast16_t res = 0, count = 1;
    for (int_fast16_t i = 1; i < size; i++)
    {
        if (arr[res] == arr[i])
        {
            count++;
        }
        else
        {
            count--;
        }
        if (count == 0)
        {
            res = i;
            count = 1;
        }
    }
    // 2nd part
    count = 0;
    for (int_fast16_t i = 0; i < size; i++)
    {
        if (arr[res] == arr[i])
        {
            count++;
        }
    }
    if (count <= size / 2)
    {
        res = -1;
    }
    return res;
}

// minimum group flips to make same O(n^2)
//  void minFlips(bool arr[] , int size){
//      uint16_t count0s = 0 , count1s = 0;
//      uint16_t minflips = 0;
//      for (int i = 0; i < size-1; i++)
//      {
//          if (arr[i] == 1)
//          {
//              while (arr[i+1] == 1)
//              {
//                  ++i;
//              }
//              count1s++;
//          }
//          else if (arr[i] == 0)
//          {
//              while (arr[i+1] == 0)
//              {
//                  ++i;
//              }
//              count0s++;

//         }
//         minflips = min(count1s , count0s);

//     }
//     cout<<minflips<<endl;
//     return;
// }

//^ minimum group flips O(n)
/* 
& There are only two types of groups (groups of 0s and groups of 1s)
& Either the counts of both groups are same or the difference between counts is at   most 1.

 */
void minFlips_v2(bool arr[], int size)
{
    //? Traverse through all array elements
    //? starting from the second element
    for (int i = 1; i < size; i++)
    {   
        //? If current element is not same
        //? as previous
        if (arr[i] != arr[i - 1])
        {
        //? If it is same as first element
        //? then it is starting of the interval
        //? to be flipped.
            if (arr[i] != arr[0])
            {
                cout << "from " << i << " to ";
            }
            else
                cout << (i - 1) << endl;
        }
    }
    if (arr[size - 1] != arr[0])
    {
        cout << size - 1 << endl;
    }
}

// max sum of k consecutive interger O(n^2)

int maxKsum(int arr[] , int size ,short int k){
    int_fast32_t maxSum = 0;
    for (int i = 0; i + k -1 < size; i++)
    {
        int_fast32_t current_sum = 0;
        for (int j = 0; j < k; j++)
        {
            current_sum+=arr[i+j];
        }
        maxSum = max(maxSum , current_sum);
    }
    return maxSum;
}

// window sliding technique for above prob O(n)
 int maxKsum_v2(int arr[], int size, unsigned short int k)
 {
     int_fast32_t curr_sum = 0;
     for (uint_fast8_t i = 0; i < k; i++)
     {
         curr_sum += arr[i];
     }
     int_fast32_t maxSum = curr_sum;
     for (uint_fast16_t i = k; i < size; i++)
     {
         curr_sum += (arr[i] - arr[i - k]);
         maxSum = max(maxSum, curr_sum);
     }
     return maxSum;
 }

// find if there is a subarray with given sum , array is unsorted and is of only non negative intergers
// bool findSumSubarray(int arr[], int size, uint16_t givenSum)
// {
//     for (int i = 0; i < size; i++)
//     {
//         uint_fast16_t sum = 0;
//         for (int j = i; j < size; j++)
//         {
//             sum += arr[j];
//             if (sum == givenSum)
//             {
//                 return true;
//             }
//         }
//     }
// }

// sliding window technique for above que O(n)
bool findSumSubarray(int arr[], int size, uint_fast16_t givenSum)
{
    uint_fast16_t sum = arr[0], start = 0;
    for (int end = 1; end < size; end++)
    {
        while (sum > givenSum && start < end - 1)
        {
            sum -= arr[start];
            start++;
        }

        if (end < size)
        {
            sum += arr[end];
        }
        if (sum == givenSum)
        {
            return true;
        }
    }

    return sum == givenSum;
}

// prefix sum array;
int main(int argc, char const *argv[])
{
    int testArr[] = {1, 4, 20, 3, 10, 5};
    bool testArr2[] = {0,1,1,1,0,0,1,1,0};
    
    
    // cout << findSumSubarray(testArr, 6, 33);
    return 0;
}
