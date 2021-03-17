#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char inputline[1024];
    char *argv[100];
    int argcount;

    while (1)
    {
        int i = 0;
        printf("$ ");

        //fgets to handle input
        fgets(inputline, 1024, stdin);

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

        //Loop used to separate tokens accordingly
        for (i = 0; i < argcount; i++)
        {
            if (i == 0)
            {
                printf("Command: %s ", argv[i]);
            }
            else if ((strcmp(argv[i], ">") != 0) && (strcmp(argv[i], "<") != 0))
            {
                printf("Parameter: %s ", argv[i]);
            }
            else
            {
                printf("Redirection: %s ", argv[i]);
                i++;
                printf("%s ", argv[i]);
            }
        }
        printf("\n");
    }
}