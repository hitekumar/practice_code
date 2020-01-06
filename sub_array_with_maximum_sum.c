#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for INT_MIN

// Kadane’s Algorithm

int arr[] = {2, -1, 4, -4, 5, 6, -1,-10, 2, 4};

int main(int argc, char ** argv)
{
    int i;
    int local_max = INT_MIN;
    int global_max = INT_MIN;
    int start = 0;
    int end = 0;

    printf("Given array:\n");
    printf("[ ");
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
        if (arr[i] > arr[i] + local_max)
        {
            local_max = arr[i];
            start = i;
        }
        else
        {
            local_max += arr[i];
        }
        if(local_max > global_max)
        {
            global_max = local_max;
            end = i;
        }

//        printf("i=%d, start=%d, end=%d, local_max=%d, global_max=%d\n",i,start,end, local_max,global_max);
    }
    printf("]\n");
    printf("Subarray with maximum sum:\n[ ");
    for (i = start;i<end;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");

    printf("Maximum sub array total is %d\n", global_max);
}
