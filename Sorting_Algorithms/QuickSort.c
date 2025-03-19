// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define EMPTY -1000

typedef char String[50];

void quick_sort(int[], int, int, String);
void print_array(int[], int);
void initialize_array(int[], int);
int lomutoPartition(int[], int, int);
int hoarePartition(int[], int, int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Quick Sort - Lomuto
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Quick Sort (Lomuto):\n");
    quick_sort(arr, 0, arr_size - 1, "lomuto");
    print_array(arr, arr_size);

    // Quick Sort - Hoare
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Quick Sort (Hoare):\n");
    quick_sort(arr, 0, arr_size - 1, "hoare");
    print_array(arr, arr_size);

    return 0;
}

void quick_sort(int arr[], int low, int high, String partitionAlgo){
    if (low < high){
        int partitionNdx = 0;
   
        if (strcmp(partitionAlgo, "hoare") == 0){
            partitionNdx = hoarePartition(arr, low, high);
        }else{
            partitionNdx = lomutoPartition(arr, low, high) - 1;
        }
       
        quick_sort(arr, low, partitionNdx, partitionAlgo);
        quick_sort(arr, partitionNdx + 1, high, partitionAlgo);
    }
}

int lomutoPartition(int arr[], int low, int high){
    int pivot = arr[high];
   
    int x = low - 1, y;
    for(y = low; y <= high; y++){
        if (arr[y] <= pivot){
            swap(&arr[++x], &arr[y]);
        }
    }
   
    return x;
}

int hoarePartition(int arr[], int low, int high){
    int pivot = arr[low];
   
    int x = low - 1, y = high + 1;
   
    while(1){
        for(x++; x <= high && arr[x] < pivot; x++){}
        for(y--; y >= low && arr[y] > pivot; y--){}

        if (x >= y)
            return y;

        swap(&arr[x], &arr[y]);
    }
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