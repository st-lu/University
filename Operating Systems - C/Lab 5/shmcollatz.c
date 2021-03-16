#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
int main(int argsize, char **arglist)
{
    printf("Starting Parent %d\n", getpid());
    char *shm_name = "myshm";
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 600);
    if (shm_fd < 0)
    {
        perror(NULL);
        return errno;
    }
    int bytesize = getpagesize();
    size_t shm_size = bytesize * (argsize - 1);
    if (ftruncate(shm_fd, shm_size) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    char *shm_ptr;
    for (int i = 1; i < argsize; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            return errno;
        else if (pid == 0)
        {
            shm_ptr = mmap(0, bytesize, PROT_WRITE, MAP_SHARED, shm_fd, (i - 1) * bytesize);
            if (shm_ptr == MAP_FAILED)
            {
                perror(NULL);
                shm_unlink(shm_name);
                return errno;
            }
            int arg = atoi(arglist[i]);
            shm_ptr += sprintf(shm_ptr, "%d : %d ", arg, arg);
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
                shm_ptr += sprintf(shm_ptr, "%d ", arg);
            }
            shm_ptr += sprintf(shm_ptr, "\n");
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            return 0;
        }
    }
    for (int i = 1; i < argsize; i++)
    {
        wait(NULL);
    }

    for (int i = 1; i < argsize; i++)
    {
        shm_ptr = mmap(0, bytesize, PROT_READ, MAP_SHARED, shm_fd, (i - 1) * bytesize);
        printf("%s", shm_ptr);
        munmap(shm_ptr, bytesize);
    }

    printf("Done Parent %d Me %d\n", getppid(), getpid());
    return 0;
}
