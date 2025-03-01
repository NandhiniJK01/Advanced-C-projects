#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PROCESSES 5

typedef struct {
    int id;
    int burst_time;
} Process;

Process process_queue[MAX_PROCESSES];
int process_count = 0;

void *execute_process(void *arg) {
    Process *p = (Process *)arg;
    printf("Process %d started, execution time: %d seconds\n", p->id, p->burst_time);
    sleep(p->burst_time);
    printf("Process %d completed.\n", p->id);
    return NULL;
}

void add_process(int id, int burst_time) {
    if (process_count >= MAX_PROCESSES) {
        printf("Process queue full! Cannot add more processes.\n");
        return;
    }
    process_queue[process_count].id = id;
    process_queue[process_count].burst_time = burst_time;
    process_count++;
    printf("Process %d added successfully.\n", id);
}

void execute_scheduler() {
    pthread_t threads[MAX_PROCESSES];
    for (int i = 0; i < process_count; i++) {
        pthread_create(&threads[i], NULL, execute_process, (void *)&process_queue[i]);
    }
    for (int i = 0; i < process_count; i++) {
        pthread_join(threads[i], NULL);
    }
    process_count = 0;
    printf("All processes completed.\n");
}

int main() {
    int choice, id, burst_time;
    while (1) {
        printf("\nOperating System Process Simulator\n");
        printf("1. Add Process\n");
        printf("2. Execute Scheduler\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter Process ID: ");
                scanf("%d", &id);
                printf("Enter Burst Time (seconds): ");
                scanf("%d", &burst_time);
                add_process(id, burst_time);
                break;
            case 2:
                execute_scheduler();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
