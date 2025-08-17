#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid;
    int burst;
    int arrival;
    int remaining;
    int start;
    int finish;
    bool completed;
} Process;

void printGanttChart(int *gantt, int len) {
    printf("Gantt Chart : ");
    int last = -1;
    for(int i = 0; i < len; i++) {
        if(gantt[i] != last) {
            printf("P%d ", gantt[i]);
            last = gantt[i];
        }
    }
    printf("\n");
}

void calculateAndPrint(Process *p, int n) {
    float total_wt = 0, total_tat = 0;
    for(int i = 0; i < n; i++) {
        int tat = p[i].finish - p[i].arrival;
        int wt = tat - p[i].burst;
        total_tat += tat;
        total_wt += wt;
    }
    printf("Average waiting time: %.2f\n", total_wt / n);
    printf("Average turnaround time: %.2f\n", total_tat / n);
}

// FCFS
void fcfs(Process *p, int n) {
    int time = 0;
    int gantt[1000], gidx = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].arrival) time = p[i].arrival;
        p[i].start = time;
        time += p[i].burst;
        p[i].finish = time;
        for(int t = p[i].start; t < p[i].finish; t++) {
            gantt[gidx++] = p[i].pid;
        }
    }
    printGanttChart(gantt, gidx);
    calculateAndPrint(p, n);
}


void resetProcesses(Process *p, int *burst, int *arrival, int n) {
    for(int i = 0; i < n; i++) {
        p[i].pid = i;
        p[i].burst = burst[i];
        p[i].arrival = arrival[i];
        p[i].completed = false;
        p[i].start = -1;
        p[i].finish = -1;
    }
}

int main() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    int burst[n], arrival[n];
    printf("Burst time: ");
    for(int i = 0; i < n; i++) scanf("%d", &burst[i]);
    printf("Arrival time: ");
    for(int i = 0; i < n; i++) scanf("%d", &arrival[i]);

    Process p[n];

    printf("\n--- FCFS ---\n");
    resetProcesses(p, burst, arrival, n);
    fcfs(p, n);
    

    return 0;
}
