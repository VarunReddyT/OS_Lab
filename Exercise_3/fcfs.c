#include<stdio.h>

int getIndex(int arr[],int size,int element){
    for(int i = 0;i<size;i++){
        if(arr[i]==element){
            return i+1;
        }
    }
    return -1;
}


int main(){
    int processes;
    printf("Enter the number of processes : ");
    scanf("%d",&processes);

    int burstTimes[processes],arrivalTimes[processes];
    int tempB,tempA;

    printf("\nEnter the burst times and arrival times of the processes \n");
    for(int i = 0; i<processes; i++){
        printf("Burst time and arrival time of process %d : ",i+1);
        scanf("%d%d",&tempB,&tempA);
        burstTimes[i] = tempB;  
        arrivalTimes[i] = tempA;
    }

    int copyBurst[processes];
    for(int i = 0;i<processes;i++){
        copyBurst[i] = burstTimes[i];
    }

    int sortTemp;
    for(int i = 0; i<processes;i++){
        for(int j = 0;j<processes-i-1;j++){
            if(arrivalTimes[j] > arrivalTimes[j+1]){
                sortTemp = arrivalTimes[j];
                arrivalTimes[j] = arrivalTimes[j+1];
                arrivalTimes[j+1] = sortTemp;
                sortTemp = burstTimes[j];
                burstTimes[j] = burstTimes[j+1];
                burstTimes[j+1] = sortTemp;
            }
        }
    }

    int turnAroundTime[processes],waitingTime[processes];
    int cumulativeTime = 0;

    printf("\nGantt Chart for FCFS scheduling is : \n");
   
    for(int i = 0;i<processes*2;i++){
        printf("--------");
    }
    printf("\n");
    printf("|");
    int tempIndex = 0;
    for(int i = 0;i<processes;i++){
        tempIndex = getIndex(copyBurst,processes,burstTimes[i]);
        printf("\tP%d\t|",tempIndex);
    }
    printf("\n");
    for(int i = 0;i<processes*2;i++){
        printf("--------");
    }
    printf("\n");
    printf("0\t\t");
    for(int i = 0;i<processes;i++){
        cumulativeTime += burstTimes[i];
        printf("%d\t\t",cumulativeTime);
        turnAroundTime[i]  = cumulativeTime-arrivalTimes[i];
        waitingTime[i] = turnAroundTime[i]-burstTimes[i];
    }
    printf("\n");

    int sumTAT = 0,sumWT = 0;

    for(int i = 0;i<processes;i++){
        sumTAT += turnAroundTime[i];
        sumWT += waitingTime[i];
    }

    printf("\nAverage Turn Around Time for the processes is : %d\n",sumTAT/processes);
    printf("Average Waiting Time for the processes is : %d\n",sumWT/processes);


}