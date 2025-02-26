#include <stdio.h>
#include <stdlib.h>

void BucketSort(int A[], int array_size) {
    // Find the maximum value in the array to determine the number of buckets
    int max_value = A[0];
    for (int i = 1; i < array_size; i++) {
        if (A[i] > max_value) {
            max_value = A[i];
        }
    }

    // Create buckets
    int BUCKETS = max_value / 10 + 1; // Number of buckets based on the range
    int *buckets = (int *)calloc(BUCKETS, sizeof(int)); // Allocate and initialize buckets

    // Count elements
    for (int i = 0; i < array_size; i++) {
        buckets[A[i] / 10]++; // Place in the appropriate bucket
    }

    // Reconstruct sorted array
    int index = 0;
    for (int j = 0; j < BUCKETS; j++) {
        for (int k = 0; k < buckets[j]; k++) {
            A[index++] = j * 10; // Reconstruct the sorted array
        }
    }

    // Free allocated memory
    free(buckets);
}

int main() {
    int A[] = {45, 61, 22, 25, 37, 78, 50, 33, 56, 19};
    int array_size = sizeof(A) / sizeof(A[0]);

    BucketSort(A, array_size);

    printf("Sorted array:\n");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}