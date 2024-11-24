#include <iostream>
#include <queue>
#include <vector>

using namespace std;



int main(int argc, char const *argv[])
{
	int n, timeQuantum;

	cout << "Enter number of processes: ";
	cin >> n;

	cout << "Enter Time Quantum: ";
	cin >> timeQuantum;

	vector<int> at(n), bt(n), tat(n), wt(n), ct(n), remaining_bt(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";

	for (int i = 0; i < n; ++i)
	 {
	 	cin >> at[i] >> bt[i];
	 	remaining_bt[i] = bt[i];
	 }

	 int currentTime = 0, complete = 0;
	 queue<int> readyQueue;
	 vector<bool> inQueue(n, false);

	 for (int i = 0; i < n; ++i)
	 {
	 	if(at[i] == 0){
	 		readyQueue.push(i);
	 		inQueue[i] = true;
	 	}
	 }

	 while(complete < n){

	 	if(readyQueue.empty()){
	 		for (int i = 0; i < n; ++i)
	 		{
	 			if(remaining_bt[i] > 0){
	 				readyQueue.push(i);
	 				inQueue[i] = true;
	 				break;
	 			}
	 		}
	 	}

	 	int index = readyQueue.front();
	 	readyQueue.pop();
	 	inQueue[index] = false;

	 	int executionTime = min(timeQuantum, remaining_bt[index]);
	 	currentTime += executionTime;
	 	remaining_bt[index] -= executionTime;

	 	for (int i = 0; i < n; ++i)
	 	{
	 		if(i != index && remaining_bt[i] > 0 && at[i] <= currentTime && !inQueue[i]){
	 			readyQueue.push(i);
	 			inQueue[i] = true;
	 		}
	 	}

	 	if(remaining_bt[index] > 0){
	 		readyQueue.push(index);
	 		inQueue[index] = true;
	 	}else{
	 		complete++;
	 		ct[index] = currentTime;
	 		tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
	 	}

	 }

	 double totalWT = 0;
    double totalTAT = 0;

    // Display the results
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i]
             << "\t" << tat[i] << "\t" << wt[i] << "\n";
            totalWT += wt[i];
            totalTAT += tat[i];
    }


    double avgWT = (double)totalWT / n;
    double avgTAT = (double)totalTAT / n;

    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;

	return 0;
}
