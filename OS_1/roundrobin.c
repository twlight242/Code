#include <stdio.h>
#include <stdlib.h>

struct process{
	int id;
	int arrival_time;
	int burst_time;
	int finish_time;
	int turnaround_time;
	int waiting_time;
	int remaining_time;
	

};

void calculateTime(struct process Processes[], int n, int timequantam){
	int currentTime = 0, complete = 0;
	while(complete < n){
		int done = 1;
		for (int i = 0; i < n; ++i)
		{
			if(Processes[i].remaining_time > 0 && Processes[i].arrival_time <= currentTime){
				done = 0;
				if(Processes[i].remaining_time <= timequantam){
					currentTime += Processes[i].remaining_time;
					Processes[i].finish_time = currentTime;
					Processes[i].turnaround_time = Processes[i].finish_time - Processes[i].arrival_time;
					Processes[i].waiting_time = Processes[i].turnaround_time - Processes[i].burst_time;
					Processes[i].remaining_time = 0;
					complete++;

				}else{
					
					Processes[i].remaining_time -= timequantam;
					currentTime += timequantam;
				}
				
			}
		}

		if(done){
			currentTime++;

		}
	}

}

void displayResults(struct process Processes[], int n){
	printf("Pid\t Arrival Time\t Burst Time Completion Time  Turnaround Time  Waiting Time \n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d \t\t %d \t %d \t\t %d \t\t %d \t\t %d \n", Processes[i].id, Processes[i].arrival_time, Processes[i].burst_time, Processes[i].finish_time, Processes[i].turnaround_time, Processes[i].waiting_time);


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
	int n, timequantam;
	printf("Enter number of processes: ");
	scanf("%d", &n);

	struct process Processes[n];

	for (int i = 0; i < n; ++i)
	{
		Processes[i].id = i + 1;
		printf("Enter arrival time and burst time for process %d: ", Processes[i].id);
		scanf("%d %d", &Processes[i].arrival_time, &Processes[i].burst_time);

		

		Processes[i].remaining_time = Processes[i].burst_time;

		



	}

	printf("Enter time quantam: ");
	scanf("%d", &timequantam);

	

	calculateTime(Processes, n, timequantam);
	displayResults(Processes, n);

	


	return 0;
}