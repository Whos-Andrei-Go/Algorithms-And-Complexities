// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BUCKETS 10

typedef struct node{
    int data;
    struct node *next;
} *List;

typedef char String[50];

void radix_sort_msd(int[], int);
void radix_sort_msd_helper(int[], int, int);
void radix_sort_lsd(int[], int);
void insert_sorted_ll(List*, List);
void print_array(int[], int);
void swap(int*, int*);
void print_ll(List);
void array_to_ll(int[], int, List*);

int main() {
    List ll = NULL;

    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 121, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 121, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);

    // Radix Sort - LSD
    printf("Radix Sort (LSD):\n");
    radix_sort_lsd(arr, arr_size);
    print_array(arr, arr_size);

    // Radix Sort - MSD
    memcpy(arr, original_arr, sizeof(original_arr));
    printf("Radix Sort (MSD):\n");
    radix_sort_msd(arr, arr_size);
    print_array(arr, arr_size);


    return 0;
}

void radix_sort_lsd(int arr[], int size){
    List* buckets = (List*) malloc(sizeof(List) * NUM_BUCKETS);
    if (buckets != NULL){
        int x, max_val = INT_MIN;
        int exp;

        // Find maximum value
        for(x = 0; x < size; x++){
            if (arr[x] > max_val){
                max_val = arr[x];
            }
        }

        for (exp = 1; max_val / exp > 0; exp *= 10){
            for(x = 0; x < NUM_BUCKETS; x++){
                buckets[x] = NULL;
            }

            for(x = 0; x < size; x++){
                List new_node = (List) malloc(sizeof(struct node));
                if (new_node != NULL){
                    int bucket_ndx = (arr[x] / exp) % 10;
                    new_node -> data = arr[x];
                    new_node -> next = NULL;
    
                    insert_sorted_ll(&buckets[bucket_ndx], new_node);
                }
            }

            int y = 0;
            for(x = 0; x < NUM_BUCKETS; x++){
                List trav = buckets[x];

                while(trav != NULL){
                    arr[y++] = trav -> data;
                    List temp = trav;
                    trav = trav -> next;
                    free(temp);
                }
            }
        } 
    }    
}

void radix_sort_msd(int arr[], int size){
    int x, max_val = INT_MIN;
    int exp = 1;

    // Find maximum value
    for(x = 0; x < size; x++){
        if (arr[x] > max_val){
            max_val = arr[x];
        }
    }

    while (max_val / exp >= 1) {
        exp *= 10;
    }
    
    exp /= 10; // divide by 10 for actual exponent

    radix_sort_msd_helper(arr, size, exp);
}
void radix_sort_msd_helper(int arr[], int size, int exp){
    List* buckets = (List*) malloc(sizeof(List) * NUM_BUCKETS);
    if (buckets != NULL && exp > 0){
        int x, bucket_sizes[NUM_BUCKETS];

        for(x = 0; x < NUM_BUCKETS; x++){
            buckets[x] = NULL;
            bucket_sizes[x] = 0;
        }

        for(x = 0; x < size; x++){
            List new_node = (List) malloc(sizeof(struct node));
            if (new_node != NULL){
                int bucket_ndx = (arr[x] / exp) % 10;
                // printf("INSERTING %d IN BUCKET %d\n", arr[x], bucket_ndx);
                new_node -> data = arr[x];
                new_node -> next = NULL;

                insert_sorted_ll(&buckets[bucket_ndx], new_node);
                bucket_sizes[bucket_ndx]++;
            }
        }

        int y2 = 0, z = 0;
        for(x = 0; x < NUM_BUCKETS; x++){
            int y = 0;

            if (bucket_sizes[x] > 0){
                List trav = buckets[x];
                // print_ll(trav);
                int bucket_size = bucket_sizes[x];
                int *bucket_arr = (int*) malloc(sizeof(int) * bucket_size);
                
                while(trav != NULL){
                    bucket_arr[y++] = trav -> data;
                    List temp = trav;
                    trav = trav -> next;
                    free(temp);
                }

                radix_sort_msd_helper(bucket_arr, bucket_size, exp / 10);

                for (z = 0; z < bucket_size; z++) {
                    arr[y2++] = bucket_arr[z];
                }

                free(bucket_arr);
            }
        }
    }   
}

void insert_sorted_ll(List *ll, List to_insert){
    List* trav;

    for(trav = ll; *trav != NULL && (*trav) -> data <= to_insert -> data; trav = &((*trav) -> next)){}

    to_insert -> next = *trav;
    *trav = to_insert;
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

void print_ll(List ll) {
    List trav;

    for(trav = ll; trav != NULL; trav = trav -> next){
        printf("%d", trav -> data);
        if (trav -> next != NULL){
            printf(" -> ");
        }
    }

    printf("\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void array_to_ll(int arr[], int size, List *ll){
    int x;

    for(x = size - 1; x >= 0; x--){
        List new_node = (List) malloc(sizeof(struct node));

        if (new_node != NULL){
            new_node -> data = arr[x];
            new_node -> next = *ll;
    
            *ll = new_node; 
        }
    }
}