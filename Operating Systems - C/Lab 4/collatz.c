#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(int argsize, char **arglist){
    if (argcnt != 3) {
        printf("Incorrect number of arguments.\n");
        return 0;
    }
    pid_t pid = fork();
    if (pid < 0)
        return errno;
    else if (pid == 0)
    {
        int arg = atoi(arglist[1]);
        printf("%d : %d ", arg, arg);
        while(arg != 1){
            if(arg%2){
                arg = 3*arg+1;
            }
            else
            {
                arg = arg/2;
            }
            printf("%d ", arg);
        }
    }
    else
    {
        wait(NULL);
        printf("\nChild %d finished\n", pid);
    }
}