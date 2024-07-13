/*You are a systems engineer at MemoryOptimize Inc., a company specializing in developing high-efficiency memory management systems for operating systems. Your team has been testing different page replacement algorithms to determine the best one for the upcoming OS release.The system has 3 page frames available. Here is the page reference string that was used in the test:
1, 2, 3, 4, 2, 1, 5, 1, 2, 3, 4, 5
Your colleague provides the following description of the page replacement behavior:
1.	The first three page requests (1, 2, 3) fill the available frames.
2.	When the fourth page (4) is requested, it replaces the page (1) that was loaded into memory.
3.	Subsequent requests for pages that are already in memory (2, 1) do not cause any replacements.
4.	When a new page (5) is requested, it replaces page (2) that was loaded into memory 
 Based on the described behavior, determine which page replacement algorithm was used
and analyze how many  pages are being replaced in memory.*/

// Sample Input and output
/*ENTER THE NUMBER OF PAGES:
20

 ENTER THE PAGE NUMBER :
6
1
1
2
0
3
4
6
0
2
1
2
1
2
0
3
2
1
2
0

 ENTER THE NUMBER OF FRAMES :3
	ref string	 page frames
6		6	-1	-1	
1		6	1	-1	
1		
2		6	1	2	
0		0	1	2	
3		0	3	2	
4		0	3	4	
6		6	3	4	
0		6	0	4	
2		6	0	2	
1		1	0	2	
2		
1		
2		
0		
3		1	3	2	
2		
1		
2		
0		1	3	0	
Page Fault Is 12*/

#include<stdio.h>


int checkElement(int elem, int arr[], int n){
    for(int i = 0;i<n;i++){
        if(arr[i] == elem){
            return 1;
        }
    }
    return 0;
}
int main(){
    int pages;
    printf("ENTER THE NUMBER OF PAGES:\n");
    scanf("%d",&pages);
    int pageNums[pages];

    int pageNumber;
    printf(" ENTER THE PAGE NUMBER :\n");
    for(int i = 0;i<pages;i++){
        scanf("%d",&pageNumber);
        pageNums[i] = pageNumber;
    }

    int frames;
    printf(" ENTER THE NUMBER OF FRAMES :");
    scanf("%d",&frames);

    printf("	ref string	 page frames\n");


    // FIFO array
    int fifo[frames];

    for(int i = 0;i<frames;i++){
        fifo[i] = -1;
    }
    int curr = 0;
    int pageFaults = 0;
    int counter = 0;
    int time[frames];

    for(int i = 0;i<pages;i++){
        if(checkElement(pageNums[i],fifo,frames) == 1){
            printf("%d\n",pageNums[i]);
        }
        else{
            pageFaults++;
            fifo[curr] = pageNums[i];
            printf("%d\t",pageNums[i]);
            for(int j = 0;j<frames; j++){
                printf("%d  ",fifo[j]);
            }
            printf("\n");
            curr++;
            if(curr == frames){
                curr = 0;
            }
        }
    }

    printf("Page Fault Is %d\n",pageFaults);

    return 0;

}