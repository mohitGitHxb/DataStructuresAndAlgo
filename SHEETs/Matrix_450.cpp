#include <bits/stdc++.h>
using namespace std;

//^ 1 spiral traversal of a matrix
// * O(RC) time and O(N) space to store answer
vector<int> spirallyTraverse(vector<vector<int>> &matrix, int r, int c)
{
    // code here
    vector<int> res;
    int top = 0, left = 0, bottom = r - 1, right = c - 1;
    while (top <= bottom && left <= right)
    {
        for (int i = left; i <= right; i++)
        {
            res.push_back(matrix[top][i]);
        }
        top++;
        for (int i = top; i <= bottom; i++)
        {
            res.push_back(matrix[i][right]);
        }
        right--;
        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
                res.push_back(matrix[bottom][i]);
            bottom--;
        }
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
                res.push_back(matrix[i][left]);
            left++;
        }
    }
    return res;
}

//^ 2 Search in row sorted and column sorted matrix
bool searchInSortedMatrix(vector<vector<int>> &mat, int x)
{
    //% O(R+C) T.C | O(1) space
    int R2 = mat.size(), C2 = mat.front().size();
    int i = 0, j = C2 - 1; //? top right element
    while (i < R2 && j >= 0)
    {
        if (mat[i][j] == x)
        {
            return true;
            // cout << "fount at position : " << i << "," << j << endl;
            return;
        }
        else if (mat[i][j] > x) //? left shift a column as all the elements of the column j must be greater than x (sorted)
        {
            j--;
        }
        else
        {
            i++; //? increment row as all the elements behind i row must be smaller than x (Sorted)
        }
    }
    return false;
    /*

&    The problem statement states that the values of the last col of the ith row is greater than the first col of (i+1)th row. Also, each row is sorted.
&    This means that, if we linearly arrange the elements of each row, we will have a sorted array. So we can now perform a binary search over it.
&    How will the matrix behave like an array without actually creating an auxiliary array?
&    It could be achieved by the following formula :
&    A n * m matrix converted into an array: matrix[x][y] : a[x * m + y]
&    An array can be converted into n * m matrix: a[x] : matrix[x / m][x % m]

    * O(log(mn)) T.C
     */
    int n = mat.size();
    int m = mat[0].size();

    //? if matrix have 0 rows or 0 columns
    if (n == 0 || m == 0)
        return false;

    //? treating matrix as array just taking care of endices
    //? [0..n*m]
    int start = 0, end = m * n - 1;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        //? a[x] : matrix[x / m][x % m] formulae
        int ind = mat[mid / m][mid % m];
        if (x == ind)
            return true;
        //? left half
        else if (x < ind)
            end = mid - 1;
        else
            //? right half
            start = mid + 1;
    }
    return false;
}

//^ 3 Rotate the matrix by 90deg
/*
~ Anti clockwise transformation
&    There are N/2 squares or cycles in a matrix of side N. Process a square one at a time. Run a loop to traverse the matrix a cycle at a time, i.e loop from 0 to N/2 – 1, loop counter is i
&    Consider elements in group of 4 in current square, rotate the 4 elements at a time. So the number of such groups in a cycle is N – 2*i.
&    So run a loop in each cycle from x to N – x – 1, loop counter is y
&    The elements in the current group is (x, y), (y, N-1-x), (N-1-x, N-1-y), (N-1-y, x), now rotate the these 4 elements, i.e (x, y) <- (y, N-1-x), (y, N-1-x)<- (N-1-x, N-1-y), (N-1-x, N-1-y)<- (N-1-y, x), (N-1-y, x)<- (x, y)
&    Print the matrix.

!   can be solved in O(NM) T.C | O(NM) space using temp matrix to store column in reversed order
* O(NM) T.C | O(1) space
 */
void rotateMatrixAnti(vector<vector<int>> &mat)
{
    int N = mat.size();
    int M = mat.front().size();
    //? considering all squares one by one
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {
            int temp = mat[i][j];
            mat[i][j] = mat[j][N - 1 - i];                 //? move value from right to top
            mat[j][N - 1 - i] = mat[N - 1 - i][N - 1 - j]; //? move value from bottom to right
            mat[N - 1 - i][N - 1 - j] = mat[N - 1 - j][i]; //? move value from left to bottom
            mat[N - 1 - j][i] = temp;                      //? temp to left
        }
    }

    //* Using reversing col [AntiClockwise]
    /*     for (int i = 0; i < N; i++)
            reverse(mat[i].begin(), mat[i].begin() + N);

            //?      Performing Transpose
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++)
                swap(mat[i][j], mat[j][i]);
        } */
}

void rotateMatrixClockwise(vector<vector<int>> &mat)
{
    int N = mat.size();
    int M = mat.front().size();
    //? Traverse each cycle
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {

            // Swap elements of each cycle
            // in clockwise direction
            int temp = mat[i][j];
            mat[i][j] = mat[N - 1 - j][i];
            mat[N - 1 - j][i] = mat[N - 1 - i][N - 1 - j];
            mat[N - 1 - i][N - 1 - j] = mat[j][N - 1 - i];
            mat[j][N - 1 - i] = temp;
        }
    }
}

//^ 4 Print all elements in sorted order from row and column wise sorted matrix
//* O(N^2logN) T.C | O(N) space
vector<vector<int>> sortedMatrix(int N, vector<vector<int>> &mat)
{
    // code here
    vector<int> v;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            v.push_back(mat[i][j]);
    sort(v.begin(), v.end());
    int k = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = v[k++];
    return mat;
}

//^ 5 Median of row wise sorted matrix
/*

& Put all the elements of the the matrix into a single vector/array and sort it
& Return the median of the vector/array.
! O(NMlog(NM)) T.C | O(NM) space

* Efficient approach using BinarySearch O(RlogC) T.C | O(1) space
& Step 1: Find the minimum and maximum element in the given array. By just traversing the first column, we find the minimum element and by just traversing the last column, we find the maximum element.

& Step 2: Now find the middle element of the array one by one and check in the matrix how many elements are present in the matrix.

Three cases can occur:-

&     If count ==  (r*c+1)/2 , so it may be the answer still we mark max as mid since we are not referring indices , we are referring the elements and 5 elements can be smaller than 6 also and 7 also , so to confirm we mark max as mid.
&    If count<(r*c+1)/2 , we mark  min as mid+1 since curr element or elements before it cannot be the answer.
&    If count>(r*c+1)/2 , we mark max as mid , since elements after this can only be the  answer now.
 */

class MedianMatrix
{
public:
    int countSmallerThanMid(vector<int> &row, int mid)
    {
        int l = 0, h = row.size() - 1;
        while (l <= h)
        {
            int md = (l + h) >> 1;
            if (row[md] <= mid)
            {
                l = md + 1;
            }
            else
            {
                h = md - 1;
            }
        }
        return l;
    }
    int median(vector<vector<int>> &matrix, int R, int C)
    {
        int low = INT_MAX;
        int high = INT_MIN;
        for (int i = 0; i < R; i++)
        {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i].back());
        }

        while (low <= high)
        {
            int mid = (low + high) >> 1;
            int cnt = 0;
            for (int i = 0; i < R; i++)
            {
                cnt += countSmallerThanMid(matrix[i], mid);
            }
            if (cnt <= (R * C) / 2)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low;
    }
};

//^ 6 row with maximum 1s in a binary row-sorted matrix
int maxRow1s(vector<vector<int>> &arr, int n, int m)
{

    /*
    ~ Method - 1 : Naive
    & A simple approach is to calculate the number of 1s in each row and have a track of maximum number of 1s in rows <= current row, if any row has more 1s than current maximum1s update the ans to <current row/> keep doing this until we reach at the end of the matrix

    ! O(N*M) T.C | O(1) space

    ~ Method - 1 : using binary search
    & for each row we can find the number of 1s by simply calculating [column - first occurrence of 1 in that row this is index of the first occurrence] whenever we encounter a row with higher number of 1s than previous max1s we update the ans to <current row/> keep doing this until we reach the last row.

    & some important conditions :  to check whether the last element of a row is '0' if it is 0 simply skip the iteration and to check whether the first element of a row is '1' if it is 1 then return this row_index

    * O(NlogM) T.C | O(1) space

    ~ Method - 3 : Best solution
     &   Step1: Get the index of first (or leftmost) 1 in the first row.
     & Step2: Do following for every row after the first row 
     &   …IF the element on left of previous leftmost 1 is 0, ignore this row. 
     &   …ELSE Move left until a 0 is found. Update the leftmost index to this index and max_row_index to be the current row.
     &   The time complexity is O(m+n) because we can possibly go as far left as we came ahead in the first step.

     * O(N+M) T.C | O(1) space
     */
    /*     	    int ans = -1;
        int max1s = 0;
    if(n == 0 || m == 0)return ans;
    for(int i = 0; i < n; i++){
        int low = 0, high = m - 1;
        if(arr[i][low] == 1)return i;
        if(arr[i][high] == 0)continue;
        while(low<=high){
            int mid = (low + high)/2;
            if(arr[i][mid] == 0){
                low = mid+1;
            }
            else if(arr[i][mid] == 1){
                if(arr[i][mid-1] == 0){
                    if(max1s < m - mid){
                        max1s = m - mid;
                        ans = i;
                    }
                    break;
                }
                high = mid;
            }
            else{
                low++;
                high--;
            }
        }
    }
    return ans; */

    // Initialize first row as row with max 1s
    int j, max_row_index = 0;
    j = m - 1;

    for (int i = 0; i < n; i++)
    {
        // Move left until a 0 is found
        bool flag = false; // to check whether a row has more 1's than previous
        while (j >= 0 && arr[i][j] == 1)
        {
            j = j - 1;   // Update the index of leftmost 1
                         // seen so far
            flag = true; // present row has more 1's than previous
        }
        // if the present row has more 1's than previous
        if (flag)
        {
            max_row_index = i; // Update max_row_index
        }
    }
    if (max_row_index == 0 && arr[0][m - 1] == 0)
        return -1;
    return max_row_index;
}

//^ 7 Kth smallest element of a row and column wise sorted matrix of size NxN
int kthSmallestMatrix(vector<vector<int>> &mat, int N, int K)
{
    /*
    ~ Method - 1 : Naive approach
    & store the elements of the matrix in a temporary data structure (vector/array)
    & and sort it then return the kth smallest element
    ! O(N^2) + O(N^2logN) T.C | O(N^N) S.C
     */
    vector<int> temp;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp.push_back(mat[i][j]);
    sort(temp.begin(), temp.end());
    return temp[K - 1];
}

class KthSmallestMatrix
{
private:
/* 
& using binary search just like in median of row wise sorted matrix , we maintain two values (startVal and endVal) and we find a value between startVal and endVal such that the number of elements less than this value = k-1, shift the range to right side if ans(elements less than startVal) is smaller than k and shift to left side if ans(elements greater than startVal) is greater than k

    * O(NlogNlogN) T.C | O(1) S.C
 */
public:
    int binarySEARCH(vector<vector<int>> &arr, int n, int i, int midVal)
    {
        int low = 0, high = n - 1;
        int m;
        while (low <= high)
        {
            m = (low + high) / 2;
            if (arr[i][m] <= midVal)
            {
                low = m + 1;
            }
            else
            {
                high = m - 1;
            }
        }
        return low;
    }
    int kthSmallest(vector<vector<int>> &arr, int n, int k)
    {
        // Your code here
        int startVal = arr[0][0];       //? starting of range as matrix is sorted
        int endVal = arr[n - 1][n - 1]; //? ending of range
        int midVal = (startVal + endVal) / 2;
        while (startVal <= endVal)
        {
            midVal = (startVal + endVal) / 2;
            int ans = 0;
            //? row-wise traversing the matrix
            for (int i = 0; i < n; i++)
            {
                ans += binarySEARCH(arr, n, i, midVal);
            }
            if (ans < k)
            {
                startVal = midVal + 1;
            }
            else
            {
                endVal = midVal - 1;
            }
        }
        return startVal;
    }
};


//^ 8 Common elements in every row of the matrix

/* 

 & The idea is to use maps. We initially insert all elements of the first row in an map. For every other element in remaining rows, we check if it is present in the map. If it is present in the map and is not duplicated in current row, we increment count of the element in map by 1, else we ignore the element. If the currently traversed row is the last row, we print the element if it has appeared m-1 times before. 

 *O(R*C) T.C | O(C) space
 */
vector<int> commonElements(vector<vector<int>> &mat){
    vector<int> ans;
    unordered_map<int, int> mp;
    //? storing the first row of matrix in a hashmap
    for(auto &col : mat.front())
        mp[col] = 1; //? initializing all occurrences as 1 to avoid duplicacy
    
    for(int i = 1; i < mat.size(); i++){
        for (int j = 0; j < mat.front().size(); j++) {
            if(mp[mat[i][j]] == i){ //? checking if the element has been present in all the rows before current row_num
                mp[mat[i][j]] = i + 1; //? incrementing the occurrence by 1
                if(i == mat.size()-1 && mp[mat[i][j]] == mat.size()){ //? element is common in all rows
                    ans.push_back(mat[i][j]);
                }
            }
        }
    }
    return ans;
}

//^ 9 Largest rectancle in a binary matrix 
class LargestRectangleInBinaryMatrix{
  private:
  /* 
  & The idea is to use three different problems 
  & 1. next smaller elements
  & 2. previous smaller elements
  & 3. Largest area of histogram

  & these three problems are solved in stack.cpp 

  & Now, we find the area of first row of the matrix by using the function3(largest area of histogram), Now we start finding  the area of remaining rows of the matrix by adding the current row to the histogram i.e (histogram[col_num] = matrix[row_num][col_num] == 0 ? 0 : matrix[row_num][col_num] + histogram[col_num]) , and we keep updating the maximum area. The main part of this problem is the function3. For largest area of histogram we make use of the function1 and function2

  *O(Row * Col) | O(col) space
   */
  public:
  vector<int> nextSmaller(vector<int> &heights){
    // if(heights.size() < 1)return heights.size();
    stack<int> stk;
    vector<int> res;
    stk.push(-1);
    for (int i = heights.size()-1; i>=0; i--) {
        while(!stk.empty() && heights[stk.top()] >= heights[i])
            stk.pop();
        if(stk.empty()){
            res.push_back(-1);
        }
        else{
            res.push_back(stk.top());
        }
        stk.push(i);
    }
    reverse(res.begin(),res.end());
    return res;
} 

vector<int> prevSmaller(vector<int> &heights){
    stack<int> stk;
    vector<int> res;
    stk.push(-1);
    for (int i = 0; i < heights.size(); i++) {
        while(!stk.empty() && heights[stk.top()] >= heights[i])
            stk.pop();
        if(stk.empty()){
            res.push_back(-1);
        }
        else{
            res.push_back(stk.top());
        }
        stk.push(i);
    }
    return res;
}

int largestRectHistogram(vector<int> &heights){
    vector<int> next = nextSmaller(heights);
    vector<int> prev = prevSmaller(heights);
    int length,breadth,area=INT_MIN;
    for(int i = 0; i < heights.size(); i++){
        length = heights[i];
        if(next[i] == -1){
            next[i] = heights.size();
        }
        breadth = next[i] - prev[i] - 1;
        area = max(area,length*breadth);
    }
    // cout << area<< "\n";
    return area;
}
    int maxArea(int M[100][100], int n, int m) {
        vector<int> histogram(m); 
        for(int j = 0; j < m; j++)
            histogram[j] = M[0][j];
            
        int maximumArea = largestRectHistogram(histogram);  //? get the maximum area of 1st row/level
        
        for(int i = 1; i < n; i++){
            for(int j = 0; j < m; j++)
            histogram[j]=(M[i][j] == 0)?0:(M[i][j]+histogram[j]); //? taking care of M[i][j] == 0 because if the base of histogram is 0 then the whole histogram collapses(building with base removed if that makes sense) 
            maximumArea = max(maximumArea,largestRectHistogram(histogram)); 
            
        }
        return maximumArea;
        
    }
};


//^ 10 find the maximum difference : mat[c][d] - mat[a][b] such that c > a & d > b

int findMaxValue(vector<vector<int>> &mat)
{
    int N = mat.size();
	//stores maximum value
	int maxValue = INT_MIN;

	// maxMatrix[i][j] stores max of elements in matrix
	// from (i, j) to (N-1, N-1)
	int maxMatrix[mat.size()][mat.front().size()];

	// last element of maxMatrix will be same's as of
	// the input matrix
	maxMatrix[N-1][N-1] = mat[N-1][N-1];

	// preprocess last row
	int maxv = mat[N-1][N-1]; // Initialize max
	for (int j = N - 2; j >= 0; j--)
	{
		maxv=max(maxv,mat[N-1][j]);
		maxMatrix[N-1][j] = maxv;
	}

	// preprocess last column
	maxv = mat[N - 1][N - 1]; // Initialize max
	for (int i = N - 2; i >= 0; i--)
	{
		maxv  = max(maxv,mat[i][N-1]);
		maxMatrix[i][N - 1] = maxv;
	}

	// preprocess rest of the matrix from bottom
	for (int i = N-2; i >= 0; i--)
	{
		for (int j = N-2; j >= 0; j--)
		{
			// Update maxValue
			maxValue = max(maxValue,maxMatrix[i+1][j+1] - mat[i][j]);
			// set maxArr (i, j)
			maxMatrix[i][j] = max(mat[i][j],max(maxMatrix[i][j + 1],maxMatrix[i + 1][j]));
		}
	}

	return maxValue;
}
int main()
{
    return 0;
}