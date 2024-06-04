#include <stdio.h>
#include <stdbool.h>

int allocation[10][10];
int max[10][10];
int need[10][10];
int available[10];
bool finish[10];

int num_processes, num_resources;
int i, j;
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
	int safe_seq = 1, want_continue=1;
	int choice;
	int iter = 0;
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