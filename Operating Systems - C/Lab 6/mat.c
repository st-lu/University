#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
int **a1, **a2, **rez, *args;
void *calc(void *v)
{
    int *argz = (int *)v;
    int i = argz[0];
    int j = argz[1];
    int len = argz[2];
    int res = 0;
    for (int k = 1; k <= len; k++)
        res += a1[i][k] * a2[k][j];
    rez[i][j] = res;
    free(argz);
    return NULL;
}


int main(int argsize, char **arglist)
{
    int n1 = atoi(arglist[1]);
    int m1 = atoi(arglist[2]);
    int cnt = 2;
    a1 = (int **)malloc(sizeof(int *) * (n1 + 1));

    for (int i = 1; i <= n1; i++)
    {
        a1[i] = (int *)malloc(sizeof(int) * (m1 + 1));
        for (int j = 1; j <= m1; j++)
        {
            a1[i][j] = atoi(arglist[++cnt]);
        }
    }

    int n2 = atoi(arglist[++cnt]);
    if (n2 != m1)
    {
        perror("Matricile au dimensiuni incompatibile");
        return errno;
    }
    int m2 = atoi(arglist[++cnt]);
    a2 = (int **)malloc(sizeof(int *) * (n2 + 1));
    for (int i = 1; i <= n2; i++)
    {
        a2[i] = (int *)malloc(sizeof(int) * (m2 + 1));
        for (int j = 1; j <= m2; j++)
        {
            a2[i][j] = atoi(arglist[++cnt]);
        }
    }

    rez = (int **)malloc(sizeof(int *) * (n1 + 1));
    for (int i = 1; i <= n1; i++)
    {
        rez[i] = (int *)malloc(sizeof(int) * (m2 + 2));
    }

    pthread_t thr[n1 * m2];
    cnt = 0;
    for (int i = 1; i <= n1; i++)
    {
        for (int j = 1; j <= m2; j++)
        {

            args = (int *)malloc(3 * sizeof(int));
            args[0] = i;
            args[1] = j;
            args[2] = m1;
            if (pthread_create(&thr[cnt++], NULL, calc, args))
            {
                perror(NULL);
                return errno;
            }
        }
    }
    cnt = 0;
    for (int i = 1; i <= n1; i++)
    {
        for (int j = 1; j <= m2; j++)
        {
            if (pthread_join(thr[cnt++], NULL))
            {
                perror(NULL);
                return errno;
            }
        }
    }

    for(int i = 1; i <= n1; i++){
        for(int j = 1; j <= m2; j++){
            printf("%d ", rez[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n1 + 1; i++)
    {
        free(a1[i]);
        free(rez[i]);
    }
    for (int i = 0; i < n2 + 1; i++)
    {
        free(a2[i]);
    }
    return 0;
}
