#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char inputline[100];
    char *argv[100];
    int argcount;
    char *pathprefix = "/bin/";
    char path[100];

    while (1)
    {
        int i = 0;
        printf("$ ");

        //fgets to handle input
        fgets(inputline, 100, stdin);

        size_t length = strlen(inputline);

        //Removes newline character at the end of the string
        if (inputline[length - 1] == '\n')
        {
            inputline[length - 1] = '\0';
        }

        //Splits the inputline into tokens, which is stored in argv
        char *token;
        token = strtok(inputline, " ");
        while (token != NULL)
        {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL;
        argcount = i;

        for (i = 0; i < argcount; i++)
        {
            if (i == 0)
            {
                //full path for execution of command should be /bin/commandX
                strcpy(path, pathprefix);
                strcat(path, argv[i]);
            }
            //Useful for later tasks
        }

        int pid = fork();
        if (pid != 0)
        {
            wait(NULL);
        }
        else
        {
            execv(path, argv);
            //If execv fails/command is not recognized
            printf("Could not execute command\n");
            return 0;
        }
    }
}