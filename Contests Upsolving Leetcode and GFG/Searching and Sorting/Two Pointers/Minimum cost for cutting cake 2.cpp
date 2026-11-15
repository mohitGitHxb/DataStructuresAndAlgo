#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumCost(int m, int n, vector<int> &horizontalCut, vector<int> &verticalCut)
    {
        long long totalCost = 0;


        //& Remember whenever we are cutting cake in one direction it will form 2 non equal or equal sized cakes
        //& We will see why maintaining these slices are important while calculating result


        long long horizontalSlices = 1, verticalSlices = 1;


        //~ It is always better to choose the cut which has maximum cost first because then it will only happen once
        //~ otherwise as seen above because of slices it will be included more than one times later on eventually
        //~ hence it is wise to cut first with maximum cost so that to make sure we do not incur this cost again


        sort(horizontalCut.rbegin(), horizontalCut.rend());
        sort(verticalCut.rbegin(), verticalCut.rend());


        int horizontalPointer = 0, verticalPointer = 0; // two pointers to form our decision which cut to make so as to get least cost;
        while (horizontalPointer < horizontalCut.size() && verticalPointer < verticalCut.size())
        {
            //% Right here it makes sense to cut horizontally so that we don't include it again

            if (horizontalCut[horizontalPointer] >= verticalCut[verticalPointer])
            {
                totalCost += verticalSlices * horizontalCut[horizontalPointer]; //& we need to count cost for all vertical components
                horizontalSlices++;                                             //& made the cut hence the cake is divided into two slices
                horizontalPointer++;                                            //& this cost has been included now so we can safely go further
            }

            //% similar for verticalCut[verticalPointer]
            else
            {
                totalCost += horizontalSlices * verticalCut[verticalPointer];
                verticalSlices++;
                verticalPointer++;
            }
        }


        //^ What if some cuts haven't been made? then just make them of course!
        //% only one while loop will run! not both
        //* The entire code is very similar to merge function of merge sort ain't it?


        while (horizontalPointer < horizontalCut.size())
        {
            totalCost += verticalSlices * horizontalCut[horizontalPointer];
            horizontalPointer++;
        }



        while (verticalPointer < verticalCut.size())
        {
            totalCost += horizontalSlices * verticalCut[verticalPointer];
            verticalPointer++;
        }



        return totalCost;
    }
};

int main()
{
    return 0;
}