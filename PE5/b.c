#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int fd[2], nbytes;
pid_t pid;
char string[] = "Test";
char readbuffer[1000];

void sig_handler(int signum)
{
    printf("Number of bytes received during the last second: %d\n", nbytes);
    nbytes = 0;
    alarm(1);
}

int main(int argc, char **argv)
{
    signal(SIGALRM, sig_handler);
    alarm(1);

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
        }
    }
}

/* - The largest supported blocksize for my system is 4096 bytes ($ diskutil info / | grep "Block Size"),
     which seems to be a good fit with the findings in this task. By testing with a block size of 1 kB
     i managed to get a bandwith of just over 1 GB/s.
   - With a block size of 4 kB i managed to get a bandwith of about 1,5 GB/s
   - Running several instances of the program does not seem to lower the bandwith
*/