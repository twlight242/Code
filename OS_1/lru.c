#include <stdio.h>
#include <stdlib.h>



int findLRU(int frame_count, int time[]){
	int min = time[0];
	int pos = 0;
	for (int i = 1; i < frame_count; ++i)
	{
		if(min > time[i]){
			min= time[i];
			pos = i;
		}
	}

	return pos;
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
		time[i] = 0;
	}

	for (int i = 0; i < page_count; ++i)
	{
		int currentPage = pages[i];

		int found = 0;

		for (int j = 0; j < frame_count; ++j)
		{
			if(frames[j] == currentPage){
				found = 1;
				time[j] = counter++;
				break;

			}
		}

		if(!found){
			int pos = findLRU(frame_count, time);
			frames[pos] = currentPage;
			time[pos] = counter++;
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