#include<bits/stdc++.h>
using namespace std;

void merge(int arr1[],int n,int arr2[],int m,int arr[])
{
    int i = 0,j=0,k=0;
    while(i < n && j < m)
    {
        if(arr1[i] < arr2[j])
        {
            arr[k] = arr1[i];
            i++;
            k++;
        }
        if(arr1[i] > arr2[j])
        {
            arr[k] = arr2[j];
            j++;
            k++;
        }
    }
    while(i < n)
    {
        arr[k] = arr1[i];
        k++;
        i++;
    }
    while(j < m)
    {
        arr[k] = arr2[j];
        k++;
        j++;
    }
    
}
int main()
{
    int arr1[6] = {2,4,5,7,8,9};
    int arr2[3] = {1,3,6};
    int arr[9] = {0};

    merge(arr1,6,arr2,3,arr);
    for (int k = 0; k < 9; k++)
    {
       cout<<arr[k]<<" ";
    }
    return 0;
}