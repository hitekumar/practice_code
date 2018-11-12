#include <stdio.h>


static int static_list[] = {10,9,8,12,17,5,2,20,1,3};
void swap(int*a, int*b)
{
    int tmp = *a;
    printf("Swaping %d and %d\n", *a, *b);
    *a = *b;
    *b = tmp;
}
void print_list(void)
{
    int list_size = sizeof(static_list)/sizeof(static_list[0]);
    int i;
    for (i =0; i<list_size; i++)
    {
        printf("%d ", static_list[i]);
        fflush(stdout);
    }
    printf("\n");
}

int partition(int l, int h)
{
    int i = l+1;
    int j = h;
    int pivot = static_list[l];
    printf("Pivot=%d, i=%d, j=%d\n", pivot,i,j);    
    while(i<j)
    {
        // Increment i untill find element greater than pivot
        while(static_list[i] <= pivot)
            i++;
        // Decrement j untill find element less than pivot
        while(static_list[j] > pivot)
            j--;
        if(i<j)
        {
            swap(&static_list[i], &static_list[j]);
        }
    }
    // Swap pivot with Jth element; placing pivot at correct position
    swap(&static_list[l], &static_list[j]);
    return j;
}

void quick_sort(int l, int h)
{
    int j;
    
    if(l<h)
    {
        j = partition(l,h);
        printf("partition=%d, l=%d, h=%d\n", j,l,h);
        print_list();
        quick_sort(l,j-1);
        quick_sort(j+1, h);
    }
}

int main(int argc, char **argv)
{
    int list_size = sizeof(static_list)/sizeof(static_list[0]);
    print_list();
    quick_sort(0,list_size-1);
    print_list();
}
