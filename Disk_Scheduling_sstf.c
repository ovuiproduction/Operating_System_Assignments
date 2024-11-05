#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int sstf(int request_seq[],int head,int size){

    int min = INT_MAX;
    int minele = head;
    int minindex;
    int seekoprations = 0;
    int visited[size];
    for(int i=0;i<size;i++){
        visited[i] = 0;
    }

    printf("\n\nSeek Sequence \n\n");
    printf("%d ",head);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(min > abs(head-request_seq[j]) && visited[j] == 0){
                min  = abs(head-request_seq[j]);
                minele = request_seq[j];
                minindex = j;
            }
        }

        visited[minindex] = 1;
        seekoprations = seekoprations + min;
        head = minele; 
        printf(" -> %d ",head);
        min = INT_MAX;
    }
   
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