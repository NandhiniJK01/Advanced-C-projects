#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define FRAME_COUNT 3

typedef struct {
    int page;
    bool valid;
} Frame;

Frame memory[FRAME_COUNT];
int page_requests[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
int request_count = sizeof(page_requests) / sizeof(page_requests[0]);

void initialize_memory() {
    for (int i = 0; i < FRAME_COUNT; i++) {
        memory[i].valid = false;
    }
}

bool is_page_in_memory(int page) {
    for (int i = 0; i < FRAME_COUNT; i++) {
        if (memory[i].valid && memory[i].page == page) {
            return true;
        }
    }
    return false;
}

void load_page(int page, int index) {
    memory[index].page = page;
    memory[index].valid = true;
}

void print_memory_state() {
    printf("Memory State: ");
    for (int i = 0; i < FRAME_COUNT; i++) {
        if (memory[i].valid) {
            printf("[%d] ", memory[i].page);
        } else {
            printf("[ ] ");
        }
    }
    printf("\n");
}

void simulate_paging() {
    int next_replacement = 0;
    int page_faults = 0;
    
    for (int i = 0; i < request_count; i++) {
        int page = page_requests[i];
        printf("Requesting page %d\n", page);
        
        if (!is_page_in_memory(page)) {
            printf("Page fault! Loading page %d\n", page);
            load_page(page, next_replacement);
            next_replacement = (next_replacement + 1) % FRAME_COUNT;
            page_faults++;
        }
        print_memory_state();
    }
    
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    printf("Virtual Memory Paging Simulator\n");
    initialize_memory();
    simulate_paging();
    return 0;
}
