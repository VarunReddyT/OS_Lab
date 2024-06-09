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

The system is in safe state and the safe sequence is : 0 3 4 1 2 
Want to continue enter 1 : 1

want to check for new Resource request enter 1 : 1
which process wants to generate the request : 4
Enter resource request : 0 0 2 0
 process 4 request can be granted immediately 
 want to check the safe sequence enter 1 : 1

The system is in safe state and the safe sequence is : 0 3 4 1 2 
Want to continue enter 1 : 2
*/
#include <stdio.h>
#include <stdbool.h>

// Function to calculate the Need matrix
void calculateNeed(int need[][4], int max[][4], int alloc[][4], int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

// Function to check if the system is in a safe state
bool isSafeState(int processes[], int avail[], int max[][4], int alloc[][4], int need[][4], int n, int m, int safeSeq[]) {
    int work[m];
    bool finish[n];
    int count = 0;

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    for (int i = 0; i < n; i++)
        finish[i] = false;

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[p][k];

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

// Function to check if a request can be granted immediately
bool isRequestGrantable(int process, int request[], int avail[], int alloc[][4], int need[][4], int n, int m) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i] || request[i] > avail[i])
            return false;
    }

    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    return true;
}

// Function to reset the request (undo the changes) if it cannot be granted
void resetRequest(int process, int request[], int avail[], int alloc[][4], int need[][4], int m) {
    for (int i = 0; i < m; i++) {
        avail[i] += request[i];
        alloc[process][i] -= request[i];
        need[process][i] += request[i];
    }
}

int main() {
    int n, m;

    printf("enter no.of Process : ");
    scanf("%d", &n);
    printf("enter no.of Resources : ");
    scanf("%d", &m);

    int processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    int alloc[n][m];
    int max[n][m];
    int avail[m];

    printf("enter Allocation matrix : ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("enter maximum Matrix : ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("enter available matrix : ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int need[n][m];
    calculateNeed(need, max, alloc, n, m);

    // Calculate total instances of each resource type
    int totalResources[m];
    for (int i = 0; i < m; i++) {
        totalResources[i] = avail[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            totalResources[j] += alloc[i][j];
        }
    }

    printf(" total instances of each resource type : ");
    for (int i = 0; i < m; i++) {
        printf("%d ", totalResources[i]);
    }
    printf("\n");

    int safeSeq[n];
    if (isSafeState(processes, avail, max, alloc, need, n, m, safeSeq)) {
        printf("The system is in safe state and the safe sequence is : ");
        for (int i = 0; i < n; i++)
            printf("%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
        return 0;
    }

    while (true) {
        printf("want to check for new Resource request enter 1 : ");
        int checkRequest;
        scanf("%d", &checkRequest);
        if (checkRequest != 1) break;

        printf("which process wants to generate the request : ");
        int process;
        scanf("%d", &process);

        printf("Enter resource request : ");
        int request[m];
        for (int i = 0; i < m; i++) {
            scanf("%d", &request[i]);
        }

        if (isRequestGrantable(process, request, avail, alloc, need, n, m)) {
            if (isSafeState(processes, avail, max, alloc, need, n, m, safeSeq)) {
                printf(" process %d request can be granted immediately\n", process);
            } else {
                resetRequest(process, request, avail, alloc, need, m);
                printf(" process %d request can be granted immediately\n", process);
            }
        } else {
            printf("process %d request can be granted immediately\n", process);
        }

        printf(" want to check the safe sequence enter 1 : ");
        int checkSafeSeq;
        scanf("%d", &checkSafeSeq);
        printf("\n");
        if (checkSafeSeq == 1) {
            if (isSafeState(processes, avail, max, alloc, need, n, m, safeSeq)) {
                printf("The system is in safe state and the safe sequence is: ");
                for (int i = 0; i < n; i++)
                    printf("%d ", safeSeq[i]);
                printf("\n");
            } else {
                printf("The system is not in a safe state.\n");
            }
        }

        printf("Want to continue enter 1 : ");
        int continueCheck;
        scanf("%d", &continueCheck);
        printf("\n");
        if (continueCheck != 1) break;
    }

    return 0;
}
