// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef char String[50];

void heap_sort(int[], int, String);
void heapify(int[], int, int, String);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Heap Sort - Min
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Heap Sort (Min):\n");
    heap_sort(arr, arr_size, "min");
    print_array(arr, arr_size);

    // Heap Sort - Max
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Heap Sort (Max):\n");
    heap_sort(arr, arr_size, "max");
    print_array(arr, arr_size);

    return 0;
}

void heapify(int arr[], int size, int parent, String type){
    int LC = 2 * parent + 1;
    int RC = LC + 1;
    int to_change = parent;
   
    int is_max = (strcmp(type, "max") == 0) ? 1 : 0;

    if (LC < size) {
        if ((is_max && arr[LC] > arr[to_change]) || (!is_max && arr[LC] < arr[to_change])) {
            to_change = LC;
        }
    }
    
    if (RC < size) {
        if ((is_max && arr[RC] > arr[to_change]) || (!is_max && arr[RC] < arr[to_change])) {
            to_change = RC;
        }
    }
   
    if (to_change != parent){
        swap(&arr[to_change], &arr[parent]);
        heapify(arr, size, to_change, type);
    }
}

void heap_sort(int arr[], int size, String type){
    int x;
   
    for(x = (size - 1) / 2; x >= 0; x--){
        heapify(arr, size, x, type);
    }
   
    for (x = size - 1; x > 0; x--) {
        swap(&arr[0], &arr[x]);
        heapify(arr, x, 0, type);
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