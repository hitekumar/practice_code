#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE   32

#define verbose


#ifdef verbose
#define debug(arg...)  printf(arg)
#else
#define debug(arg...)   
#endif


int static_list[LIST_SIZE] = {0};

void populate_list()
{
    int i;
    printf("Unsorted list\n");
    for (i = 0; i < LIST_SIZE; i++)
    {
        static_list[i] = rand() % LIST_SIZE;
    }
}

int print_list()
{
    int i; 
    for (i = 0; i < LIST_SIZE; i++)
    {
        printf("%2d ", static_list[i]);
    }
    printf("\n");
    return 0;
}

void swap(int i, int j)
{
    int tmp;
    if (( i < 0 && i > LIST_SIZE) && ( j < 0 && j > LIST_SIZE))
    {
        printf("%s-- %d index out of boud, exiting\n", __func__, i);
        exit(1);
    }
    debug("swaping @%d %d with %d\n", i, static_list[i], static_list[i+1]);
    tmp = static_list[i];
    static_list[i] = static_list[j];
    static_list[j] = tmp;
   
}

// O(n^2)
int bubble_sort()
{
    int i,j;
    printf("Bubble sort O(n^2)\n");
    for (j = 0; j < LIST_SIZE; j++)
    {
        for (i = 0; i < LIST_SIZE-1; i++)
        {
            if (static_list[i] > static_list[i+1])
            {
                swap(i, i+1);
            } 
        }
    }
    return 0;
}

// O(n^2)
int selection_sort()
{
    int i,j;
    int iMin = 0;
    int tmp;

    printf("Selection sort O(n^2)\n");
    for (j = 0; j < LIST_SIZE; j++)
    {
        iMin = j;
        for (i = j+1; i < LIST_SIZE; i++)
        {   
            if (static_list[iMin] > static_list[i])
            {
                // Found new minimum
                iMin = i;
            }
        }
        if (iMin != j)
            swap(j, iMin);
    }

}

// Merge sort
void merge(int *list, int*L, int nl, int *R, int nr)
{
    int i = 0, j =0 , k = 0;
    debug("merging ");
    for(i = 0; i < nl;i++)
        debug("%d ", L[i]);
    debug("| ");
    for(i = 0; i < nr;i++)
        debug("%d ", R[i]);
    debug("\n");

    i = 0;
    while(i<nl && j < nr)
    {
        if (L[i] < R[j])
            list[k++] = L[i++];
        else
            list[k++] = R[j++];
    }
    while(i<nl)
            list[k++] = L[i++];
    while(j<nr)
            list[k++] = R[j++];
    debug("merged ");
    for (i =0; i < (nl+nr); i++)
        debug("%d ", list[i]);
    debug("\n");
    
}
void merge_sort(int *list, int count)
{
    int mid, i, *L, *R;
    if (count < 2)  return; // If array has less than 2 element do nothing
    
    mid = count /2;

    L = (int*)malloc(mid * sizeof(int));
    R = (int*)malloc((count -mid) * sizeof(int));
    
    for(i = 0; i<mid; i++)
    {
        L[i] = list[i];
        debug("%d ", L[i]);
    }
    debug("| ");
    for(i = mid;i< count;i++)
    {
        R[i-mid] = list[i];
        debug("%d ", R[i-mid]);
    }
    debug("\n");
    merge_sort(L, mid);
    merge_sort(R,count-mid);

    merge(list, L, mid, R, count - mid);

    free(L);
    free(R);

}

int linear_serach()
{
    return 0;
}

int binary_search(int val, int low, int high)
{
    int mid = (low+high)/2;
    int ret = 0;
    if (val == static_list[mid])
    {
        printf("Found at %d\n", mid);
        ret = mid;
    }
    else if (val < static_list[mid])
    {
        binary_search(val, low, mid);
    }
    else
    {
        binary_search(val, mid+1, high);
    }
    return ret;
}

// Quick sort
int partition(int low, int high)
{
    int pivot = static_list[high];  // take last element as pivot
    int i = low -1; // index of smallar element
    int j = 0;
    for (j = low; j < high; j++)
    {
       // If current element is smallar or equal than pivot 
        if (static_list[j] <= pivot)
        {
            i++;    // increment index of smallar element
            swap(i, j);
        }
    }
    swap(i+1, high); // place pivot at right location
    debug("partition is %d\n", i+1);
    return (i+1);   // found partition where all smallar are in left and all greater are in right
}

void quick_sort(int low, int high)
{
    int partition_index = 0;
    debug("low = %d, high = %d\n", low, high);
    if (low < high)
    {
        partition_index = partition(low, high);
        
        quick_sort(low, partition_index -1);
        quick_sort(partition_index +1, high);
    }
}

int main()
{
// -----Bubble sort--------
    populate_list();
    print_list();
    bubble_sort();
    print_list();
//------selection sort ---
    populate_list();
    print_list();
    selection_sort();
    print_list();
// merge sort--------------
    populate_list();
    print_list();   
    printf("Merge sort\n");
    merge_sort(static_list, LIST_SIZE);
    print_list();
// quick sort------------
    populate_list();
    print_list();   
    printf("quick sort\n");
    quick_sort(0, LIST_SIZE -1);
    print_list();   
    binary_search(static_list[10], 0, LIST_SIZE -1);


}
