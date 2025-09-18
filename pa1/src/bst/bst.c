#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// node structure for bst
struct Node {
    int info;
    struct Node *left;
    struct Node *right;
};

int delete(struct Node **root, int value);
int insert(struct Node **root, int value);
int search(struct Node *root, int value);
void freeSpace(struct Node *root);
void printTree(struct Node *root);

/*struct Node* createNode(int num) {
    struct Node* curr = (struct Node*)malloc(sizeof(struct Node));
    curr->info = num;
    curr->left = NULL;
    curr->right = NULL;
    return curr;
 
}*/ 

/*
int insert(struct Node **rootNode, int value){
    if (rootNode == NULL) {
        createNode(value);
        return 1;
    }
    
    if (value < (*rootNode)->info) {
        return insert(&((*rootNode)->left), value);
    } 
    else if (value > (*rootNode)->info) {
        return insert(&((*rootNode)->right), value);
    }
    else{
    return 0;
    }
} */

// New insert 

int insert(struct Node **root, int value) {
    struct Node *current = *root;
    struct Node *parent = NULL;

    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->info = value;
    newNode->left = newNode->right = NULL;

    if (current == NULL) {
        *root = newNode;
        return 1; 
    }

    while (current != NULL) {
        parent = current;
        if (value < current->info) {
            current = current->left;
        } else if (value > current->info) {
            current = current->right;
        } else {
            free(newNode);
            return 0;
        }
    }

    if (value < parent->info) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return 1; 
} 

//search function
int search(struct Node *rootNode, int num) {
    while (rootNode != NULL) {
        if (num < rootNode->info) {
            rootNode = rootNode->left;
        } 
        else if (num > rootNode->info) {
            rootNode = rootNode->right;
        } 
        else {
            return 1;  

        }
    }
    return 0;  
}

//print
void printTree(struct Node *rootNode) {
    if (rootNode == NULL) {
        printf("");
        return; 
    }
    printf("(");

    printTree(rootNode->left);
    printf("%d", rootNode->info);
    printTree(rootNode->right); 

    printf(")");
}


int delete(struct Node **rootNode, int num) {
    if (*rootNode == NULL) {
        return 0; 
    }

    struct Node *curr = *rootNode;
    //searching jawn
    if (num < curr->info) {
        return delete(&(curr->left), num); 
    } 
    else if (num > curr->info) {
        return delete(&(curr->right), num);
    } 
    else {
        struct Node *tempNode = curr;
        //Leaf node i
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            *rootNode = NULL;
        }
        //one child right
        else if (curr->left == NULL) {
            *rootNode = curr->right;
            free(tempNode);
        }
        //one child left
        else if (curr->right == NULL) {

            *rootNode = curr->left;
            free(tempNode);
        }
        //two children
        else {
            struct Node *succ = curr->left;
            struct Node *parent = curr;

            while (succ->right != NULL) {
                
                parent = succ;
                succ = succ->right;

            }

            curr->info = succ->info;

            if (parent == curr) {
                parent->left = succ->left;  

            } else {
                parent->right = succ->left;

            }
            free(succ);
        }

        return 1; 
    }
}

void freeSpace(struct Node *root) {
    if (root == NULL) {
        return;
    }

    freeSpace(root->left);
    freeSpace(root->right);
    free(root);
}
//main function
int main() {
    struct Node *rootNode = NULL;
    int num;
    char direction;

    while (scanf(" %c", &direction) == 1) {
        if (direction == 'i' || direction == 's' || direction == 'd') {
            if (scanf("%d", &num) != 1) {
                continue;  
            }
        }
        //Inserting
        if (direction == 'i') {
            if (insert(&rootNode, num)) {
                printf("inserted\n");
            } 
            else {
                printf("not inserted\n");
            }
        }
        //Searching
        else if (direction == 's') {
            if (search(rootNode, num)) {
                printf("present\n");
            } 
            else {
                printf("absent\n");
            }
        }
        //Printing
        else if (direction == 'p') {
            printTree(rootNode);
            printf("\n");
        }
        else if (direction == 'd') {
            if (delete(&rootNode, num)) {
                printf("deleted\n");
            } 
            else {
                printf("absent\n");
            }
        }
    }
    freeSpace(rootNode);  
    return 0;
}