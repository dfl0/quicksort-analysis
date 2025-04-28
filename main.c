#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

int main(void) {
    /* short example input */
    int arr[] = { 3, 9, 1, 6, 0, 8, 2, 5, 4, 7 };
    int n = 10;

    printf("unsorted: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    quick_sort(arr, 0, n - 1);

    printf("sorted:   ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
