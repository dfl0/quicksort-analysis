#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void parse_file(char *path, int *arr, int max_size) {
    FILE *file = fopen(path, "r");
    char line[256];

    int i = 0;
    while (i < max_size && fgets(line, sizeof(line), file)) {
        arr[i++] = atoi(line);
    }
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

/* this uses Hoare's partition procedure */
int partition(int arr[], int p, int r) {
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
void quick_sort(int arr[], int p, int r) {
    if (p < r) {
        /* find index q, such that every element in arr[p, q] is less than or equal to every element in arr[q + 1, r] */
        int q = partition(arr, p, r);
        /* recursively call quicksort on both sub-arrays */
        quick_sort(arr, p, q);
        quick_sort(arr, q + 1, r);
    }
}

void hybrid_quick_sort(int arr[], int p, int r, int threshold) { // add extra "threshold parameter to test multiple thresholds
    while (p < r) {
        if (r - p + 1 < threshold) { // if in threshold, sort using insertion sort
            insertion_sort(arr + p, r - p + 1);
            break;
        }

        else {
            int q = partition(arr, p, r);
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

int main(void) {
    clock_t start, end;
    double time_taken;

    /* quicksort on 1,000,000 already sorted elements */
    int n1 = 100000;
    int input1[n1];
    parse_file("ordered100000.txt", input1, n1);

    start = clock();

    quick_sort(input1, 0, n1 - 1);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("quicksort(100000 sorted): %8fs\n", time_taken);

    /* quicksort on 1,000,000 randomly ordered elements */
    int n2 = 100000;
    int input2[n2];
    parse_file("shuf100000.txt", input2, n2);

    start = clock();

    quick_sort(input2, 0, n2 - 1);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("quicksort(100000 unsorted): %8fs\n", time_taken);

    // C++ Sorting algorithm switches at 16
    /* hybrid quick sort on 1,000,000 already sorted elements with threshold 16 */
    start = clock();
    hybrid_quick_sort(input1, 0, n1 - 1, 16);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("hybrid_quicksort_16(1000000 sorted): %8fs\n", time_taken);

    /* hybrid quick sort on 1,000,000 randomly ordered elements with threshold 16 */
    start = clock();
    hybrid_quick_sort(input2, 0, n2 - 1, 16);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("hybrid_quicksort_16(1000000 unsorted): %8fs\n", time_taken);

    /* hybrid quick sort on 1,000,000 already sorted elements with threshold 32 */
    start = clock();
    hybrid_quick_sort(input1, 0, n1 - 1, 32);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("hybrid_quicksort_32(1000000 sorted): %8fs\n", time_taken);

    /* hybrid quick sort on 1,000,000 randomly ordered elements with threshold 32 */
    start = clock();
    hybrid_quick_sort(input2, 0, n2 - 1, 32);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("hybrid_quicksort_32(1000000 unsorted): %8fs\n", time_taken);

    // Java Quicksort switches at 44
    /* hybrid quick sort on 1,000,000 already sorted elements with threshold 44 */
    start = clock();
    hybrid_quick_sort(input1, 0, n1 - 1, 16);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("hybrid_quicksort_44(1000000 sorted): %8fs\n", time_taken);

    /* hybrid quick sort on 1,000,000 randomly ordered elements with threshold 44 */
    start = clock();
    hybrid_quick_sort(input2, 0, n2 - 1, 16);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("hybrid_quicksort_44(1000000 unsorted): %8fs\n", time_taken);

    return 0;
}
