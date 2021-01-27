#include <stdio.h>

int n = 6;              //number to sum up to
char global_uninitialized;             //testing address
int global_initialized = 1;             //testing address

int sum_n(int n)
{
    if (n == 1){
    return 1;
    }
    
    int sum = n + sum_n(n-1);
    printf("the local variable sum is temporarely stored in %p\n", &sum);
    return sum;
}

int main(void)
{
    printf("The sum of numbers from 1 to %d is %d \n", n, sum_n(n));
    printf("Address of a global initialized int is %p\n", &n);
    printf("Address of a global uninitialized char is %p\n", &global_uninitialized);
    
    float local_float = 45.5;   //testing address
    printf("Address of initialized local float is %p\n", &local_float);
    
    int local_uninitialized;  //testing address
    printf("Address of uninitialized local variable is %p\n", &local_uninitialized);
    
    return 0;
}

/*
 a) with n equal to 2147483647, the problem stops working properly and starts spitting out negative numbers. This is because that is the highest number an integer can possibly represent on a 32-bit
    computer.
 
 b) The distance between the addresses of uninitialized and local, which are both declared in main, is 4. This is because they take up 4 bytes of memory each.
 
 c) Global integers are stored either in the Block Storage Segment or the Data Segment based on if they are uninitialized or initialized. Local integers are stored on the stack unless specified. This
    difference in memory storage gives the two variables very different addresses.
 
 d)  Local variables are stored on the  stack, which starts at the highest address and grows downwards for each new local variable made.
*/
