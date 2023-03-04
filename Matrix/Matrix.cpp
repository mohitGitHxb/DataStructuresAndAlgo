#include <bits/stdc++.h>
#define R 3
#define C 3
#define R2 4
#define C2 4

using namespace std;

// double pointer approach
//  void printMat(int **arr , int m , int n){
//      for (int i = 0; i < m; i++)
//      {
//          for (int j = 0; j < n; j++)
//          {
//              cout << arr[i][j] << " ";
//          }
//          cout << endl;
//      }
//  }

void printMat(int mat[R2][C2])
{

    for (int i = 0; i < R2; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

//^ print in a snake pattern Ø(RC)
 void printMatSnake(int mat[R][C]){
     for (int i = 0; i < R; i++)
     {
         if (i%2==0)  //? even rows are printed normally
         {
             for (int j = 0; j < C; j++)
             {
                 cout<<mat[i][j]<<" ";
             }
        }
        else
        {
            for (int j = C - 1; j >= 0; j--)
            {
                cout << mat[i][j] <<" ";
            }
        }
    }
}

//^ print boundaries of a matrix

void printBoundary(int mat[R2][C2])
{
    for (int i = 0; i < R2; i++)
    {
        int temp = R2 - 1;
        if (i == 0)
        {
            for (int j = 0; j < C2; j++)
            {
                cout << mat[i][j] << " ";
            }
        }
        else if (i + 1 == R2)
        {
            for (int j = C2 - 1; j >= 0; j--)
            {
                cout << mat[i][j] << " ";
            }
            if(C2 == 1)continue;
            for (int k = temp-1; k > 0; k--)
            {
                cout << mat[k][0] << " ";
            }
        }
        else
        {
            cout << mat[i][C2-1] << " ";
        }
    }
}

//^ transpose of a matrix using temp matrix
 void transpose(int mat[R][C]){
     int temp[R][C];
     for (int i = 0; i < R; i++)
     {
         for (int j = 0; j < C; j++)
         {
             temp[i][j] = mat[j][i];
         }

    }
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            mat[i][j] = temp[i][j];
        }

    }
}

void transpose_v2(int mat[R][C]){
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            swap(mat[i][j] , mat[j][i]);
        }

    }
}

// rotate a matrix by 90 deg
 void rotateMatrix(int mat[R2][C2]){
     int temp[R2][C2];
     for (int i = 0; i < R2; i++)
     {
         for (int j = C2-1; j >= 0; j--)
         {
             temp[R2-j-1][i] = mat[i][j]; //? interchange column to row and reverse col
         }

    }
    for (int i = 0; i < R2; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            mat[i][j] = temp[i][j];
        }

    }
}

void printSpiral(int mat[R2][C2])
{
    uint_fast8_t top = 0, left = 0, bottom = R2 - 1, right = C2 - 1;
    while (top <= bottom && left <= right)
    {
        for (int i = left; i <= right; i++) // prints top row
        {
            cout << mat[top][i] << " ";
        }
        top++;
        for (int i = top; i <= bottom; i++) // prints right column
        {
            cout << mat[i][right] << " ";
        }
        right--;
        if (top <= bottom)
        {
            for (int i = right; i >= left; i--) // prints bottom row(R to L) or reversed order
            {
                cout << mat[bottom][i] << " ";
            }
            bottom--;
        }
        if (left <= right)
        {

            for (int i = bottom; i >= top; i--) // print left column in reversed order
            {
                cout << mat[i][left] << " ";
            }
            left++;
        }
    }
}

// search in row wise and column wise

// void searchInMatrix(int mat[R2][C2] , int x){
//     for (int i = 0; i < R2; i++)
//     {
//         for (int j = 0; j < C2; j++)
//         {
//             if (mat[i][j] == x)
//             {
//                 cout<<"found at position : "<<i+1<<","<<j+1<<endl;
//                 return;
//             }

//         }

//     }
//     cout << "not found"<<endl;

// }

// search in sorted row and column wise matrix O(R+C)
void searchInSortedMatrix(int mat[R2][C2], int x)
{
    int i = 0, j = C2 - 1; //? top right element
    while (i < R2 && j >= 0)
    {
        if (mat[i][j] == x)
        {
            cout << "fount at position : " << i << "," << j << endl;
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
    printf("Not found");
}

//median of row wise sorted matrix O(r*log(max-min)*logC)
/*Assumptions ↪ odd sized matrix , all distinct elements*/

int medianMatrix(int mat[R][C]){
    int min = mat[0][0] , max = mat[0][C-1];
    for (int i = 1; i < R; i++)
    {
        if (mat[i][0] < min)
        {
            min = mat[i][0];
        }
        if (mat[i][C-1]>max)
        {
            max = mat[i][C-1];
        }
        
    }
    int medPos = (R*C+1)/2; //median position of odd sized matrix
    while (min<max) //binary search
    {
        int mid = (min+max)/2;
        int midPos = 0;
        for (int i = 0; i < R; i++)
        {
            midPos += upper_bound(mat[i],mat[i]+C,mid) - mat[i]; //index of first greater than element
        }
        if (midPos < medPos)
        {
            mid++;
        }
        else
        max = mid;
        
    }
    return min;
    
}
int main(int argc, char const *argv[])
{
    int matrix[R][C] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrix2[R2][C2] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // printBoundary(matrix2);
    // transpose_v2(matrix);
    rotateMatrix(matrix2);
    printMat(matrix2);
    // printSpiral(matrix2);
    // printMat(matrix);
    // searchInSortedMatrix(matrix2, 7);
    // cout<<medianMatrix(matrix);

    return 0;
}
