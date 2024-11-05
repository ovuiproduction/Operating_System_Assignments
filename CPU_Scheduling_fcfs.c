#include<stdio.h>
#include<stdlib.h>


//structure for process info
struct proc{
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
}ganchart[100];

// structure for ready queue
struct Node{
    struct proc node;
    struct Node* next;
};

struct Node *head = NULL;
struct Node* temp = NULL;
int rare = 0;

void insert(struct proc node){

    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->node = node;
    newnode->next = NULL;
    
    if(head == NULL){
        head = newnode;
    }
    else{
        temp = head;
        while(temp->next!= NULL){
            temp = temp->next;
        }
        temp->next = newnode;
    }
    rare++;
}

void delete(int pid){
    
    temp = head;
    while(temp!=NULL){
        if(temp->node.pid == pid){
            if(temp == head){
                head = head->next;
                free(temp);
                break;
            }
            else if(temp->next == NULL){
                struct Node* temp2 = head;
                struct Node* prev = temp2;
                while(temp2->next!=NULL){
                    prev = temp2;
                    temp2 = temp2->next;
                }
                prev->next = NULL;
                free(temp);
                break;
            }
            else{
                struct Node* temp2 = head;
                struct Node* prev = temp2;
                while(temp2->node.pid != pid){
                    prev = temp2;
                    temp2 = temp2->next;
                }
                prev->next = temp2->next;
                free(temp);
                break;
            }
        }
        temp = temp->next;
    }
    rare--;
}

struct proc findmin(){
    
    temp = head;
    struct proc min = head->node;
    
    while(temp!= NULL)
    {
        if(min.at > temp->node.at){
            min = temp->node; 
        }
        temp = temp->next;
    }
    return min;
}

int pc =0;
void addprocess(struct proc arr[],int pid , int at, int bt){
    
    arr[pc].pid = pid;
    arr[pc].at = at;
    arr[pc].bt = bt;
    arr[pc].wt = 0;
    arr[pc].tat = 0;
    arr[pc].ct = 0;
    pc++;
    
}

int gpc = 0;

void fcfs(struct proc arr[]){

    //sort process w.r.t their at

    for(int i =0;i<pc;i++){
        for(int j=i+1;j<pc;j++){
            if(arr[j].at < arr[i].at){
                struct proc tempnode = arr[j];
                arr[j] = arr[i];
                arr[i] = tempnode;
            }
        }
    }

    int visited[pc+1];
    for(int i =0;i<pc+1;i++){
        visited[i] =0;
    }
    visited[0] = 99;

    int ct =arr[0].at;

    insert(arr[0]);
    visited[arr[0].pid] = 1;

    while(rare != 0){

        struct proc curr = findmin();

        ct = ct + curr.bt;
        curr.ct = ct;
        curr.wt = curr.ct - (curr.at + curr.bt);
        curr.tat = curr.bt + curr.wt;

        ganchart[gpc++] = curr;

        for(int i =0;i<pc;i++){
            if(arr[i].at <= ct && visited[arr[i].pid] == 0){
                insert(arr[i]);
                visited[arr[i].pid] = 1;
            }
        }
        
        delete(curr.pid);
        struct Node* temp3 = head;
    }
}

void processExeStatistics(struct proc arr[]){

    printf("\n");
    printf("Given Data : \n\n");
    printf("PID     AT      BT\n");
    for(int i =0;i<pc;i++){
        printf("%d%8d%8d",arr[i].pid,arr[i].at,arr[i].bt);
        printf("\n");
    }

    
    fcfs(arr);

    printf("PID     AT      BT      WT      TAT      CT\n");
    for(int i=0;i<pc;i++){
        printf("%d%8d%8d%8d%9d%9d",ganchart[i].pid,ganchart[i].at,ganchart[i].bt,ganchart[i].wt,ganchart[i].tat,ganchart[i].ct);
        printf("\n");
    }

    printf("Process Execution Sequeance : ");
    for(int i =0;i<pc;i++){
        printf("%d ",ganchart[i].pid);
    }
}

void awt_tat(struct proc arr[]){

    fcfs(arr);

    int twt = 0;
    int ttat =0;

    for(int i =0;i<pc;i++){
        twt = twt + ganchart[i].wt;
        ttat = ttat + ganchart[i].tat;
    }

    float awt = (float)twt/pc;

    float atat = (float)ttat/pc;

    printf("\n");
    printf("Average Waiting Time : %.1f",awt);
    printf("\n");
    printf("Average Turn Around Time : %.1f",atat);
    printf("\n");
}

int main(){

     printf("1 ==> Enter Process\n2 ==> Process Execution Statistics\n3 ==> Average Waiting Time & Average Turn Around Time\n");

    int entrycode,option;
    int pid,at,bt,np;
    printf("\nEnter Number Of Process : ");
    scanf("%d",&np);
    struct proc arr[np];

    do{

        printf("\n\nenter option : ");
        scanf("%d",&option);
      
        switch(option){
            //case 1 for entering processes
            case 1:
                for(int i=0;i<np;i++){
                printf("\n\nEnter Process ID : ");
                scanf("%d",&pid);
                printf("Enter Process AT : ");
                scanf("%d",&at);
                printf("Enter Process BT : ");
                scanf("%d",&bt);
                addprocess(arr,pid,at,bt);
                getchar();
                printf("\n");
                }
                break;
            
            //case 2 for display Given Data & Process Execution Data
            case 2:
                processExeStatistics(arr);
                break;

            // case 3 for displaying Average Waiting Time & Average Turn Around Time
            case 3:
                awt_tat(arr);
                break;

            // default case
            default :
                printf("\nenter valid Inputs");
                break;
        }

        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);

    }while(entrycode != 0);
}