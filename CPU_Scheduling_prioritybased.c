#include<stdio.h>
#include<stdlib.h>


//structure for process info
struct proc{
    int pid;
    int at;
    int pt;
    int bt;
    int rbt;
    int wt;
    int tat;
    int ct;
}ganchart[100];

int pc =0;
void addprocess(struct proc arr[] , int pid , int at, int bt,int pt){
    
    arr[pc].pid = pid;
    arr[pc].at = at;
    arr[pc].bt = bt;
    arr[pc].rbt = bt;
    arr[pc].pt = pt;
    arr[pc].wt = 0;
    arr[pc].tat = 0;
    arr[pc].ct = 0;
    pc++;
    
}

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

    struct proc min_array[pc];
    int min_count =0;
   
    temp = head;
    struct proc min = head->node;
    
    while(temp!= NULL)
    {
        if(min.pt > temp->node.pt){
            min = temp->node; 
        }
        temp = temp->next;
    }
   //handaling the more than one min
    temp = head;
    while(temp!= NULL)
    {
        if(temp->node.pt == min.pt){
           min_array[min_count++] = temp->node;
        }
        temp = temp->next;
    }
    struct proc ans = min_array[0];
    for(int i =0;i<min_count;i++){
        if(ans.at > min_array[i].at){
            ans = min_array[i];
        }
    }

    return ans;
}



int found(int pid){

    struct Node* tempnode = head;

    while(tempnode!= NULL){
        if(tempnode->node.pid == pid){
            return 0;
        }
        tempnode = tempnode->next;
    }
    return 1;
}

int gpc = 0;

void prioritybased(struct proc arr[]){

    //sort process w.r.t their AT


    for(int i =0;i<pc;i++){
        for(int j=i+1;j<pc;j++){
            if(arr[j].at < arr[i].at){
                struct proc tempnode = arr[j];
                arr[j] = arr[i];
                arr[i] = tempnode;
            }
        }
    }

    int maxAT = arr[pc-1].at;

    int ct =arr[0].at;

    insert(arr[0]);
    
    while(rare != 0){

        struct proc curr = findmin();

        for(int i =0;i<pc;i++){
            if(arr[i].pid == curr.pid && arr[i].rbt != 0){
                if(ct >= maxAT){
                    ct = ct + arr[i].rbt;
                    arr[i].rbt = 0;
                }
                else{
                    arr[i].rbt = arr[i].rbt - 1;
                    ct = ct + 1;
                }
            }
        }

        curr.ct = ct;
        curr.wt = curr.ct - (curr.at + curr.bt);
        curr.tat = curr.bt + curr.wt;
        curr.rbt = curr.rbt - 1;

        ganchart[gpc++] = curr;
      
        for(int i =0;i<pc;i++){
            if(arr[i].at <= ct && arr[i].rbt != 0 && arr[i].pid != curr.pid && found(arr[i].pid)){
                insert(arr[i]);
            }
        }

        struct Node *temp3 = head;
        delete(curr.pid);
        for(int i =0;i<pc;i++){
            if(arr[i].pid == curr.pid && arr[i].rbt != 0){
                insert(arr[i]);
            }
        }
    }
}

int alreadyexist(struct proc processes[] , struct proc key,int limit){

    for(int i =0;i<limit;i++){
        if(key.pid == processes[i].pid){
            return 0;
        }
    }
    return 1;
}

void processStatics(){

    struct proc processes[pc];
    int c = 0;
    int responsetime[pc];
    for(int i =0;i<pc;i++){
        responsetime[i] = -1;
    }
    int res_count =0;
    int res_time = 0;

    for(int i =0;i<gpc;i++){
        if(responsetime[ganchart[i].pid -1] == -1){
        responsetime[ganchart[i].pid-1] = res_time;
        }
        res_time = ganchart[i].ct; 
    }

    for(int i=gpc-1;i>=0;i--){
        if(alreadyexist(processes , ganchart[i] ,c)){
        processes[c++] = ganchart[i];
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
    printf("\n\nProcess Execution Details \n\n");
    printf("-----------------------------------------------------------\n");
    printf("PID     AT      BT      PT      WT      TAT     CT      RT\n");
    printf("-----------------------------------------------------------\n");
    for(int i =0;i<pc;i++){
        printf("%d%8d%8d%8d%9d%8d%8d%8d",processes[i].pid ,processes[i].at,processes[i].bt,processes[i].pt, processes[i].wt,processes[i].tat,processes[i].ct ,responsetime[i]);
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
    int twt = 0 ;int ttat =0;
    for(int i =0;i<pc;i++){
        twt = twt + processes[i].wt;
        ttat = ttat + processes[i].tat;
    }

    float awt = (float)twt / pc;
    float atat = (float)ttat /pc;

    printf("\n\n*Avareage Waiting Time :  %.1f",awt);
    printf("\n\n*Avareage Turn Around Time :  %.1f\n\n",atat);


    printf("\n\nganchart  :   ");
    for(int i =0;i<gpc;i++){
        printf("%d  ",ganchart[i].pid);
    }
    printf("\n");

}

int main(){


    printf("\n1 ==> Enter Process\n2 ==> Ganchart && Process Execution Statistics\n\n");

    int entrycode,option;
    int pid,at,bt,np,pt;
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
                printf("Enter Process PT : ");
                scanf("%d",&pt);
                addprocess(arr,pid,at,bt,pt);
                getchar();
                printf("\n");
                }
                break;
            
            //case 2 for display Given Data & Process Execution Data
            case 2:
                prioritybased(arr);
                processStatics();
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