// Implement the C program for CPU Scheduling Algorithms: Round Robin with different arrival time.	

#include <stdio.h>

struct Process 
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void roundRobin(struct Process processes[], int n, int quantum) 
{
    int currentTime = 0;
    int completed = 0;

    while (completed < n) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0) 
            {
                if (processes[i].remaining_time <= quantum) 
                {
                    currentTime += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    completed++;
                } 
                else 
                {
                    currentTime += quantum;
                    processes[i].remaining_time -= quantum;
                }

                processes[i].turnaround_time = currentTime - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                if (processes[i].waiting_time < 0) 
                {
                    processes[i].waiting_time = 0;
                }
            }
        }
    }
}

void calculateAvgTimes(struct Process processes[], int n) 
{
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    for (int i = 0; i < n; i++) 
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() 
{
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Process processes[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) 
    {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    roundRobin(processes, n, quantum);

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    calculateAvgTimes(processes, n);

    return 0;
}
