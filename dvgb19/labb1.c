#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "file.fifo"
#define MAX_LENGTH 1000

pthread_mutex_t lock;
int n;
int BufferSize;
int TimeInterval;
sem_t buffer;


void *producer(void *thread_id){
    char str[MAX_LENGTH];
	int fd;
    long tid = (long)thread_id;

    sprintf(str, "Item #%ld\n", tid);
    printf("thread #%ld is created\n", tid);
    while(1)
    {
        pthread_mutex_lock(&lock);
        fd = open(FIFO_NAME, O_WRONLY); /* open FIFO for writing */

        write(fd, str, strlen(str));
        close(fd);
        sem_wait(&buffer);
        pthread_mutex_unlock(&lock);
        printf("Thread #%ld wrote %s", tid, str);
        sleep(TimeInterval);
    }
}

void* consumer(){
    char str[MAX_LENGTH];
	int fd;
    sleep(1);
    while (1)
    {
        pthread_mutex_lock(&lock);
        
        fd = open(FIFO_NAME, O_RDONLY); /* open FIFO for reading */

        read(fd, str, MAX_LENGTH);
        close(fd);
        sem_post(&buffer);
        pthread_mutex_unlock(&lock);
        printf("Consumer consumed %s", str);
    }
}

int main(){
    pthread_t tid2[n];
    pthread_t producerid;
    mkfifo(FIFO_NAME, 0666); /* make FIFO, if not already existed*/
    if (pthread_mutex_init(&lock, NULL) != 0)
        printf("mutex lock failed to init");
    printf("Number of producers: ");
    scanf("%d", &n);
    printf("\nBuffersize: ");
    scanf("%d", &BufferSize);
    printf("\nTimeInterval: ");
    scanf("%d", &TimeInterval);
    
    sem_init(&buffer, 0, BufferSize);
    pthread_mutex_init(&lock, NULL);
    
    for (int i = 0; i < n; i++) {
        pthread_create(&tid2[i], NULL, producer, (void *)i);
    }
    pthread_create(&producerid, NULL, consumer, NULL);


    while (1) ;
    pthread_mutex_destroy(&lock); 
    
}