/* Write a program for SJF
Enter the number of process:4
Enter process name, arrival time& burst time:1
1
3
Enter process name, arrival time& burst time:2
2
4
Enter process name, arrival time& burst time:3
1
2
Enter process name, arrival time& burst time:4
4
4

Processname	arrivaltime	bursttime	waitingtime	turnaroundtime
3	       1		       2		       0		       2
1	       1		       3		       2		       5
2	       2		       4		       4		       8
4	       4		       4		       6		      10
Average waiting time: 3.000000
Average turnaroundtime: 6.250000*/

#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of process:");
    scanf("%d",&n);
    int processName[n],arrivalTime[n],burstTime[n];
    int temp;
    for(int i = 0;i<n;i++){
        printf("Enter process name, arrival time& burst time:");
        scanf("%d %d %d",&processName[i],&arrivalTime[i],&burstTime[i]);
    }
    printf("\n");
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n-i-1;j++){
            if((arrivalTime[j] > arrivalTime[j+1]) || arrivalTime[j] == arrivalTime[j+1] && burstTime[j] > burstTime[j+1]){
                temp = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j+1];
                arrivalTime[j+1] = temp;
                temp = burstTime[j];
                burstTime[j] = burstTime[j+1];
                burstTime[j+1] = temp;
                temp = processName[j];
                processName[j] = processName[j+1];
                processName[j+1] = temp;
            }
        }
    }
    int completionTime[n],waitingTime[n],TAT[n],WT[n];
    int cumulativeSum = 1;
    float totalTat = 0, totalWt = 0;
    printf("ProcessName Arrivaltime Bursttime  WaitingTime TurnaroundTime\n");
    for(int i = 0;i<n;i++){
        cumulativeSum += burstTime[i];
        completionTime[i] = cumulativeSum;
        TAT[i] = completionTime[i] - arrivalTime[i];
        WT[i] = TAT[i] - burstTime[i];
        totalTat += TAT[i];
        totalWt += WT[i];
        printf("%d\t   %d\t\t%d\t\t%d\t\t%d\n",processName[i],arrivalTime[i],burstTime[i],WT[i],TAT[i]);
    }
    printf("Average waiting time: %f\n",totalWt/n);
    printf("Average turnaroundtime: %f\n",totalTat/n);
    
    return 0;
}