#include <bits/stdc++.h>
using namespace std;

// bubble sort Ø(n2)
// void bubbleSort(vector<int> &arr)
// {
// for (int i = 0; i < arr.size() - 1; i++)
// {
//     for (int j = 0; j < arr.size() - i - 1; j++)
//     {
//         if (arr[j] > arr[j + 1])
//         {
//             swap(arr[j], arr[j + 1]);
//         }
//     }
// }
// return;
// }

// //.bubble sort optimized
// void bubbleSort_v2(vector<int> &arr)
// {
//     for (int i = 0; i < arr.size() - 1; i++)
//     {
//         bool swapped = false;

//         for (int j = 0; j < arr.size() - i - 1; j++)
//         {
//             if (arr[j] > arr[j + 1])
//             {
//                 swap(arr[j], arr[j + 1]);
//                 swapped = true;

//             }
//         }
//         if (swapped == false)
//         {
//             break;
//         }

//     }
//     return;
// }

// selection sort Ø(n2)
//  void selectionSort(vector<int> &arr)
//  {
//      for (int i = 0; i < arr.size()-1; i++)
//      {
//          int minIndex = i;
//          for (int j = i + 1; j < arr.size(); j++)
//          {
//              if (arr[j] < arr[minIndex])

//             {
//                 minIndex = j;
//             }
//         }
//         swap(arr[minIndex], arr[i]);
//     }
// }

// Insertion sort (for small arrays) O(n2)
// void insertionSort(vector<int> &arr)
// {
//     for (int i = 1; i < arr.size(); i++)
//     {
//         int key = arr[i];
//         int j = i - 1;
//         while (arr[j] > key && j >= 0)
//         {
//             arr[j + 1] = arr[j];
//             j--;
//         }

//         arr[j + 1] = key;
//     }
// }

// merge two sorted arrays O(sz1+sz2)*(totalsizelogn)
//  void mergeSortFunc(vector<int> &arr1 , vector<int> &arr2){
//      vector<int> merged;
//      merge(arr1.begin(),arr1.end(),arr2.begin(),arr2.end(),merged.begin());
//      sort(merged.begin() , merged.end());
//  }

// void mergeSortFunc2(vector<int> &arr1, vector<int> &arr2)
// {
//     uint_fast16_t i = 0, j = 0;
//     while (i < arr1.size() && j < arr2.size())
//     {
//         if (arr1[i] <= arr2[j])
//         {
//             cout << arr1[i] << " ";
//             i++;
//         }
//         else
//         {
//             cout << arr2[j] << " ";
//             j++;
//         }
//     }
//     while (i < arr1.size())
//     {
//         cout << arr1[i] << " ";
//         ++i;
//     }
//     while (j < arr2.size())
//     {
//         cout << arr2[j] << " ";
//         ++j;
//     }
// }

// merge function of merge sort O(n)

void Merge(vector<int> &arr, int low, int mid, int high)
{
    int n1 = mid - low + 1, n2 = high - mid;
    int left[n1], right[n2];
    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[low + i];
    }
    for (int i = 0; i < n2; i++)
    {
        right[i] = arr[n1 + i];
    }
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            k++;
            i++;
        }
        else
        {
            arr[k] = right[j];
            k++;
            j++;
        }
    }
    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// merge sort algorithm Ø(nlogn)

void mergeSort(vector<int> &arr, int l, int r)
{
    if (r > l)
    {                             // atleast two elements are needed
        int m = l + (r - l) / 2;  // same as (l+r)/2
        mergeSort(arr, l, m);     // sort element low to mid
        mergeSort(arr, m + 1, r); // sort elements mid to high
        Merge(arr, l, m, r);
    } // merge two sorted arrays
}

// intersection of two sorted arrays
// void intersection(vector<int> &arr1, vector<int> &arr2)
// {
//     uint_fast16_t i = 0, j = 0;
//     while (i < arr1.size() && j < arr2.size())
//     {
//         if (i > 0 && arr1[i] == arr1[i - 1]) // no need to process duplicate elements
//         {
//             ++i;
//             continue;
//         }
//         else if (arr1[i] > arr2[j]) // if arr1[i] is greater than every remaining element of arr1 has to be greater than arr2 elements(sorted)
//         {
//             j++;
//         }
//         else if (arr1[i] < arr2[j]) // same concept again
//         {
//             i++;
//         }
//         else
//         {
//             cout << arr1[i] << " ";
//             i++;
//             j++;
//         }
//     }
// }

// union of two sorted arrays(similar to merge func)
// void unionOf(vector<int> &arr1, vector<int> &arr2)
// {
//     int i = 0, j = 0;
//     while (i < arr1.size() && j < arr2.size())
//     {
//         if (arr1[i] == arr1[i - 1] && i > 0) // only unique elements
//         {
//             i++;
//             continue;
//         }
//         if (arr2[j] == arr2[j - 1] && j > 0) // only unique elements
//         {
//             j++;
//             continue;
//         }
//         else if (arr1[i] > arr2[j])
//         {
//             cout << arr2[j] << " ";
//             j++;
//         }
//         else if (arr1[i] < arr2[j])
//         {
//             cout << arr1[i] << " ";
//             i++;
//         }

//         else
//         {
//             cout << arr1[i] << " ";
//             i++;
//             j++;
//         }
//     }
//     while (i < arr1.size())
//     {
//         if (i > 0 && arr1[i] != arr1[i - 1])
//         {
//             cout << arr1[i] << " ";
//             ++i;
//         }
//     }

//     while (j < arr2.size())
//     {
//         if (j > 0 && arr2[j] != arr2[j - 1])
//         {
//             cout << arr2[j] << " ";
//             ++j;
//         }
//     }
// }

// count inversion in an array O(n^2)
//  int countInversions(vector<int> &arr){
//      int res = 0;
//      for (int i = 0; i < arr.size()-1; i++)
//      {
//          for (int j = i + 1; j < arr.size(); j++)
//          {
//              if(arr[i] > arr[j]){  //checks whether an element at higher index is smaller than the current index.
//                  ++res;
//              }
//          }

//     }
//     return res;

// }

// count inversions O(nlogn)
//  int countAndMerge(vector<int> &arr, int low, int mid, int high)
//  {
//      int n1 = mid - low + 1, n2 = high - mid;
//      int left[n1], right[n2];
//      for (int i = 0; i < n1; i++)
//      {
//          left[i] = arr[low + i];
//      }
//      for (int i = 0; i < n2; i++)
//      {
//          right[i] = arr[n1 + i];
//      }
//      int i = 0, j = 0, k = 0,res = 0 ;
//      while (i < n1 && j < n2)
//      {
//          if (left[i] <= right[j])
//          {
//              arr[k] = left[i];
//              k++;
//              i++;
//          }
//          else
//          {
//              arr[k] = right[j];
//              k++;
//              j++;
//              res+=(n1-i); //smaller than every other element after left[i]
//          }
//      }
//      while (i < n1)
//      {
//          arr[k] = left[i];
//          i++;
//          k++;
//      }
//      while (j < n2)
//      {
//          arr[k] = right[j];
//          j++;
//          k++;
//      }
//      return res;
//  }

// int countInversions_v2(vector<int> &arr , int l , int r){
//     int res = 0;
//     if (l < r)
//     {
//         int m = (l+r)/2;
//         res += countInversions_v2(arr,l,m); //count inversions in left half
//         res += countInversions_v2(arr,m+1,r); //count inversions in right half
//         res+= countAndMerge(arr,l,m,r);
//     }
//     return res;

// }

// partition function of Quick sort O(n) , space = O(n)

// void partition(vector<int> &arr, int l, int h , int p)
// {
//     int temp[h - l + 1], index = 0;
//     for (int i = l; i <= h; i++)
//     {
//         if (arr[i] <= arr[p]) // elements smaller than arr[p] are being stored in left side of arr[p]
//         {
//             temp[index] = arr[i];
//             index++;
//         }
//     }
//     for (int i = l; i <= h; i++)
//     {
//         if (arr[i] > arr[p]) //elements greater than arr[p] are being stored in right side of arr[p]
//         {
//             temp[index] = arr[i];
//             index++;
//         }
//     }
//     for (int i = l; i <= h; i++)
//     {
//         arr[i] = temp[i - l]; //copying elements back to arr
//     }
// }

//^ lomuto partition O(n)
int lomutoPartition(vector<int> &arr, int l, int h)
{
    int pivot = arr[h]; //? always last element
    int i = l - 1;
    for (int j = l; j <= h - 1; j++)
    {
        if (arr[j] < pivot)
        {
            ++i;
            swap(arr[i], arr[j]); //? all smaller elements comes before pivot
        }
    }
    swap(arr[i + 1], arr[h]); //? swaps pivot element with next bigger element after i
    return (i + 1);
    //? swap(arr[p],arr[h]) for custom pivot
}

//^ hoare's partition O(n)
int hoarespartition(vector<int> &arr, int l, int h)
{
    int pivot = arr[l]; // first element is pivot
    int i = l - 1, j = h + 1;
    while (true)
    {
        do
        {
            ++i;
        } while (arr[i] < pivot); // l to i must be smaller than =  pivot
        do
        {
            j--;
        } while (arr[j] > pivot); // j to h must be greater than =   pivot
        if (i >= j)               // i and j crossed each other
        {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

/* 
 & Quick sort : worst case O(n^2) avg case O(nlogn)
 & stable only in case of naive partition
 & lomuto and hoares are not stable sort*/

// Quick sort using lomuto Ø(nlogn)

// void quickSort(vector<int> &arr , int low , int high){
//     if(low<high){
//         int_fast16_t p = lomutoPartition(arr,low,high); //returns index
//         quickSort(arr,low,p-1);
//         quickSort(arr,p+1,high);
//     }
//     return;
// }

// quick sort using hoare's partition
void quickSort_v2(vector<int> &arr, int l, int h)
{
    if (l < h)
    {
        int_fast16_t p = hoarespartition(arr, l, h); /* p is partitioning index, arr[p] is now  at right place */
        quickSort_v2(arr, l, p); // separately sorts element before
        quickSort_v2(arr, p + 1, h);
    }
    return;
}

// tail call elimination in Quick sort
void quickSort_v3(vector<int> &arr, int l, int h)
{
begin:
    if (l < h)
    {
        int_fast16_t p = hoarespartition(arr, l, h); /* p is partitioning index, arr[p] is now
              at right place */
        quickSort_v3(arr, l, p);                     // separately sorts element before
        l = p + 1;
        goto begin; // optimizes extra space;
    }
    return;
}

//^ Kth smallest element in an unsorted array with distinct element
//  int KthSMALLESTelement(vector<int> &arr , uint_fast16_t k){
//      sort(arr.begin(),arr.end()); //?sort the array and return the kth index element
//      return arr[k-1];
//  }

//^ lomuto partition approach for kth smallest element Ø(n) [QUICK SELECT🅾🅿]
int KthSMALLESTelement(vector<int> &arr, int k)
{
    int_fast16_t l = 0, r = arr.size() - 1;
    while (l <= r) //? similar like binary search
    {
        uint_fast16_t p = lomutoPartition(arr, l, r);
        if (p == (k - 1))
        {
            return arr[p];
        }
        else if (p > (k - 1)) //? partition in left side of the array
        {
            r = p - 1;
        }
        else
            l = p + 1;
    }
    return -1;
}

//^ chocolate distribution problem nlogn sol
 int minDIFF(vector<int> &arr , int m){
     sort(arr.begin(),arr.end());
     int low = 0 , high = low + m - 1,res = INT16_MAX;
     while (high<arr.size())
     {
         int diff = abs(arr[high]-arr[low]);
         res = min(res,diff);
         low++;
         high++;
     }
     return res;

}

// sort an array with two types of elements 1. pos and negative

// void separateElements(vector<int> &arr){
//     vector<int> temp(arr.size()); //naive partition of qsort
//     int j = 0;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i]<0)
//         {
//             temp[j++] = arr[i];
//         }
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i]>=0)
//         {
//             temp[j++] = arr[i];
//         }
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         arr[i] = temp[i];
//     }

// }

// efficient approach using hoares/lomuto partition Ø(n)
 void separateElements(vector<int> &arr){
     int  i = -1, j = arr.size();
     while (1)
     {
         do{i++;}while(arr[i]<0);
         do{j--;}while(arr[j]>=0);
         if (i>=j)
         {
             return;
         }
         swap(arr[i], arr[j]);

    }

}

// sort an array of 0s , 1s and 2s || three way partitioning || partition around a range Ø(n)

// void segregateElements(vector<int> &arr)
// {
//     vector<int> temp(arr.size());
//     uint_fast16_t j = 0;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i] == 0)
//         {
//             temp[j++] = arr[i];
//         }
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i] == 1)
//         {
//             temp[j++] = arr[i];
//         }
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i] == 2)
//         {
//             temp[j++] = arr[i];
//         }
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         arr[i] = temp[i];
//     }
// }

// dutch national flag algo efficient solution
 void segregateElements_v2(vector<int> &arr){
     uint_fast16_t low = 0 , mid = 0 , high = arr.size() - 1;
     while (mid<=high)
     {
         if (arr[mid] == 0)
         {
             swap(arr[low],arr[mid]); /* 0s must come between index = 0  and index = low*/
             low++; mid++;
         }
         else if (arr[mid] == 1) /* 1s must come b/w low and mid*/
         {
             mid++;
         }
         else
         {
             swap(arr[mid],arr[high]); /*2s must come b/w high and last index of the array*/
             high--;
         }

    }

    return;
}

// minimum difference in an array O(nlogn)
// int minDifferenceInArray(vector<int> &arr)
// {
//     int minimumDifference = INT16_MAX;
//     sort(arr.begin(), arr.end());
//     for (int i = 1; i < arr.size(); i++)
//     {
//         int currentDifference = arr[i] - arr[i - 1];
//         minimumDifference = min(minimumDifference, abs(currentDifference));
//     }
//     return minimumDifference;
// }

// merge overlapping intervals
//  void mergeOverlapping(vector<pair<int,int>> &arr){
//      sort(arr.begin(),arr.end());
//      vector<pair<int,int>> temp;
//      int curr = 0;
//      temp.push_back({0,0});
//      for (int i = 1; i < arr.size(); i++)
//      {
//          if (arr[i].first <= arr[i-1].second)
//          {
//              if (arr[i].first <= temp[curr].second && curr>=1)
//              {
//                 temp[curr].second = max(arr[i].second,arr[i-1].second);
//              }
//              else{
//                  temp.push_back(make_pair(arr[i-1].first,max(arr[i].second,arr[i-1].second)));
//                  ++curr;
//              }
//          }

//     }
//     for (auto &i : temp)
//     {
//         cout<<i.first<<" -> "<<i.second<<endl;
//     }
// }

// meeting the maximum guests O(nlogn)
// int maxGuest(vector<int> &arr,vector<int> &dept){
//     sort(arr.begin(),arr.end());
//     sort(dept.begin(),dept.end());
//     uint_fast16_t  i = 0 , j = 0 , res = 1 , curr = 1;
//     while (i < arr.size() && j < dept.size())
//     {
//         if (arr[i] <= dept[j]) // considering 1 arrival
//         {
//             curr++;
//             i++;
//         }
//         else{
//             j++;
//             curr--;
//         }
//         res = max(res,curr);

//     }
//     return res;

// }

/* cycle sort
    worst case : O(n^2)
    does minimum writes
    not stable
*/
// cycle sort for distinct elements
// void cycleSortForDistinct(vector<int> &arr)
// {
//     for (int i = 0; i < arr.size(); i++) // i is cycle start
//     {
//         int item = arr[i];
//         int pos = i;
//         for (int j = i + 1; j < arr.size()-1; j++)
//         {
//             if (arr[j] < item)
//                 pos++;
//         }
//         swap(item, arr[pos]);
//         while (pos != i)
//         {
//             pos = i;
//             for (int j = i + 1; j < arr.size(); j++)
//             {
//                 if (arr[j] < item)
//                 {
//                     pos++;
//                 }
//             }
//             swap(item, arr[pos]);
//         }
//     }
// }

// /* Heap sort O(nlogn)*/
// void maxHeapify(vector<int> &arr ,int n, int i){
//     int largest = i , left = 2*i + 1 , right = 2*i + 2;
//     if (left<n && arr[left]>arr[largest]){largest = left;}
//     if(right<n && arr[right]>arr[largest]){largest = right;}
//     if (largest != i)
//     {
//         swap(arr[largest],arr[i]);
//         maxHeapify(arr,n,largest);
//     }
// }

// void buildHeap(vector<int> &arr,int n){
//     for (int i = (n-2)/2; i >= 0 ; i--)
//     {
//         maxHeapify(arr,n,i);
//     }

// }
// void heapSort(vector<int> &arr,int n){
//     buildHeap(arr,n);
//     for (int i = n - 1; i >= 0; i--)
//     {
//         swap(arr[0],arr[i]);
//         maxHeapify(arr,i,0);
//     }

// }

// counting sort for range[0,k-1] (small ranges) Ø(n+k)
// void countSort(vector<int> &arr, int k)
// {
//     vector<int> Count(k); // creates an array with element's frequency in range 0 to k-1 and shows how many elements <= current element (i)
//     for (int i = 0; i < arr.size(); i++)
//     {
//         Count[arr[i]]++;
//     }
//     for (int i = 1; i < k; i++)
//     {
//         Count[i] = Count[i - 1] + Count[i];
//     }
//     vector<int> temp(arr.size());
//     for (int i = arr.size() - 1; i >= 0; i--) // reverse traversing == stable sort
//     {
//         temp[Count[arr[i]] - 1] = arr[i];
//         Count[arr[i]]--;
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         arr[i] = temp[i];
//     }
// }

// radix sort trade b/w space and time

// void countingSort(vector<int> &arr, int exp)
// {
//     // consider k == exp
//     vector<int> Count(10); // creates an array with element's frequency in range 0 to k-1 and shows how many elements <= current element (i)
//     for (int i = 0; i < arr.size(); i++)
//     {
//         Count[(arr[i] / exp) % 100]++; // gives last digit when k = 1 , gives 2nd last digit when k = 2
//     }
//     for (int i = 0; i < 10; i++)
//     {
//         Count[i] = Count[i - 1] + Count[i];
//     }
//     vector<int> temp(arr.size());
//     for (int i = arr.size() - 1; i >= 0; i--) // reverse traversing == stable sort
//     {
//         temp[Count[(arr[i] / exp) % 10] - 1] = arr[i];
//         Count[(arr[i] / exp) % 10]--;
//     }
//     for (int i = 0; i < arr.size(); i++)
//     {
//         arr[i] = temp[i];
//     }
// }
// void radixSort(vector<int> &arr)
// {
//     int maxElement = arr[0];
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i] > maxElement)
//             maxElement = arr[i];
//     }                                                 // get maximum element
//     for (int exp = 1; maxElement / exp > 0; exp * 10) // power of 10 (10^0,10^1 ...)
//     {
//         countingSort(arr, exp);
//     }
// }

// Bucket sort (uniformly distributed in range from 1 to 10^8 || 0.0 to 0.1) O(n)
void bucketSort(vector<int> &arr, int buckets)
{
    // can get range by doing MAX_ELEMENT - MIN_ELEMENT
    int max_val = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        max_val = max(max_val, arr[i]);
    }
    max_val++;
    vector<int> bkt[buckets];
    for (int i = 0; i < arr.size(); i++)
    {
        int bi = (buckets * (arr[i])) / max_val;
        bkt[bi].push_back(arr[i]);
    }
    for (int i = 0; i < buckets; i++)
    {
        sort(bkt[i].begin(), bkt[i].end());
    }
    int index = 0;
    for (int i = 0; i < buckets; i++)
    {
        for (int j = 0; j < bkt[i].size(); j++)
        {
            arr[index++] = bkt[i][j];
        }
    }
}
int main(int argc, char const *argv[])
{
    vector<int> vec = {0, 0, 1, 1, 2, 2, 1, 0, 1};
    vector<int> temp = {8, 1, 5, 5, 2, 0, 3, 2, 10, 8};
    // vector<pair<int,int>> MOI = {{1,3},{2,4},{5,7},{6,8}};
    // insertionSort(arr);
    // unionOf(temp, vec);
    // Merge(vec,0,2,4);
    // mergeSort(vec, 0, 4);
    // intersection(vec, temp);
    // lomutoPartition(vec, 0, 4);
    // quickSort_v3(temp,0,6);
    // cout<<KthSMALLESTelement(temp,3);
    // cout<<minDIFF(temp,5);
    // separateElements(temp);
    // segregateElements_v2(vec);
    // cout << minDifferenceInArray(temp);
    // mergeOverlapping(MOI);
    // cycleSortForDistinct(temp);
    // heapSort(temp,temp.size());
    // countSort(temp,11);
    // radixSort(temp);
    // for (auto &i : temp)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    return 0;
}
