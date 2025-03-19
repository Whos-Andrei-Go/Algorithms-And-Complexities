// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define EMPTY -1000
#define INFINITY INT_MAX

void tournament_sort_offline(int[], int);
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
    
    // Tournament Sort (Offline)
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Tournament Sort (Offline):\n");
    tournament_sort_offline(arr, arr_size);
    print_array(arr, arr_size);

     // Tournament Sort (Online)
     memcpy(arr, original_arr, sizeof(original_arr));
     printf("Tournament Sort (Online):\n");
     tournament_sort_online(arr, arr_size);
     print_array(arr, arr_size);
 

    return 0;
}

void tournament_sort_offline(int arr[], int size){
    int tree_size = 2 * size - 1;
    int x, y;

    int tree[tree_size];
    int temp[size];

    memcpy(temp, arr, size * sizeof(int));

    for(x = size; x < tree_size; x++){
        tree[x] = x - size;
    }

    int start = tree_size - 1, right, left, parent;

    for(x = 0; x < size; x++){
        for(right = start; right > 0; right -= 2){
            left = right - 1;
            parent = left / 2;

            if (temp[tree[left]] <= temp[tree[right]]){
                tree[parent] = tree[left];
            }else{
                tree[parent] = tree[right];
            }
        }

        arr[x] = temp[tree[0]];
        temp[tree[0]] = INFINITY;

        // start = (tree_size - (size - tree[0]) - 1) / 2 * 2 + 2;
    }
}

void tournament_sort_online(int arr[], int size) {
    int tree_size = 7;
    int x, sort_ndx = -1, disqualified_ndx = -1;
    int start = tree_size - 1;
    int right, left, parent;
    int tree_is_empty = 0;

    // Memory allocation
    int *tree = (int*) malloc(sizeof(int) * tree_size);
    int *temp = (int*) malloc(sizeof(int) * size);
    int *sorted_arr = (int*) malloc(sizeof(int) * size);
    int *disqualified = (int*) malloc(sizeof(int) * size);
    int *merged = (int*) malloc(sizeof(int) * size);

    // Proceed only if all allocations succeed
    if (tree != NULL && temp != NULL && sorted_arr != NULL && disqualified != NULL && merged != NULL) {

        // Copy array to temp storage
        for (x = 0; x < size; x++) {
            temp[x] = arr[x];
        }

        // Sets the value of the leaves to the element in temp
        for (x = 0; x < 4; x++) {
            tree[x + 3] = (x < size && temp[x] != INFINITY) ? temp[x] : INFINITY;
        }

        // Initialize tree root
        tree[0] = 0;

        // Tournament selection loop
        while (tree_is_empty == 0) {
            // Build tournament tree
            for (right = start; right > 0; right -= 2) {
                left = right - 1;
                parent = left / 2;

                if (right >= 3) {
                    tree[parent] = (tree[left] <= tree[right]) ? left : right;
                    // printf("CURRENT PARENT IS NOW SET TO %d \n", tree[parent]);
                } else {
                    tree[parent] = (tree[tree[left]] <= tree[tree[right]]) ? tree[left] : tree[right];
                    // printf("INNER PARENT IS NOW SET TO %d \n", tree[parent]);
                }
            }

            // Extract winner
            if (tree[tree[0]] != INFINITY) {
                // printf("WINNER IS %d \n", tree[tree[0]]);
                sorted_arr[++sort_ndx] = tree[tree[0]];

                // Move elements smaller than the winner to disqualified array
                for (; x < size && temp[x] < sorted_arr[sort_ndx]; x++) {
                    disqualified[++disqualified_ndx] = temp[x];
                }

                // Insert next element from temp into the tree
                if (x < size) {
                    if (temp[x] != INFINITY) {
                        tree[tree[0]] = (temp[x] >= sorted_arr[sort_ndx]) ? temp[x] : INFINITY;
                        // printf("INSERTED %d \n", tree[tree[0]]);
                    } else {
                        tree[tree[0]] = INFINITY;
                        // printf("INSERTED INFINITY\n");
                    }
                    x++;
                } else {
                    tree[tree[0]] = INFINITY;
                    // printf("INSERTED INFINITY\n");
                }
            } else {
                tree_is_empty = 1;
            }
        }

        // Handle disqualified elements recursively
        if (disqualified_ndx > 0) {
            // printf("CURRENT DISQUALIFIED ARRAY: \n");
            // print_array(disqualified, size);

            tournament_sort_online(disqualified, disqualified_ndx);

            // printf("NEW DISQUALIFIED ARRAY: \n");
            // print_array(disqualified, size);

            merge_array(sorted_arr, sort_ndx + 1, disqualified, disqualified_ndx + 1, merged);
            memcpy(sorted_arr, merged, sizeof(int) * size);
        }

        // Copy sorted values back to original array
        memcpy(arr, sorted_arr, sizeof(int) * size);
    }

    // Free allocated memory
    free(tree);
    free(temp);
    free(sorted_arr);
    free(disqualified);
    free(merged);
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

void build_winner_tree(int *tree, int *temp, int size, int tree_size){

}