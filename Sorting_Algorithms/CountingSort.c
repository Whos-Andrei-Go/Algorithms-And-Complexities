// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void counting_sort(int[], int);
void counting_sort_no_cum_sum(int[], int);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    // Adjusted the data to fit for this
    int original_arr[] = {0, 1, 4, 3, 1, 2, 3, 2, 2, 5, 6, 4, 0, 0, 8, 5};
    int arr[] = {0, 1, 4, 3, 1, 2, 3, 2, 2, 5, 6, 4, 0, 0, 8, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Counting Sort
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Counting Sort:\n");
    counting_sort(arr, arr_size);
    print_array(arr, arr_size);

    // Counting Sort - No cumulative_sum
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Counting Sort (No Cumulative Sum):\n");
    counting_sort_no_cum_sum(arr, arr_size);
    print_array(arr, arr_size);

    return 0;
}

void counting_sort(int arr[], int size){
    // Find max value;
    int x, max = 0;

    for(x = 0; x < size; x++){
        if (arr[x] > max){
            max = arr[x];
        }
    }

    int *count_array = (int*) calloc((max + 1), sizeof(int));
    int *output_array = (int*) malloc(sizeof(int) * size);

    for(x = 0; x < size; x++){
        count_array[arr[x]]++;
    }

    for(x = 1; x <= max; x++){
        count_array[x] += count_array[x - 1];
    }
       

    for(x = size - 1; x >= 0; x--){
        output_array[count_array[arr[x]] - 1] = arr[x];
        count_array[arr[x]]--;
    }

    for (x = 0; x < size; x++)
        arr[x] = output_array[x];

    free(output_array);
    free(count_array);
}

void counting_sort_no_cum_sum(int arr[], int size){
    // Find max value;
    int x, max = 0;

    for(x = 0; x < size; x++){
        if (arr[x] > max){
            max = arr[x];
        }
    }

    int *count_array = (int*) malloc(sizeof(int) * (max + 1));

    for(x = 0; x <= max; x++){
        count_array[x] = 0;
    }

    for(x = 0; x < size; x++){
        count_array[arr[x]]++;
    }

    int y = 0;
    for (x = 0; x <= max; x++) {
        while (count_array[x] > 0) {
            arr[y++] = x;
            count_array[x]--;
        }
    }

    free(count_array);
}

void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}