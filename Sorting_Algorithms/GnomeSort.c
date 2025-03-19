// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

void gnome_sort(int[], int);
void gnome_sort_memoization(int[], int);
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
    printf("Gnome Sort:\n");
    gnome_sort_memoization(arr, arr_size);
    print_array(arr, arr_size);

    return 0;
}

void gnome_sort(int arr[], int size){
    int x = 1;
    
    while (x < size){
        if (x > 0 && arr[x] < arr[x - 1]){
            swap(&arr[x], &arr[x - 1]);
            x--;
        }else{
            x++;
        }
    }
}

void gnome_sort_memoization(int arr[], int size){
    int x = 1, prev = 0;
    
    while (x < size){
        if (x > 0 && arr[x] < arr[x - 1]){
            swap(&arr[x], &arr[x - 1]);

            if (prev == 0){
                prev = x;
            }
           
            x--;
        }else{
            if (x == 0){
                x = prev;
                prev = 0;
            }
           
            x++;
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