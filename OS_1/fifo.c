#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

int isPageInFrame(int frames[], int frame_count, int page){
	for (int i = 0; i < frame_count; ++i)
	{
		if(frames[i] == page){
			return 1;
		}
	}

	return 0;
}



int main(int argc, char const *argv[])
{
	int frame_count, page_count;
	int page_faults = 0;
	int nextFrameToReplace = 0;

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
	
	int frames[MAX_FRAMES];
	for (int i = 0; i < frame_count; ++i)
	{
		frames[i] = -1;
	}

	for (int i = 0; i < page_count; ++i)
	{
		int currentPage = pages[i];

		if(!isPageInFrame(frames, frame_count, currentPage)){
			frames[nextFrameToReplace] = currentPage;
			page_faults++;
			nextFrameToReplace = (nextFrameToReplace + 1) % frame_count;
		}

	}

	printf("\nTotal Page Faults: %d\n", page_faults);

	return 0;
}