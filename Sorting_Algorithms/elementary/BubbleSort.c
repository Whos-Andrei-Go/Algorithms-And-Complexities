// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void bubble_sort(int[], int);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Bubble Sort
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Bubble Sort:\n");
    bubble_sort(arr, arr_size);
    print_array(arr, arr_size);

    return 0;
}

void bubble_sort(int arr[], int size){
    int x, y;
    bool swapped = true;
    
    for(x = 0; swapped && x < size - 1; x++){
        swapped = false;

        for(y = 0; y < size - x - 1; y++){
            if (arr[y] > arr[y + 1]){
                swap(&arr[y], &arr[y + 1]);
                swapped = true;
            }
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