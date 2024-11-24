#include <stdio.h>
#include <stdlib.h>

void calculateScan(int requests[], int n, int initial_head, int disk_size, int direction){
	int totalseektime = 0;
	int currentHead = initial_head;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if(requests[i] > requests[j]){
				int temp = requests[i];
				requests[i] = requests[j];
				requests[j] = temp;
			}
		}
	}

	printf("\nDisk Scheduling using SCAN Algorithm:\n");
	printf("------------------------------------------------\n");
	printf("| Request No. | Request | Seek Time |\n");
	printf("------------------------------------------------\n");

	int start_index = 0;
	while(start_index < n && requests[start_index] < initial_head){
		start_index++;

	}

	if(direction == 1){
		for (int i = start_index; i < n; ++i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;

			printf("| %2d | %3d | %3d |\n", i - start_index + 1, requests[i], seek_time);

			currentHead = requests[i];

		}

		int end_seek_time = disk_size - 1 - currentHead;
		totalseektime += end_seek_time;
		printf("|  _  | %3d | %3d |\n",disk_size - 1, end_seek_time);
		currentHead = disk_size - 1;

		for (int i = start_index - 1; i >= 0; --i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;

			printf("| %2d | %3d | %3d |\n", start_index - i + n - 1, requests[i], seek_time);

			currentHead = requests[i];


		}

	}else{

		for (int i = start_index - 1; i >= 0; --i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;

			printf("| %2d | %3d | %3d |\n", start_index - i, requests[i], seek_time);

			currentHead = requests[i];

		}

		int end_seek_time = currentHead - 0;
		totalseektime += end_seek_time;

		printf("|  _  |  0  | %3d |\n", end_seek_time);

		currentHead = 0;

		for (int i = start_index; i < n; ++i)
		{
			int seek_time = abs(requests[i] - currentHead);
			totalseektime += seek_time;
			printf("| %2d | %3d | %3d |\n", i + 1 , requests[i], seek_time);
			currentHead = requests[i];



		}



	}

	printf("Total Seek Time: %d\n", totalseektime); 
}

int main(int argc, char const *argv[])
{
	int n, head, direction, disk_size;

	printf("Enter number of disk requests: ");
	scanf("%d", &n);

	int requests[n];

	printf("Enter disk size: ");
	scanf("%d", &disk_size);

	printf("Enter initial head position: ");
	scanf("%d", &head);

	printf("Enter direction:\n 1 - right or 0 - left: ");
	scanf("%d", &direction);

	printf("Enter disk requests: \n");
	for (int i = 0; i < n; ++i)
	{
		printf("Request%d: ", i + 1);
		scanf("%d", &requests[i]);

	}

	calculateScan(requests, n, head, disk_size, direction);



	return 0;
}