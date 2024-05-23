/*2.Imagine an animation studio, Pixie Animations, which specializes in creating short animated films and digital commercials. Due to the studio’s growing popularity and increased client demands, the animation rendering tasks have piled up. Throughout a typical day, various rendering tasks are submitted to the server. Each task has a specific duration determined by the complexity of the animation scenes involved. The goal is to minimize the overall waiting time and maximize resource utilization by strategically scheduling the tasks based on their duration. Write the Corresponding CPU Scheduling algorithm.
Here are some example tasks that the server might receive on a typical day:
•	Task A - Rendering a simple character animation: Burst Time = 15 minutes, Arrival Time = 09:00 AM
•	Task B - Rendering a complex explosion scene: Burst Time = 30 minutes, Arrival Time = 09:10 AM
•	Task C - Rendering a detailed background scene: Burst Time = 20 minutes, Arrival Time = 09:15 AM
•	Task D - Rendering a short dialogue scene: Burst Time = 10 minutes, Arrival Time = 09:30 AM
*/

//Identify the type of CPU scheduling algorithm for the scenario and implement the same in C Language. Calculate Average Turn Around time and Average Waiting time for each of the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with the output of the program.

#include<stdio.h>

int hrToMin(char * arrT){
    int hours = (arrT[0] - '0')*10 + arrT[1] - '0';
    int minutes = (arrT[3] - '0')*10 + arrT[4] - '0';
    return hours*60 + minutes;
}

int main(){
    int processes = 4;
    int processNames[] = {1,2,3,4};
    int burstTime[] = {15,30,20,10};
    char *arrivalTime[] = {"09:00","09:10","09:15","09:30"};
    int arrivalT[processes];
    for(int i = 0;i<processes;i++){
        arrivalT[i] = hrToMin(arrivalTime[i]);
    }
    int WT[processes],TAT[processes],completionTime[processes];
    int isCompleted[] = {0,0,0,0};
    int currTime = 0;
    int completedTasks = 0;
    float totalTAT = 0;
    float totalWT = 0;
    
    while(completedTasks<processes){
        int minBT = 9999;
        int shortestTask = -1;
        for(int i = 0;i<processes;i++){
            if(arrivalT[i] <= currTime && isCompleted[i] == 0){
                if(burstTime[i] < minBT){
                    minBT = burstTime[i];
                    shortestTask = i;
                }
            }
        }
        if(shortestTask == -1){
            currTime++;
            continue;
        }
        currTime += burstTime[shortestTask];
        completionTime[shortestTask] = currTime;
        TAT[shortestTask] = completionTime[shortestTask] - arrivalT[shortestTask];
        WT[shortestTask] = TAT[shortestTask] - burstTime[shortestTask];
        totalTAT += TAT[shortestTask];
        totalWT += WT[shortestTask];
        isCompleted[shortestTask] = 1;
        completedTasks++;
    }
    printf("Process\tBurst Time\tArrival Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for(int i = 0;i<processes;i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",processNames[i],burstTime[i],arrivalT[i],completionTime[i],TAT[i],WT[i]);
    }
    printf("Average Turn Around Time : %.2f\n",totalTAT/processes);
    printf("Average Waiting Time : %.2f\n",totalWT/processes);
    return 0;
}