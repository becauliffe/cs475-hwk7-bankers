

int **createMatrix(int numThreads, int numResources);
int **readMatrix(int numThreads, int numResources, FILE *fp);
int checkAllocation(int **allocated, int **max, int numThreads, int numResources);
int checkTotal(int *total, int **matrix, int numThreads, int numResources);
int **addMatrix(int **one, int **two, int numThreads, int numResources);
int **subMatrix(int **one, int **two, int numThreads, int numResources);
int *addArray(int *one, int *two, int numResources);
void freeUp(int **matrix, int numThreads);