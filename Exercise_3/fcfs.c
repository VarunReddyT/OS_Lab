#include<stdio.h>

int main(){
    int processes;
    printf("Enter the number of processes : ");
    scanf("%d",&processes);

    int burstTimes[processes],arrivalTimes[processes],ganttProcess[processes];
    int tempB,tempA,sortTemp;

    printf("\nEnter the burst times and arrival times of the processes \n");
    for(int i = 0; i<processes; i++){
        ganttProcess[i] = i;
        printf("Burst time and arrival time of process %d : ",i);
        scanf("%d%d",&tempB,&tempA);
        burstTimes[i] = tempB;  
        arrivalTimes[i] = tempA;
    }

    for(int i = 0; i<processes;i++){
        for(int j = 0;j<processes-i-1;j++){
            if(arrivalTimes[j] > arrivalTimes[j+1]){
                sortTemp = arrivalTimes[j];
                arrivalTimes[j] = arrivalTimes[j+1];
                arrivalTimes[j+1] = sortTemp;
                sortTemp = burstTimes[j];
                burstTimes[j] = burstTimes[j+1];
                burstTimes[j+1] = sortTemp;
                sortTemp = ganttProcess[j];
                ganttProcess[j] = ganttProcess[j+1];
                ganttProcess[j+1] = sortTemp;

            }
        }
    }

    int turnAroundTime[processes],waitTime[processes];
    // int completionTime[processes];
    int cumulativeTime = 0;

    printf("\nGantt Chart for FCFS scheduling is : \n");
   
    for(int i = 0;i<processes*2;i++){
        printf("--------");
    }
    printf("\n");
    printf("|");
    for(int i = 0;i<processes;i++){
        printf("\tP%d\t|",ganttProcess[i]);
    }
    printf("\n");
    for(int i = 0;i<processes*2;i++){
        printf("--------");
    }
    printf("\n");
    printf("0\t\t");

    for(int i = 0;i<processes;i++){
        cumulativeTime += burstTimes[i];
        // completionTime[i] = cumulativeTime;
        printf("%d\t\t",cumulativeTime);
        turnAroundTime[i]  = cumulativeTime-arrivalTimes[i];
        waitTime[i] = turnAroundTime[i]-burstTimes[i];
    }
    printf("\n\n");

    // for(int i = 0;i<processes;i++){
    //     printf("CT for P%d = %d\nTAT for P%d = %d\nWT for P%d = %d\n",i+1,completionTime[i],i+1,turnAroundTime[i],i+1,waitingTime[i]);
    //     printf("\n");
    // }
    
    int sumTAT = 0,sumWT = 0;

    for(int i = 0;i<processes;i++){
        sumTAT += turnAroundTime[i];
        sumWT += waitTime[i];
    }

    printf("Average Turn Around Time for the processes is : %d\n",sumTAT/processes);
    printf("Average Waiting Time for the processes is : %d\n",sumWT/processes);
    return 0;
}