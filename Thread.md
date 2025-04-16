#define GNU_GNU_SOURCE  // Corrected macro name
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sched.h>  // For sched_getcpu()

// Thread function for subtraction
void* subtraction(void* arg)
{
    int process_no = sched_getcpu();
    printf("Subtraction thread running on CPU core: %d\n", process_no);
    return NULL;
}

// Thread function for addition
void* addition(void* arg)
{
    int process_no = sched_getcpu();
    printf("Addition thread running on CPU core: %d\n", process_no);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    // Create threads
    pthread_create(&thread1, NULL, addition, NULL);
    pthread_create(&thread2, NULL, subtraction, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}


//g++ -D_GNU_SOURCE t.cpp -o t -pthread
./t
