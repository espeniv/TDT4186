#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd[2], nbytes;
    pid_t pid;
    char string[] = "Test";
    char readbuffer[80];

    pipe(fd);
    pid = fork();

    if (pid == 0)
    {
        close(fd[0]);
        for (;;)
        {
            write(fd[1], string, (strlen(string)));
        }
    }
    else
    {
        close(fd[1]);
        for (;;)
        {
            nbytes += read(fd[0], readbuffer, sizeof(readbuffer));
            printf("Number of bytes received so far: %d \n", nbytes);
        }
    }
}