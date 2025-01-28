#include <stdio.h> // This includes the standard I/O library for printing output.
#include <stdlib.h> // This includes the standard library for functions like exit and macros like EXIT_FAILURE.
#include <pthread.h> // This includes the POSIX threads library for multithreading support.

int sum = 0; // Shared variable to store the sum of natural numbers.
int i = 1; // Shared variable to track the current number being added.
int last_thread = 0; // Variable to track which thread added the final number.
pthread_mutex_t mutex; // Mutex to ensure thread-safe access to shared variables.

void* add_natural(void* arg) {
    int thread_id = *(int*)arg; // Retrieve the thread ID passed as argument.
    int n = *(int*)(arg + sizeof(int)); // Retrieve the limit N passed as part of argument.

    while (1) {
        pthread_mutex_lock(&mutex); // Lock the mutex to prevent race conditions.

        if (i > n) { // Check if all numbers up to N have been added.
            pthread_mutex_unlock(&mutex); // Unlock the mutex before exiting.
            break;
        }

        sum += i; // Add the current number to the sum.
        last_thread = thread_id; // Record the ID of the thread adding the number.
        i++; // Increment the counter to the next number.

        pthread_mutex_unlock(&mutex); // Unlock the mutex to allow other threads to proceed.
    }

    return NULL; // Exit the thread function.
}

int main() {
    int n; // Variable to store the user-inputted positive integer.

    printf("Enter a positive integer N: ");
    scanf("%d", &n); // Prompt the user for input.

    if (n <= 0) { // Validate the input.
        printf("N must be a positive integer.\n");
        return EXIT_FAILURE; // Exit if input is invalid.
    }

    pthread_t thread1, thread2; // Declare the thread variables.
    int thread_id1 = 1, thread_id2 = 2; // IDs for threads 1 and 2.
    int args1[2] = {thread_id1, n}; // Array to pass thread ID and N to thread 1.
    int args2[2] = {thread_id2, n}; // Array to pass thread ID and N to thread 2.

    // Initialize the mutex.
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return EXIT_FAILURE;
    }

    // Create threads.
    if (pthread_create(&thread1, NULL, add_natural, args1) != 0 ||
        pthread_create(&thread2, NULL, add_natural, args2) != 0) {
        perror("Thread creation failed");
        return EXIT_FAILURE;
    }

    // Join threads.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Display results.
    printf("The total sum of the first %d natural numbers is: %d\n", n, sum);
    printf("Thread %d added the final number to the sum.\n", last_thread);

    // Destroy the mutex.
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
