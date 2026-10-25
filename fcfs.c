#include <stdio.h>
#define MAX 100

typedef struct {
    int pid, arrival_time, burst_time;
    int waiting_time, turnaround_time, response_time;
} Process;

void fcfs(Process p[], int n) {
    int order[MAX], start[MAX], finish[MAX];
    double total_wt = 0, total_tat = 0, total_rt = 0;
    for (int i = 0; i < n; i++) order[i] = i;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[order[j]].arrival_time < p[order[i]].arrival_time) {
                int temp = order[i]; order[i] = order[j]; order[j] = temp;
            }
    int time = 0;
    for (int i = 0; i < n; i++) {
        int k = order[i];
        if (time < p[k].arrival_time) time = p[k].arrival_time;
        start[i] = time;
        p[k].waiting_time = time - p[k].arrival_time;
        p[k].response_time = p[k].waiting_time;
        time += p[k].burst_time;
        finish[i] = time;
        p[k].turnaround_time = time - p[k].arrival_time;
    }
    printf("\n=== First Come First Served (FCFS) ===\nGantt Chart: ");
    int previous = 0;
    for (int i = 0; i < n; i++) {
        if (start[i] > previous) printf("| Idle (%d-%d) ", previous, start[i]);
        printf("| P%d (%d-%d) ", p[order[i]].pid, start[i], finish[i]);
        previous = finish[i];
    }
    printf("|\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time,
               p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

int main() {
    Process p[MAX]; int n;
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &p[i].arrival_time, &p[i].burst_time) != 2 ||
            p[i].arrival_time < 0 || p[i].burst_time <= 0) return 1;
    }
    fcfs(p, n);
    return 0;
}

