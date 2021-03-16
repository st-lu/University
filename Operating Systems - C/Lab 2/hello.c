#include <unistd.h>
#include <string.h>
int main() {
    char buf[100] = "Hello world!\n";
    write(2, buf, strlen(buf));
    return 0;
}