#include<stdio.h>
#include<stdlib.h>

struct Node{
    int page;
    struct Node *next;
};

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



int main(){

    int request_no;
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

    int queue[100];
    int front = 0;
    int rare = 0;

    for(int i=0;i<request_no;i++){

        for(int i=0;i<fream_size;i++){
            if(frame[i] == -1){
                flag = 1;
                free_index = i;
                break;
            }
        }

        if(flag == 1 && !present(request_seq[request_count],frame,fream_size)){
            miss++;
            pagef++;
            frame[free_index] = request_seq[request_count];
            queue[rare++] = request_seq[request_count];
            printf("\nCash MISS\n Page  %d  is inserted\n",request_seq[request_count]);
            request_count++;

        }
        else{
            
            if(present(request_seq[request_count],frame,fream_size)){
                hit++;
                printf("\nCash HIT\n Page %d is Already in the page table\n\n",request_seq[request_count]);
                request_count++;
                continue;
            }
            else{
                miss++;
                int target = queue[front++];
                int index = find_index(target,frame,fream_size);

                frame[index] = request_seq[request_count];
                queue[rare++] = request_seq[request_count];
                printf("\nCash MISS\n Page %d is Replaced with %d\n",target,request_seq[request_count]);
                request_count++;
                pagef++;
            }
        }
        flag =0;
    }
  
    printf("\n\nTotal Number Of Page Faults are : %d\n\n",pagef);

    printf("\n\nTotal Number Of Page HITS : %d\n",hit);
    printf("\nTotal Number Of Page MISS : %d\n\n",miss);
}