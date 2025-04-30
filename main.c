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

    int n = 100000;

    /* quicksort on 100,000 already sorted elements */
    int input1[n];
    parse_file("ordered100000.txt", input1, n);

    start = clock();
    quick_sort(input1, 0, n - 1);
    end = clock();
    printf("quicksort(100000 sorted): %8fs\n",
           seconds_taken(start, end));

    /* quicksort on 100,000 randomly ordered elements */
    int input2[n];
    parse_file("shuf100000.txt", input2, n);

    start = clock();
    quick_sort(input2, 0, n - 1);
    end = clock();
    printf("quicksort(100000 unsorted): %8fs\n",
           seconds_taken(start, end));

    // C++ Sorting algorithm switches at 16
    /* hybrid quick sort on 100,000 already sorted elements with threshold 16 */
    int input3[n];
    parse_file("ordered100000.txt", input3, n);

    start = clock();
    hybrid_quick_sort(input3, 0, n - 1, 16);
    end = clock();
    printf("hybrid_quicksort_16(100000 sorted): %8fs\n",
           seconds_taken(start, end));

    /* hybrid quick sort on 100,000 randomly ordered elements with threshold 16 */
    int input4[n];
    parse_file("shuf100000.txt", input4, n);

    start = clock();
    hybrid_quick_sort(input4, 0, n - 1, 16);
    end = clock();
    printf("hybrid_quicksort_16(100000 unsorted): %8fs\n",
           seconds_taken(start, end));

    /* hybrid quick sort on 100,000 already sorted elements with threshold 32 */
    int input5[n];
    parse_file("ordered100000.txt", input5, n);

    start = clock();
    hybrid_quick_sort(input5, 0, n - 1, 32);
    end = clock();
    printf("hybrid_quicksort_32(100000 sorted): %8fs\n",
           seconds_taken(start, end));

    /* hybrid quick sort on 100,000 randomly ordered elements with threshold 32 */
    int input6[n];
    parse_file("shuf100000.txt", input6, n);

    start = clock();
    hybrid_quick_sort(input6, 0, n - 1, 32);
    end = clock();
    printf("hybrid_quicksort_32(100000 unsorted): %8fs\n",
           seconds_taken(start, end));

    // Java Quicksort switches at 44
    /* hybrid quick sort on 100,000 already sorted elements with threshold 44 */
    int input7[n];
    parse_file("ordered100000.txt", input7, n);

    start = clock();
    hybrid_quick_sort(input7, 0, n - 1, 44);
    end = clock();
    printf("hybrid_quicksort_44(100000 sorted): %8fs\n",
           seconds_taken(start, end));

    /* hybrid quick sort on 100,000 randomly ordered elements with threshold 44 */
    int input8[n];
    parse_file("shuf100000.txt", input8, n);

    start = clock();
    hybrid_quick_sort(input8, 0, n - 1, 44);
    end = clock();
    printf("hybrid_quicksort_44(100000 unsorted): %8fs\n",
           seconds_taken(start, end));

    return 0;
}
