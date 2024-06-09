//Excercise 5
/*Consider the following snapshot of a system. P0, P1, P2, P3, P4 are the processes and A, B, C, D are the resource types. The values in the table indicates the number of instances of a specific resource (for example: 3 3 2 1 under the last column indicates that there are 3 A-type, 3 B-type, 2 C-type and 1 D-type resources are available after allocating the resources to all five processes). The numbers under allocation-column indicate that those number of resources are allocated to various processes mentioned in the first column. The numbers under Max- column indicate the maximum number of resources required by the processes. For example: in 1st row under allocation- column 2 0 0 1 indicate there are 2 A-type, 0 B-type, 0 C-type and 1 D- type resources are allocated to process P0. Whereas 4 2 1 2 under Max-column indicate that process P0‘s maximum requirement is 4 A- type, 2 B-type, 1 C-type and 2 D-type resources.

Process	Allocation             Max       Available
    A B C D	                A B C D      A B C D
P0  2 0 0 1             	4 2 1 2	      3 3 2 1          
P1	3 1 2 1             	5 2 5 2	
P2	2 1 0 3	                2 3 1 6	
P3	1 3 1 2	                1 4 2 4	
P4	1 4 3 2	                3 6 6 5	         	                            

 
Answer the following questions using banker’s algorithm by providing all intermediate steps
a.	How many instances of resources are present in the system under each type of a resource?
b.	Compute the Need matrix for the given snapshot of a system.
c.	Verify whether the snapshot of the present system is in a safe state by demonstrating an order in which the processes may complete. If a request from process P1 arrives for (1,1,0,0), can the request be granted immediately?
d.	If a request from process P4 arrives for (0,0,2,0), can the request be granted immediately?
*/
// sample Input & output
/*
enter no.of Process : 5
enter no.of Resources : 4
enter Allocation matrix: 2 0 0 1
3 1 2 1
2 1 0 3
1 3 1 2
1 4 3 2
enter maximum Matrix : 4 2 1 2
5 2 5 2
2 3 1 6
1 4 2 4
3 6 6 5
enter available matrix : 3 3 2 1
 total instances of each resource type : 12 12 8 10 
The system is in safe state and the safe sequence is : 0 3 4 1 2 
want to check for new Resource request enter 1 : 1
which process wants to generate the request : 1
Enter resource request : 1 1 0 0
 process 1 request can be granted immediately 
 want to check the safe sequence enter 1 : 1 

The system is in safe state and the safe sequence is : 0    3 4 1 2 
Want to continue enter 1 : 1

want to check for new Resource request enter 1 : 1
which process wants to generate the request : 4
Enter resource request : 0 0 2 0
 process 4 request can be granted immediately 
 want to check the safe sequence enter 1 : 1

The system is in safe state and the safe sequence is : 0 3 4 1 2 
Want to continue enter 1 : 2
*/
#include<stdio.h>
#include<stdbool.h>

void calculateNeed(int need[][4], int max[][4], int alloc[][4], int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

void safeState(bool flag, int process, int safeSequence[]){
    if(flag){
        printf("The system is in safe state and the safe sequence is : ");
        for(int i = 0; i < process; i++){
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else{
        printf("The system is not in a safe state.\n");
    }
}

bool SafetyAlgo(int process, int resources, int allocated[][4], int available[4], int need[][4],int safeSequence[]){
    int finish[5] = {0};
    int finishCount = 0;

    int i = 0;
    int current = 0;
    int work[resources];
    for(int i = 0; i < resources; i++){
        work[i] = available[i];
    }
    while(finishCount < process){
        int j = 0;
        while(j<resources){
            if(need[i][j] > work[j]){
                break;
            }
            j++;
        }
        if(j == resources && finish[i] == 0){
            for(int k = 0; k < resources; k++){
                work[k] += allocated[i][k];
            }
            finish[i] = 1;
            finishCount++;
            safeSequence[finishCount-1] = i;
        }
        i = (i+1)%process;
        current++;
        if(current > process*process){
            return false;
        }
    }
    return true;
}

void calculateTotalResources(int TotalResources[], int allocated[][4], int available[],int process, int resources){
    for(int i = 0; i < resources; i++){
        int sum = available[i];
        for(int j = 0; j < process; j++){
            sum += allocated[j][i];
        }
        TotalResources[i] = sum;
    }

}
int main(){
    int process;
    printf("enter no.of Process : ");
    scanf("%d", &process);
    int resources;
    printf("enter no.of Resources : ");
    scanf("%d", &resources);
    int allocated[process][resources], max[process][resources];
    printf("enter Allocation matrix: ");
    for(int i = 0; i < process; i++){
        for(int j = 0; j < resources; j++){
            scanf("%d", &allocated[i][j]);
        }
    }
    printf("enter maximum Matrix : ");
    for(int i = 0; i < process; i++){
        for(int j = 0; j < resources; j++){
            scanf("%d", &max[i][j]);
        }
    }
    int available[resources];
    printf("enter available matrix : ");
    for(int i = 0; i < resources; i++){
        scanf("%d", &available[i]);
    }
    int need[5][4];
    calculateNeed(need, max, allocated,process, resources);



    int TotalResources[resources];
    calculateTotalResources(TotalResources, allocated,available, process, resources);

    printf(" total instances of each resource type : ");
    for(int i = 0; i < resources; i++){
        printf("%d ", TotalResources[i]);
    }
    printf("\n");
    int safeSequence[5];
    bool safe = SafetyAlgo(process, resources, allocated, available, need, safeSequence);
    safeState(safe, process, safeSequence);
    while(true){
        bool flag = true;
        int want_resource;
        printf("want to check for new Resource request enter 1 : ");
        scanf("%d", &want_resource);
        if(want_resource != 1){
            break;
        }
        int process_id;
        printf("which process wants to generate the request : ");
        scanf("%d", &process_id);

        int request[resources];
        printf("Enter resource request : ");
        for(int i = 0; i < resources; i++){
            scanf("%d", &request[i]);
        }
        for(int i = 0; i < resources; i++){
            if(request[i] > available[i] || request[i] > need[process_id][i]){
                printf("first one cannot be granted immediately.\n");
                flag = false;
                break;
            }
        }
        if(flag == false){
            continue;
        }
        // we are just pretending to allocate the resources to the process
        for(int i = 0; i < resources; i++){
            available[i] -= request[i];
            allocated[process_id][i] += request[i];
            need[process_id][i] -= request[i];
        }
        safe = SafetyAlgo(process, resources, allocated, available, need, safeSequence);
        
        if(!safe){
            printf("process %d request cannot be granted immediately\n",process_id);
            // After checking the safe state we are reverting the changes
         for(int i = 0; i < resources; i++){
            available[i] += request[i];
            allocated[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
            continue;
        }
        printf("process %d request can be granted immediately\n",process_id);
        
        int safeChoice;
        printf("want to check the safe sequence enter 1 : ");
        scanf("%d", &safeChoice);
        if(safeChoice != 1){
            break;
        }
        printf("\n");
        safeState(safe, process, safeSequence);
        int wantContinue;
        printf("Want to continue enter 1 : ");
        scanf("%d", &wantContinue);
        printf("\n");
        
        if(wantContinue != 1){
            break;
        }
    }
    
    
    return 0;
}