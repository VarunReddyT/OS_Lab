#include <stdio.h>
#include <stdbool.h>
bool check(int resources, int need[resources], int available[resources]);
void getSafeSequence(int processors, int resources, int allocated[processors][resources], int max[processors][resources], int need[processors][resources], int *available);
void check_request(int process_number, int processors, int resources, int request[resources], int allocated[processors][resources], int max[processors][resources], int need[processors][resources], int available[resources]);
int main()
{
    int processors, resources;
    printf("Enter number of processors : ");
    scanf("%d", &processors);
    printf("Enter number of resources : ");
    scanf("%d", &resources);
    int allocated[processors][resources], max[processors][resources];
    printf("Enter Allocation Matrix\n");
    for (int i = 0; i < processors; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocated[i][j]);
        }
    }
    printf("Enter Max Matrix\n");
    for (int i = 0; i < processors; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    int available[resources];
    for (int i = 0;i < resources; i++)
    {
        printf("\nEnter available of resource %c :", (i + 65));
        //(i+65) prints the characters starting from A (Ascii value of A is 65)
        scanf("%d", &available[i]);
    }
printf("\nThe Number Of Instances Of Resource Present In The System Under Each Type Of Resource are :\n");
//total instances are sum of resources available and allocated for each processor 
int instances[resources];
for(int i=0;i<resources;i++)
{
        instances[i] = 0;
}
for(int i=0;i<processors;i++)
{
        for (int j = 0; j < resources; j++)
        {
            instances[j] += allocated[i][j];
        }
}
for(int i=0;i<resources;i++)
{
        instances[i] += available[i];
}
for(int i=0;i<resources;i++)
{
        printf("%c = %d\n", (i + 65), instances[i]);
}
printf("\nThe Need Matrix is \n");
//need matrix is the difference between maximum and allocated
int need[processors][resources];
for(int i=0;i<processors;i++)
{
        for (int j = 0; j < resources; j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n"); // just to allign the matrix to next row
}
int current_available[processors];
for(int i=0;i<processors;i++)
{
        current_available[i] = available[i];
}
getSafeSequence(processors,resources,allocated,max,need,current_available);
printf("\n\nIf a request from process p1 arrives for (1,1,0,0), can the request be granted?");
//according to question only 4 resources 
int request1[4];
request1[0]=1;
request1[1]=1;
int current_available1[processors];
for(int i=0;i<processors;i++)
{
        current_available1[i] = available[i];
}
check_request(1,processors,resources,request1,allocated,max,need,current_available1);
printf("\n\nIf a request from process p4 arrives for (0,0,2,0), can the request be granted?\n"); 
int request2[4];
request2[2]=2;
int current_available2[processors];
for(int i=0;i<processors;i++)
{
        current_available2[i] = available[i];
}
check_request(4,processors,resources,request2,allocated,max,need,current_available2);
}
void getSafeSequence(int processors, int resources, int allocated[processors][resources], int max[processors][resources], int need[processors][resources], int available[resources])
{
    int computed = 0;
    int computed_order[processors]; // order of computed processors
    int pointer_to_computed = 0;    // a pointer to add order of processors to computed_order
    bool processed[processors];
    for (int i = 0; i < processors; i++)
    {
        processed[i] = false;
    } // boolean array that stores whether process is completed or not.
    while (computed < processors)
    {
        bool any_process_computed = false;
        for (int
                 i = 0;
             i < processors; i++)
        {
            if (processed[i])
            {
                continue;
            }
            if (check(resources, need[i], available))
            { // check if need is less than available 
            for(int j = 0; j < resources;j++)
                {
                    available[j] += allocated[i][j]; // adding the allocated resources because the process is completed
                }
                processed[i] = true;
                any_process_computed = true;
                computed_order[pointer_to_computed++] = i;
                computed += 1;
            }
        }
        if (!any_process_computed)
        {
            break;
        } // the system is not in safe state because no resource can be allocated
    }
    if (computed == processors)
    { // if all processors are computed the system is in safe state
        printf("\nThe System is in safe state and the safe sequence is :\n");
        for (int i = 0; i < processors; i++)
        {
            printf("P%d ", computed_order[i]);
        }
    }
    else
    {
        printf("The System is not in safe state and the processes will be in deadlock\n");
    }
}
bool check(int resources, int need[resources], int available[resources])
{
    for (int i = 0; i < resources; i++)
    {
        if (need[i] > available[i])
        {
            return false;
        }
    }
    return true;
}
void check_request(int process_number, int processors, int resources, int request[resources], int allocated[processors][resources], int max[processors][resources], int need[processors][resources], int available[resources])
{
    if (check(resources, request, available))
    {
        if (check(resources, request, need[process_number]))
        {
            for (int i = 0; i < resources; i++)
            {
                available[i] -= request[i];
                allocated[process_number][i] += request[i];
                need[process_number][i] = max[process_number][i] - allocated[process_number][i];
            }
            getSafeSequence(processors, resources, allocated, max, need, available);
            return;
        }
    }
    printf("Request cannot be granted\n");
}