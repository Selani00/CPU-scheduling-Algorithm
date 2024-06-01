#include<iostream>
using namespace std;

#include<vector>
#include<map>

int main(){

    // get the number of processes
    int number_of_processes;
    cout<< "Enter the number of processes: ";
    cin >> number_of_processes;

    cout <<endl;

    // map to store the arrival time and burst time of each process. Here key is arrival time and value is burst time
    map<int, int> process;

    // Get the arrival time and burst time of each process in a single line
    cout << "Enter the arrival time and burst time of process separated by space: "<<endl;
    for (int i = 0; i < number_of_processes; i++) {
        int arrival_time, burst_time;      
        cin >> arrival_time >> burst_time;

        process[arrival_time] = burst_time;
    }

   

    // array to store the completion time of each process
    vector<int> completion_time(number_of_processes);

    // get the completion time of each process  
    int temp=0; 
    int index =0;
    for(const auto& i: process){
        
        if(i.first == 0){
            temp=  i.second;
        }else{
            temp = i.second + temp;
        }

        completion_time[index] = temp;
        index++;      
    }


    // array to store the turnaround time of each process
    vector<int> turnaround_time(number_of_processes);

    
    // get the turnaround time of each process
    int temp1=0;
    for (auto i: process){
        turnaround_time[temp1] = completion_time[temp1] - i.first;
        temp1++;
    }


    // array to store the waiting time of each process
    vector<int> waiting_time(number_of_processes);

    // get the waiting time of each process
    int temp2=0;
    for (auto i: process){
        waiting_time[temp2] = turnaround_time[temp2] - i.second;
        temp2++;
    }

   
    // print the average waiting times
    int sum =0;
    for(int i=0; i<number_of_processes; i++){
        sum = sum + waiting_time[i];
    }
    double average_waiting_time = sum/number_of_processes;
    cout <<endl;
    cout << "\nAverage waiting time: " << average_waiting_time <<endl;


}