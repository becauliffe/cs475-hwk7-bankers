#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

int *isSafe(int *available, int **allocated, int **need, int *order, int numThreads, int numResources)
{
    int *newAvail = (int *)malloc(numResources * sizeof(int *));
    int doneCounter = numThreads;
    for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
    {
        newAvail[resourceNum] = available[resourceNum];
    }
    int finish[numThreads];

    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        finish[threadNum] = 0;
    }
    int fail = 0;

    while (doneCounter > 0)
    {
        int progress = 0;
        for (int threadNum = 0; threadNum < numThreads; threadNum++)
        {
            if (finish[threadNum] == 0)
            {
                for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
                {
                    if (newAvail[resourceNum] < need[threadNum][resourceNum])
                    {
                        fail = 1;
                        break;
                    }
                }
                if (!fail)
                {
                    newAvail = addArray(newAvail, allocated[threadNum], numResources);
                    printf("%d %d %d\n", newAvail[0], newAvail[1], newAvail[2]);
                    finish[threadNum] = 1;
                    order[numThreads - doneCounter] = threadNum;
                    doneCounter--;
                    progress = 1;
                }
                else
                {
                    fail = 0;
                }
            }
        }
        if (progress == 0)
        {
            int orderInc = 1;
            order[0] = -1;
            for (int threadNum = 0; threadNum < numThreads; threadNum++)
            {
                if (finish[threadNum] == 0)
                {
                    order[orderInc] = threadNum;
                    orderInc++;
                }
            }
            order[orderInc] = -1; // might cause seg fault if non of the threads run
            free(newAvail);
            return order;
        }
    }
    free(newAvail);
    return order;
}

int bruteForce(int *available, int **allocated, int **need, int *ordering, int numThreads, int numResources)
{
    int *newAvail = (int *)malloc(numResources * sizeof(int *));
    for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
    {
        newAvail[resourceNum] = available[resourceNum];
    }

    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        int actualThread = ordering[threadNum];
        for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
        {
            if (newAvail[resourceNum] < need[actualThread][resourceNum])
            {
                // next permutation
                free(newAvail);
                return 0;
            }
        }
        newAvail = addArray(newAvail, allocated[actualThread], numResources);
    }

    printf("SAFE: ");
    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        printf("T%d, ", ordering[threadNum]);
    }
    printf("\n");

    free(newAvail);
    return 1;
}

/**
 * finds every safe schedule
 * lots of params lol
 **/
void allSafe(int *available, int **allocated, int **need, int numThreads, int numResources)
{
    int starter[numThreads];
    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        starter[threadNum] = threadNum;
    }

    permute(starter, 0, numThreads, available, allocated, need, numThreads, numResources);
}

// following functions were adapted from multiple web sources as well as myself
/* swap 2 values by index */
void swap(int *arr, int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

/* permute an array recursively */
void permute(int *arr, int start, int end, int *available, int **allocated, int **need, int numThreads, int numResources)
{
    int i;

    if (start == end) /* this function is done */
    {
        bruteForce(available, allocated, need, arr, numThreads, numResources);
        return;
    }

    permute(arr, start + 1, end, available, allocated, need, numThreads, numResources); /* start at next element */

    /* permute remaining elements recursively */
    for (i = start + 1; i < end; i++)
    {
        if (arr[start] == arr[i])
            continue; /* skip */

        swap(arr, start, i);

        permute(arr, start + 1, end, available, allocated, need, numThreads, numResources);

        swap(arr, start, i); /* restore element order */
    }
}
