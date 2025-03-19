// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define EMPTY -1000

void strand_sort(int[], int);
void print_array(int[], int);
void initialize_array(int[], int);
void merge_array(int[], int, int[], int, int []);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Comb Sort
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Strand Sort:\n");
    strand_sort(arr, arr_size);
    print_array(arr, arr_size);

    return 0;
}

void strand_sort(int arr[], int size){
    int sorted_arr[size], strand_arr[size], merged_arr[size];
    int sorted_size = 0, strand_size = 1, x, strand_max = EMPTY;

    initialize_array(sorted_arr, size);
    initialize_array(merged_arr, size);

    while (strand_size != 0){
        strand_max = EMPTY;
        strand_size = 0;
        
        initialize_array(strand_arr, size);
    
        for(x = 0; x < size; x++){
            if (arr[x] != EMPTY && arr[x] > strand_max){
                strand_arr[strand_size++] = arr[x];
                strand_max = arr[x];
                arr[x] = EMPTY;
            }
        }

        merge_array(sorted_arr, sorted_size, strand_arr, strand_size, merged_arr);
        memcpy(sorted_arr, merged_arr, sizeof(merged_arr));
        sorted_size += strand_size;
    }
   
    memcpy(arr, sorted_arr, sizeof(sorted_arr));
}

void initialize_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = EMPTY;
    }
}

void merge_array(int arr1[], int size1, int arr2[], int size2, int merged[]) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }

    while (i < size1) {
        merged[k++] = arr1[i++];
    }

    while (j < size2) {
        merged[k++] = arr2[j++];
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