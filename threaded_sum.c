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