#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

int findFarthest(int frame_count, int pages[], int frames[], int index, int page_count){
	int farthestDistane = -1;
	int farthestIndex = -1;
	for (int i = 0; i < frame_count; ++i)
	{	
		int j;
		for (j = index; j < page_count; ++j)
		{
			if(frames[i] == pages[j]){
				if(j > farthestDistane){
					farthestDistane = j;
					farthestIndex = i;
				}
				break;
			}
		}
		if(j == page_count){
			return i;
		}



	}
	if(farthestIndex == -1){
		return 0;
	}

	return farthestIndex;


}

int isPageInFrame(int frame_count, int frames[], int page){
	for (int i = 0; i < frame_count; ++i)
	{
		if (frames[i] == page)
		{
			return 1;
		}
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	int frame_count, page_count;
	int counter = 1, page_faults = 0;
	printf("Enter number of frames: ");
	scanf("%d", &frame_count);

	printf("Enter number of pages in reference string: ");
	scanf("%d", &page_count);

	int pages[page_count];
	printf("Enter the reference string: ");
	for (int i = 0; i < page_count; ++i)
	{
		scanf("%d", &pages[i]);
	}

	int frames[frame_count];
	int time[frame_count];
	for (int i = 0; i < frame_count; ++i)
	{
		frames[i] = -1;
		
	}

	for (int i = 0; i < page_count; ++i)
	{
		int currentPage = pages[i];
		if(!isPageInFrame(frame_count, frames, currentPage)){
			int pageToReplace = findFarthest(frame_count, pages, frames, i + 1, page_count);
			frames[pageToReplace] = currentPage;
			page_faults++;

		}

		printf("Current frames: ");  
        for (int k = 0; k < frame_count; ++k) {  
            printf("%d\t", frames[k]);  
        }  
        printf("\n");


	}

	printf("\nTotal Page Faults = %d\n", page_faults);  
	return 0;
}