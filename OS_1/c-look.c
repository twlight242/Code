#include <stdio.h>
#include <stdlib.h>

void calculateClook(int requests[], int n, int disk_size, int initial_head, int direction){
	int totalseektime = 0;
	int currentHead = initial_head;

	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if(requests[i] > requests[j]){int temp = requests[i];
						requests[i] = requests[j];
						requests[j] = temp;}
		}
	}

	int start_index = 0;

	while(start_index < n && requests[start_index] < initial_head){
		start_index++;
	}

	printf("\nDisk Scheduling using C-LOOK Algorithm:\n");
	printf("------------------------------------------------\n");
	printf("| Request no | Request | Seek time | \n");
	printf("------------------------------------------------\n");

	if(direction == 1){
		for (int i = start_index; i < n; ++i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;
			printf("| %2d | %3d | %3d | \n", i - start_index + 1, requests[i], seek_time);
			currentHead = requests[i];
		}

		int reset_seek_time = abs(currentHead - requests[0]);
		totalseektime += reset_seek_time;
		printf("| _ | %3d | %3d | \n", requests[0], reset_seek_time);

		currentHead = requests[0];

		for (int i = 1; i < start_index; ++i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;
			printf("| %2d | %3d | %3d | \n", i + n - start_index, requests[i], seek_time);
			currentHead = requests[i];
		}
	}else{
		for (int i = start_index - 1; i >= 0; --i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;
			printf("| %2d | %3d | %3d | \n", start_index - i, requests[i], seek_time);
			currentHead = requests[i];
		}

		int reset_seek_time = abs(currentHead - requests[n - 1]);
		totalseektime += reset_seek_time;
		printf("| _ | %3d | %3d | \n", requests[n - 1], reset_seek_time);
		currentHead = requests[n - 1];

		for (int i = n - 2; i >= start_index; --i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;
			printf("| %2d | %3d | %3d | \n",  n - (i - start_index) - 1, requests[i], seek_time);
			currentHead = requests[i];
		}




	}

	printf("------------------------------------------------\n");
	printf("Total Seek Time: %d\n", totalseektime);



}


int main(int argc, char const *argv[])
{
	

	int n, disk_size, head, direction;

	printf("Enter number of disk requests: ");
	scanf("%d", &n);

	printf("Enter disk size: ");
	scanf("%d", &disk_size);

	printf("Enter initial head position: ");
	scanf("%d", &head);

	printf("Enter direction:\n 1 - right or 0 - left: ");
	scanf("%d", &direction);

	int requests[n];

	printf("Enter disk requests: \n");
	for (int i = 0; i < n; ++i)
	{
		printf("Request%d: ", i + 1);
		scanf("%d", &requests[i]);

	}

	calculateClook(requests, n, disk_size, head, direction);

	return 0;
}