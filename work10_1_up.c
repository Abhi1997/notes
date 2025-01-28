#include <stdio.h> // This includes the standard I/O library for printing output.
#include <stdlib.h> // This includes the standard library for functions like exit and macros like EXIT_FAILURE.
#include <pthread.h> // This includes the POSIX threads library for multithreading support.

const int MAX_COUNT = 50; // Defines the maximum value the shared counter can reach as a global constant.

int shared_counter = 0; // This is the shared counter incremented by all threads.
int check_variable = 0; // Stores the thread number that reaches 50 first.
pthread_mutex_t counter_mutex; // Mutex to ensure thread-safe access to shared resources.

void* count_thread1(void* arg) { // Thread function for thread 1.
    while (1) {
        pthread_mutex_lock(&counter_mutex); // Locks the mutex to prevent other threads from accessing shared resources.

        if (shared_counter >= MAX_COUNT) { // Checks if the shared counter has reached or exceeded the maximum value.
            pthread_mutex_unlock(&counter_mutex); // Unlocks the mutex before exiting the loop.
            break;
        }

        shared_counter++; // Increments the shared counter by 1.
        if (shared_counter == MAX_COUNT && check_variable == 0) { // Checks if the current thread is the first to reach the maximum counter value.
            check_variable = 1; // Marks thread 1 as the first to reach the maximum value.
        }

        pthread_mutex_unlock(&counter_mutex); // Unlocks the mutex to allow other threads to access shared resources.
    }
    return NULL; // Exits the thread function.
}

void* count_thread2(void* arg) { // Thread function for thread 2.
    while (1) {
        pthread_mutex_lock(&counter_mutex); // Locks the mutex to prevent other threads from accessing shared resources.

        if (shared_counter >= MAX_COUNT) { // Checks if the shared counter has reached or exceeded the maximum value.
            pthread_mutex_unlock(&counter_mutex); // Unlocks the mutex before exiting the loop.
            break;
        }

        shared_counter++; // Increments the shared counter by 1.
        if (shared_counter == MAX_COUNT && check_variable == 0) { // Checks if the current thread is the first to reach the maximum counter value.
            check_variable = 2; // Marks thread 2 as the first to reach the maximum value.
        }

        pthread_mutex_unlock(&counter_mutex); // Unlocks the mutex to allow other threads to access shared resources.
    }
    return NULL; // Exits the thread function.
}

void* count_thread3(void* arg) { // Thread function for thread 3.
    while (1) {
        pthread_mutex_lock(&counter_mutex); // Locks the mutex to prevent other threads from accessing shared resources.

        if (shared_counter >= MAX_COUNT) { // Checks if the shared counter has reached or exceeded the maximum value.
            pthread_mutex_unlock(&counter_mutex); // Unlocks the mutex before exiting the loop.
            break;
        }

        shared_counter++; // Increments the shared counter by 1.
        if (shared_counter == MAX_COUNT && check_variable == 0) { // Checks if the current thread is the first to reach the maximum counter value.
            check_variable = 3; // Marks thread 3 as the first to reach the maximum value.
        }

        pthread_mutex_unlock(&counter_mutex); // Unlocks the mutex to allow other threads to access shared resources.
    }
    return NULL; // Exits the thread function.
}

int main() {
    pthread_t thread1, thread2, thread3; // Declares the thread variables for the three threads.

    // Initialize the mutex.
    if (pthread_mutex_init(&counter_mutex, NULL) != 0) { // Initializes the mutex and checks for initialization failure.
        perror("Mutex initialization failed"); // Prints an error message if the mutex initialization fails.
        return EXIT_FAILURE; // Exits the program with a failure status.
    }

    // Create threads.
    if (pthread_create(&thread1, NULL, count_thread1, NULL) != 0 || // Creates thread 1 and assigns the respective function.
        pthread_create(&thread2, NULL, count_thread2, NULL) != 0 || // Creates thread 2 and assigns the respective function.
        pthread_create(&thread3, NULL, count_thread3, NULL) != 0) { // Creates thread 3 and assigns the respective function.
        perror("Thread creation failed"); // Prints an error message if thread creation fails.
        return EXIT_FAILURE; // Exits the program with a failure status.
    }

    // Join threads.
    pthread_join(thread1, NULL); // Waits for thread 1 to finish execution.
    pthread_join(thread2, NULL); // Waits for thread 2 to finish execution.
    pthread_join(thread3, NULL); // Waits for thread 3 to finish execution.

    // Display results.
    printf("Thread %d reached 50 first!\n", check_variable); // Prints which thread was the first to reach the maximum counter value.

    // Destroy the mutex.
    pthread_mutex_destroy(&counter_mutex); // Destroys the mutex to release resources.

    return EXIT_SUCCESS; // Exits the program with a success status.
}