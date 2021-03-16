#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define NTHRS 5
pthread_mutex_t mtx;
sem_t sem;
int S = 0;

int init()
{
    if (pthread_mutex_init(&mtx, NULL))
    {
        perror(NULL);
        return errno;
    }

    if (sem_init(&sem, 0, 0))
    {
        perror(NULL);
    }
}

int barrier_point()
{
    pthread_mutex_lock(&mtx);
    S++;
    pthread_mutex_unlock(&mtx);

    if (S < NTHRS)
    {

        if (sem_wait(&sem))
        {
            perror(NULL);
            return errno;
        }
        
    }
    else
    {
        for(int i = 0; i < NTHRS; i++){
            if (sem_post(&sem))
            {
                perror(NULL);
                return errno;
            }
        }
    }

    
}

void *tfun(void *v)
{
    int *tid = (int *)v;
    printf("%d reached the barrier\n", *tid);
    barrier_point();
    printf("%d passed the barrier\n", *tid);

    free(tid);
    return NULL;
}

int main()
{
    init();
    pthread_t thr[NTHRS];
    int *id;
    for (int i = 0; i < NTHRS; i++)
    {
        id = (int *)malloc(sizeof(int));
        *id = i;
        if (pthread_create(&thr[i], NULL, tfun, id))
        {
            perror(NULL);
            return errno;
        }
    }

    for (int i = 0; i < NTHRS; i++)
    {
        if (pthread_join(thr[i], NULL))
        {
            perror(NULL);
            return errno;
        }
    }

    pthread_mutex_destroy(&mtx);
    sem_destroy(&sem);
}