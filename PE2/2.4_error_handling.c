#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //Again, this is needed for mac (or atleast my setup)

//Implementation of 2.2
int main(void){
    int i=1;

    while (i != -1){
    printf("%s", "Enter a number: ");
    scanf(" %d", &i);
    //Error handling (2.4)
    if(i < 1) {
    	printf("Error: alarm timer can not be negative\n"); //Cant use perror here
	return(-1);
    }
    //Implementation of 2.3
    int p = waitpid(-1, NULL, WNOHANG);
    while(p > 0){
    	printf("Process %d was deceased\n", p);
	p = waitpid(-1, NULL, WNOHANG);
    }
    int pid = fork();
    //Error handling
    if (pid == -1) {
	perror("Error: ");
	return(-1);	
    }
 
    if (pid == 0) {
        int sleepValue = sleep(i);
	//Error checking
	if(sleepValue > 0){
	    perror("Error: ");
	    return(-1);
	}
        printf("\nAlarm is ringing in the child with child process ID = %d!\nEnter a number: ",getpid());
	exit(1);
    }
    else {
        printf("The newly created alarm has child process ID = %d and is set go off in %d seconds\n",pid,i);
	}	
    }
    return 0;
}
