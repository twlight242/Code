#include <stdio.h>
#include <stdlib.h>

void calculate(int requests[], int n, int initial_head){
	int totalseektime = 0;
	int visited[n];
	int currentHead = initial_head;
	int count = 0;

	for (int i = 0; i < n; ++i)
	{
		visited[i] = 0;
	}

	printf("\nDisk Scheduling using SSTF Algorithm:\n");
	printf("------------------------------------------------\n");
	printf("| Request No. | Request | Seek Time |\n");
	printf("------------------------------------------------\n");

	while(count < n){
		int minseektime = 10000;
		int minindex = -1;
		for (int i = 0; i < n; ++i)
		{
			if(!visited[i]){
				int seek_time = abs(requests[i] - currentHead);
				if(seek_time < minseektime){
					minseektime = seek_time;
					minindex = i;
				}
			}
		}

		if(minindex != -1){
			totalseektime += minseektime;
			printf("| %2d | %3d | %3d |\n", count + 1, requests[minindex], minseektime);
			currentHead = requests[minindex];
			visited[minindex] = 1;
			count++;
		}
	}

	printf("------------------------------------------------\n");
	printf("Total Seek Time: %d\n", totalseektime);
}

int main(int argc, char const *argv[])
{
	int n, head;
	printf("Enter number of disk requests: ");
	scanf("%d", &n);

	int requests[n];

	printf("Enter initial head position: ");
	scanf("%d", &head);

	printf("Enter disk requests: \n");
	for (int i = 0; i < n; ++i)
	{
		printf("Request %d: ", i + 1);
		scanf("%d", &requests[i]);
	}

	calculate(requests, n, head);



	return 0;
}