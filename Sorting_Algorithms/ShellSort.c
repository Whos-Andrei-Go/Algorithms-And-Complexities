// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

void shell_sort(int[], int);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Shell Sort
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Shell Sort:\n");
    shell_sort_min(arr, arr_size);
    print_array(arr, arr_size);


    return 0;
}

void shell_sort(int arr[], int size){
    int x, y, gap;
    
    for(gap = size / 2; gap > 0; gap /= 2){
        for(x = gap; x < size; x++){
            int key = arr[x];
    
            for(y = x; y >= gap && arr[y - gap] > key; y -= gap){
                arr[y] = arr[y - gap];
            }
    
            arr[y] = key;
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