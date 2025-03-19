// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void comb_sort(int[], int);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Comb Sort
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Comb Sort:\n");
    comb_sort(arr, arr_size);
    print_array(arr, arr_size);

    return 0;
}

void comb_sort(int arr[], int size){
    int x, gap = size;
    bool swapped = true;
    
    do{
        gap = (gap * 10) / 13;

        if (gap < 1){
            gap = 1;
        }

        swapped = false;

        for(x = 0; x < size - gap; x++){
            if (arr[x] > arr[x + gap]){
                swap(&arr[x], &arr[x + gap]);
                swapped = true;
            }
        }
    }while (gap > 1 || swapped);
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