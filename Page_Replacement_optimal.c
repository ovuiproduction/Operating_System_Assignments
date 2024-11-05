#include<stdio.h>
#include<stdlib.h>

struct frnode{
    int page;
    int dist;
};


int present(int target,int frame[],int frame_size){

    int size = frame_size;

    for(int i=0;i<size;i++){
        if(frame[i] == target){
            return 1;
        }
    }
    return 0;
}

int find_index(int target,int frame[],int frame_size){

    int size = frame_size;

    for(int i=0;i<size;i++){
        if(frame[i] == target){
            return i;
        }
    }
}

void optimal(int prs[],int prs_size,int frame_size){        //page request string

    int size = prs_size;
    int hit =0;
    int miss = 0;

    int frame[frame_size];
    for(int i=0;i<frame_size;i++){
        frame[i] = -1;
    }

    int pagef = 0;
    int flag = 0;
    int request_count = 0;
    int free_index;

    struct frnode future_ref[frame_size];
    int count =0;

    for(int i=0;i<size;i++){

        for(int j=0;j<frame_size;j++){
            if(frame[j] == -1){
                flag = 1;
                free_index = j;
                break;
            }
        }

        if(flag == 1 && !present(prs[request_count],frame,frame_size)){
            pagef++;
            frame[free_index] = prs[request_count];
            printf("\nCash MISS\n Page  %d  is inserted\n",prs[request_count]);
            miss++;
            request_count++; 
        }
        else{
            
            if(present(prs[request_count],frame,frame_size)){
                printf("\nCash HIT\n Page %d is Already in the page table\n\n",prs[request_count]);
                hit++;
                request_count++;
                continue;
            }
            else{
                miss++;
                int c =0;
                int nf =0;
                int notflag = 0;
                for(int k=0;k<frame_size;k++){
                    for(int j=request_count;j<size;j++){
                        // printf("\n%d  %d\n",frame[k],prs[j]);
                        if(frame[k] == prs[j]){
                            nf =1;
                            future_ref[count].dist = c;
                            future_ref[count].page = frame[k];
                            // printf("\n%d ->dist->  %d\n",future_ref[count].page,future_ref[count].dist);
                            count++;
                            break;
                        }
                        c++;
                    }
                    if(nf == 0){                           //page is not in future string 
                        future_ref[count].dist = 99;       //so dist is infinite we assume to 99
                        future_ref[count].page = frame[k];
                        count++;
                    }
                    nf =0;
                    c = 0;
                }

                int max = 0;
                int rpage = -1;

                for(int j=0;j<count;j++){
                    if(max < future_ref[j].dist){
                        max = future_ref[j].dist;
                        rpage = future_ref[j].page;
                    }
                }
                
                int index = find_index(rpage,frame,frame_size);
                printf("\nCash MISS\n Page %d is Replaced with %d\n",rpage,prs[request_count]);
                frame[index] = prs[request_count];
                request_count++;
                pagef++;

                count = 0;
            }
        }
        flag =0;
    }
    printf("\n\nTotal Number Of Page Faults are : %d\n\n",pagef);
    printf("\n\nTotal Number Of Page HITS : %d\n",hit);
    printf("\nTotal Number Of Page MISS : %d\n\n",miss);
}   


int main(){

    int totalPages ;
    int frame_size;
    
    printf("\nEnter No of pages : ");
    scanf("%d",&totalPages);

    printf("\n\nEnter fream Size : ");
    scanf("%d",&frame_size);

    int prs[totalPages];

     for(int i=0;i<totalPages;i++){
        printf("\nEnter page id  :");
        scanf("%d",&prs[i]);
    }

    
    optimal(prs,totalPages,frame_size);
}