#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void bubble_sort(int arr[], int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = i + 1; j < end; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Sorted array using bubble sort from child process: ");
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selection_sort(int arr[], int start, int end) {
    int min_idx;
    for (int i = start; i < end - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < end; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    printf("Sorted array using selection sort from parent process: ");
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void create_zombie_process() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        printf("Child process created for Zombie state. Child PID = %d\n", getpid());
        exit(0); // Child exits immediately, but will remain in zombie state
    } else if (pid > 0) { // Parent process
        printf("Parent process (PID = %d) sleeping to leave child in zombie state.\n", getpid());
        sleep(10); // Parent sleeps and does not wait for the child, creating a zombie
        printf("Parent process woke up.\n");
         
    } else {
        perror("Fork failed");
        exit(1);
    }
}

void create_orphan_process() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        printf("Child process (PID = %d) is now an orphan.\n", getpid());
        sleep(10); // Child process continues running after parent exits
        printf("Orphan process finished: Child PID = %d\n", getpid());
    } else if (pid > 0) { // Parent process
        printf("Parent process (PID = %d) exiting early to create orphan.\n", getpid());
        exit(0); // Parent exits, leaving the child to become orphaned
    } else {
        perror("Fork failed");
        exit(1);
    }
}

int main() {
    int size;

    // Input size of the array
    printf("Enter size of array: ");
    scanf("%d", &size);

    int arr[size];

    // Input array elements
    printf("Enter %d numbers in array: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int status;
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        printf("\n-------Hello from child process-------\n");
        printf("Child process id: %d\n", getpid());
        bubble_sort(arr, 0, size);  // Child sorts using bubble sort
        exit(0);  // Ensure the child process exits after sorting
    } else if (pid > 0) {  // Parent process
        wait(&status);  // Wait for the child process to finish
        printf("\n-------Hello from parent process-------\n");
        printf("Parent process id: %d\n", getpid());
        selection_sort(arr, 0, size);  // Parent sorts using selection sort
    } else {
        // Handle the case where fork fails
        perror("Fork failed");
        exit(1);
    }

    // Demonstrate Zombie Process
    printf("\nCreating Zombie process:\n");
    create_zombie_process();

    // Demonstrate Orphan Process
    printf("\nCreating Orphan process:\n");
    create_orphan_process();

    return 0;
}
