#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "pthread_main.h"
#define NUM_THREADS 5
SYSTEMTIME currentTime;

void *thread_function(void *arg)
{
    int *num = (int *)arg;
    for (int i = 0; i < 5; i++)
    {
        GetSystemTime(&currentTime);
        printf("main_4 Thread running: %d %d %d\n", *num, currentTime.wSecond, currentTime.wMilliseconds);
        (*num)++;
        sleep(1);
    }
    return NULL;
}

uint8_t main_4()
{
    pthread_t thread;

    int num = 0;
    if (pthread_create(&thread, NULL, thread_function, &num) != 0)
    {
        perror("Failed to create thread\n");
        return 1;
    }

    if (pthread_join(thread, NULL) != 0)
    {
        perror("Failed to join thread\n");
        return 1;
    }
    printf("Thread finished with num = %d\n", num);
    return 0;
}

uint8_t pthread_main()
{
    main_4();
    return 0;
}
