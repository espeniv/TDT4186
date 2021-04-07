#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd[2], nbytes;
    pid_t pid;
    char string[] = "Test\n";
    char readbuffer[80];
    int bytecount = 0;

    pipe(fd);
    pid = fork();

    if (pid == 0)
    {
        for (;;)
        {
            close(fd[0]);
            write(fd[1], string, (strlen(string) + 1));
        }
    }
    else
    {
        for (;;)
        {
            close(fd[1]);
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            bytecount += sizeof(nbytes);
            printf("Number of bytes sent so far: %d \n", bytecount);
        }
    }
}