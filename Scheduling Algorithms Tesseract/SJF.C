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
    int processess;
    printf("Enter the number of process:");
    scanf("%d",&processess);
    int processName[processess],arrivalTime[processess],burstTime[processess];
    int tempP,tempA,tempB;
    for(int i = 0;i<processess;i++){
        printf("Enter process name, arrival time& burst time:");
        scanf("%d %d %d",&tempP,&tempA,&tempB);
        processName[i] = tempP;
        arrivalTime[i] = tempA;
        burstTime[i] = tempB;
    }
    printf("\n");
    int temp;
    for(int i = 0;i<processess;i++){
        for(int j = 0;j<processess-i-1;j++){
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
    int completionTime[processess],waitingTime[processess];
    int tat[processess],wt[processess];
    int cumulativeSum = 1;
    float totalTat = 0;
    float totalWt = 0;
    printf("ProcessName arrivaltime bursttime  waitingtime turnaroundtime\n");
    for(int i = 0;i<processess;i++){
        cumulativeSum += burstTime[i];
        completionTime[i] = cumulativeSum;
        tat[i] = completionTime[i] - arrivalTime[i];
        wt[i] = tat[i] - burstTime[i];
        totalTat += tat[i];
        totalWt += wt[i];
        printf("%d\t   %d\t\t%d\t\t%d\t\t%d\n",processName[i],arrivalTime[i],burstTime[i],wt[i],tat[i]);
    }
    printf("Average waiting time: %f\n",totalWt/processess);
    printf("Average turnaroundtime: %f\n",totalTat/processess);
    
    return 0;
}