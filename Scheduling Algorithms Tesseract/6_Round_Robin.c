/* 6.A local library system incorporates several branches, each equipped with computers used for catalog searches, digital archives access, and various educational programs. During the peak hours of library operation, patrons often need to use computers for tasks like research, document processing, or accessing public records. The library staff sets up a system where each user is allotted a 2-minute slot. If a user’s task is not completed within this period, they go back to the end of the queue for another turn. identify the scheduling algorithm.
Process Id	Arrival time	Burst time
P1             	0	        5
P2          	1	            3
P3	            2	            1
P4	            3           	2
P5          	4           	3*/

// Identify the type of CPU scheduling algorithm for the scenario and implement the same in C Language. Calculate Average Turn Around time and Average Waiting time for each of the scheduling algorithm by taking arrival times accordingly.
// Calculate the times by using gantt chart in observation and crosscheck the same with the output of the program.

#include <stdio.h>
#include <stdlib.h>

void enqueue(int **queue, int *size, int *capacity, int *rear, int element)
{
    if (*size == *capacity)
    {
        *capacity *= 2;
        *queue = (int *)realloc(*queue, *capacity * sizeof(int));
    }
    *rear = (*rear + 1) % *capacity;
    (*queue)[*rear] = element;
    (*size)++;
}

int dequeue(int *queue, int *size, int *capacity, int *front, int *rear)
{
    if (*size == 0)
    {
        return -1;
    }
    int element = queue[*front];
    *front = (*front + 1) % *capacity;
    (*size)--;
    return element;
}

int main()
{
    int n = 5;
    int time_q = 2;
    int arrival[] = {0, 1, 2, 3, 4};
    int burst[] = {5, 3, 1, 2, 3};
    int remTime[] = {5, 3, 1, 2, 3};
    int complete[] = {-1, -1, -1, -1, -1};
    int TAT[n], WT[n],currTime = arrival[0], completed = 0;
    float totalTat = 0, totalWt = 0;

    // Ready queue
    int *queue = (int *)malloc(n * sizeof(int));
    int size = 0, capacity = n, front = 0, rear = -1;

    for (int i = 0; i < n; i++)
    {
        if (arrival[i] == 0)
        {
            enqueue(&queue, &size, &capacity, &rear, i);
        }
    }

    while (completed < n)
    {
        if (size == 0)
        {
            currTime++;
            for (int i = 0; i < n; i++)
            {
                if (arrival[i] == currTime)
                {
                    enqueue(&queue, &size, &capacity, &rear, i);
                }
            }
            continue;
        }

        int currP = dequeue(queue, &size, &capacity, &front, &rear);

        if (remTime[currP] > time_q)
        {
            remTime[currP] -= time_q;
            currTime += time_q;
        }
        else
        {
            currTime += remTime[currP];
            remTime[currP] = 0;
            complete[currP] = currTime;
            TAT[currP] = complete[currP] - arrival[currP];
            WT[currP] = TAT[currP] - burst[currP];
            totalTat += TAT[currP];
            totalWt += WT[currP];
            completed++;
        }

        for (int i = 0; i < n; i++)
        {
            if (arrival[i] > currTime - time_q && arrival[i] <= currTime && remTime[i] > 0)
            {
                int found = 0;
                for (int j = 0; j < size; j++)
                {
                    if (queue[(front + j) % capacity] == i)
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    enqueue(&queue, &size, &capacity, &rear, i);
                }
            }
        }

        if (remTime[currP] > 0)
        {
            enqueue(&queue, &size, &capacity, &rear, currP);
        }
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, arrival[i], burst[i], complete[i], TAT[i], WT[i]);
    }
    printf("Average Turnaround Time: %.2f mins\n", totalTat / n);
    printf("Average Waiting Time: %.2f mins\n", totalWt / n);

    free(queue);

    return 0;
}
