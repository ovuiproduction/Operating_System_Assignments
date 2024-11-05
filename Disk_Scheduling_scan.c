#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


int findmin(int request_seq[],int size){

    int min = 999;

    for(int i=0;i<size;i++){
        if(min > request_seq[i]){
            min = request_seq[i];
        }
    }

    return min;
}

int findmax(int request_seq[],int size){

    int max = 0;

    for(int i=0;i<size;i++){
        if(max < request_seq[i]){
            max = request_seq[i];
        }
    }

    return max;
}

int sstf(int request_seq[],int head,int size){

    int seek_seq[size+2];
    int seek_count =0;

    int initialPosition = head;

    int min = INT_MAX;
    int minele = head;
    int minindex;

    int seekoprations = 0;

    int visited[size];
    for(int i=0;i<size;i++){
        visited[i] = 0;
    }

    int minlimit = findmin(request_seq,size);
    int maxlimit = findmax(request_seq,size);
    
    seek_seq[seek_count++] = head;

    for(int i=0;i<size;i++){        //Decreasing

        for(int j=0;j<size;j++){
            if(min > abs(head-request_seq[j]) && visited[j] == 0 && request_seq[j] < initialPosition){
                min  = abs(head-request_seq[j]);
                minele = request_seq[j];
                minindex = j;
            }
        }

        visited[minindex] = 1;
        head = minele; 
        seek_seq[seek_count++] = head;
        min = INT_MAX;
        if(head == minlimit){
            head = 0;
            seek_seq[seek_count++] = head;
            seekoprations = seekoprations + abs(initialPosition - 0);
            break;
        }
    }

    min = INT_MAX;

     for(int i=0;i<size;i++){           //increasing
        
        for(int j=0;j<size;j++){
            if(min > abs(head-request_seq[j]) && visited[j] == 0){
                min  = abs(head-request_seq[j]);
                minele = request_seq[j];
                minindex = j;
            }
        }

        visited[minindex] = 1;
        head = minele; 
        seek_seq[seek_count++] = head;
        min = INT_MAX;
        if(head == maxlimit){   
            seekoprations = seekoprations + abs(head - 0);
            break;
        }
    }

    printf("\n\nSeek Sequence \n\n");
    for(int i=0;i<size+2;i++){
        printf("%d -> ",seek_seq[i]);
    }
    printf("End");
    return seekoprations;
} 

void main(){

    int no_request ; 
    int initial;
    printf("\nEnter No of Requests : ");
    scanf("%d",&no_request);

    int requestSequence[no_request];
    printf("\n\nEnter Request Sequence \n");

    for(int i=0;i<no_request;i++){
        printf("\n\nEnter request Entry : ");
        scanf("%d",&requestSequence[i]);
    }

    printf("\n\nEnter initial head Position : ");
    scanf("%d",&initial);


    int seekoprations = sstf(requestSequence,initial,no_request);
    printf("\n\nTotal Seek Oprations : %d\n\n",seekoprations);
}