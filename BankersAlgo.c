#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <stdbool.h>


int main(){

    int n ;  //number of process
    int r;  //number of resources
    

    printf("\nEnter number of process : ");
    scanf("%d",&n);
    
    printf("\nEnter number of resources : ");
    scanf("%d",&r);
    

    int allocation[n][r];
    int max[n][r];
    int available[r];
    int safe_seq[n];
    int completed[n];
    int need[n][r];
    int arr_count =0;
    int Cp_count = 0;
    int prev_cp_count = 0;
    int k =0;
    int flag = 0;

    
    printf("\nEnter Allocation matrix of resources : \n\n");
   for(int i=0;i<n;i++){
       for(int j=0;j<r;j++){
            printf("R_%d  : ",j);
            scanf("%d",&allocation[i][j]);
       }
       printf("\n");
   }
   
   
   printf("\nEnter MaxNeed matrix of resources for each process: \n\n");
   for(int i=0;i<n;i++){
       for(int j=0;j<r;j++){
           printf("R_%d  : ",j);
           scanf("%d",&max[i][j]);
       }
       printf("\n");
   }

   printf("\n\nEnter Available resources : \n\n");
   for(int i=0;i<r;i++){
        printf("R_%d  : ",i);
        scanf("%d",&available[i]);
   }


    for(int i =0;i<n;i++){
        completed[i] = 0;
    }
    
    for(int i =0;i<n;i++){
        for(int j =0;j<r;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    } 
    

    int totalA =0,totalB=0,totalC=0;
    for(int i=0;i<n;i++){
        totalA = totalA + allocation[i][0];
        totalB = totalB + allocation[i][1];
        totalC = totalC + allocation[i][2];
    }
    totalA = totalA + available[0];
    totalB = totalB + available[1];
    totalC = totalC + available[2];
    
    
    while(true){

        if(Cp_count >= n){
            break;
        }

        if(completed[k] == 0 && need[k][0] <= available[0] && need[k][1] <= available[1] && need[k][2] <= available[2]){
           
           printf("\n*Request is granted of P_%d",k);

            completed[k] = 1;
            Cp_count++;
            flag = 1;
            safe_seq[arr_count++] = k;
          
            for(int j=0;j<r;j++){
                need[k][j] =0;
            }
            
            for(int j=0;j<r;j++){
                available[j] = available[j] + allocation[k][j];
            }
           
        } 
        else{
            if(completed[k] == 1){
                printf("\nprocess P_%d is already Completed.",k);
            }
            else{
            printf("\nRequest is denied of P_%d",k);
            printf("\nneed > available");
            printf("\nNeed : ");
            for(int i=0;i<r;i++){
                printf("%d ",need[k][i]);
            }
            printf("\nAvaliability : ");
            for(int i=0;i<r;i++){
                printf("%d ",available[i]);
            }
            }
        }

        printf("\n\n");
         if(k == n-1){
            if(flag == 0){
                printf("unsafe");
                break;
            }else{
                flag = 0;
            }
        }
        k = (k+1)%n; 
    }

    if(totalA == available[0] && totalB == available[1] && totalC == available[2]){
        printf("\n\n***System is in Safe State\n");
        printf("\nSafe Sequence : ");
        for(int i =0;i<n;i++){
            printf("%d ",safe_seq[i]);
        }
        printf("\n\n");
    }
    else{
        printf("\n***System is not in safe state\n");
    }
    
}