#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>   // wait() ফাংশনের জন্য
#include <sys/shm.h>    // shared memory এর জন্য

int global_var = 10;    // গ্লোবাল ভেরিয়েবল

int main()
{
    int local_var = 20, status;
    int *local_address, *global_address;
    pid_t pid;
    key_t key;
    int shmid;
    int shared_var = 30;

    local_address = &local_var;
    global_address = &global_var;

    // ফর্ক করার আগের অবস্থা
    printf("Before fork():\n");
    printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
    printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

    // শেয়ার্ড মেমোরি তৈরি করা
    key = 1234;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget: ");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory ID: %d\n", shmid);

    // চাইল্ড প্রসেস তৈরি করা
    pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // চাইল্ড প্রসেস
        printf("\n[Child Process]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // চাইল্ড প্রসেসে ভেরিয়েবল পরিবর্তন
        local_var = 100;
        global_var = 200;

        printf("\n[Child Process After Modification]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // শেয়ার্ড মেমোরিতে কানেক্ট করা
        void *shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (void *)-1)
        {
            perror("shmat: ");
            exit(EXIT_FAILURE);
        }

        // শেয়ার্ড মেমোরিতে মান লেখা
        int *shm_ptr = (int *)shmaddr;
        *shm_ptr = 20;

        // চাইল্ড প্রসেসের লুপ
        for (int i = 0; i < 10; i++)
        {
            printf("Child Process Loop: %d\n", i);
            sleep(1);
        }

        // শেয়ার্ড মেমোরি থেকে পড়া
        printf("Child process writing to shared memory: %d\n", shm_ptr[0]);

        // শেয়ার্ড মেমোরি থেকে ডিটাচ করা
        if (shmdt(shmaddr) == -1)
        {
            perror("shmdt: ");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS); // চাইল্ড প্রসেস শেষ
    }
    else
    {
        // প্যারেন্ট প্রসেস
        printf("\n[Parent Process]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // প্যারেন্ট প্রসেসে ভেরিয়েবল পরিবর্তন
        local_var = 100;
        global_var = 200;

        printf("\n[Parent Process After Modification]\n");
        printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
        printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);

        // চাইল্ড প্রসেস শেষ হওয়ার জন্য অপেক্ষা
        wait(&status);

        // প্যারেন্ট প্রসেস শেয়ার্ড মেমোরিতে কানেক্ট করে
        void *shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (void *)-1)
        {
            perror("shmat: ");
            exit(EXIT_FAILURE);
        }

        // প্যারেন্ট প্রসেসের লুপ
        for (int i = 0; i < 10; i++)
        {
            printf("hi, I am parent process\n");
            sleep(1);
        }

        // শেয়ার্ড মেমোরি থেকে পড়া
        int *shm_ptr = (int *)shmaddr;
        printf("Parent process reading from shared memory: %d\n", shm_ptr[0]);

        // শেয়ার্ড মেমোরি থেকে ডিটাচ করা
        if (shmdt(shmaddr) == -1)
        {
            perror("shmdt: ");
            exit(EXIT_FAILURE);
        }

        // প্যারেন্ট প্রসেস আবার নিজের কাজ চালিয়ে যাবে
        for (int i = 0; i < 10; i++)
        {
            printf("\n[Parent Process Loop]\n");
            printf("Global variable: %d, Local variable: %d\n", global_var, local_var);
            printf("Local address = %p, Global address = %p\n", (void *)local_address, (void *)global_address);
            sleep(1);
        }

        printf("\nSuccessfully terminated.\n");
    }

    return 0;
}
