
int *isSafe(int *available, int **allocated, int **need, int *order, int numThreads, int numResources);

// int *permute(int *, int, int);
void permute(int *arr, int start, int end, int *available, int **allocated, int **need, int numThreads, int numResources);

void swap(int *, int, int);
int factorial(int n);
void test(int numThreads);
void allSafe(int *available, int **allocated, int **need, int numThreads, int numResources);
int bruteForce(int *available, int **allocated, int **need, int *ordering, int numThreads, int numResources);