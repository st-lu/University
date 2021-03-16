#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argcnt, char** arglist) {
    if (argcnt != 3) {
        printf("Incorrect number of arguments.\n");
        return 0;
    }

    int file1 = open(arglist[1], O_RDONLY);
    if(file1 < 0){
        perror("Can't open first file");
        return errno;
    }
    int file2 = open(arglist[2], O_CREAT|O_RDWR);

    struct stat sb;
    stat(arglist[1], &sb);
    int file1size = sb.st_size;
    char content[file1size];
    read(file1, content, file1size);
    write(file2, content, file1size);

    close(file1);
    close(file2);
    return 0;
}