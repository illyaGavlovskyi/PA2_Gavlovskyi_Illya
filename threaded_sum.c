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
        printf("Too many threads requeste\n");
        return -1;
    }

    if(sizeOfData == -1)
    {
        return -1;
    }

    long long int totalSum = 0;
    struct timeval startTime;
    
    gettimeofday(&startTime, NULL);

    pthread_mutex_t m;
    thread_data_t threadDatal[numberOfThreads];


    for(int i = 0; i < ; i++)
    {

    }


    

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
    

}