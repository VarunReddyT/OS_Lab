/*Imagine you are using a web browser that supports multiple tabs, 
you have several tabs open simultaneously. Each tab represents a page in memory 
you've accessed recently. If you open more tabs than your browser can display 
once (exceeding the available memory), the browser needs to manage which 
to keep in memory. Determine which page replacement algorithm was used 
analyze how many pages are being replaced in memory.*/

//Sample Input and Output
/*Enter no of pages:20
Enter the reference string:6 1 1 2 0 3 4 6 0 2 1 2 1 2 0 3 2 1 2 0
Enter no of frames:3

	6
	6	1
	6	1	2
	0	1	2
	0	3	2
	0	3	4
	6	3	4
	6	0	4
	6	0	2
	1	0	2
	3	0	2
	3	1	2
	0	1	2

The no of page faults is 13*/

#include <stdio.h>

void lru_page_replacement(int num_frames, int num_pages, int pages[]) {
    int frames[num_frames];
    int counter[num_frames];
    int page_faults = 0;
    int time = 0;
    int is_changed = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("\n");

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                counter[j] = ++time;
                break;
            }
        }


        if (!found) {
            page_faults++;
            is_changed = 1; 

            int lru_index = 0;
            for (int j = 1; j < num_frames; j++) {
                if (counter[j] < counter[lru_index]) {
                    lru_index = j;
                }
            }

            frames[lru_index] = page;
            counter[lru_index] = ++time;
        }


        if (is_changed) {
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf(" "); 
            }
            printf("\n");
            is_changed = 0;
        }
    }

    printf("\nThe number of page faults is %d\n", page_faults);
}

int main() {
    int num_frames, num_pages;

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    int pages[num_pages];
    printf("Enter the reference string: ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    lru_page_replacement(num_frames, num_pages, pages);

    return 0;
}

