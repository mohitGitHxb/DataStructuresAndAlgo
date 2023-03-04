#include <bits/stdc++.h>
using namespace std;

/* Utility function to print an array */
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";

    cout << endl;
}


void printMatrix(vector<vector<int>> &mat){
    for (int i = 0; i < mat.size(); i++){
            for (auto &&j : mat[i])
            {
                cout << j << " "; 
            }
            cout << ",";
    }
    cout << "\n";
        
            
}

void printArray(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";

    cout << endl;
}

//^ 1) Reverse an array of integers

//~ O(N) time and O(1) space
void reverseArray(vector<int> &arr)
{
    for (int i = 0; i < arr.size() / 2; i++)
    {
        swap(arr[i], arr[arr.size() - i - 1]);
    }
}

//! Recursive function
//~ O(N) time and O(N) recursion stack space
void reverseArrayRecursive(vector<int> &arr, int start, int end)
{
    if (start < end && start >= 0 && end < arr.size())
    {
        swap(arr[start], arr[end]);
        reverseArrayRecursive(arr, start + 1, end - 1);
    }
}

//^ 2) Maximum and minimum of an Array

//~ O(N) time and O(1) space total number of comparisons is 1 + 2(n-2) in the worst case
pair<int, int> getMinMax(vector<int> &arr)
{
    int referenceMin = INT_MAX;
    int referenceMax = INT_MIN;
    for (auto &x : arr)
    {
        referenceMin = min(referenceMin, x);
        referenceMax = max(referenceMax, x);
    }
    return {referenceMin, referenceMax};
}

/*
&  Maximum and minimum of an array using the tournament method:

&  Divide the array into two parts and compare the maximums and minimums of the two &  parts to get the maximum and the minimum of the whole array.

~ O(N) time and O(logN) space total comparisons are 3N/2 - 2;

* Pair MaxMin(array, array_size)
*    if array_size = 1
*        return element as both max and min
*    else if arry_size = 2
*        one comparison to determine max and min
*         return that pair
*    else    /* array_size  > 2
?        recur for max and min of left half
?        recur for max and min of right half
?        one comparison determines true max of the two candidates
?        one comparison determines true min of the two candidates
?        return the pair of max and min
*/

/* pair<int,int> getMinMax2(vector<int> &arr,int low,int high) {
    pair<int,int> minmax={-1000000,1000000};
    if(arr.size() == 1) return {arr[0],arr[0]};
    if(arr.size() == 2) return {min(arr[0],arr[1]),max(arr[1],arr[0])};
    else if(low <= high)
    {
        if (low == high) return {arr[low],arr[low]};
        if (high+1 == low) return {min(arr[low],arr[high]),max(arr[high],arr[low])};

        int mid = (low + high)/2;
        pair<int,int> leftArray = getMinMax2(arr,low,mid);
        pair<int,int> rightArray = getMinMax2(arr,mid+1,high);

        minmax.first = min(leftArray.first,rightArray.first);
        minmax.second = max(leftArray.second,rightArray.second);
        return minmax;
    }
    return minmax;
} */

/*
& If n is odd then initialize min and max as the first element. 
& If n is even then initialize min and max as minimum and maximum of the first two & elements respectively. 
& For the rest of the elements, pick them in pairs and compare their 
& maximum and minimum with max and min respectively. 
~ O(N) time and O(1) space total comparisons 3N/2 - 2
 */
pair<int, int> getMinMax3(vector<int> &arr)
{
    pair<int, int> minmax;
    if (arr.size() == 1)
    {
        return {arr[0], arr[0]};
    }

    //? If there are more than one elements,
    //? then initialize min and max
    minmax.first = min(arr[0], arr[1]);
    minmax.second = max(arr[0], arr[1]);
    for (int i = 2; i < arr.size(); i++)
    {
        if (arr[i] < minmax.second)
        {
            minmax.second = arr[i];
        }
        else if (arr[i] > minmax.first)
        {
            minmax.first = arr[i];
        }
    }
    return minmax;

    // one liner ??
    //    return minmax_element(arr.begin(), arr.end());
}

//^ 3 Kth maximum and minimum
//~ O(NlogN) time and O(1) space
pair<int, int> kthMaxMin(vector<int> &arr, int k)
{
    if (k < 1)
        return {-1, -1};
    sort(arr.begin(), arr.end());
    return {arr[k - 1], arr[arr.size() - k]};
}

/*
& The idea is to randomly pick a pivot element. To implement randomized partition, we use a random function, rand() to generate index between l and r, swap the element at randomly generated index with the last element, and finally call the standard partition process which uses last element as pivot.

~ O(N^2) worst case T.C | O(N) average case T.C | O(1) space
 */
//? Standard partition process of QuickSort(). It considers the last 
//? element as pivot and moves all smaller element to left of it and 
//? greater elements to right. This function is used by randomPart
int parition(vector<int> &arr, int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] < x)
        {
            swap(arr[j], arr[i]);
            ++i;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

//?  Picks a random pivot element between l and r and partitions 
//?  arr[l..r] around the randomly picked element using partition()
int randomPartition(vector<int> &arr, int l, int r)
{
    int n = r - l + 1;
    int pivot = rand() % n;
    swap(arr[l + pivot], arr[r]);
    return parition(arr, l, r);
}

int kthSmallest(vector<int> &arr, int l, int r, int k)
{
    //? if k is smaller than no. of elements in an array..
    if (k > 0 && k <= r - l + 1)
    {

        //* parition the array around a random element and get position of the pivot element in sorted array
        int pos = randomPartition(arr, l, r);

        if (pos - l == k - 1)
            return arr[pos];
        if (pos - l > k - 1) //% if pos is more recur for left half
            return kthSmallest(arr, l, pos - 1, k);
        else
            return kthSmallest(arr, pos + 1, r, k - pos + l - 1); //% recur for right half
    }

    return INT16_MIN;
}

//^ 4 Sort an array of 0,1,2s

/*
&    Keep three indices low = 1, mid = 1, and high = N and there are four ranges, 1 to low (the range containing 0), low to mid (the range containing 1), mid to high (the range containing unknown elements) and high to N (the range containing 2).
&    Traverse the array from start to end and mid is less than high. (Loop counter is i)
&    If the element is 0 then swap the element with the element at index low and update low = low + 1 and mid = mid + 1
&    If the element is 1 then update mid = mid + 1
&    If the element is 2 then swap the element with the element at index high and update high = high – 1 and update i = i – 1. As the swapped element is not processed
&   Print the array.

 */
void sort012(vector<int> &arr)
{
    // code here
    int n = arr.size();
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high)
    {
        switch (arr[mid])
        {
        case 0:
            swap(arr[low], arr[mid]);
            low++;
            mid++;
            break;
        case 1:
            mid++;
            break;
        case 2:
            swap(arr[mid], arr[high]);
            high--;
            break;
        }
    }
}

//^ 5 Move all negative elements to end
//~ O(N) time and space (if order doesn't matter it can be solved in O(1) space by using the quicksort parition considering the pivot = 0)

void segregateElements(vector<int> &arr)
{
    vector<int> temp;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > 0)
        {
            temp.push_back(arr[i]);
        }
    }
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < 0)
        {
            temp.push_back(arr[i]);
        }
        arr[i] = temp.at(i);
    }
}

//^ 6 Union and intersection of two sorted arrays...
//% Assuming all elements in arrays are distinct

vector<int> unionOfArrays(vector<int> &A, vector<int> &B)
{
    //! O((N+M)log(N+M)) time and O(N+M) space <-->  doesn't use the fact that array is sorted

    // set<int> s(A.begin(), A.end());
    // vector<int> u;
    // for (int i = 0; i < B.size(); i++)
    // {
    //     s.insert(B[i]);
    // }
    // for (auto &&i : s)
    // {
    //     u.push_back(i);
    // }
    // return u;

    //* Efficient approach O(N+M) time and O(1) space for sorted and distinct array
    vector<int> res;
    int i = 0, j = 0;
    while (i < A.size() && j < B.size())
    {
        if (A[i] < B[j])
        {

            res.push_back(A[i]);
            ++i;
        }
        else if (B[j] < A[i])
        {

            res.push_back(B[j]);
            j++;
        }
        else
        {

            res.push_back(B[j]);
            j++;
            i++;
        }
    }

    //> Print remaining elements of the larger array */
    while (i < A.size())
    {
        res.push_back(A[i++]);
    }

    while (j < B.size())
            res.push_back(B[j++]);
}

vector<int> intersectionOfArrays(vector<int> A, vector<int> B)
{
    //~ O(N+M) time and O(N) space <--> doesn't use the fact that array is sorted
    unordered_set<int> mp;
    vector<int> res;
    for (int i = 0; i < A.size(); i++)
    {
        mp.insert(A[i]);
    }
    for (int i = 0; i < B.size(); i++)
    {
        if (mp.find(A[i]) != mp.end())
        {
            res.push_back(B[i]);
        }
    }
    return res;
}



//^ 7 Cyclically rotate array 'D' places

/* 
~    Reverse the first ‘d’ elements
~    Reverse last (N-d) elements
~    Reverse the whole array.
~      O(N) time and O(1) space
 */
void rotateArrayByD(vector<int> &arr,int d){
    int k = d % arr.size();
    reverse(arr.begin(),arr.begin()+k);
    reverse(arr.begin()+k,arr.end());
    reverse(arr.begin(),arr.end());
}


//^ 8 largest sum contiguous array (Kadane's algorithm)
int largestSumContiguousArray(vector<int> &arr){
    int res = arr[0], maxEnding = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        maxEnding = max(maxEnding+arr[i],arr[i]);
        res = max(maxEnding,res);
    }
    return res;

    /*

&    To print the subarray with the maximum sum the idea is to maintain start index & of maximum_sum_ending_here at current index so that whenever maximum_sum_so_far is & updated with maximum_sum_ending_here then start index and end index of subarray can be updated with start and current index
    
     */
/*     int max_so_far = 0,maxEnding=0;
    int start_index = 0 ,end_index = 0, s = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        maxEnding += arr[i];
        if (max_so_far < maxEnding)
        {
            max_so_far = maxEnding;
            start_index = s;
            end_index = i;
        }
        if(maxEnding < 0)
        {
            maxEnding = 0;
            s = i+1;
        }
        
    }
    cout << "Maximum contiguous sum is " << max_so_far
    << endl;
        cout << "Starting index " << start_index << endl
    << "Ending index " << end_index << endl; */
    
    
}


// ^ 8 Minimize the maximum difference in an array

/* 
& Sort the array 
& Try to make each height of the tower maximum by decreasing the height of all the  towers to the right by k and increasing all the height of the towers to the left by & k. Check whether the current index tower has the maximum height or not by comparing it with a[n]-k. If the tower’s height is greater than the a[n]-k then it’s the tallest tower available.
&     Similarly, find the shortest tower and minimize the difference between these two towers.  
 */

//~ O(NlogN) T.C | O(1) space
int getMinDiff(vector<int> &arr,int k){
    sort(arr.begin(),arr.end());
    int minDiff = arr.back() - arr.front();
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] - k >= 0)
        {
        int tempMax,tempMin;
        tempMax = max(arr[i-1]+k,arr.back()-k); //? Max element when we subtract k to whole array
        tempMin = min(arr.front()+k,arr[i]-k); //? Minimum element when we add k to whole array
        minDiff = min(tempMax-tempMin,minDiff);
        }
        
    }
        return minDiff;
}

//^ 9 Minimum number of jumps to reach the end of the array
//~ O(N) T.C | O(1) space
bool canReachEndOfArray(vector<int> &arr){
    if(arr.size() == 1) return true;
    if(arr.size() == 0 || arr.front() == 0) return false;
    int maximumReach = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if(maximumReach >= arr.size()) //? reached the end...
            return true;
        if (maximumReach < i) //? further steps are impossible now...
        {
            return false;
        }

        maximumReach = max(maximumReach, arr[i] + i);
        
    }
}
int minJumps(vector<int> &arr, int n){
        
        if(arr[0] == 0 && n>1)return -1;
        if(n < 2)return 0; 
        int jumps=1;
        int steps=arr[0];
        int maxRange=arr[0];
        for(int i = 1; i<n; i++){
           if( i == n-1){
               return jumps;
           }
           maxRange = max(maxRange,arr[i]+i);
           steps--;
           if(steps == 0){
              jumps++;
              if(maxRange <= i)return -1;
              steps = maxRange - i;
           }
        }
        return -1;
    }

// ^ 10 Find duplicate in an array of N+1 integers

int getDuplicate(vector<int> &arr){
    /*

&    Sort the input array (arr).
&    Iterate through the array, comparing the current number to the previous number (i.e. compare arr[i]to arr[i−1] where i>0).
&    Return the first number that is equal to its predecessor.

!  O(NlogN) T.C | O(1) S.C
      */
  /*    sort(arr.begin(), arr.end());
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] == arr[i - 1])
                return arr[i];
        }
        return -1; */
/* 

&    In order to achieve linear time complexity, we need to be able to insert elements into a data structure and look them up in constant time. A HashSet/unordered_set is well suited for this purpose. Initialize an empty hashset, seen.

&    Iterate over the array and first check if the current element exists in the hashset (seen).
&        If it does exist in the hashset, that number is the duplicate and can be returned right away.

&    Otherwise, insert the current element into seen, move to the next element in the array and repeat step 2.

! O(N) T.C | O(N) S.C
 */
/* unordered_set<int> seen;
        for (auto &num : arr) {
            if (seen.count(num))
                return num;
            seen.insert(num);
        }
        return -1;
 */
   /*  
   
&   Iterate over the array, evaluating each element (let's call the current element cur).

&    Since we use negative marking, we must ensure that the current element (cur) is positive (i.e. if cur is negative, then use its absolute value).

&    Check if nums[cur] is negative.

&        If it is, then we have already performed this operation for the same number, and hence cur is the duplicate number. Store cur as the duplicate and exit the loop.

&        Otherwise, flip the sign of nums[cur](i.e. make it negative). Move to the next element and repeat step 3.

&    Once we've identified the duplicate, we could just return the duplicate number. However, even though we were not able to meet the problem constraints, we can show that we are mindful of the constraints by restoring the array. This is done by changing all negative numbers to positive. 

* O(N) T.C | O(1) S.C 

*/

        int duplicate = -1;
        for (int i = 0; i < arr.size(); i++) {
            int cur = abs(arr[i]);
            if (arr[cur] < 0) {
                duplicate = cur;
                break;
            }
            arr[cur] *= -1;
        }
        for (auto &&i : arr) 
        {
            i = abs(i);
        }
        
/* 
    & using Fast and Slow pointers (Linked list) method
*   O(N) T.C | O(1) space   
 */

    int slow = arr[0];
    int fast = arr[0];
    do
    {
        slow = arr[slow]; 
        fast = arr[arr[fast]];
    } while (slow != fast); //? moving the slow ptr by 1 and fast by 2
    fast = arr[0];
    while (slow != fast) //? moving both slow and fast by 1
    {
        slow = arr[slow];
        fast = arr[fast];
    }
    return slow;       

}

//^ 9 Merge two sorted arrays
void mergeArray(vector<int> &A, vector<int> &B){
    /* 
&    Create an array arr3[] of size n1 + n2.
&    Simultaneously traverse A[] and B[]. 
&    Pick smaller of current elements in A[] and B[], copy this smaller element to next position in arr3[] and move ahead in arr3[] and the array whose element is picked.
&    If there are remaining elements in A[] or B[], copy them also in arr3[].
     */
/* 
    vector<int> C(A.size()+B.size());
    int i=0,j=0;
    int k=0;
    while (i<A.size() && j<B.size()) 
    {
        if(A[i] > B[i]){
            C[k++] = B[j++];
        }
        else if(A[i] <= B[i])
        {
            C[k++] = A[i++];
        }
        
    }
    while (i < A.size())
    {
        C[k++] = A[i++];
    }
    while (j < B.size())
    {
        C[k++] = B[j++];
    }
    @ 'C' is the resultant merged Array..
     */

    /* 

    % Insertion Sort Method
&    Sort list 1 by always comparing with the head/first of list 2 and swap if required
&    After each head/first swap, perform insertion of the swapped element into the correct position in list 2 which will eventually sort list 2 at the end
&    For every swapped item from list 1, perform insertion sort in list 2 to find its correct position so that when list 1 is sorted, list 2 is also sorted
    ~ O(MN) T.C and O(1) space
     */
    int n=A.size();
    int m=B.size();
/*    int i = 0;
	int j = 0;
	while (i < n && j < m) {
		//? if A[i] <= B[j] then both array is already
		//? sorted
		if (A[i] <= B[j]) {
			i++;
		}
		else if (A[i] > B[j]) {
			//? if A[i]>B[j] then first we swap both
			//? element so that A[i] become smaller means
			//? A[] become sorted then we check that
			//? B[j] is smaller than all other element in
			//? right side of B[j] if B[] is not sorted
			//? then we linearly do sorting
			//? means while adjacent element are less than
			//? new B[j] we do sorting like by changing
			//? position of element by shifting one position
			//? toward left
			swap(A[i], B[j]);
			i++;
			if (j < m - 1 && B[j + 1] < B[j]) {
				int temp = B[j];
				int tempj = j + 1;
				while (B[tempj] < temp && tempj < m) {
					B[tempj - 1] = B[tempj];
					tempj++;
				}
				B[tempj - 1] = temp;
			}
		}
	} */

    
    /* 
&    The idea: We start comparing elements that are far from each other rather than adjacent. 
&For every pass, we calculate the gap and compare the elements towards the right of the gap. Every pass, the gap reduces to the ceiling value of dividing by 2.

    *O((M+N)log(M+N)) T.C | O(1) space

     */

    int gap = ((n+m)%2==0) ? (n+m)/2 : (n+m)/2 + 1;
    int i=0,j=0;
    while (gap != 0)
    {
        for(i = 0; i + gap < n; i++){
            if(A[i] > A[i+gap]){
                swap(A[i],A[i+gap]);
            }
        }

        for (j = (gap > n)? gap-n:0; j < m && i < n; j++,i++)
        {
            if (A[i] > B[j])
            {
                swap(A[i],B[j]);
            }
        }

        if (j<m)
        {
            for (j = 0; j + gap < m ; j++)
            {
                if (B[j] > B[j+gap])
                {
                    swap(B[j],B[j+gap]);
                }
            }
        }
        
        gap =(gap>1) ? (gap/2) + gap%2:0;        
    }



    /* 
    @ Euclidean Division Lemma Method

&    Suppose we have a number A and we want to 
&    convert it to a number B and there is also a 
&    constraint that we can recover number A any 
&    time without using other variable.To achieve 
&    this we chose a number N which is greater 
&    than both numbers and add B*N in A.
&    so A --> A+B*N

&    To get number B out of (A+B*N) 
&    we divide (A+B*N) by N.
&    so (A+B*N)/N = B.

&    To get number A out of (A+B*N) 
&    we take modulo with N.
&    so (A+B*N)%N = A.

&    -> In short by taking modulo 
&    we get old number back and taking divide 
&    we new number.


&   We first find the maximum element of both arrays and increment it by one to avoid collision of 0 and maximum element during modulo operation. The idea is to traverse both arrays from starting simultaneously. Let’s say an element in a is a[i] and in b is b[j] and k is the position at where the next minimum number will come. Now update value a[k] if k<n else b[k-n] by adding min(a[i],b[j])*maximum_element. After updating all the elements divide all the elements by maximum_element so we get the updated array back. 
    
     */

  /*   int mx = 0;
	
	//? Find maximum element of both array
	for (int i = 0; i < n; i++) {
		mx = max(mx, A[i]);
	}
	for (int i = 0; i < m; i++) {
		mx = max(mx, B[i]);
	}
	
	//? increment by one to avoid collision of 0 and maximum
	//? element of array in modulo operation
	mx++;
	int i = 0, j = 0, k = 0;
	while (i < n && j < m && k < (n + m)) {
		
		// recover back original element to compare
		int e1 = A[i] % mx;
		int e2 = B[j] % mx;
		if (e1 <= e2) {
			
			// update element by adding multiplication
			// with new number
			if (k < n)
				A[k] += (e1 * mx);
			else
				B[k - n] += (e1 * mx);
			i++;
			k++;
		}
		else {
			
			// update element by adding multiplication
			// with new number
			if (k < n)
				A[k] += (e2 * mx);
			else
				B[k - n] += (e2 * mx);
			j++;
			k++;
		}
	}
	
	// process those elements which are left in array a
	while (i < n) {
		int el = A[i] % mx;
		if (k < n)
			A[k] += (el * mx);
		else
			B[k - n] += (el * mx);
		i++;
		k++;
	}
	
	// process those elements which are left in array b
	while (j < m) {
		int el = B[j] % mx;
		if (k < n)
			A[k] += (el * mx);
		else
			B[k - n] += (el * mx);
		j++;
		k++;
	}
	
	// finally update elements by dividing
	// with maximum element
	for (int i = 0; i < n; i++)
		A[i] = A[i] / mx;

	// finally update elements by dividing
	// with maximum element
	for (int i = 0; i < m; i++)
		B[i] = B[i] / mx;
     */
}
//^ 10 Merge Intervals
//* O(NlogN) T.C | O(N) space
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {

        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        for (auto interval : intervals) {
            //? if the list of merged intervals is empty or if the current
            //? interval does not overlap with the previous, simply append it.
            if (merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }
            //? otherwise, there is overlap, so we merge the current and previous
            //? intervals.
            else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }
        return merged;
    }

//^ 11 Next Permutations
/* 
&    Iterate over the given array from end and find the first index (pivot) which doesn’t follow property of non-increasing suffix, (i.e,  arr[i] < arr[i + 1]).
&    Check if pivot index does not exist 
&        This means that the given sequence in the array is the largest as possible. So, swap the complete array.
&    Otherwise, Iterate the array from the end and find for the successor of pivot in suffix.
&    Swap the pivot and successor
&    Minimize the suffix part by reversing the array from pivot + 1 till N.

*   O(N) T.C | O(1) space
 */
 void nextPermutation(vector<int>& nums) {
        if(nums.size() == 0 || nums.size() == 1){
            return;
        }
        int pivot = INT_MIN;
        for(int i = nums.size()-2; i >= 0; i--){
            if(nums[i] < nums[i + 1]){
                pivot = i;
                break;
            }
        }

        if( pivot < 0){
            reverse(nums.begin(),nums.end());
            return;
        }
        for(int i = nums.size() - 1; i >= pivot ; i--){
            if(nums[i] > nums[pivot]){
                swap(nums[i],nums[pivot]);
                break;
            }
        }
        reverse(nums.begin() + pivot + 1 , nums.end());
}



//^ 12 Count Inversions
int countInversions(vector<int> &arr){
    /* 
    & Traverse through the array, and for every index, find the number of smaller elements on its right side of the array. This can be done using a nested loop. Sum up the counts for all indices in the array and print the sum.

    ! O(N^2) T.C || O(1) S.C
     */
        int c = 0;
        int N = arr.size();
        for(long i = 0; i<N; i++){
            long curr = arr[i];
            for(long j = i + 1; j < N; j++){
                if(arr[j] < curr){
                    c++;
                }
            }
        }
        return c;

        //! O(N^2) worst case T.C but performs better on average 
  /*       if(N == 0)return 0;
        multiset<long long> s;
        s.insert(arr[0]);
        long long inversions = 0;
        for(long i = 1 ; i < N; i++){
            s.insert(arr[i]);
            auto it = s.upper_bound(arr[i]);
            inversions += distance(it,s.end());
        }
        return inversions; */
}

/* 
&    The idea is similar to merge sort, divide the array into two equal or almost equal halves in each step until the base case is reached.
& Create a function merge that counts the number of inversions when two halves of the array are merged, 

&    Create two indices i and j, i is the index for the first half, and j is an index of the second half. 
&    If a[i] is greater than a[j], then there are (mid – i) inversions because left and right subarrays are sorted, so all the remaining elements in left-subarray (a[i+1], a[i+2] … a[mid]) will be greater than a[j].

& Create a recursive function to divide the array into halves and find the answer by summing the number of inversions in the first half, the number of inversions in the second half and the number of inversions by merging the two.

&    The base case of recursion is when there is only one element in the given half.

* O(NlogN) T.C | O(N) S.C
 */

class countInversions{
    private:
    long long ans=0;
    public:
     void mergeSort(long long arr[], long long lo, long long hi) {
        if(lo<hi) {
            long long mid = lo + (hi-lo)/2;
            mergeSort(arr, lo, mid);
            mergeSort(arr, mid+1, hi);
            merge(arr, lo, mid, hi);
        }
    }
    
    void merge(long long arr[], long long lo, long long mid, long long hi) {
        long long  n1 = mid-lo+1, n2 = hi-mid;
        long long arr1[n1], arr2[n2];
        for(long i=0; i<n1; i++) arr1[i] = arr[lo+i];
        for(long i=0; i<n2; i++) arr2[i] = arr[mid+i+1];
        long long i=0, j=0, k=lo;
        while(i<n1 && j<n2) {
            if(arr1[i]<=arr2[j]) arr[k++] = arr1[i++];
            else {
                ans += n1 - i;  //% single additional line... 
                arr[k++] = arr2[j++];
            }
        }
        while(i<n1) arr[k++] = arr1[i++];
        while(j<n2) arr[k++] = arr2[j++];
    }
    long long int inversionCount(long long arr[], long long N)
    {
        // Your Code Here
        if(N == 0)return 0;
        mergeSort(arr,0,N-1);
        return ans;
}


};


   

//^ 13 Best time to sell stock
int maxProfit(vector<int>& prices) {
        //* O(N) T.C | O(1) space (one transaction allowed)
/*         int profit = 0;
        int minimumPrice = prices[0];
        for(int i = 1; i < prices.size(); i++){
            minimumPrice = min(minimumPrice,prices[i]);
            profit = max(profit,prices[i] - minimumPrice);
        }
        return profit; */


        //* O(N) T.C | O(1) space (infinite transaction allowed)
         int profit = 0,curr=0;
        for(int i = 1; i < prices.size(); i++){
            if(prices[i-1] < prices[i]){
                curr += prices[i] - prices[i-1];
            }
                profit = max(profit,curr);
        }
        return profit;
}


//^ 14 Count pairs with given sum
    int getPairsCount(vector<int> &arr ,  int k) {
        // code here
        int n = arr.size();
        int count  = 0;
        unordered_map<int,int> s;
        for(int i=0;i<n;i++){
            
            if(s.find(k - arr[i]) != s.end()){
                count += s[k - arr[i]];
            }
            s[arr[i]]++;
        }
        return count;
    }


//^ 15 Common elements in 3 sorted arrays
/* 
~ Three pointer technique
* O(n1+n2+n3) T.C | O(1) S.C (not taking into account the space required for ans)
 */
 vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3)
        {
            //code here.
            int A1 = 0;
            int B1 = 0;
            int C1 = 0;
            vector<int> ans;
            int prev = -10000; //? to take care of the duplicates
            while(A1 < n1 && B1 < n2 && C1 < n3){
                if(A[A1] == B[B1] && B[B1] == C[C1]){
                    if(prev != -10000 && prev == C[C1]){
                    A1++;
                    B1++;
                    C1++;
                    continue;   
                    }
                    prev = C[C1];
                    ans.push_back(C[C1]);
                    A1++;
                    B1++;
                    C1++;
                }
                else if(A[A1] < B[B1]){ //? A[A1] is smallest among three elements
                    A1++;
                }
                else if(B[B1] < C[C1]){ //? B[B1] is smallest among three elements
                    B1++;
                }
                else{ //? C[C1] is smallest among three elements
                    C1++;
                }
            }
            return ans;
}


//^ 16 Rearrange array in alternating positive & negative items

void rearrangeArray(vector<int> &arr){
/* 
&    We can store the positive values and negative values in two separate data structures.
&    We will start filling the original array with alternating negative and positive values in the same order 
&    in which it appears in the original array.

* O(N) T.C | O(N) space (Order is preserved) 
 */
/* 
    vector<int> negative_values;
    vector<int> positive_values;
    for (auto &&i : arr)
    {
        if (i >= 0)
        {
            positive_values.push_back(i);
        }
        else{
            negative_values.push_back(i);
        }
    }
    int i=0,j = 0,k=0;
    bool flag=false;
    for (i = 0; i < arr.size() && j < positive_values.size() && k < negative_values.size(); i++)
    {
        if(flag){
            arr[i] = positive_values[j++];
            flag = !flag;
        }
        else{
            arr[i] = negative_values[k++];
            flag = !flag;
        }
    }
    if(flag){
        while (j < positive_values.size()) 
        {
            arr[i++] = positive_values[j++];
        }
    }
    else
    {
        while (k < negative_values.size())
        {
         
        arr[i++] = negative_values[k++];
        }
        
    }
     */

    //~ if order is not maintained it can be solved using O(1) space..
    int n = arr.size();
    int i = 0,j=n-1;
    //? shifting all negative values to the end
    while (i < j)
    {
        while(i <= n-1 && arr[i] > 0)
            i++;
        while (j >= 0 && arr[j] < 0)
            j--;
        if(i < j){
            swap(arr[i], arr[j]);
        }
    }
    //? 'i' has index of leftmost negative element
    if( i==0 || i == n)return;
    //? start with first positive
    //? element at index 0
    //? Rearrange array in alternating
    //? positive & negative items

    int  k = 0;
    while (k < n && i < n) 
    {
        swap(arr[k] , arr[i++]);
        k+=2;
    }
}

//^ 17 Subarray with zero sum

bool SubWithZeroSum(vector<int> &arr){
            int prefixSum = 0;
        unordered_set<int> s;
        for(int i = 0; i < arr.size(); i++){
            prefixSum += arr[i];
            if(s.find(prefixSum) != s.end() || prefixSum == 0 || arr[i] == 0){
                return true;
            }
            s.insert(prefixSum);
        }
        return false;
}


//^ 18 Factorial of a large number
/* 

&    Create an array res[] of MAX size where MAX is a number of maximum digits in output. 
&    Initialize value stored in res[] as 1 and initialize res_size (size of ‘res[]’) as 1. 
&    Multiply x with res[] and update res[] and res_size to store the multiplication result for all the numbers from x = 2 to n.
&    To multiply a number x with the number stored in res[], one by one multiply x with every digit of res[].
&    To implement multiply function perform the following steps:
&        Initialize carry as 0. 
&        Do following for i = 0 to res_size – 1 
&           Find value of res[i] * x + carry. Let this value be prod. 
&            Update res[i] by storing the last digit of prod in it. 
&            Update carry by storing the remaining digits in carry. 
&        Put all digits of carry in res[] and increase res_size by the number of digits in carry.
 */

int multiply(int x, vector<int> &ans, int ans_size){
        int carry = 0;
        for(int i=0;i<ans_size;i++){
            int product = ans[i] * x + carry;
            ans[i] = product % 10;
            carry = product / 10;
        }
        
        while(carry != 0){
            ans[ans_size] = carry % 10;
            carry = carry / 10;
            ans_size++;
        }
        return ans_size;
    }
    vector<int> factorial(int N){
        vector<int> ans(3000);
        ans[0] = 1;
        int ans_size = 1;
        for(int x = 2; x <= N; x++){
            ans_size = multiply(x,ans,ans_size);
        }
        reverse(ans.begin() , ans.begin() + ans_size);
        vector<int> res(ans.begin() , ans.begin() + ans_size);
        return res;
    }


//^ 19 maximum product subarray 
long long maximumProductSubarray(vector<int> &arr){

    //! Brute force O(N^2) T.C | O(1) S.C
/*     int res = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        int curr = arr[i];
        if (curr == 0)
        {
            continue;
        }
        
        for (int j = i + 1; j < arr.size(); j++){
            if (arr[j] == 0)
            {
                break;
            }
            curr *= arr[j];
            res = max(res, curr);
        }
            res = max(res, curr);
    }
    return res; */

    //* O(N) T.C | O(1) space
    if(arr.empty()) return arr.size();
	    long long res = INT_MIN;
	    long long product = 1; 
	    for(int i = 0; i<arr.size(); i++){
	        product = product * arr[i];
	        res = max(res,product);
	        if(product == 0) //? handling cases where arr[i] becomes 0 as 0 times anything is 0 so to avoid product stuck at 0 we change product to 1 as 1 times the number is number itself...
	            product = 1;
	    }
	    product = 1;
        //? traversing from the other side also to counter cases when only first element is negative or maximum product subarray exists after some 0 entries...
	    for(int i = arr.size() -1;i>=0;i--){
	        
	        product = product * arr[i];
	        res = max(res,product);
	        if(product == 0)
	            product = 1;
	    }
	    
	    return res;

        /* 
        &    Here we use 3 variables called max_so_far, max_ending_here & min_ending_here
&    For every index, the maximum number ending at that index will be the maximum(arr[i], max_ending_here * arr[i], min_ending_here[i]*arr[i])
&    Similarly, the minimum number ending here will be the minimum of these 3
&    Thus we get the final value for the maximum product subarray
        
        * O(N) solution with single traversal
         */

        long long max_so_far = INT_MIN,max_ending=0,min_ending=0;
        for (long i = 0;i < arr.size();i++)
        {
            max_ending = (max_ending == 0)?i:max_ending*arr[i];
            min_ending = (min_ending == 0)?i:min_ending*arr[arr.size() - i - 1];
            max_so_far = max(max_so_far,max(min_ending,max_ending));
        }
        return max_so_far;
        
    
}

//^ 20 Longest consecutive subsequence
int longest_sequences(vector<int> &arr){
    int N = arr.size();

    /* 
& sort the array and initialize two variables maxLength and currLength which stores maxLength and length till current element of a consecutive subsequence respectively

& update maxLength when currLength is greater than maxLength 
& if arr[i] != arr[i-1] + 1 then currLength = 1 (starting of next subsequence) 

    ! O(NlogN) solution O(1) extra space ... (O(logN) space i.e sorting)
     */
 /*    sort(arr.begin(),arr.end());
      int maxLength = -100000,currLength=1;
      for(int i = 1; i < N; i++){
          if(arr[i] == arr[i - 1]){
              continue;
          }
          if(arr[i] == arr[i-1] + 1 ){
            currLength++;
            maxLength = max(maxLength,currLength);
          }
          else{
          currLength = 1;
              
          }
      }
      return maxLength; */


        /* 
        
&            Create an empty hash.
&    Insert all array elements to hash.
&    Do the following for every element arr[i]
&    Check if this element is the starting point of a subsequence. To check this, simply look for arr[i] – 1 in the hash, if not found, then this is the first element of a subsequence.
&    If this element is the first element, then count the number of elements in the consecutive starting with this element. Iterate from arr[i] + 1 till the last element that can be found.
&    If the count is more than the previous longest subsequence found, then update this.

    * O(N) T.C | O(N) S.C
         */

            unordered_set<int> s(arr.begin(),arr.begin()+N);
      int maxLength = 0;
      for(int i = 0; i < N; i++){
          if(s.find(arr[i]-1) == s.end()){
              int currLength = 1;
              while(s.find(arr[i] + currLength)!=s.end()){
                  currLength++;
              }
              
              maxLength = max(currLength,maxLength);
          }
      }
      return (maxLength==0)?1:maxLength;
} 

//^ 21 find all elements that appear more than N/K times 
//* O(N) T.C and S.C
int getOccurence(vector<int>& arr,int k){
    int n = arr.size();
      unordered_map<int,int> mp;
        for(int i=0;i<n;i++)
            mp[arr[i]]++;
        int count=0;
        for(auto &x : mp){
            count = (x.second > n/k)?count+1:count;
        }
        return count;
}

//^ 22 find a triplet whose sum is equal to X
bool find3sum(vector<int> &A,int X){
    int n = A.size();
    /* 
    & using set and applying similar logic of two sum
    ! O(n^2) T.C | O(N) space
     */
/*      unordered_set<int> s;
        sort(A.begin(),A.begin()+n);
        for(int i = 0; i < n; i++){
            int twoSum = X - A[i];
            for(int j = i + 1; j < n; j++){
                if(s.find(twoSum-A[j]) != s.end())return true;
                s.insert(A[j]);
            }
            s.clear();
        }
        return false; */

// * O(N^2) T.C | O(1) space
            int l, r;
    //? Sorting the elements.
    sort(A.begin(), A.end());

    //? Traversing the array elements.
    for (int i = 0; i < n-2; i++)
    {
        //? Taking two pointers. One at element after ith index and another
        //? at the last index.
        l = i + 1; 
        r = n-1; 
        while (l < r)
        {
            //? If sum of elements at indexes i, l and r is equal to required number, we return true.
            if( A[i] + A[l] + A[r] == X)
                return 1;
            //? Else if the sum is less than required number, it means we need
            //? to increase the sum so we increase the left pointer l.
            else if (A[i] + A[l] + A[r] < X)
                l++;
            //? Else the sum is more than required number and we need to
            //? decrease the sum so we decrease the right pointer r.
            else 
                r--;
        }
    }

    //returning false if no triplet sum equal to required number is present.
    return 0;


}

//^ 23 buy and sell stock (2 transactions) 
int maxProfit3(vector<int>&price){
    /* 
&    Suppose you make some profit p1 by doing your first transaction in the stock market. Now you are excited to purchase another stock to earn more profit. Suppose the price of the second stock you aim to buy is x. Now, for you, the net effective price that you are spending from your pocket for this stock will be x-p1, because you already have p1 bucks in your hand. Now, if you sell the second stock at price y your net profit p2 will be p2 = y - (x-p1). You have to do nothing but maximize this profit p2.

* O(N) T.C | O(1) space
    */
    
    if(price.empty())return 0;
    int firstBuy = INT_MAX;
    int firstProfit = 0;
    int secondBuy = INT_MAX;
    int secondProfit = 0;
    for(auto &i : price){
        firstBuy = min(firstBuy,i);
        firstProfit = max(firstProfit, i - firstBuy);
        secondBuy  = min(secondBuy, i - firstProfit);
        secondProfit = max(secondProfit,i - secondBuy);
    }
    return secondProfit;
}


//^ 24 Array subset of other array

bool isSubset(vector<int>& arr,vector<int>&other){
    if (other.size() > arr.size())
    {
        return false;
    }
    unordered_map<int,int> mp;
    for (auto &&i : arr) 
    {
        mp[i]++;
    }
    for (auto &&i : other) 
    {
        if (mp.find(i) == mp.end())
        {
            return false;
        }
        else if (mp[i] == 0)
        {
            return false;
        }
        else{
            mp[i]--;
        }
    }

    return true;
}

//^ 25 Trapping rain water problem
 int trappingWater(vector<int> &height){

    //! O(N) T.C | O(N) space
/*        int n = height.size();
        //? left[i] contains height of tallest bar to the 
        //? left of bar at ith index including itself.
        vector<int> left(n, 0);
      
        //? right[i] contains height of tallest bar to 
        //? the right of bar at ith index including itself. 
        vector<int> right(n, 0); 
      
        int water = 0;
      
        //? Storing values of tallest bar from first index till ith index.
        left[0] = height[0];
        for (int i = 1;i < n;i++) {
            left[i] = max(left[i - 1], height[i]);
        }
      
        //? Storing values of tallest bar from last index till ith index. 
        right[n-1] = height[n-1]; 
        for (int i = n - 2;i >= 0;i--) {
            right[i] = max(right[i + 1], height[i]);
        }
      
        //? Storing the result by choosing the minimum of heights of tallest bar to
        //? the right and left of the bar at current index and also subtracting the
        //? value of current index to get water accumulated at current index.
        for (int i = 0;i < n;i++) {
            water += max(0, min(left[i], right[i]) - height[i]);
        }
        // returning the result.
        return water; */

        /* 
    &   initialize left ptr = 0 and right ptr = size - 1
    &   while left < right do{
    &   if height[left] < height[right]
    &       if(height[left] > leftMax) update leftMax
    &       else add leftMax - height[left] to ans
    &       Add 1 to left
    &   else 
    &       if(height[left] > rightMax) update rightMax
    &       else add rightMax - height[right] to ans
    &       subtract 1 from right }

    * O(N) T.C | O(1) space
         */
     if (height.size()==0) return 0; 
        int left = 0, right = height.size()-1; 
        int leftMax=0, rightMax=0; 
        int ans = 0; 
        while (left < right) {
            if (height[left] > leftMax) leftMax = height[left]; 
            if (height[right] > rightMax) rightMax = height[right];
            if (leftMax < rightMax) {
                ans += max(0, leftMax-height[left]); 
                left++; 
            } else {
                ans += max(0, rightMax-height[right]); 
                right--; 
            }
        }
        return ans; 
}



//^ 26 smallest subarray with sum greater than 'x'

int smallest_subarray(vector<int> &arr,int x){
    /* 
& using sliding window and two pointers approach to solve
& first find the first subarray whose sum is greater than x
& then, start = 0 and end = subarray.length - 1 find the minSize
& subtract arr[start] from currSum(first subarray) sum and make sure this currSum is greater than x
& if not greater than x then move end to right side and adding arr[end] elements to currSum
& minimize the size of minSize and current subarray size(obtainable from start,end)
* O(N) T.C | O(1) S.C
     */
/*      int n = arr.size();
        int start = 0;
        int end = -1;
        int currSum = 0;
        for(int i = 0; i < n; i++){
            currSum+=arr[i];
            if(currSum>x){
                end = i;
                break;
            }
        }
        if(end == -1)return 0;
        int minSize = end - start + 1;
        while(start<=end && end < n){
            currSum -= arr[start++];
            while(currSum <= x && end < n){
                currSum += arr[++end];
            }
            if(currSum > x)
            minSize = min(minSize,end-start+1);
        }
        return minSize; */
        //* simplified version 
          int i=0, j=0, sum = arr[0], mini = INT_MAX;
       while(j<arr.size()) {
           if(sum <= x) {
               j++;
               sum = sum + arr[j];
           }
           else if(sum > x) {
               mini = min(mini, j-i+1);
               sum = sum - arr[i];
               i++;
           }
       }
       return mini;
}


// ^ 27 Three way partitioning
//* O(N) T.C | O(1) S.C {same approach as sort 0,1,2 array}
 void threeWayPartition(vector<int>& arr,int a, int b)
    {
        if(b<a || arr.size() < 2)return;
        int low = 0, high = arr.size()-1;
        int mid = low;
        while(mid<=high){
            if(arr[mid]<a){
                swap(arr[low++],arr[mid++]);
            }
            else if(arr[mid]>=a && arr[mid] <= b){
                mid++;
            }
            else{
                swap(arr[high--],arr[mid]);
            }
        }
    }

//^ 28 Minimum swap to group elements <= k
/* 
    * O(N) T.C | O(1) S.C

&    Find count of all elements which are less than or equals to ‘k’. Let’s say the count is ‘cnt’
&    Using two pointer technique for window of length ‘cnt’, each time keep track of how many elements in this range are greater than ‘k’. Let’s say the total count is ‘bad’.
&    Repeat step 2, for every window of length ‘cnt’ and take minimum of count ‘bad’ among them. This will be the final answer.

 */
int minSwap(vector<int>& arr, int k){
        int windowSize=0,start=0,end=0;
        for(int i = 0; i < arr.size(); i++){
            if(arr[i] <= k){
                windowSize++;
            }
        }
        if(windowSize == 0 || arr.size() < 2)return 0;
        end = windowSize - 1;
        int favorable=0,notfavourable=0,res;
        for(int i = start; i <= end; i++){
            if(arr[i] <= k)
                favorable++;
            else
                notfavourable++;
        }
        if(favorable == windowSize){
            return 0;
        }
        res = notfavourable;
        while(end<arr.size()){
            res = min(res,notfavourable);
            end++;
            if(end < arr.size() && arr[end]>k)notfavourable++;
            if(start < arr.size() && arr[start]>k)notfavourable--;
            start++;
            
        }
        return res;

    }

//^ 29/30 Median of two sorted Arrays
double MedianOfArrays(vector<int>& arr, vector<int>& brr)
    {
        /*
        & for algorithm watch yt video bruh
        * O(min(logN,logM)) T.C | O(1) space using binary search 
          */
        if(brr.size() < arr.size())return MedianOfArrays(brr,arr);
        int n1 = arr.size();
       int n2 = brr.size();
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
               int maximum = max(max1,max2);
               int minimum = min(min1,min2);
               if((n1 + n2) % 2 == 0)
                   return (double)((maximum + minimum) / 2.0);
               else
                   return (double)maximum;
           }
           else if(max1 > min2)
               end = i1 - 1;
           else
               begin = i1 + 1;
       }
    return 0.0;
}

//^ 31 Chocolate distribution problem
long long findMinDiff(vector<long long> a, long long n, long long m){
    /* 
    
     */
        if(m > n || a.empty())return 0;
    sort(a.begin() , a.end());
    long long ans = INT_MAX;
    long long minEle,maxEle;
    for(int i = 0; i < n && m + i <= n; i++){
        minEle = a[i];
        maxEle = a[m+i-1];
        ans = min(maxEle - minEle,ans);
    }
    return ans;
}
int main(int argc, char const *argv[])
{
    vector<int> arr = {4,0,0,3,1,4,5};
    vector<int> brr = {0, 1, 2, 3, 4, 5, 6, 7};
    vector<vector<int>> mat = {{1,4},{4,5}};
    // reverseArray(arr);
    // reverseArrayRecursive(arr,0,9);
    // pair<int,int> p = getMinMax(arr);
    // pair<int,int> p = getMinMax2(arr,0,9);
    // cout << p.first << " " << p.second << endl;
    // segregateElements(arr);
    // vector<int> res = unionOfArrays(arr, brr);
    // res = intersectionOfArrays(arr, brr);
    // rotateArrayByD(brr,3);
    // printArray(brr);
    // vector<vector<int>> res = mergeIntervals(mat);
    // printMatrix(res);
    // nextPermutation(arr);
    // rearrangeArray(arr);
    // maxProfit3(arr);
    // printArray(arr);
    cout << smallest_subarray(arr,7);
    return 0;
}
