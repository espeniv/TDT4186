#include <stdio.h>

int n = 100;              //number of reccursions
char acter;             //testing address

int sum_n(int n)
{
    int uninitialized;  //testing address
    float local = 45.5;   //testing address

    
    int sum = 0;        //sum of reccursion
    
    
    for(int i = 1; i<=n; ++i)
    {
        sum += i;
        printf("Address of localInt is %p \n", &sum);
    }
    printf("Address of local is %p\n", &local);
    printf("Address of uninitialized is %p\n", &uninitialized);
    
    return sum;
}

int main(void)
{
    printf("The sum of numbers from 1 to %d is %d \n", n, sum_n(n));
    printf("Address of n is %p\n", &n);
    printf("Address of acter is %p\n", &acter);
    
    return 0;
}

/*
 a) 2147483647 is the highest number an integer can possibly represent on a 32-bit
    computer.
 
 b) The distance between the addresses of uninitialized and local, which are both declared in main, is 4. This is because they take up 4 bytes of memory each.
 
 c) Global integers are static and are stored in a fixed location decided by the
    compiler. Local integers are stored on the stack unless specified. This
    difference in memory storage gives the two variables very different addresses.
 
 d)
*/
