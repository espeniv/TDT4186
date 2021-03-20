#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

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
                //strcat(path, argv[i]);
            }
        }

        int pid = fork();
        if (pid == 0)
        { 
            // redirect > and <
            int fd0,fd1,i,in=0,out=0;
            char input[64],output[64];

            // sets '<' or '>' to argv[i] = NULL
            for(i=0;argv[i]!='\0';i++)
            {
                if(strcmp(argv[i],"<")==0)
                {        
                    argv[i]=NULL;
                    strcpy(input,argv[i+1]);
                    in=2;           
                }               

                if(strcmp(argv[i],">")==0)
                {      
                    argv[i]=NULL;
                    strcpy(output,argv[i+1]);
                    out=2;
                }         
            }
            // if < in input
            if(in)
            {   
                int fd0;
                if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
                    perror("Not able to open input file");
                    exit(0);
                }           
                dup2(fd0, 0);
                close(fd0);
            }

            //if > in input
            if (out)
            {
                int fd1 ;
                if ((fd1 = creat(output , 0644)) < 0) {
                    perror("Not able to open output file");
                    exit(0);
                }           
                dup2(fd1, STDOUT_FILENO);
                close(fd1);
            }

            execvp(*argv, argv);
            perror("execvp");
            _exit(1);
        }

        else
        {
            execv(path, argv);
            wait(NULL);

        }
    }
}