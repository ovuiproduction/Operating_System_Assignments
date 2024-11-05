#include<stdio.h>
#include<stdlib.h>


int fcfs(int requestSequence[],int initial,int size){

    int prev = initial;
    int next = initial;
    int seekoprations = 0;

    printf("\nSeek sequence  \n\n");
    for(int i=0;i<size;i++){
        next = requestSequence[i];
        seekoprations = seekoprations + abs(next-prev);
        printf("%d\n",next);
        prev = next;
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

    int seekoprations = fcfs(requestSequence,initial,no_request);


    printf("\nTootal Seek Oprations : %d\n\n",seekoprations);
}