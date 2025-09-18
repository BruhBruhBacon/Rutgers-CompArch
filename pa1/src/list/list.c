#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int info;
    struct Node* next;
};

struct Node* createNode(int num) {
    struct Node* newNode = malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }

    newNode->info = num;
    newNode->next = NULL;
    //printf("cn %d",newNode->info);
    return newNode;
}

void MakeSorted(struct Node **head,int num){
    struct Node *checker = *head;
    while (checker != NULL) {
        if (num == checker->info) {
            return;
        }
        checker = checker->next;
    }
    //printf("ms %d", num);
    //Check if it is a repeat firstly
    struct Node *nod =createNode(num);    

    if(*head == NULL || (*head)->info > nod->info){
        nod ->next = *head;
        *head = nod;
        //printf("%d",nod->info);
    }
    else{
        struct Node* check = *head;
        //printf("%d",nod->info);
        while (check != NULL) {
            if(num == check->info){
        //         printf("checking same %d",check->info);
                return;
            }
            check = check->next;
        } 
        //printf("\n"); 

        struct Node* current = *head;
        //find position where new node is greater than current or reach end
        while(current->next != NULL && current->next->info < nod->info){
            current = current->next;
        }
        nod->next = current->next;
        current->next = nod;
    }
}

void deleteNode(struct Node **head,int num){
    
    struct Node *curr = *head;
    struct Node *prev = NULL;

    if(curr == NULL){
        return;
    }

    //Checks if its head node
    if(curr->info == num){
        *head = curr->next;
        free(curr);
        return;
    }

    
    //skips over deleted nod in LL
    while (curr != NULL && curr->info != num) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        return;
    }
    prev->next = curr->next;
    free(curr);    
}

int checkRepeat(struct Node *head,int num){
    struct Node* curr = head;
    //printf("%d",head->info);
    while (curr != NULL) {
        if(num == curr->info){
   //         printf("checking same %d",curr->info);
            return 1;
        }
        curr = curr->next;
    }
    //printf("\n");
    return 0;
}

void printList(struct Node* head) {
    int len = 0;
    struct Node* curr = head;
    while (curr != NULL) {
        //printf("tick ");
        len++;
        curr = curr->next;
    }
    curr = head;
    printf("%d :",len);
    while (curr != NULL) {
        //printf("smach");
        printf(" %d",curr->info);
        curr = curr->next;
    }
    printf("\n");
    
}

int main(){
struct Node* head = NULL; 
    char nodChanger;
    int num;

    while (scanf(" %c %d", &nodChanger, &num) == 2) {  
        if (nodChanger == 'i') {
            MakeSorted(&head, num);
        } else if (nodChanger == 'd') {
            deleteNode(&head, num);  
        }
        printList(head);
    }

    struct Node* curr = head;
    while (curr != NULL) {
        struct Node* temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}