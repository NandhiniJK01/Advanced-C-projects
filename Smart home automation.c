#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Device;

#define MAX_DEVICES 5
Device devices[MAX_DEVICES];
int device_count = 0;

void add_device(int id, const char *name) {
    if (device_count >= MAX_DEVICES) {
        printf("Device limit reached!\n");
        return;
    }
    devices[device_count].id = id;
    strncpy(devices[device_count].name, name, 50);
    devices[device_count].status = 0; // Initially OFF
    device_count++;
    printf("Device '%s' added successfully.\n", name);
}

void control_device(int id, int state) {
    for (int i = 0; i < device_count; i++) {
        if (devices[i].id == id) {
            devices[i].status = state;
            printf("Device '%s' turned %s.\n", devices[i].name, state ? "ON" : "OFF");
            return;
        }
    }
    printf("Device not found!\n");
}

void list_devices() {
    printf("\nDevices:\n");
    for (int i = 0; i < device_count; i++) {
        printf("ID: %d, Name: %s, Status: %s\n", devices[i].id, devices[i].name, devices[i].status ? "ON" : "OFF");
    }
}

int main() {
    int choice, id, state;
    char name[50];

    while (1) {
        printf("\nSmart Home Automation System\n");
        printf("1. Add Device\n");
        printf("2. Control Device\n");
        printf("3. List Devices\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Device ID: ");
                scanf("%d", &id);
                printf("Enter Device Name: ");
                scanf("%s", name);
                add_device(id, name);
                break;
            case 2:
                printf("Enter Device ID: ");
                scanf("%d", &id);
                printf("Enter 1 to turn ON, 0 to turn OFF: ");
                scanf("%d", &state);
                control_device(id, state);
                break;
            case 3:
                list_devices();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
