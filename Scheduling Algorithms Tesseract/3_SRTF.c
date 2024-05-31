/* 3. Imagine an Emergency Medical Dispatch Center (EMDC) tasked with coordinating emergency medical responses across a large urban area. The center receives calls about various emergencies—accidents, medical crises, and urgent patient transfers. Identify the algorithm helps prioritize shorter-duration tasks, allowing the center to quickly dispatch assistance for multiple emergencies, potentially saving more lives by reducing the response time.
Task Simulation:
Here are some examples of calls received by the EMDC one morning:
1.	Call A - Rapid response for a cardiac arrest at a home: Initial Burst Time = 7 minutes, Arrival Time = 08:00 AM
2.	Call B - Ambulance dispatch for a minor car accident: Initial Burst Time = 5 minutes, Arrival Time = 08:01 AM
3.	Call C - Coordinate a helicopter for a critical transfer from a rural area: Initial Burst Time = 3 minutes, Arrival Time = 08:02 AM
4.	Call D - Send paramedics to a multiple injury accident on a highway: Initial Burst Time = 20 minutes, Arrival Time = 08:15 AM
5.	Call E - Dispatch an ambulance for a sudden stroke case: Initial Burst Time = 10 minutes, Arrival Time = 08:20 AM
*/

// Identify the type of CPU scheduling algorithm for the scenario and implement the same in C Language. Calculate Average Turn Around time and Average Waiting time for each of the scheduling algorithm by taking arrival times accordingly.
// Calculate the times by using gantt chart in observation and crosscheck the same with the output of the program.

#include <stdio.h>
#include <stdbool.h>

int main() {

    int processes = 5;
    int processNames[] = {1, 2, 3, 4, 5};
    int burstTime[] = {7, 5, 3, 20, 10};
    int remainingTime[] = {7, 5, 3, 20, 10};
    int arrivalTime[] = {480, 481, 482, 495, 500};

    int WT[processes], TAT[processes], completionTime[processes];
    float totalWT = 0, totalTAT = 0;

    int currentTime = 0;
    int completedTasks = 0;
    int isCompleted[] = {0,0,0,0,0};


    while (completedTasks < processes) {
        int shortestProcess = -1;
        int shortestTime = 99999;

        for (int i = 0; i < processes; i++) {
            if (isCompleted[i] == 0 && arrivalTime[i] <= currentTime && remainingTime[i] < shortestTime) {
                shortestTime = remainingTime[i];
                shortestProcess = i;
            }
        }

        if (shortestProcess != -1) {
            remainingTime[shortestProcess]--;
            if (remainingTime[shortestProcess] == 0) {
                completionTime[shortestProcess] = currentTime + 1;
                TAT[shortestProcess] = completionTime[shortestProcess] - arrivalTime[shortestProcess];
                WT[shortestProcess] = TAT[shortestProcess] - burstTime[shortestProcess];
                totalTAT += TAT[shortestProcess];
                totalWT += WT[shortestProcess];
                isCompleted[shortestProcess] = 1;
                completedTasks++;
            }
        }
        currentTime++;
    }


    printf("Process\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processNames[i], burstTime[i], arrivalTime[i], completionTime[i],TAT[i], WT[i]);
    }

    printf("Average Turnaround Time: %.2f\n", totalTAT / processes);
    printf("Average Waiting Time: %.2f\n", totalWT / processes);

    return 0;
}
