#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rate.h"

int compare(const void *a, const void *b) {
    return ((Task*)a)->period - ((Task*)b)->period;
}

void rate(FILE *input, infoR inf) {
    if (!input) return;
    rewind(input);

    int total_time, n = 0;
    if (fscanf(input, "%d", &total_time) != 1) return;

    Task tasks[100];
    memset(tasks, 0, sizeof(tasks));

    while (n < 100) {
        char temp_name[10];
        int p, b;
        if (fscanf(input, "%s %d %d", temp_name, &p, &b) != 3) break;

        if (p <= inf.per) {
            strcpy(tasks[n].name, temp_name);
            tasks[n].period = p;
            tasks[n].burst = b;
            n++;
        }
    }

    qsort(tasks, n, sizeof(Task), compare);

    FILE *output = fopen("rate_dsob.out", "w");
    if (!output) return;

    fprintf(output, "EXECUTION BY RATE\n");
    fprintf(output, "\n");

    int time = 0, last_chosen = -1, duration = 0;

    while (time < total_time) {
        int chosen = -1;

        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                if (tasks[i].remaining > 0) {
                    tasks[i].lost++;
                    tasks[i].killed++;
                }
                tasks[i].remaining = tasks[i].burst;
                tasks[i].deadline = time + tasks[i].period;
                tasks[i].next_release += tasks[i].period;
            }
        }

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                chosen = i;
                break;
            }
        }

        if (chosen != last_chosen || duration >= inf.cap) {
            if (last_chosen != -1) {
                fprintf(output, "[%s] for %d units - %c\n", tasks[last_chosen].name, duration, tasks[last_chosen].remaining == 0 ? 'F' : 'H');
            } else if (time > 0 && duration > 0) {
                fprintf(output, "idle for %d units\n", duration);
            }
            duration = 0;
        }

        if (chosen != -1) {
            tasks[chosen].remaining--;
            if (tasks[chosen].remaining == 0) {
                tasks[chosen].complete++;
            } else if (time + 1 >= tasks[chosen].deadline) {
                tasks[chosen].lost++;
                tasks[chosen].killed++;
                tasks[chosen].remaining = 0;
            }
            last_chosen = chosen;
        } else {
            last_chosen = -1;
        }

        duration++;
        time++;
    }

    if (last_chosen != -1) {
        fprintf(output, "[%s] for %d units - %c\n", tasks[last_chosen].name, duration, tasks[last_chosen].remaining == 0 ? 'F' : 'H');
    }

    fprintf(output, "\nLOST DEADLINES\n");
    fprintf(output, "\n");
    for (int i = 0; i < n; i++) fprintf(output, "[%s] %d\n", tasks[i].name, tasks[i].lost);

    fprintf(output, "\nCOMPLETE EXECUTION\n");
    fprintf(output, "\n");
    for (int i = 0; i < n; i++) fprintf(output, "[%s] %d\n", tasks[i].name, tasks[i].complete);

    fprintf(output, "\nKILLED\n");
    fprintf(output, "\n");
    for (int i = 0; i < n; i++) fprintf(output, "[%s] %d\n", tasks[i].name, tasks[i].killed);

    fclose(output);
}