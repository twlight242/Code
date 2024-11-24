#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process{
	int id;
	int arrival_time;
	int burst_time;
	int finish_time;
	int turnaround_time;
	int waiting_time;
	int remaining_time;
	bool isCompleted;

};

void calculateTime(struct process Processes[], int n){
	int currentTime = 0, complete = 0;

	while(complete < n){
		int minindex = -1;
		int min_remaining_time = 1e9;

		for (int i = 0; i < n; ++i)
		{
			if(!Processes[i].isCompleted && Processes[i].arrival_time <= currentTime && Processes[i].remaining_time < min_remaining_time){
				min_remaining_time = Processes[i].remaining_time;
				minindex = i;

			}
		}

		if(minindex != -1){
			Processes[minindex] = Processes[minindex].remaining_time--;
			currentTime++;

			if(Processes[minindex].remaining_time == 0){
				Processes[minindex].finish_time = currentTime;
				Processes[minindex].turnaround_time = Processes[minindex].finish_time - Processes[minindex].arrival_time;
				Processes[minindex].waiting_time = Processes[minindex].turnaround_time - Processes[minindex].burst_time;
				Processes[minindex].isCompleted = true;
				complete++;
			}

		}else{
			currentTime++;
		}


	}
}

void displayResults(struct process Processes[], int n){
	printf("Pid \t Arrival Time \t Burst Time \t completion time \t Turn around time \t Waiting time\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%d \t %d \t\t %d \t\t %d \t\t\t %d \t\t\t %d \n", Processes[i].id, Processes[i].arrival_time, Processes[i].burst_time, Processes[i].finish_time, Processes[i].turnaround_time, Processes[i].waiting_time);

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
		Processes[i].isCompleted = false;
		Processes[i].remaining_time = Processes[i].burst_time;



	}

	calculateTime(Processes, n);
	displayResults(Processes, n);

	return 0;
}