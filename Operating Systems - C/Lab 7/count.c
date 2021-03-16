#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_RESOURCES 5
pthread_mutex_t mtx;
int availableR;

int decrease_count(int count)
{

    pthread_mutex_lock(&mtx);
    if (availableR < count)
    {
        pthread_mutex_unlock(&mtx);
        return 1;
    }

    availableR -= count;
    printf("Got %d resources %d remaining\n", count, availableR);
    pthread_mutex_unlock(&mtx);
    return 0;
}

int increase_count(int count)
{

    pthread_mutex_lock(&mtx);
    availableR += count;
    printf("Release %d resources %d remaining\n", count, availableR);
    pthread_mutex_unlock(&mtx);
    return 0;
}

void *f(void *v)
{
    int *resources = (int *)v;

    while (decrease_count(*resources));
    increase_count(*resources);
    
    free(resources);
    return NULL;
}

int main()
{
    availableR = MAX_RESOURCES;
    printf("MAX_RESOURCES = %d\n", availableR);
    int v[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        v[i] = rand() % MAX_RESOURCES + 1;
    }

    if (pthread_mutex_init(&mtx, NULL))
    {
        perror(NULL);
        return errno;
    }

    pthread_t thr[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        if (pthread_create(&thr[i], NULL, f, &v[i]))
        {
            perror(NULL);
            return errno;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        if (pthread_join(thr[i], NULL))
        {
            perror(NULL);
            return errno;
        }
    }

    pthread_mutex_destroy(&mtx);
}