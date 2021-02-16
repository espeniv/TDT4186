#include <stdio.h>
#include <unistd.h> //Needed for mac (only?)

//Implementation of task 2.1
int main(void){
    int i=1;

    while (i != -1){
    printf("%s", "Enter a number: ");
    scanf(" %d", &i);
    sleep(i);
    printf("Alarm is ringing!\n");
    }
    return 0;
}
