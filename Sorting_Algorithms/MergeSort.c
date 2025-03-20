// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef char* String;

void merge(int[], int, int, int);
void merge_sort(int[], int, int, String);
void print_array(int[], int);
void swap(int*, int*);
int min(int, int);

int main() {
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 231, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);
    
    // Merge Sort - Top Down
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Merge Sort (Top Down):\n");
    merge_sort(arr, 0, arr_size - 1, "topdown");
    print_array(arr, arr_size);

      // Merge Sort - Bottom Up
      memcpy(arr, original_arr, sizeof(original_arr));
      printf("Merge Sort (Bottom Up):\n");
      merge_sort(arr, 0, arr_size - 1, "bottomup");
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

    while (x < size){
        arr[z++] = temp_arr[x++];
    }

    while (y < size_2){
        arr[z++] = temp_arr_2[y++];
    }
}


void merge_sort(int arr[], int left, int right, String type){
    if (left < right){
        if (strcmp(type, "topdown") == 0){
            int middle = (left + right) / 2;

            merge_sort(arr, left, middle, type);
            merge_sort(arr, middle + 1, right, type);

            merge(arr, left, middle, right);
        }else{
            int cur_size, size = right + 1;
            for (int cur_size = 1; cur_size < size; cur_size *= 2) {
                for (int left_start = left; left_start < right; left_start += 2 * cur_size) {
                    int mid = min(left_start + cur_size - 1, right);
                    int right_end = min(left_start + 2 * cur_size - 1, right);
    
                    if (mid < right_end) {
                        merge(arr, left_start, mid, right_end);
                    }
                }
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

int min(int a, int b) {
    return (a < b) ? a : b;
}
