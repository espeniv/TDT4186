#include <stdio.h>
#include <unistd.h>

 int main(void){
     int i=1;

     while (i != -1){
          printf("%s", "Enter a number: ");
          scanf(" %d", &i);
          int pid = fork();

          if (pid == 0) {    //if in child process
              sleep(i);
              printf("Alarm is ringing in the child with child process ID = %d!\nEnter a number: ",getpid());
              exit(1);
          }
          else {             //if in parent process
              printf("The newly created alarm has child process ID = %d and is set go off in %d seconds\n",pid,i);
          }

     }
     return 0;

 } 
