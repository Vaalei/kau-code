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
sem_t zero;


void *producer(){
    char str[MAX_LENGTH];
	int fd;

    sprintf(str, "test\n");
    fd = open(FIFO_NAME, O_WRONLY|O_NONBLOCK); /* open FIFO for writing */
    printf("producer is created\n");
    while(1)
    {
        sem_wait(&buffer);
        pthread_mutex_lock(&lock);
        write(fd, str, strlen(str));
        pthread_mutex_unlock(&lock);
        printf("producer wrote %s", str);
        sem_post(&zero);
        sleep(TimeInterval);
    }
    close(fd);
}

void* consumer(void *thread_id){
    char str[MAX_LENGTH];
	int fd;
    long tid = (long)thread_id;
    fd = open(FIFO_NAME, O_RDONLY); /* open FIFO for reading */
    printf("consumer #%ld is created\n", tid);
    while (1)
    {
        sem_wait(&zero);
        pthread_mutex_lock(&lock);
        read(fd, str, MAX_LENGTH);
        sem_post(&buffer);
        pthread_mutex_unlock(&lock);
        printf("Consumer #%ld consumed %s", tid, str);
    }
    close(fd);
}

int main(){
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
    pthread_t tid[n];
    
    sem_init(&buffer, 0, BufferSize);
    sem_init(&zero, 0, 0);
    pthread_mutex_init(&lock, NULL);
    
    for (int i = 0; i < n; i++) {
        pthread_create(&tid[i], NULL, consumer, (void *)i);
    }
    pthread_create(&producerid, NULL, producer, NULL);


    for (int i = 0; i < n; i++) {
        pthread_join(&tid[i], NULL);
    }
    pthread_join(&producerid, NULL);


    pthread_mutex_destroy(&lock);
    sem_destroy(&buffer);
}