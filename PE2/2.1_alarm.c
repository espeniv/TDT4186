#include <stdio.h>

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
