#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 40
int fib_num[MAX_SIZE];
static int call = 0;
// Method 1, using regular recursion
int fib(int n)
{
    call++;
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;
    return fib(n-1) + fib(n-2);
}


// Method 2, memoization (DP)
int fib_dp(int n)
{
    call++;
    int tmp,tmp2;
    if (n == 0) return 0;
    if (n == 1|| n == 2) return 1;
    if (fib_num[n-1] == -1)
    {
        fib_num[n-1] = fib(n-1);
    }
    if (fib_num[n-2] == -1)
    {
        fib_num[n-2] = fib(n-2);
    }
    return fib_num[n-1] + fib_num[n-2];
}


void print_fib(void)
{
    int i;
    for(i=0;i<MAX_SIZE;i++)
    {
        printf("%d ", fib_num[i]);
    }
    printf("\n");
}

int main (int argc, char**argv)
{
    int i;
    
    memset(fib_num, -1, sizeof(fib_num));
    call = 0;
    for(i = MAX_SIZE-1; i>=0;i--)
        fib_num[i] = fib(i);
    print_fib();
    printf("Called fib function %d times\n", call);

    // DP Method
    memset(fib_num, -1, sizeof(fib_num));
    call = 0;
    for (i =MAX_SIZE-1; i>=0; i--)
        fib_num[i] = fib_dp(i);
    print_fib();
    printf("Called fib_dp function %d times\n", call);

}
