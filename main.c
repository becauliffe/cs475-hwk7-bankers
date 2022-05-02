#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "banker.h"
#include <errno.h>

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures
  if (argc != 2)
  {
    printf("Must include file\n");
    return 1;
  }
  FILE *fp;

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("%s: %s\n", argv[1], strerror(errno));
    return 1;
  }
  int numResources; // number of resource types
  int numThreads;   // number of threads
  fscanf(fp, "%d", &numResources);
  fscanf(fp, "%d", &numThreads);

  int *total = (int *)malloc(numResources * sizeof(int *));
  int *available = (int *)malloc(numResources * sizeof(int *));

  for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
  {
    fscanf(fp, "%d", &total[resourceNum]);
  }

  int **max = readMatrix(numThreads, numResources, fp);
  int **allocated = readMatrix(numThreads, numResources, fp);
  int **need = subMatrix(max, allocated, numThreads, numResources);
  int *order = (int *)malloc(numThreads * sizeof(int *));
  for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
  {
    available[resourceNum] = total[resourceNum];
  }
  for (int threadNum = 0; threadNum < numThreads; threadNum++)
  {
    for (int resourceNum = 0; resourceNum < numResources; resourceNum++)
    {
      available[resourceNum] -= allocated[threadNum][resourceNum];
    }
  }
  if (!checkTotal(total, allocated, numThreads, numResources))
  {
    printf("Integrity test failed: allocated resources exceed total resources\n");
    return 1;
  }
  if (!checkAllocation(allocated, max, numThreads, numResources))
  {
    printf("Integrity test failed: allocated resources exceed demand for Thread 2\n");
    return 1;
  }
  // This is the extra credit uncomment this and
  // allSafe(available, allocated, need, numThreads, numResources);
  // comment out the below code from here

  order = isSafe(available, allocated, need, order, numThreads, numResources);

  if (order[0] == -1)
  {
    printf("UNSAFE: ");
    int i = 1;
    while (order[i] != -1)
    {
      printf("T%d ", order[i++]);
    }
    printf("cant finish\n");
    return 0;
  }
  printf("SAFE: ");
  for (int threadNum = 0; threadNum < numThreads; threadNum++)
  {
    printf("T%d ", order[threadNum]);
  }
  printf("\n");
  // to here and it should work

  // cleanup
  fclose(fp);
  free(order);
  free(total);
  free(available);
  freeUp(max, numThreads);
  freeUp(allocated, numThreads);
  freeUp(need, numThreads);
  return 0;
}