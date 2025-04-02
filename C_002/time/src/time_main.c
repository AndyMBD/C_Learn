#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "time_main.h"
#define TIME_NUM_THREADS 5
void *time_thread_function(void *arg)
{

    time_t current_time;
    struct tm *time_info;
    char buffer[80];

    int *num = (int *)arg;
    for (int i = 0; i < TIME_NUM_THREADS; i++)
    {
        time(&current_time);
        time_info = localtime(&current_time);

        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
        printf("time_main_4 Thread running: %d %s\n", *num, buffer);

        (*num)++;

        sleep(1);
    }

    return NULL;
}
int time_main_1()
{
    SYSTEMTIME currentTime;
    GetSystemTime(&currentTime);
    printf("time_main_1 time: %u/%u/%u %u:%u:%u:%u %d\n",
           currentTime.wYear,
           currentTime.wMonth,
           currentTime.wDay,
           currentTime.wHour,
           currentTime.wMinute,
           currentTime.wSecond,
           currentTime.wMilliseconds,
           currentTime.wDayOfWeek);
    return 0;
}
uint8_t time_main_2()
{
    LARGE_INTEGER li;
    LONGLONG start, end, freq;
    QueryPerformanceFrequency(&li);
    freq = li.QuadPart;
    QueryPerformanceCounter(&li);
    start = li.QuadPart;
    Sleep(100);
    QueryPerformanceCounter(&li);
    end = li.QuadPart;
    int useTime = (int)((end - start) * 1000 / freq);
    printf("time_main_2 time: %d ms\n", useTime);
    return 0;
}
uint8_t time_main_3()
{
    DWORD start, stop; 
    start = GetTickCount();
    Sleep(100);
    stop = GetTickCount();
    printf("time_main_3 time: %lld ms\n", stop - start);
    return 0;
}
uint8_t time_main_4()
{
    pthread_t thread;

    int num = 0;

    if (pthread_create(&thread, NULL, time_thread_function, &num) != 0)
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
long long time_getSystemTime() {
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}

int time_main_5() {
    long long start=time_getSystemTime();
    sleep(1);
    long long end=time_getSystemTime();

    printf("time_main_5 time: %lld ms\n", end-start);
    return 0;
}
int time_main_6() {
    time_t t_start, t_end; 
    t_start = time(NULL) ;
    Sleep(100);
    t_end = time(NULL) ;
    printf("time_main_6 time: %.5ef s\n", difftime(t_end,t_start)) ;
    return 0;
}
uint8_t time_main()
{
    printf("time function test start\n") ;
    time_main_1();
    time_main_2();
    time_main_3();
    time_main_4();
    time_main_5();
    time_main_6();
    printf("time function test end\n") ;
    return 0;
}
