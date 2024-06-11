/* 4. Airlines categorize passengers into different groups based on various criteria such as frequent flyer status, class of service, special needs, and more. Each group is assigned a priority level, and within that priority, boarding is handled in the order that passengers arrive at the gate
•	Priority Assignment:
1.	First Priority: First-class passengers, high-tier frequent flyers, and passengers requiring special assistance (e.g., wheelchair users).Arrival time: 3 and assistance time: 5min
2.	Second Priority: Business class and mid-tier frequent flyers. Arrival time: 0 and assistance time: 10min
3.	Third Priority: Premium economy passengers. Arrival time: 4 and assistance time: 7min
4.	Fourth Priority: Economy class passengers. Arrival time: 1 and assistance time: 8min
5.	Final Priority: Basic economy or last-minute ticket purchasers, Arrival time: 5 and assistance time: 6min
*/

//Identify the type of CPU scheduling algorithm for the scenario and implement the same in C Language. Calculate Average Turn Around time and Average Waiting time for each of the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with the output of the program.

#include<stdio.h>

int main(){
    int n = 5;
    int processNames[] = {1,2,3,4,5};
    int arrivalTime[] = {3,0,4,1,5};
    int burstTime[] = {5,10,7,8,6};
    int remainingTime[] = {5,10,7,8,6};
    int priority[] = {1,2,3,4,5};
    int TAT[n],WT[n],completionTime[n];
    float totalTat = 0, totalWt = 0;
    int currTime = arrivalTime[0];
    
    for(int i = 0;i<n;i++){
        int hPriority = 20;
        int index = -1;
        
        for(int j = 0;j<n;j++){
            if(arrivalTime[j] <= currTime && remainingTime[j] > 0 && priority[j]<hPriority){
                hPriority = priority[j];
                index = j;
            }
        }
        
        if(index == -1){
            currTime++;
            i--;
            continue;
        }
        
        while(remainingTime[index]>0){
            remainingTime[index]--;
            currTime++;
        }
        
        completionTime[index] = currTime;
        TAT[index] = completionTime[index] - arrivalTime[index];
        WT[index] = TAT[index] - burstTime[index];
        
        totalTat += TAT[index];
        totalWt += WT[index];
    }
    
    printf("Process\tPriority\tBT\tAT\tCT\tTAT\tWT\n");
    for(int i = 0;i<n;i++){
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n",processNames[i],priority[i],burstTime[i],arrivalTime[i],completionTime[i],TAT[i],WT[i]);
    }
    
    printf("Average Turn Around Time : %.2f mins\n",totalTat/n);
    printf("Average Waiting Time : %.2f mins\n",totalWt/n);
    
    return 0;
}