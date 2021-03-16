#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
void * reverse(void *v){
    char *str = (char *)v;
    int len = strlen(str);
    char *aux = (char*)malloc(len);
    for(int i = 0; i < len; i++){
        aux[i] = str[len-i-1];
    }
    return aux;
}
int main(int argsize, char **arglist)
{
    if(argsize != 2){
        printf("Incorrect number of arguments");
        return 0;
    }
    pthread_t thr;
    if( pthread_create(&thr, NULL, reverse, arglist[1])){
        perror(NULL);
        return errno;
    }
    char *result;
    if(pthread_join(thr, &result)){
        perror(NULL);
        return errno;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}
