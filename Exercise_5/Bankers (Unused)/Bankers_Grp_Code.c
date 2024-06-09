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
#include <stdio.h>
#include <stdbool.h>

int allocation[10][10],max[10][10],need[10][10],available[10];
int num_processes, num_resources,i, j;
bool finish[10];

void calculate_need_matrix() {
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool is_safe_state(int work[], int safe_sequence[]) {
    int finish_count = 0;
    while (finish_count < num_processes) {
        bool found = false;
        for (i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safe_sequence[finish_count++] = i;
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

void handle_resource_request(int process_id, int request[]) {
    for (i = 0; i < num_resources; i++) {
        if (request[i] > available[i] || request[i] > need[process_id][i]) {
            printf("first one cannot be granted immediately.\n");
            return;
        }
    }

    for (i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    int work[num_resources];
    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    int safe_sequence[num_processes];
    if (is_safe_state(work, safe_sequence)) {
        printf("Request cannot be granted immediately.\n");
        for (i = 0; i < num_resources; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
    } else {
        printf("process %d request can be granted immediately\n",process_id);
    }
}

int main() {
    printf("enter no.of Process : ");
    scanf("%d", &num_processes);
    printf("enter no.of Resources : ");
    scanf("%d", &num_resources);

    printf("enter Allocation matrix: ");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("enter maximum Matrix : ");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("enter available matrix : ");
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    calculate_need_matrix();

    int total_instances[num_resources];
    for (i = 0; i < num_resources; i++) {
        total_instances[i] = available[i];
        for (j = 0; j < num_processes; j++) {
            total_instances[i] += allocation[j][i];
        }
    }

    printf("total instances of each resource type : ");
    for (i = 0; i < num_resources; i++) {
        printf("%d ", total_instances[i]);
    }
    printf("\n");

    int work[num_resources];
    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }
	int safe_seq = 1, want_continue=1,iter = 0;
	int choice;
    do {
	    int safe_sequence[num_processes];
	    
	    if (safe_seq == 1) {
	    	if (iter == 0) {
	    		if (is_safe_state(work, safe_sequence)) {
			        printf("The system is in safe state and the safe sequence is : ");
			        for (i = 0; i < num_processes; i++) {
			            printf("%d ", safe_sequence[i]);
			        }
			        printf("\n");
			    } else {
			        printf("The system is not in a safe state.\n");
		    	}
	    	}
	    	else {
	    		if (is_safe_state(work, safe_sequence)) {
			        printf("The system is not in a safe state.\n");
			    } else {
			        
			        printf("The system is in safe state and the safe sequence is : ");
			        for (i = 0; i < num_processes; i++) {
			            printf("%d ", safe_sequence[i]);
			        }
			        printf("\n");
			    }
			}
		}
		if (want_continue != 1) {
			printf("Want to continue enter 1 : ");
			scanf("%d", &want_continue);
			printf("\n");	
		}
		if (want_continue != 1) {
			break;
		}
        printf("want to check for new Resource request enter 1 : ");
        scanf("%d", &choice);
        if (choice == 1) {
            int process_id;
            printf("which process wants to generate the request : ");
            scanf("%d", &process_id);
            int request[num_resources];
            printf("Enter resource request : ");
            for (i = 0; i < num_resources; i++) {
                scanf("%d", &request[i]);
            }
            handle_resource_request(process_id, request);
        }
        safe_seq = 0;
        want_continue = 0;
        if (safe_seq != 1){
	    	printf("want to check the safe sequence enter 1 : ");
	    	scanf("%d", &safe_seq);
	    	printf("\n");
		}
		iter += 1;
    } while (choice == 1);

    return 0;
}