#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/**
 * mallocs a matrix with the proper size
 * @param the number of processes
 * @param the number of resource types
 * @return 2d array (matrix)
 **/

int **createMatrix(int numThreads, int numResources)
{
    int **matrix = (int **)malloc(numThreads * sizeof(int *));
    for (int i = 0; i < numThreads; i++)
    {
        matrix[i] = (int *)malloc(numResources * sizeof(int));
    }
    return matrix;
}
/**
 * mallocs a matrix with the proper size
 * then populates it from a file
 * @param the number of processes
 * @param the number of resource types
 * @param file pointer
 * @return matrix populated
 **/
int **readMatrix(int numThreads, int numResources, FILE *fp)
{
    int **matrix = createMatrix(numThreads, numResources);
    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
        {
            fscanf(fp, "%d", &matrix[threadNum][resourceNum]);
        }
    }
    return matrix;
}
/**
 * add matrices
 * @param first matrix
 * @param second matrix
 * @param the number of processes
 * @param the number of resource types
 * @return 2d array (matrix)
 **/
int **addMatrix(int **one, int **two, int numThreads, int numResources)
{
    int **result = createMatrix(numThreads, numResources);

    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
        {
            result[threadNum][resourceNum] = one[threadNum][resourceNum] + two[threadNum][resourceNum];
        }
    }
    return result;
}

/**
 * adds one dimensial matrices
 * @param first matrix
 * @param second matrix
 * @param the number of processes
 * @param the number of resource types
 * @return array
 **/
int *addArray(int *one, int *two, int numResources)
{
    for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
    {
        one[resourceNum] += two[resourceNum];
    }
    return one;
}

/**
 * subtract matrices
 * @param first matrix
 * @param second matrix
 * @param the number of processes
 * @param the number of resource types
 * @return 2d array (matrix)
 **/
int **subMatrix(int **one, int **two, int numThreads, int numResources)
{
    int **result = createMatrix(numThreads, numResources);

    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
        {
            result[threadNum][resourceNum] = one[threadNum][resourceNum] - two[threadNum][resourceNum];
        }
    }
    return result;
}
/**
 * check one
 * makes sure total resources doesnt exceed allocated
 **/
int checkTotal(int *total, int **matrix, int numThreads, int numResources)
{
    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
        {
            if (total[resourceNum] < matrix[threadNum][resourceNum])
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * check two
 * makes sure allocated resources doesnt exceed demand
 **/
int checkAllocation(int **allocated, int **max, int numThreads, int numResources)
{
    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
        {
            if (allocated[threadNum][resourceNum] > max[threadNum][resourceNum])
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * frees a matrix
 **/
void freeUp(int **matrix, int numThreads)
{
    for (int threadNum = 0; threadNum < numThreads; threadNum++)
    {
        free(matrix[threadNum]);
    }
    free(matrix);
}