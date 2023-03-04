#include<bits/stdc++.h>

using namespace std;
/* 
~Binary heap is a complete binary tree (stored as an array)
todo left(i) = 2i + 1
todo right(i) = 2i + 2
todo parent(i) = floor((i-1)/2)
 */
class MinHeap
{
private:
    int data;
    int size;
    int capacity;
    int* arr;
public:
    MinHeap(int c);
    ~MinHeap();
    inline int left(int i){return 2*i + 1; }
    inline int right(int i){return 2*i + 2;}
    inline int parent(int i){return (i-1)/2;}

    void insert(int x){  //~ log(size) time
        if(size == capacity)return;
        arr[size++] = x;
        for (int i = size-1; i!=0&&arr[parent(i)] > arr[i]; i++)
        {
            swap(arr[i] , arr[parent(i)]);
            i = parent(i);
        }
    }

    void minHeapify(int i){  //~ O(logn) time;
        int leftChild = left(i) , rightChild = right(i);
        int smallest = i;
        if (leftChild < size && arr[leftChild] < arr[i])
        {
            smallest = leftChild;
        }
        if (rightChild < size && arr[rightChild] < arr[smallest])
        {
            smallest = rightChild;
        }
        if (smallest != i)
        {
            swap(arr[i],arr[smallest]);
            minHeapify(smallest);
        }
        
    }
        int extractMinimum(){  //& O(logn) time
            if(size == 0)return INT_MIN;
            if(size == 1){size--; return arr[0];}
            swap(arr[0],arr[size-1]);size--;
            minHeapify(0); 
            return arr[size];
        }
    
    void decreaseKey(int i, int x){  //& O(logN) time
        arr[i] = x;
        while (i != 0 && arr[parent(i)] > arr[i])
        {
            swap(arr[i],arr[parent(i)]);
            i = parent(i);
        }
        
    }

    void deleteKey(int i){
        decreaseKey(i,INT_MIN);
        extractMinimum();
    }

    void buildHeap(){ //& O(N) time
        /* 
        ~ when you heapify from bottom to top you assume that bottom part is already heapified
        ~ last node's parent = ((n-1)-1)/2        
         */
        for (int i = (size-2)/2; i>=0; i--) 
        {
            minHeapify(i);
        }
        
    }
        
};

MinHeap::MinHeap(int c)
{
    arr = new int[c];
    capacity = c;
    size = 0;
}

MinHeap::~MinHeap()
{
    delete arr;
}



//^ Heap sort O(nlogn) 
void maxHeapify(int arr[],int size, int i){

        int leftChild = 2*i + 1 , rightChild = 2*i + 2;
        int largest = i;
        if (leftChild < size && arr[leftChild] > arr[i])
        {
            largest = leftChild;
        }
        if (rightChild < size && arr[rightChild] > arr[largest])
        {
            largest = rightChild;
        }
        if (largest != i)
        {
            swap(arr[i],arr[largest]);
            maxHeapify(arr,i,largest);
        }
}
void buildHeap(int arr[],int size){
    for (int i = (size - 2)/2; i >= 0; i--)
    {
        maxHeapify(arr,size,i);
    }
}


void heapSort(int arr[],int n){
    buildHeap(arr,n);
    for (int i = n - 1; i >= 1; i--)
    {
        swap(arr[0],arr[i]);
        maxHeapify(arr,i,0);
    }   
}



//^ print K closest



void printKclosest(int arr[],int n,int k,int x){


    //! O(NK) time and O(N) space
  /*   vector<bool> visited(n,false);
    for (int i = 0; i < k; i++)
    {
    int minDiff = INT_MIN;
    int minDiffIdx; //? index of next closest element
    for (int j = 0; j < n; j++)
    {
        if (visited[j] == false && abs(arr[j] - x)<=minDiff)
        {
            minDiff = abs(arr[j]-x);
            minDiffIdx = 3;
        }
        
    }
    
    cout << arr[minDiffIdx] << " ";
    visited[minDiffIdx] = true;
    } */


    //* NlogK
    priority_queue<pair<int,int>> pq;
    for (int i = 0; i < k; i++)
    {
        pq.emplace(abs(arr[i]-x),i);
    }
    for (int i = n; i < n; i++)
    {   
        int diff = abs(arr[i] - x);
        if (pq.top().first > diff)
        {
            pq.pop();
            pq.emplace(diff,i);
        }
        
    }
    
    for (int i = 0; i < k; i++)
    {
        auto it = pq.top();
        pq.pop();
        cout << arr[it.second] <<" ";
    }
}


//^ Sort a K-sorted array O((N+K)logK) time
void sortK(vector<int> &arr,int K){
    priority_queue<int,vector<int>,greater<int>> pq; //?min heap
    for (int i = 0; i <= K; i++)
    {
        pq.push(arr[i]);
    }
    int index = 0; //? tells us where to put next element in the sorted array
    for (int i = K+1; i < arr.size(); i++) //?reversing first K elements
    {
        arr[index++] = pq.top();
        pq.pop();
        pq.push(arr[i]);
    }

    while (!pq.empty())
    {
        arr[index++] = pq.top();
        pq.pop();
    }
}

//^ Merge K sorted Arrays
struct triplet
{
    int val,arrayPosition,elementPosition;
    triplet(int v,int ap,int ep){val=v; arrayPosition=ap; elementPosition=ep;}
};
struct MyCmp
{
bool operator()(triplet &t1,triplet &t2){
    return t1.val > t2.val;
}};




vector<int> mergeKSorted(vector<vector<int>> &arr){
    //! method-1 copy all the elements in resultant array and sort it O(NKlogNK) time.
    //~ method-2 copy first array to resultant array and merge current array into resultant array for each successive array O(NK^2) time.
    //* method-3 using min heap of objects O(NKlogK) time;
    vector<int> res;
    priority_queue<triplet,vector<triplet>,MyCmp> pq;
    for (int i = 0; i < arr.size(); i++)
    {
        triplet t(arr[i][0],i,0);
        pq.emplace(t);
    }
    while (!pq.empty())
    {
        triplet curr = pq.top(); 
        pq.pop();
        res.push_back(curr.val);
        int ap = curr.arrayPosition;
        int ep = curr.elementPosition;
        if(ep + 1 < arr[ap].size()){
            triplet t(arr[ap][ep+1],ap,ep+1);
            pq.emplace(t);
        }
    }
    return res;
}

//^ median of a stream

void medianStream(vector<int> &arr){

    //!method-1 : maintaining sorted array O(N^2);
    //? method-2 : Augmented BST using kthSmallest  O(NlogN) on average
    //*method-3 : using double heaps i.e smaller half and greater half heaps O(NlogN) on worst too.
    priority_queue<int,vector<int>,greater<int>> min; //? smaller half elements
    priority_queue<int> max; //? greater half elements
    max.push(arr[0]);
    cout << arr[0] <<" ";
    for (int i = 1; i < arr.size(); i++)
    {
        int curr = arr[i];
        if (max.size() > min.size())
        {
            if (max.top() > curr)
            {
                min.push(max.top());
                max.pop();
                max.push(curr);

            }
            else
            {
                min.push(curr);
            }
            
            cout << (float)(max.top()+ min.top())/2 <<" ";
            
        }
        else
        {
            if(curr<=max.top()){
                max.push(curr);
            }
            else
            {
                min.push(curr);
                max.push(min.top());
                min.pop();
            }
            cout << max.top() << " ";
            
        }
        
        
    }
    
    
}
int main(){
    vector<int> arr={25,7,10,15,20};
    medianStream(arr);
}