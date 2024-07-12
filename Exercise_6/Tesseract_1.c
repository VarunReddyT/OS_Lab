/*The library's virtual system is divided into pages of specified size each. 
The system can address up to some amount of memory using logical addresses and 
has a physical memory. 
The page table maps logical pages to physical frames.
Tasks:
1.	Calculate no.of frames and no.of pages
2.	Determine the page number and offset for each logical address.
3.	Use the page table to find the corresponding frame number.*/

/* Sample Input and Output

Enter page size,logical memory capacity and physical memory capacity: 2
6
4

 No of frames=2 
 No.of pages=3
Enter the page table(Enter frame no as -1 if that page is not present in any frame)
pageno	frameno
-------	-------

0		0


1		1


2		-1
Enter the logical address(i.e,page no & offset):1
3
Physical address(i.e,frame no & offset):1,3
Do you want to continue(1/0)?:0*/
#include <stdio.h>

int main()
{
    int pageSize, logicalMemory, physicalMemory;
    int numPages, numFrames;

    printf("Enter page size, logical memory capacity, and physical memory capacity: ");
    scanf("%d %d %d", &pageSize, &logicalMemory, &physicalMemory);
    numPages = logicalMemory / pageSize;
    numFrames = physicalMemory / pageSize;

    printf("\n No of frames = %d\n", numFrames);
    printf(" No of pages = %d\n", numPages);

    int pageTable[numPages];
    printf("Enter the page table (Enter frame no as -1 if that page is not present in any frame):\n");
    printf("pageno\tframeno\n");
    printf("-------\t-------\n");

    for (int i = 0; i < numPages; i++)
    {
        printf("%d\t", i);
        scanf("%d", &pageTable[i]);
    }

    int continueFlag = 1;
    while (continueFlag)
    {
        int pageNumber, offset;
        printf("Enter the logical address (i.e., page no & offset):");
        scanf("%d %d", &pageNumber, &offset);

        int frameNumber = pageTable[pageNumber];

        if (frameNumber != -1)
        {
            printf("Physical address (i.e., frame no & offset): %d,%d\n", frameNumber, offset);
        }
        else
        {
            printf("Page %d is not present in any frame\n", pageNumber);
        }

        printf("Do you want to continue (1/0)?: ");
        scanf("%d", &continueFlag);
    }

    return 0;
}


