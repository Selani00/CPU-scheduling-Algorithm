#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    // Define a structure to represent each process
    typedef struct process {
        int arrival_time, burst_time, completion_time, turnaround_time, waiting_time, btt;
        string pro_id; // Process ID
    } Schedule;

    // Comparison function to sort processes by arrival time
    auto compare = [](Schedule a, Schedule b) {
        return a.arrival_time < b.arrival_time;
    };

    // Comparison function to sort processes by burst time
    auto compare2 = [](Schedule a, Schedule b) {
        return a.burst_time < b.burst_time;
    };

    Schedule pro[10]; // Array to store processes
    int n, i, j, pcom; // n: number of processes, i & j: iteration variables, pcom: processes completed

    cout << "Enter the number of Processes: ";
    cin >> n;

    cout << "Enter the arrival time and burst time of process separated by space: \n";

    // Input process details
    for (i = 0; i < n; i++) {
               
        cin >> pro[i].arrival_time; 
        cin >> pro[i].burst_time;   
        pro[i].btt = pro[i].burst_time; 
    }

    // Sort processes by their arrival time
    sort(pro, pro + n, compare);

    i = 0;     
    pcom = 0; 

    // Loop until all processes are completed
    while (pcom < n) {
        // Find the processes that have arrived by the current time
        for (j = 0; j < n; j++) {
            if (pro[j].arrival_time > i)
                break;
        }

        // Sort the arrived processes by burst time
        sort(pro, pro + j, compare2);

        // If there are processes that have arrived
        if (j > 0) {
            // Find the first process that is not yet completed
            for (j = 0; j < n; j++) {
                if (pro[j].burst_time != 0)
                    break;
            }
            // If the next process's arrival time is in the future, skip time to its arrival
            if (pro[j].arrival_time > i) {
                i = pro[j].arrival_time;
            }
            // Update the completion time of the current process
            pro[j].completion_time = i + 1;
            // Decrement the remaining burst time of the current process
            pro[j].burst_time--;
        }
        i++; // Increment current time
        pcom = 0; // Reset completed process count

        // Count the number of processes that are completed
        for (j = 0; j < n; j++) {
            if (pro[j].burst_time == 0)
                pcom++;
        }
    }

    double sum = 0;        
    double avg_wait_time;  

    // Calculate turnaround time and waiting time for each process
    for (i = 0; i < n; i++) {
        pro[i].turnaround_time = pro[i].completion_time - pro[i].arrival_time; 
        pro[i].waiting_time = pro[i].turnaround_time - pro[i].btt;             

        sum += pro[i].waiting_time; // Add waiting time to sum
    }

    // Calculate average waiting time
    avg_wait_time = sum / n;
    
    cout << "\nAverage waiting time: " << avg_wait_time << endl;

    return 0;
}
