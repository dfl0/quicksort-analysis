#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAD 85

int swaps; // keep track of number of swaps

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swaps++;
}

void parse_file(char *path, int *arr, int max_size) {
    FILE *file = fopen(path, "r");
    char line[256];

    int i = 0;
    while (i < max_size && fgets(line, sizeof(line), file)) {
        arr[i++] = atoi(line);
    }
}

double seconds_taken(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* n = number of elements in the input array arr */
void insertion_sort(int arr[], int n) {
    /* for every element starting from the second ... */
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* ... shift over the previous elements until the correct spot is found for the current */
        while (arr[j] > key && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// pivot type:
// 0 = first element
// 1 = last element
// 2 = random element
// 3 = median of three
/* this uses Hoare's partition procedure */
int partition(int arr[], int p, int r, int pivotType) {
    //determine pivot index
    int pivotIndex = p;
    if(pivotType == 1)
	    pivotIndex = r;
    if(pivotType == 2)
	    pivotIndex = p + rand() % (r-p+1);
    if(pivotType == 3){
    	int m = (p+r) / 2;
	//determine the median value
	if(arr[p] < arr[m] && arr[m] < arr[r])
		pivotIndex = m;
	else if(arr[p] < arr[r] && arr[r] < arr[m])
		pivotIndex = r;
	else
		pivotIndex = p;
    }

    //swap pivot into arr[p]
    swap(&arr[p], &arr[pivotIndex]);

    int x = arr[p]; // selects the first element as the initial pivot
    int i = p - 1;
    int j = r + 1;

    while (1) {
        do {j--;} while (arr[j] > x);
        do {i++;} while (arr[i] < x);

        if (i < j) swap(&arr[i], &arr[j]);
        else return j;
    }
}

/* for an input array with n elements (i.e., arr[0..n-1]) p = 0 and r = n - 1 */
void quick_sort(int arr[], int p, int r, int pivotType) {
    if (p < r) {
        /* find index q, such that every element in arr[p, q] is less than or equal to every element in arr[q + 1, r] */
        int q = partition(arr, p, r, pivotType);
        /* recursively call quicksort on both sub-arrays */
        quick_sort(arr, p, q, pivotType);
        quick_sort(arr, q + 1, r, pivotType);
    }
}

void hybrid_quick_sort(int arr[], int p, int r, int threshold) { // add extra "threshold parameter to test multiple thresholds
    while (p < r) {
        if (r - p + 1 < threshold) { // if in threshold, sort using insertion sort
            insertion_sort(arr + p, r - p + 1);
            break;
        }

        else {
            int q = partition(arr, p, r, 0); //use default pivot type for this
            if (q - p < r - q) {
                hybrid_quick_sort(arr, p, q, threshold);
                p = q + 1;
            }

            else {
                hybrid_quick_sort(arr, q + 1, r, threshold);
                r = q;
            }
        }
    }
}

void runQuicksort(char* file, int pivotType)
{
	clock_t start, end;
	int n = 100000;
	int input[n];
	parse_file(file, input, n);

    swaps = 0;
	start = clock();
	quick_sort(input, 0, n-1, pivotType);
	end = clock();
	printf("%8.5f s  (%d swaps)\n", seconds_taken(start, end), swaps);
}

void runHybridQuicksort(char* file, int threshold)
{
	clock_t start, end;
	int n = 100000;
	int input[n];
	parse_file(file, input, n);

    swaps = 0;
	start = clock();
	quick_sort(input, 0, n-1, threshold);
	end = clock();
	printf("%8.5f s  (%d swaps)\n", seconds_taken(start, end), swaps);
}

int main(void) {
    /* sorted elements */
    char *msg = "quicksort on 100,000 sorted elements with last element pivot:";
    printf("%-*s", PAD, msg);
    runQuicksort("ordered100000.txt", 0);

    msg = "quicksort on 100,000 sorted elements with first element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("ordered100000.txt", 1);

    msg = "quicksort on 100,000 sorted elements with random element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("ordered100000.txt", 2);

    msg = "quicksort on 100,000 sorted elements with median-of-three element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("ordered100000.txt", 3);

    /* reverse order elements */
    msg = "quicksort on 100,000 elements in reverse order with last element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("rev100000.txt", 0);

    msg = "quicksort on 100,000 elements in reverse order with first element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("rev100000.txt", 1);

    msg = "quicksort on 100,000 elements in reverse order with random element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("rev100000.txt", 2);

    msg = "quicksort on 100,000 elements in reverse order with median-of-three element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("rev100000.txt", 3);

    /* unsorted elements */
    msg = "quicksort on 100,000 randomly sorted elements with last element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("shuf100000.txt", 0);

    msg = "quicksort on 100,000 randomly sorted elements with first element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("shuf100000.txt", 1);

    msg = "quicksort on 100,000 randomly sorted elements with random element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("shuf100000.txt", 2);

    msg = "quicksort on 100,000 randomly sorted elements with median-of-three element pivot: ";
    printf("%-*s", PAD, msg);
    runQuicksort("shuf100000.txt", 3);


    /* Hybrid Quicksort */

    /* sorted elements */
    msg = "hybrid quicksort on 100,000 sorted elements with threshold 16: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("ordered100000.txt", 16);

    msg = "hybrid quicksort on 100,000 sorted elements with threshold 32: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("ordered100000.txt", 32);

    // Java Quicksort switches at 44
    msg = "hybrid quicksort on 100,000 sorted elements with threshold 44: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("ordered100000.txt", 44);

    /* reverse order elements */
    msg = "hybrid quicksort on 100,000 elements in reverse order with threshold 16: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("rev100000.txt", 16);

    msg = "hybrid quicksort on 100,000 elements in reverse order with threshold 32: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("rev100000.txt", 32);

    // Java Quicksort switches at 44
    msg = "hybrid quicksort on 100,000 elements in reverse order with threshold 44: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("rev100000.txt", 44);

    /* unsorted elements */
    msg = "hybrid quicksort on 100,000 randomly sorted elements with threshold 16: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("shuf100000.txt", 16);

    msg = "hybrid quicksort on 100,000 randomly sorted elements with threshold 32: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("shuf100000.txt", 32);

    // Java Quicksort switches at 44
    msg = "hybrid quicksort on 100,000 randomly sorted elements with threshold 44: ";
    printf("%-*s", PAD, msg);
    runHybridQuicksort("shuf100000.txt", 44);

    return 0;
}
