// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BUCKETS 10

typedef struct node{
    int data;
    struct node *next;
} *List;

void bucket_sort(int[], int);
void insert_sorted_ll(List*, List);
void print_array(int[], int);
void swap(int*, int*);
void print_ll(List);
void array_to_ll(int[], int, List*);

int main() {
    List ll = NULL;

    // Changed just to better split into buckets
    int original_arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 121, 31, 44, 67};
    int arr[] = {10, 21, 83, 45, 67, 30, 30, 27, 91, 74, 15, 105, 121, 31, 44, 67};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original Array:\n");
    print_array(arr, arr_size);

    // Bucket Sort
    printf("Bucket Sort:\n");
    bucket_sort(arr, arr_size);
    print_array(arr, arr_size);


    return 0;
}

void bucket_sort(int arr[], int size){
    List* buckets = (List*) malloc(sizeof(List) * NUM_BUCKETS);
    if (buckets != NULL){
        int x, y = 0, max_val = INT_MIN;

        for(x = 0; x < size; x++){
            if (arr[x] > max_val){
                max_val = arr[x];
            }
        }

        for(x = 0; x < NUM_BUCKETS; x++){
            buckets[x] = NULL;
        }

        for(x = 0; x < size; x++){
            List new_node = (List) malloc(sizeof(struct node));
            if (new_node != NULL){
                int bucket_ndx = (arr[x] * NUM_BUCKETS) / (max_val + 1);
                new_node -> data = arr[x];
                new_node -> next = NULL;

                insert_sorted_ll(&buckets[bucket_ndx], new_node);
            }
        }

        for(x = 0; x < NUM_BUCKETS; x++){
            List trav = buckets[x];

            while(trav != NULL){
                arr[y++] = trav -> data;
                List temp = trav;
                trav = trav -> next;
                free(temp);
            }
        }

        free(buckets);
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