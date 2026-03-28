#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "early.h"

void early(FILE *input, infoE inf) {
    if (!input) return;
    rewind(input);

    int total_time, n = 0;
    if (fscanf(input, "%d", &total_time) != 1) return;

    TaskEDF tasks[100];
    memset(tasks, 0, sizeof(tasks));

    while (n < 100) {
        char temp_name[10];
        int b, p, d;
        if (fscanf(input, "%s %d %d %d", temp_name, &b, &p, &d) != 4) break;

        if (p <= inf.per && d <= inf.dead) {
            strcpy(tasks[n].name, temp_name);
            tasks[n].burst = b;
            tasks[n].period = p;
            tasks[n].deadline = d;
            n++;
        }
    }

    FILE *output = fopen("edf_dsob.out", "w");
    if (!output) return;

    fprintf(output, "EXECUTION BY EDF\n");
    fprintf(output, "\n");

    int time = 0, last_chosen = -1, duration = 0;

    while (time < total_time) {
        int chosen = -1, earliest = 2147483647;

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

            if (tasks[i].remaining > 0 && tasks[i].current_absolute_deadline < earliest) {
                earliest = tasks[i].current_absolute_deadline;
                chosen = i;
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
            } else if (time + 1 >= tasks[chosen].current_absolute_deadline) {
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