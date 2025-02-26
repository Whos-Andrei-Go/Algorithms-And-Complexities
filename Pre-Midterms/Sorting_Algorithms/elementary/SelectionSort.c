// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

void selection_sort_min(int[], int);
void selection_sort_max(int[], int);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Selection Sort Min
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Selection Sort (Min):\n");
    selection_sort_min(arr, arr_size);
    print_array(arr, arr_size);

    // Selection Sort Max
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Selection Sort (Max):\n");
    selection_sort_max(arr, arr_size);
    print_array(arr, arr_size);

    return 0;
}

void selection_sort_min(int arr[], int size){
    int x, y;
    
    for(x = 0; x < size - 1; x++){
        int minNdx = x; 

        for(y = x + 1; y < size; y++){
            if (arr[y] < arr[minNdx]){
                minNdx = y;
            }
        }

        if (minNdx != x){
            swap(&arr[minNdx], &arr[x]);
        }
    }
}

void selection_sort_max(int arr[], int size){
    int x, y;
    
    for(x = size - 1; x > 0; x--){
        int maxNdx = x; 

        for(y = x - 1; y >= 0; y--){
            if (arr[y] > arr[maxNdx]){
                maxNdx = y;
            }
        }

        if (maxNdx != x){
            swap(&arr[maxNdx], &arr[x]);
        }
    }
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