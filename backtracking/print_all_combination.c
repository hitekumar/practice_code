/* 
Given an array of size n, generate and print all possible combinations 
of r elements in array. 
For example, if input array is {1, 2, 3, 4} and r is 2, 
then output should be {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4} and {3, 4}.
*/

//https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/

#include <stdio.h>
#include <stdlib.h>

void print_all_comb_recursive(int *arr, int n, int r, int arr_idx, int comb_idx, int * combination) {
    int i=0;
    // if combination array is filled print it 
    if (comb_idx == r) {
        for (i = 0; i < r; i++) 
            printf("%d ", combination[i]);
        printf("\n");
        return;
    }
    // if all element from arr are done
    if (arr_idx >= n) 
        return;

    //Put current element from arr to current position in combination
    combination[comb_idx] = arr[arr_idx];
    // Call recursive to next element 
    print_all_comb_recursive(arr,n,r,arr_idx+1,comb_idx+1,combination);

    // Once current element from arr is picked, exclude it and move to next element in arr
    print_all_comb_recursive(arr,n,r,arr_idx+1,comb_idx,combination);


}

void print_all_combination(int *arr, int n, int r) {
    // memory to hold the combination data
    int *combination = malloc(sizeof(int) * r);

    print_all_comb_recursive(arr, n, r, 0, 0, combination);
    free(combination);
}



int main(int argc, char ** argv)
{
    int arr[] = {1,2,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int r,i;
    
    for (i =0; i <n;i++) {
        printf("%d ", arr[i]);
    }
    
    r = 3;
    printf("\nr = %d\n", r);
    print_all_combination(arr,n, r); 

    r = 4;
    printf("\nr = %d\n", r);
    print_all_combination(arr,n, r); 


    return 0;
}
