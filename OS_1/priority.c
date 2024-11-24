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
	int priority;
	int remaining_time;
	bool isCompleted;

};

void priority_non_premptive(struct process Processes[], int n){
	int currentTime = 0, complete = 0;
	while(complete < n){
		int minindex = -1;
		int highestpriority = 1e9;
		for (int i = 0; i < n; ++i)
		{
			if(!Processes[i].isCompleted && Processes[i].arrival_time <= currentTime && Processes[i].priority < highestpriority){
				highestpriority = Processes[i].priority;
				minindex = i;
			}
			
		}
		if(minindex == -1){
				currentTime++;
			}else{
				Processes[minindex].finish_time = currentTime + Processes[minindex].burst_time;
				Processes[minindex].turnaround_time = Processes[minindex].finish_time - Processes[minindex].arrival_time;
				Processes[minindex].waiting_time = Processes[minindex].turnaround_time - Processes[minindex].burst_time;

				Processes[minindex].isCompleted = true;

				currentTime = Processes[minindex].finish_time;
				complete++;
			}
	}

}

void priority_premptive(struct process Processes[], int n){
	int currentTime = 0, complete = 0;
	while(complete < n){
		int minindex = -1;
		int highestpriority = 1e9;
		for (int i = 0; i < n; ++i)
		{
			if(!Processes[i].isCompleted && Processes[i].arrival_time <= currentTime && Processes[i].priority < highestpriority){
				highestpriority = Processes[i].priority;
				minindex = i;
			}

			
		}

		if(minindex != -1){
				Processes[minindex].remaining_time--;
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
	printf("Pid\t Arrival Time\t Burst Time  Priority\t Completion Time  Turnaround Time  Waiting Time \n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d \t\t %d \t %d \t\t %d \t\t %d \t\t %d \t\t %d \n", Processes[i].id, Processes[i].arrival_time, Processes[i].burst_time, Processes[i].priority, Processes[i].finish_time, Processes[i].turnaround_time, Processes[i].waiting_time);


	}

	float totalturnaroundtime = 0 , totalwaitingtime = 0;

	for (int i = 0; i < n; ++i)
	{
		totalturnaroundtime += Processes[i].turnaround_time;
		totalwaitingtime += Processes[i].waiting_time;
	}

	printf("Average turn-around time is: %.2f \n", totalturnaroundtime/n);
	printf("Average waiting time is: %.2f \n", totalwaitingtime/n);


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
		printf("Enter arrival time and burst time and priority for process %d: ", Processes[i].id);
		scanf("%d %d %d", &Processes[i].arrival_time, &Processes[i].burst_time, &Processes[i].priority);

		Processes[i].isCompleted = false;

		Processes[i].remaining_time = Processes[i].burst_time;


	}

	int choice;

	printf("Choose scheduling: \n 1. Non-premptive Priority \n 2. Premptive Priority \n");
	scanf("%d", &choice);
	
	if(choice == 1){
		priority_non_premptive(Processes, n);
		displayResults(Processes, n);
	}else if(choice == 2){
		priority_premptive(Processes, n);
		displayResults(Processes, n);

	}else{
		printf("Invalid choice!\n");
		return 0;
	}


	return 0;
}