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

int findexistance(int pid){
    
    temp = head;
    
    while(temp!= NULL)
    {
       if(temp->node.pid == pid){
        return 0;
       }
        temp = temp->next;
    }
    return 1;
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

void roundrobin(struct proc arr[],int timeQ){

    int rbt[pc+1];
    int k = 0;
    for(int i =1;i<pc+1;i++){
        rbt[i] = arr[k++].bt;
    }
    rbt[0] = 99;

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

    int ct =arr[0].at;
    insert(arr[0]);
    
    while(rare != 0){

        struct proc curr = head->node;
        if(rbt[curr.pid] < timeQ){
            ct = ct + rbt[curr.pid];
            rbt[curr.pid] = 0;
        }else{
        ct = ct + timeQ;
        rbt[curr.pid] = rbt[curr.pid] - timeQ;
        }
        curr.ct = ct;
        curr.wt = curr.ct - (curr.at + curr.bt);
        curr.tat = curr.bt + curr.wt;

        ganchart[gpc++] = curr;

        for(int i =0;i<pc;i++){
            if(arr[i].at <= ct && findexistance(arr[i].pid) && rbt[arr[i].pid] != 0){
                insert(arr[i]);
            }
        }
        delete(curr.pid);
        if(rbt[curr.pid] != 0){
            insert(curr);
        }
    }
}

void processStatics(struct proc arr[],int timeQ){

    roundrobin(arr,timeQ);
 
    int visited[6];
    for(int i =0;i<pc+1;i++){
        visited[i] = 0;
    }
    visited[0] = 99;
    struct proc processes[pc];
    int k =0;
    for(int i=gpc-1;i>=0;i--){
        if(visited[ganchart[i].pid] == 0){
            processes[k++] = ganchart[i];
            visited[ganchart[i].pid] = 1;
        }
        else{
            continue;
        }
    }
     for(int i =0;i<pc;i++){
        for(int j=i+1;j<pc;j++){
            if(processes[j].pid < processes[i].pid){
                struct proc tempnode = processes[j];
                processes[j] = processes[i];
                processes[i] = tempnode;
            }
        }
    }
    printf("\n\n***Process Execuation Table***\n\n");
    printf("PID     AT      BT      WT      TAT     CT\n");
    for(int i=0;i<pc;i++){
        printf("%d%8d%8d%8d%9d%8d",processes[i].pid,processes[i].at,processes[i].bt,processes[i].wt,processes[i].tat,processes[i].ct);
        printf("\n");
    }


    printf("\n\n*Process Execuation Sequeance  :  ");
    for(int i =0;i<gpc;i++){
        printf("%d  ",ganchart[i].pid);
    }


    int twt = 0;
    int ttat =0;

    for(int i =0;i<pc;i++){
        twt = twt + processes[i].wt;
        ttat = ttat + processes[i].tat;
    }

    float awt = (float)twt/pc;

    float atat = (float)ttat/pc;

    printf("\n\n***Process Execuation Statistics***\n\n");
    printf("Average Waiting Time : %.1f",awt);
    printf("\n");
    printf("Average Turn Around Time : %.1f",atat);
    printf("\n");


}


int main(){

    
    printf("1 ==> Enter Process\n2 ==> Process Execution Statistics & Average Waiting Time & Average Turn Around Time\n");

    int entrycode,option;
    int pid,at,bt,np,timeQ;
    printf("\nEnter Number Of Process : ");
    scanf("%d",&np);
    printf("\n\nEnter Time Quantum : ");
    scanf("%d",&timeQ);
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
                processStatics(arr,timeQ);
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