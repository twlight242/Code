#include <stdio.h>
#include <stdlib.h>

struct process{
	int id;
	int arrival_time;
	int burst_time;
	int completion_time;
	int waiting_time;
	int turnaround_time;

};

void calculateTime(struct process Processes[], int n){
	int currentTime = 0;
	for (int i = 0; i < n; ++i)		
	{
		if(Processes[i].arrival_time > currentTime){
			currentTime = Processes[i].arrival_time;

		}

		Processes[i].completion_time = currentTime + Processes[i].burst_time;
		Processes[i].turnaround_time = Processes[i].completion_time - Processes[i].arrival_time;
		Processes[i].waiting_time = Processes[i].turnaround_time - Processes[i].burst_time;

		currentTime = Processes[i].completion_time;
		
	}

}

void displayResults(struct process Processes[], int n){
	printf("Pid \t Arrival Time \t Burst Time \t completion time \t Turn around time \t Waiting time\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%d \t %d \t\t %d \t\t %d \t\t\t %d \t\t\t %d \n", Processes[i].id, Processes[i].arrival_time, Processes[i].burst_time, Processes[i].completion_time, Processes[i].turnaround_time, Processes[i].waiting_time);

	}

	float totalturnaroundtime = 0, totalwaitingtime = 0;

	for (int i = 0; i < n; ++i)
	{
		totalturnaroundtime += Processes[i].turnaround_time;
		totalwaitingtime += Processes[i].waiting_time;
	}

	printf("Average turn-around time: %.2f \n", totalturnaroundtime/n);
	printf("Average waiting time: %.2f \n", totalwaitingtime/n);

}


int main(int argc, char const *argv[])
{
	int n;
	printf("Enter number of processes: ");
	scanf("%d", &n);

	struct process Processes[n];

	for (int i = 0; i < n; ++i)
	{
		Processes[i].id = i + 1;
		printf("Enter arrival time and burst time of process: %d ", Processes[i].id);
		scanf("%d %d", &Processes[i].arrival_time, &Processes[i].burst_time);


	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if(Processes[i].arrival_time > Processes[j].arrival_time){
				struct process temp = Processes[i];
				Processes[i] = Processes[j];
				Processes[j] = temp;
			}
		}
	}

	calculateTime(Processes, n);
	displayResults(Processes, n);
	return 0;
}