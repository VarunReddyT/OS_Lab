/*1.Let's consider a school computer lab where students use computers for various educational activities, including research, programming assignments, and multimedia projects based on their arrival times.Here are some example tasks (student activities) that the lab server might receive throughout the day:
•	Student A needs to complete an online quiz: Burst Time = 15 minutes, Arrival Time = 08:30 AM
•	Student B is working on a programming assignment: Burst Time = 40 minutes, Arrival Time = 08:40 AM
•	Student C wants to edit a multimedia project: Burst Time = 25 minutes, Arrival Time = 08:50 AM
•	Student D needs to research for a presentation: Burst Time = 30 minutes, Arrival Time = 09:00 AM
Objective:
Your task as a developer is to  help the students to carry their tasks by using a scheduling algorithm. Calculate the waiting time and turnaround time for each task, and determine the average waiting and turnaround time for the day's tasks.
*/

//Identify the type of CPU scheduling algorithm for the scenario and implement the same in C Language. Calculate Average Turn Around time and Average Waiting time for each of the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with the output of the program.

#include<stdio.h>

int hrToMin(char* arrT){
    int hours = (arrT[0]-'0')*10 + arrT[1]-'0';
    int minutes = (arrT[3]-'0')*10 + arrT[4]-'0';
    return hours*60 + minutes;
}
int main(){
    int processes = 4;
    int burstTime[] = {15,40,25,30};
    char* arrivalTime[] = {"08:30","08:40","08:50","09:00"};
    int arrivalT[processes];
    for(int i = 0;i<processes;i++){
        arrivalT[i] = hrToMin(arrivalTime[i]);
    }
    int completionTime[processes];
    int TAT[processes],WT[processes];
    int cumulativeSum = arrivalT[0];
    float totalTat = 0;
    float totalWt = 0;
    printf("PID\tBT\tAT\tCT\tTAT\tWT\n");
    for(int i = 0;i<processes;i++){
        cumulativeSum += burstTime[i];
        completionTime[i] = cumulativeSum;
        TAT[i] = completionTime[i] - arrivalT[i];
        totalTat += TAT[i];
        WT[i] = TAT[i] - burstTime[i];
        totalWt += WT[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,burstTime[i],arrivalT[i],completionTime[i],TAT[i],WT[i]);
    }
    printf("Average Turn Around Time : %f\n",totalTat/processes);
    printf("Average Waiting Time : %f\n",totalWt/processes);
    
    
    return 0;
}