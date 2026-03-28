#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "early.h"

typedef struct {
    char name[10];
    int period;
    int burst;
    int remaining;
    int next_release;
    int deadline;
    int current_absolute_deadline;
    int lost;
    int complete;
    int killed;
} TaskEDF;

void early(FILE *input, infoE inf) {
    if (input == NULL) return;

    rewind(input);

    int total_time;
    if (fscanf(input, "%d", &total_time) != 1) return;

    TaskEDF tasks[100];
    int n = 0;

    while (n < 100 && fscanf(input, "%s %d %d %d", tasks[n].name, &tasks[n].burst, &tasks[n].period, &tasks[n].deadline) == 4) {
        tasks[n].remaining = 0;
        tasks[n].next_release = 0;
        tasks[n].current_absolute_deadline = 0;
        tasks[n].lost = 0;
        tasks[n].complete = 0;
        tasks[n].killed = 0;
        n++;
    }

    FILE *output = fopen("edf_dsob.out", "w");
    if (!output) return;

    fprintf(output, "EXECUTION BY EDF\n");
    fprintf(output,"\n");

    int time = 0;
    int last_chosen = -1;
    int current_exec_duration = 0;

    while (time < total_time) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                if (tasks[i].remaining > 0) {
                    tasks[i].lost++;
                    tasks[i].killed++;
                }
                tasks[i].remaining = tasks[i].burst;
                tasks[i].current_absolute_deadline = time + tasks[i].deadline;
                tasks[i].next_release += tasks[i].period;
            }
        }

        int chosen = -1;
        int earliest_deadline = 999999;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                if (tasks[i].current_absolute_deadline < earliest_deadline) {
                    earliest_deadline = tasks[i].current_absolute_deadline;
                    chosen = i;
                }
            }
        }

        if (chosen != last_chosen && last_chosen != -1) {
            if (tasks[last_chosen].remaining == 0) {
                fprintf(output, "[%s] for %d units - F\n", tasks[last_chosen].name, current_exec_duration);
            } else {
                fprintf(output, "[%s] for %d units - H\n", tasks[last_chosen].name, current_exec_duration);
            }
            current_exec_duration = 0;
        }

        if (chosen == -1) {
            fprintf(output, "idle for 1 units\n");
            time++;
            last_chosen = -1;
            continue;
        }

        tasks[chosen].remaining--;
        time++;
        current_exec_duration++;

        if (tasks[chosen].remaining == 0) {
            tasks[chosen].complete++;
        } else if (time >= tasks[chosen].current_absolute_deadline) {
            tasks[chosen].lost++;
            tasks[chosen].killed++;
            tasks[chosen].remaining = 0;
        }

        last_chosen = chosen;
    }

    if (last_chosen != -1) {
        if (tasks[last_chosen].remaining == 0) {
            fprintf(output, "[%s] for %d units - F\n", tasks[last_chosen].name, current_exec_duration);
        } else {
            fprintf(output, "[%s] for %d units - H\n", tasks[last_chosen].name, current_exec_duration);
        }
    }

    fprintf(output, "\nLOST DEADLINES\n");
    fprintf(output,"\n");
    for (int i = 0; i < n; i++) fprintf(output, "[%s] %d\n", tasks[i].name, tasks[i].lost);

    fprintf(output, "\nCOMPLETE EXECUTION\n");
    fprintf(output,"\n");
    for (int i = 0; i < n; i++) fprintf(output, "[%s] %d\n", tasks[i].name, tasks[i].complete);

    fprintf(output, "\nKILLED\n");
    fprintf(output,"\n");
    for (int i = 0; i < n; i++) fprintf(output, "[%s] %d\n", tasks[i].name, tasks[i].killed);

    fclose(output);
}