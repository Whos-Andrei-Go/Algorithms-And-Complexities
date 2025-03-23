#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ORDER 3

typedef struct node{
    int keys[2 * ORDER - 1];
    struct node *children[2 * ORDER];
    struct node *next;
    int numKeys;
    int leaf; // 1 if leaf
}*Node;

Node createNode(int);
void traverse(Node);
Node search(Node, int);
void insert(Node*, int);
void insertNonFull(Node, int);
void splitChild(Node, int, Node);
int isFull(Node);

int main() {
    Node root = createNode(1);

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 31, 28};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++) {
        insert(&root, keys[i]);
    }

    printf("B-Tree traversal: ");
    traverse(root);
    printf("\n");

    int searchKey = 12;
    Node found = search(root, searchKey);

    if (found != NULL) {
        printf("Key %d found in the B-Tree.\n", searchKey);
    } else {
        printf("Key %d not found in the B-Tree.\n", searchKey);
    }

    return 0;
}

Node createNode(int leaf){
    Node node = (Node) malloc(sizeof(struct node));
    node -> leaf = leaf;
    node -> numKeys = 0;
    node -> next = NULL;

    int x;
    for(x = 0; x < 2 * ORDER; x++){
        node -> children[x] = NULL;
    }

    return node;
}

Node search(Node root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && key == root->keys[i]) {
        return root;
    }
    if (root->leaf) {
        return NULL;
    }
    return search(root->children[i], key);
}

void splitChild(Node parent, int x, Node child){
    Node newChild = createNode(child -> leaf);
    newChild -> numKeys = ORDER - 1;

    int y;
    for(y = 0; y < ORDER - 1; y++){
        newChild -> keys[y] = child -> keys[y + ORDER];
    }

    if (!(child -> leaf)){
        for(y = 0; y < ORDER; y++){
            newChild -> children[y] = child -> children[y + ORDER];
        }
    }

    child -> numKeys = ORDER - 1;

    for(y = parent -> numKeys; y > x; y--){
        parent -> children[y + 1] = parent -> children[y];
    }

    parent -> children[y + 1] = newChild;

    for (y = parent-> numKeys - 1; y >= x; y--) {
        parent->keys[y + 1] = parent->keys[y];
    }

    parent->keys[x] = child->keys[ORDER - 1];
    parent->numKeys++;
}

void insertNonFull(Node node, int key){
    int x = (node -> numKeys) - 1;

    if (node -> leaf){
        for(; x >= 0 && key < node -> keys[x]; x--){
            node -> keys [x + 1] = node -> keys[x];
        }
        node -> keys[x + 1] = key;
        (node -> numKeys)++;
    }else{
        for(; x >= 0 && key < node -> keys[x]; x--){}
        x++;

        if (isFull(node -> children[x])){
            splitChild(node, x, node -> children[x]);

            if (key > node -> keys[x]){
                x++;
            }
        }

        insertNonFull(node -> children[x], key);
    }
}

void insert(Node* root, int key) {
    if (isFull(*root)) {
        Node newRoot = createNode(0);
        newRoot->children[0] = *root;
        splitChild(newRoot, 0, *root);
        
        int x = (key > newRoot->keys[0]) ? 1 : 0;
        insertNonFull(newRoot->children[x], key);

        *root = newRoot;
    } else {
        insertNonFull(*root, key);
    }
}

void traverse(Node node){
    if (node != NULL){
        int x;
        for(x = 0; x < node -> numKeys; x++){
            if (!node->leaf) {
                traverse(node->children[x]);
            }
                
        } 

        if (node->leaf) {
            for (x = 0; x < node->numKeys; x++) {
                printf("%d ", node->keys[x]);
            }
        }

        if (!(node -> leaf)){
            traverse(node -> children[x]);
        }
    }
}

int isFull(Node node){
    return (node -> numKeys) == 2 * ORDER - 1;
}