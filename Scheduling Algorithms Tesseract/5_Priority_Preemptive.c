/* 5. An IT help desk in a large corporation handles a range of technical issues and requests from employees. Given the varied nature and urgency of these issues, which scheduling system is employed to ensure that critical IT support requests are handled promptly, while less urgent issues are addressed in an orderly fashion. IT staff can switch between tasks based on real-time reevaluation of priorities as new tickets arrive.
Considering this as the inputs: Calculate Average Turn Around time and Average Waiting time
Process Id	Priority	Arrival Time	Burst Time
1	        2(L)	    0	                     1
2       	6	        1                      	7
3	        3	        2	                    3
4	        5           3                   	6
5	        4	        4                   	5
6	        10(H)   	5	                    15
7	        9	        15	                    8 */

//Identify the type of CPU scheduling algorithm for the scenario and implement the same in C Language. Calculate Average Turn Around time and Average Waiting time for each of the scheduling algorithm by taking arrival times accordingly.
//Calculate the times by using gantt chart in observation and crosscheck the same with the output of the program.

#include<stdio.h>

int main(){
    int n = 7;
    int processNames[] = {1,2,3,4,5,6,7};
    int priority[] = {2,6,3,5,4,10,9};
    int arrivalTime[] = {0,1,2,3,4,5,15};
    int burstTime[] = {1,7,3,6,5,15,8};
    int remaining[] = {1,7,3,6,5,15,8};
    int completionTime[n],TAT[n],WT[n];
    float totalTat = 0, totalWt = 0;
    int currTime = 0,completed = 0;
    
    while(completed < n){
        int hPriority = -1;
        int index = -1;
        for(int i = 0;i<n;i++){
            if(arrivalTime[i] <= currTime && remaining[i]>0 && priority[i]>hPriority){
                hPriority = priority[i];
                index = i;
            }
        }
        if(index == -1){
            currTime++;
            continue;
        }
        
        remaining[index]--;
        currTime++;
        
        if(remaining[index] == 0){
            completionTime[index] = currTime;
            TAT[index] = completionTime[index] - arrivalTime[index];
            WT[index] = TAT[index] - burstTime[index];
            
            totalTat += TAT[index];
            totalWt += WT[index];
            
            completed++;
        }
    }
    
    printf("Process\tPriority\tBT\tAT\tCT\tTAT\tWT\n");
    for(int i = 0;i<n;i++){
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n",processNames[i],priority[i],burstTime[i],arrivalTime[i],completionTime[i],TAT[i],WT[i]);
    }
    
    printf("Average Turn Around Time : %.2f mins\n",totalTat/n);
    printf("Average Waiting Time : %.2f mins\n",totalWt/n);
    return 0;
}