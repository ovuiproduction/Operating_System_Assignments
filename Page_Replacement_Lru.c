#include<stdio.h>
#include<stdlib.h>

struct Node{
    int page;
    struct Node *next;
};

struct Node* head = NULL;

int find_index(int target,int frame[],int fream_size){

    int size = fream_size;

    for(int i=0;i<size;i++){
        if(target == frame[i]){
            return i;
        }
    }
}

int present(int target,int frame[],int fream_size){

    int size = fream_size;

    for(int i=0;i<size;i++){
        if(target == frame[i]){
            return 1;
        }
    }
    return 0;
}

void insert(int page){

    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->page = page;
    newnode->next = NULL;

    if(head == NULL){
        head = newnode;
    }
    else{
        struct Node* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

void delete(int target){

    struct Node* temp = head;

    while(temp!= NULL){

        if(temp->page == target){

            if(temp == head){
                head = head->next;
                free(temp);
            }
            else if(temp->next == NULL){
                struct Node* prev = head;
                struct Node* curr = head;
                while(curr->next != NULL){
                    prev = curr;
                    curr = curr->next;
                }
                prev->next = NULL;
                free(temp);
            }
            else{
                struct Node* prev = head;
                struct Node* curr = head;
                while(curr != temp){
                    prev = curr;
                    curr = curr->next;
                }
                prev->next = temp->next;
                free(temp);
            }
            break;
        }
        temp = temp->next;
    }
}


int main(){

    int request_no ;
    int fream_size;
    int hit =0;
    int miss =0;

    printf("\nEnter No of pages : ");
    scanf("%d",&request_no);

    printf("\n\nEnter fream Size : ");
    scanf("%d",&fream_size);


    int request_seq[request_no];
    int frame[fream_size];

    for(int i=0;i<request_no;i++){
        printf("\nEnter page id  :");
        scanf("%d",&request_seq[i]);
    }

    for(int i=0;i<fream_size;i++){
        frame[i] = -1;
    }


    int flag = 0;
    int free_index;
    int request_count = 0;
    int pagef =0;



    for(int i=0;i<request_no;i++){

        for(int j=0;j<fream_size;j++){
            if(frame[j] == -1){
                flag = 1;
                free_index = j;
                break;
            }
        }

        if(flag == 1 && !present(request_seq[request_count],frame,fream_size)){
            pagef++;
            frame[free_index] = request_seq[request_count];
            printf("\nCash MISS\n Page  %d  is inserted",request_seq[request_count]);
            miss++;
            insert(request_seq[request_count]);
            request_count++; 

        }
        else{
            
            if(present(request_seq[request_count],frame,fream_size)){
                hit++;
                delete(request_seq[request_count]);
                insert(request_seq[request_count]);
                printf("\nCash HIT\n Page %d is Already in the page table\n\n",request_seq[request_count]);
                request_count++;
                continue;
            }
            else{
                miss++;
                int index = find_index(head->page,frame,fream_size);
                printf("\nCash MISS\n Page %d is Replaced with %d",head->page,request_seq[request_count]);
                frame[index] = request_seq[request_count];
                delete(head->page);
                insert(request_seq[request_count]);
                request_count++;
                pagef++;

            }
        }
        flag =0;
        printf("\n\n\n");
    }
    printf("\n\nTotal Number Of Page Faults are : %d\n\n",pagef);

    printf("\n\nTotal Number Of Page HITS : %d\n",hit);
    printf("\nTotal Number Of Page MISS : %d\n\n",miss);
}