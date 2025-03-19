// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

void merge(int[], int, int, int);
void merge_sort(int[], int, int);
void print_array(int[], int);
void swap(int*, int*);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Merge Sort
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Merge Sort:\n");
    merge_sort(arr, 0, arr_size - 1);
    print_array(arr, arr_size);


    return 0;
}

void merge(int arr[], int left, int middle, int right){
    int x, y, z;
    int size = middle - left + 1, size_2 = right - middle; 

    int temp_arr[size], temp_arr_2[size_2];

    // Copy elements from arr to temp arrs
    for(x = 0; x < size; x++){
        temp_arr[x] = arr[left + x];
    }

    for (y = 0; y < size_2; y++){
        temp_arr_2[y] = arr[middle + 1 + y];
    }

    x = y = 0;
    z = left;

    while (x < size && y < size_2){
        arr[z++] = (temp_arr[x] < temp_arr_2[y] ? temp_arr[x++] : temp_arr_2[y++]);
    }

    int *remaining_arr = temp_arr;
    
    while (x < size){
        arr[z++] = temp_arr[x++];
    }

    while (y < size_2){
        arr[z++] = temp_arr_2[y++];
    }
}


void merge_sort(int arr[], int left, int right){
    if (left < right){
        int middle = (left + right) / 2;

        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);

        merge(arr, left, middle, right);
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