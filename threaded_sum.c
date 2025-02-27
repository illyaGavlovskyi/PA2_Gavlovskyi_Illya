//Illya Gavlovskyi
//CS 446
//Febuary 27, 2025

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<pthread.h>
#include<sys/time.h>

#define SIZE 1000000

typedef struct _thread_data_t
{
    const int *data;
    int startInd;
    int endInd;
    pthread_mutex_t *lock;
    long long int *totalSum;
} thread_data_t;

int readFile(char file[], int numArray[]);
void *arraySum(void* a);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Not enough parameters.\n");
        return -1;
    }

    int data[SIZE];
    int sizeOfData = readFile(argv[1], data);
    int numberOfThreads = atoi(argv[2]);

    if(sizeOfData < numberOfThreads)
    {
        printf("Too many threads requeste.\n");
        return -1;
    }

    if(sizeOfData == -1)
    {
        return -1;
    }

    long long int totalSum = 0;

    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    thread_data_t threadData[numberOfThreads];

    int sliceOfDataSize = sizeOfData / numberOfThreads;
    int remainder = sizeOfData % numberOfThreads;

    for(int i = 0; i < numberOfThreads; i++)
    {
        threadData[i].data = data;

        threadData[i].startInd = i * sliceOfDataSize;
        if(i == (numberOfThreads - 1))
        {
            threadData[i].endInd = (((i + 1) * sliceOfDataSize) + remainder);
        }
        else
        {
            threadData[i].endInd = ((i + 1) * sliceOfDataSize);
        }

        threadData[i].lock = &lock;
        threadData[i].totalSum = &totalSum;   
    }

    pthread_t threads[numberOfThreads];
    for(int i = 0; i < numberOfThreads; i++)
    {
        pthread_create(&threads[i], NULL, arraySum, &threadData[i]);
    }
    for(int i = 0; i < numberOfThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Final sum: %lld\n", totalSum);

    gettimeofday(&endTime, NULL);

    double totalTime = ((endTime.tv_sec - startTime.tv_sec) * 1000) + ((endTime.tv_usec - startTime.tv_usec) / 1000);
    printf("Total time of execution: %lf\n", totalTime);

    return 0;
}

int readFile(char file[], int numArray[])
{
    FILE *openFile = fopen(file, "r");
    if(!openFile)
    {
        return -1;
    }
    int num = 0;
    while(fscanf(openFile, "%d", &numArray[num]) == 1)
    {
        num++;
    }
    fclose(openFile);
    return num;
}

void *arraySum(void* a)
{
    thread_data_t* inputData = (thread_data_t*)a;
    long long int threadSum = 0;

    for(int i = inputData->startInd; i < inputData->endInd; i++)
    {
        threadSum += inputData->data[i];
    }

    pthread_mutex_lock(inputData->lock);

    *inputData->totalSum += threadSum;

    pthread_mutex_unlock(inputData->lock);

    return NULL;
}