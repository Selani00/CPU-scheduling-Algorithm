#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateTurnaroundTime(vector<Process>& processes) {
    for (Process& p : processes) {
        p.turnaroundTime = p.completionTime - p.arrivalTime;
    }
}

void calculateWaitingTime(vector<Process>& processes) {
    for (Process& p : processes) {
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }
}

int main() {
    int numberOfProcesses;
    int timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> numberOfProcesses;

    vector<Process> processes(numberOfProcesses);

    cout << "Enter arrival times and burst times for each process:\n";
    for (int i = 0; i < numberOfProcesses; ++i) {
        cout << "Process " << i + 1 << " arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " burst time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].id = i + 1;
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    int currentTime = 0;
    int remainingProcesses = numberOfProcesses;

    while (remainingProcesses > 0) {
        for (int i = 0; i < numberOfProcesses; ++i) {
            if (processes[i].remainingTime > 0) {
                int executeTime = min(timeQuantum, processes[i].remainingTime);
                processes[i].remainingTime -= executeTime;
                currentTime += executeTime;
                if (processes[i].remainingTime == 0) {
                    processes[i].completionTime = currentTime;
                    --remainingProcesses;
                }
            }
        }
    }

    calculateTurnaroundTime(processes);
    calculateWaitingTime(processes);

    // Print table
    cout << "Process\tTurnaround Time\tWaiting Time\n";
    double totalWaitingTime = 0;
    for (const Process& p : processes) {
        cout << p.id << "\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
        totalWaitingTime += p.waitingTime;
    }
    cout << "Average Waiting Time: " << totalWaitingTime / numberOfProcesses << endl;

    return 0;
}
