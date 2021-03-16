#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(int argsize, char **arglist)
{
    printf("Starting Parent %d\n", getpid());
    for (int i = 1; i < argsize; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            return errno;
        else if (pid == 0)
        {
            int arg = atoi(arglist[i]);
            printf("%d : %d ", arg, arg);
            while (arg != 1)
            {
                if (arg % 2)
                {
                    arg = 3 * arg + 1;
                }
                else
                {
                    arg = arg / 2;
                }
                printf("%d ", arg);
            }
            printf("\n");
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            return 0;
        }
    }
    for (int i = 1; i < argsize; i++)
    {
        wait(NULL);
    }
    printf("Done Parent %d Me %d\n", getppid(), getpid());
    return 0;
}