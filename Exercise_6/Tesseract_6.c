/*Imagine you are managing a library with limited shelf space for books ,
capable of holding a fixed number of books.There are more books in the library 
than there are shelves, necessitating a system to decide which books to keep 
on the shelves for quick access. When a new book needs to be placed on the 
shelf (cache miss), algorithm would replace the book that is least likely 
to be requested again, based on perfect knowledge of future borrowing patterns. 
When a new book needs to be placed on the shelf (cache miss), 
the  algorithm would replace the book that is least likely to be requested 
again in the future, based on perfect knowledge of future borrowing patterns.*/

//Sample Input & Output
/*Enter number of frames: 3
Enter number of pages: 20
Enter page reference string: 6 1 1 2 0 3 4 6 0 2 1 2 1 2 0 3 2 1 2 0

6	-1	-1	
6	1	-1	
6	1	-1	
6	1	2	
6	0	2	
6	0	3	
6	0	4	
6	0	4	
6	0	4	
2	0	4	
2	0	1	
2	0	1	
2	0	1	
2	0	1	
2	0	1	
2	3	1	
2	3	1	
2	3	1	
2	3	1	
0	3	1	

Total Page Faults = 10*/


#include <stdio.h>

int find_furthest_page_index(int pages[], int current_index, int frames[], int num_frames, int num_pages) {
    int furthest_index = -1;
    int furthest_distance = -1;

    for (int i = 0; i < num_frames; i++) {
        int j;
        for (j = current_index; j < num_pages; j++) {
            if (frames[i] == pages[j]) {
                if (j > furthest_distance) {
                    furthest_distance = j;
                    furthest_index = i;
                }
                break;
            }
        }
        if (j == num_pages) {
            return i;
        }
    }
    return furthest_index;
}

void optimal_page_replacement(int num_frames, int num_pages, int pages[]) {
    int frames[num_frames];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;
        

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            page_faults++;
            int replace_index = find_furthest_page_index(pages, i + 1, frames, num_frames, num_pages);

            frames[replace_index] = page;
        }


        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("-1 ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
}

int main() {
    int num_frames, num_pages;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    int pages[num_pages];
    printf("Enter page reference string: ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    optimal_page_replacement(num_frames, num_pages, pages);

    return 0;
}

