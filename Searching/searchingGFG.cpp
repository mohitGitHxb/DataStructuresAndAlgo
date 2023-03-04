#include <bits/stdc++.h>
using namespace std;

// binary search O(logn)
 int binarySearch(vector<int> &arr,int x){
     int low=0,high=arr.size()-1;
     for (int i = low; i <= high; i++)
     {
         int mid = (low + high)/2;
         if (arr[mid] == x)
         {
             return mid;
         }
         else if (arr[mid]>x)
         {
             high = mid - 1;
         }
         else if (arr[mid]<x)
         {
             low = mid + 1;
         }
         else{continue;}

    }
    return -1;
}

// binarySearchRecursive() O(logn) O(logn) auxiallary space
int binarySearchRecursive(vector<int> &arr, int x)
{
    static uint_fast16_t low = 0, high = arr.size() - 1;
    static uint_fast16_t mid = 0;
    if (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] > x)
        {
            high = mid - 1;
            binarySearchRecursive(arr, x);
        }
        else if (arr[mid] < x)
        {
            low = mid + 1;
            binarySearchRecursive(arr, x);
        }
        else if (arr[mid] == x)
        {
            return mid;
        }
    }
    else
        return -1;
}

// index of first occurrence
// int firstOccurrence(vector<int> &arr, int x)
// {
//     uint_fast16_t low = 0, high = arr.size() - 1;
//     while (low <= high)
//     {
//         uint_fast16_t mid = (low + high) / 2;
//         if (arr[mid] == x)
//         {
//             for (int i = low; i < mid; i++)
//             {
//                 if (arr[i] == x)
//                 {
//                     return i;
//                 }
//             }
//             return mid;
//         }
//         else if (arr[mid] > x)
//         {
//             high = mid - 1;
//         }
//         else if (arr[mid] < x)
//         {
//             low = mid + 1;
//         }
//         else
//         {
//             continue;
//         }
//     }
//     return -1;
// }

//^ index of first occurrence optimized
//* O(LogN) T.C | O(1) S.C
int firstOccurrence_v2(vector<int> &arr, int x)
{
    uint_fast16_t low = 0, high = arr.size() - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] > x)
        {
            high = mid - 1;
        }
        else if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            if (mid == 0 || (arr[mid - 1] != arr[mid]))
            {
                return mid;
            }
            else
            {
                high = mid - 1;
            }
        }
    }
}

//^ last occurrence of an number
//* O(logN) T.C | O(1) S.C
 int lastOccurrence(vector<int> &arr, int x)
 {
     uint_fast16_t low = 0, high = arr.size() - 1, mid;
     while (low <= high)
     {
         mid = (low + high) / 2;
         if (arr[mid] > x)
         {
             high = mid - 1;
         }
         else if (arr[mid] < x)
         {
             low = mid + 1;
         }
         else
         {    //? changed this portion only to check for an index higher than the current
             if (mid == arr.size() - 1 || (arr[mid + 1] != arr[mid]))
             {
                 return mid;
             }
             else
             {
                 low = mid + 1;
             }
         }
     }
 }

//^s count occurrences in a sorted array
 int getOccurrences(vector<int> &arr , int x){
     int first = firstOccurrence_v2(arr,x);
     if (first == -1)
     {
         return 0;
     }
     else
     {
         return (lastOccurrence(arr,x) - first + 1);
     }
 }

// count 1's in an sorted array
//  int count1s(vector<int> &arr){
//      int first = firstOccurrence_v2(arr,1);
//      return arr.size() - first;
//  }

//^ sqrt floor of a number using binary search
//* O(logN) T.C | O(1) space
int sqrtFloor(int x)
{
    uint_fast16_t low = 0, high = x, ans = 1;
    while (low <= high)
    {
        uint_fast16_t mid = (low + high) / 2;
        if (mid * mid == x)
        {
            return mid;
        }
        else if (mid * mid > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
            ans = mid;
        }
    }
    return ans;
}

// search in an infinite sorted array
int searchINF(vector<int> &arr, int x)
{
    uint16_t i = 0;
    while (true)
    {
        if (arr[i] == x)
        {
            return i;
        }
        if (arr[i] > x)
        {
            return -1;
        }
        i++;
    }
}

//^ search in an inf array O(log(position))
//  int searchINF_v2(vector<int> &arr,int x){
//      if (arr[0] == x)
//      {
//          return 0;
//      }
//      uint_fast16_t i = 1;
//      while (arr[i] < x)
//      {
//          i=i*2;
//          if(arr[i] == x){return i;}

//     }
//     return binarySearch(arr,x,i/2 + 1 , i - 1);

// }

//^ search in a sorted rotated array
//* O(logN) T.C | O(1) S.C
int searchRotated(vector<int> &arr, int x)
{
    uint_fast16_t low = 0, high = arr.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == x)
        {
            return mid;
        }
        else if (arr[low] < arr[mid])
        {
            if (x >= arr[low] && x < arr[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else
        {
            if (x > arr[mid] && x <= arr[high])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
    }
    return -1;
}

// peak element in an array
// int getPeak(vector<int> &arr)
// {
//     if (arr.size() == 1)
//     {
//         return arr[0];
//     }
//     if (arr[0] >= arr[1])
//     {
//         return arr[0];
//     }
//     if (arr[arr.size() - 1] >= arr[arr.size() - 2])
//     {
//         return arr[arr.size() - 1];
//     }
//     for (int i = 1; i < arr.size() - 1; i++)
//     {
//         if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1])
//         {
//             return arr[i];
//         }
//     }
// }

// find if there is pair whose sum is equal to given sum in a sorted array.
// void printSumPair(vector<int> &arr, int x)
// {
//     uint_fast16_t left = 0, right = arr.size() - 1;
//     while (left < right)
//     {
//         if (arr[left] + arr[right] == x)
//         {
//             cout << arr[left] << " " << arr[right] << endl;
//             return;
//         }
//         else if (arr[left] + arr[right] > x)
//         {
//             right--;
//         }
//         else if (arr[left] + arr[right] < x)
//         {
//             left++;
//         }
//         else
//         {
//             return;
//         }
//     }
// }

// given a sorted array and a sum , find if there is a triplet with given sum.
//  bool isTriplet(vector<int>  &arr  , int x){
//      for (int i = 0; i < arr.size(); i++)
//      {
//          if(isPair(arr,i+1,arr.size()-1,x - arr[i]))
//              return true;
//      }
//      return false;
//  }

// int findRepeatingElement(vector<int> &arr){
//     sort(arr.begin(),arr.end());
//     for (int i = 0; i < arr.size(); i++)
//     {
//         // uint_fast8_t c = 0;
//         if (arr[i] == arr[i+1])
//         {
//             return arr[i];
//         }

//     }
// }

// repeating elements O(n)
//  int findRepeatingElement_v2(vector<int> &arr){
//      uint_fast8_t slow = arr[0],fast = arr[0];
//      do
//      {
//          slow = arr[slow];
//          fast = arr[arr[fast]];
//      } while (slow != fast);

//     slow = arr[0];
//     while (slow != fast)
//     {
//         slow = arr[slow];
//         fast = arr[fast];
//     }
//     return slow;
// }

// median of two sorted arrays O((n1+n2)*log(n1+n2))
// float medianSorted(vector<int> &arr1, vector<int> &arr2)
// {
//     vector<int> mergedArray = arr1;
//     merge(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), mergedArray.begin());
//     sort(mergedArray.begin(), mergedArray.end());
//     int midTerm = (mergedArray.size() - 1) / 2;
//     if ((arr1.size() + arr2.size()) % 2 != 0)
//     {
//         return mergedArray[midTerm];
//     }
//     else
//     {
//         return (mergedArray[midTerm - 1] + mergedArray[midTerm]) / 2;
//     }
// }

// median of two merged sorted array O(logn1) n1<=n2
int findMedian(int arr[], int n, int brr[], int m)
    {
          int n1 = (n<m) ? n : m;
       int n2 = (n>m) ? n : m;
       int begin = 0, end = n1;
       
       while(begin <= end)
       {
           int i1 = (begin + end)/2;
           int i2 = (n1 + n2 + 1)/2 - i1;
           int min1 = (i1 == n1) ? INT_MAX : arr[i1];
           int min2 = (i2 == n2) ? INT_MAX : brr[i2];
           int max1 = (i1 == 0) ? INT_MIN : arr[i1- 1];
           int max2 = (i2 == 0) ? INT_MIN : brr[i2- 1];
           
           if((max1 <= min2) && (max2 <= min1))
           {
               int max = (max1 > max2) ? max1 : max2;
               int min = (min1 < min2) ? min1 : min2;
               if((n1 + n2) % 2 == 0)
                   return (double)((max + min) / 2);
               else
                   return (double)max;
           }
           else if(max1 > min2)
               end = i1 - 1;
           else
               begin = i1 + 1;
       }
            
    }

// majority elements in an array
// int getMajority(vector<int> &arr)
// {
//     sort(arr.begin(), arr.end());
//     uint_fast16_t count = 0;
//     const uint_fast16_t maj = (arr.size() - 1) / 2;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[maj] == arr[i])
//         {
//             count++;
//         }
//     }
//     if (count >= (maj + 1))
//     {
//         return maj;
//     }
//     else
//     {
//         return -1;
//     }
// }

// Allocate min no. of pages
int sum(vector<int> &arr, int b, int e)
{
    int s = 0;
    for (int i = b; i < e; i++)
    {
        s += arr[i];
    }
    return s;
}
int minPages(vector<int> &arr, int n, int k)
{
    if (k == 1)
    {
        return sum(arr, 0, n - 1);
    }
    if (n == 1)
    {
        return arr[0];
    }
    int res = INT32_MAX;
    for (int i = 1; i < n; i++)
    {
        res = min(res, max(minPages(arr, i, k - 1), sum(arr, i, n - 1)));
    }
    return res;
}

// binary search mthod
bool isFeasible(vector<int> &arr, int k, int ans)
{
    int req = 1, sum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (sum + arr[i] > ans)
        {
            req++;
            sum = arr[i];
        }
        else
        {
            sum += arr[i];
        }
    }
    return (req <= k);
}
int minPages_v2(vector<int> &arr, int k)
{
    int sum = 0, mx = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        mx = max(mx, arr[i]);
    }
    int low = mx, high = sum, res = 0;
    while (low <= high)
    {
        int mid = (mid + high) / 2;
        if (isFeasible(arr, k, mid))
        {
            res = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
        return res;
    }
}
int main(int argc, char const *argv[])
{

    vector<int> test1 = {10, 20, 30, 40, 50};
    cout << minPages(test1, 5, 2);
    return 0;
}
