/*
 * Find a subarray from a given array of integers with minimum sum
 * in: {10,4,2,5,6,3,8,1}, subarray size is 3
 * out:{4,2,5}
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_subarray(int* a, int size, int window)
{
    int sum = INT_MAX;
    int i,j,tmp;
    int index=0;

    if (size < window)
        return 0;
    for (i = 0; i < size -window; i++)
    {
        tmp = 0;
        for (j=i;j<i+window;j++)
        {
            tmp += a[j];
        }
        if(sum > tmp)
        {
            sum = tmp;
            index = i;  //start of window
            printf("sum=%d, index=%d\n", sum,i);
        }
    }
    printf("index = %d\n", index);
    return index;
}

int main(int argc, char ** argv)
{
    int a[] = {10,4,2,5,6,3,8,1};
    int sub_array_index = 0;
    int size = sizeof(a)/sizeof(a[0]);
    int window=3;
    int i;
    sub_array_index = find_subarray(a,size,window);

    printf("Given array: ");
    for(i=0;i<size;i++)
    {
        printf("%d ", a[i]);
    }
    printf("\nSub array: ");

    for(i=sub_array_index;i<=window;i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
