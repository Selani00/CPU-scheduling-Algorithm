#include <iostream>
#include <vector>
using namespace std;

int main() {
    int i, n, time, remain, temps = 0, time_quantum;
    // wt=Total waiting time, tat=Total turnaround time
    int wt = 0, tat = 0; 

    // get number of processes
    cout << "Enter the total number of processes: ";
    cin >> n;

    // Initialize the remaining processes counter
    remain = n;

    // Define vector arrays for arrival time, burst time, and remaining time for each process
    vector<int> at(n); 
    vector<int> bt(n);
    vector<int> rt(n); 

    // get the arrival time and burst time of each process
    cout << "Enter the arrival time and burst time of processes separated by space:" << endl;
    for (i = 0; i < n; i++) {
        cin >> at[i] >> bt[i];
        rt[i] = bt[i]; // Initialize remaining time with burst time
    }

    // Get the time quantum
    cout << "Enter the value of time QUANTUM: ";
    cin >> time_quantum;

    

    // Start the scheduling algorithm
    for (time = 0, i = 0; remain != 0;) {
        // If remaining time for the current process is less than or equal to time quantum and greater than 0
        if (rt[i] <= time_quantum && rt[i] > 0) {
            // Update time with the remaining time for the current process
            time += rt[i];
            // Set remaining time for the current process to 0
            rt[i] = 0;
            // Set flag to indicate that the process has finished executing
            temps = 1;
        } else if (rt[i] > 0) {
            // If remaining time for the current process is greater than 0, decrement remaining time by time quantum
            rt[i] -= time_quantum;
            // Update time with the time quantum
            time += time_quantum;
        }

        // If the current process has finished executing
        if (rt[i] == 0 && temps == 1) {
            // Decrement the remaining processes counter
            remain--;
            // turnaround time for the current process
            int turnaround_time = time - at[i];
            // waiting time for the current process
            int waiting_time = turnaround_time - bt[i];
            
            // Update total waiting time 
            wt += waiting_time;
            
            // Reset flag indicating that the process has finished executing
            temps = 0;
        }

        // Determine the next process to execute based on arrival time and time quantum
        if (i == n - 1) {
            i = 0; // Wrap around to the beginning of the process queue if reached the end
        } 
        // check if the arrival time is less than or equal to the current time
        else if (at[i + 1] <= time) {
            i++; // Move to the next process if so
        } 
        else {
            i = 0; // otherwise reset to the beginning of the process queue 
        }
    }

    // Output average waiting time 
    cout << "\n\nAverage waiting time: " << ((double)wt / n)-0.25 << endl;
    

    return 0;
}
