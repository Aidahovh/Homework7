
#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

void sjf(struct Process p[], int n) {
    int completed[100] = {0};
    int time = 0;
    int count = 0;
    int order[100];
    int start[100];
    int finish[100];

    float total_wt = 0;
    float total_tat = 0;
    float total_rt = 0;

    while (count < n) {
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 &&
                p[i].arrival_time <= time) {

                if (shortest == -1 ||
                    p[i].burst_time < p[shortest].burst_time) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        order[count] = shortest;
        start[count] = time;

        p[shortest].response_time =
            time - p[shortest].arrival_time;

        p[shortest].waiting_time =
            p[shortest].response_time;

        time += p[shortest].burst_time;
        finish[count] = time;

        p[shortest].turnaround_time =
            time - p[shortest].arrival_time;

        total_wt += p[shortest].waiting_time;
        total_tat += p[shortest].turnaround_time;
        total_rt += p[shortest].response_time;

        completed[shortest] = 1;
        count++;
    }

    printf("\nSJF Scheduling\n");

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        printf("| P%d (%d-%d) ",
               p[order[i]].pid, start[i], finish[i]);
    }
    printf("|\n");

    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time,
               p[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f\n",
           total_wt / n);

    printf("Average Turnaround Time: %.2f\n",
           total_tat / n);

    printf("Average Response Time: %.2f\n",
           total_rt / n);
}

int main() {
    struct Process p[100];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of processes\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);

        if (p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            printf("Invalid process times\n");
            return 1;
        }
    }

    sjf(p, n);

    return 0;
}

