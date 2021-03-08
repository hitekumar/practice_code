/* In knapsack (0-1) we are given a set of items, each with weight and value,
wnad we need to determine the number of each item to inclide in a collection 
so that the total weight is less thean or equal to the given limit and total 
value is as large as possibe.

input:
value  = {20, 5, 10, 40, 15, 25}
weight = {1,  2, 3,  8,  7,  4}
capacity = 10
Output is 60.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max (int a, int b) {
    if (a>b)
        return a;
    else
        return b;
}


int find_knapsac(int *v, int *w, int n, int c) {
    int include, exclude;

    // Base case, no item left or capcity is 0
    if ( c == 0 || n < 0 )
        return 0;
    // if capacity is negative, this can happen when try to put itme bigger than capcity
    if (c < 0) 
        return INT_MIN;


    // Include current item and find knapsec for rest of items
    include = v[n] + find_knapsac(v, w, n-1, c - w[n] );

    // exclude current item and find knapsec for rest of items 
    exclude = find_knapsac(v, w, n-1, c);
    printf("%d:%d - v[%d]=%d, w[%d]=%d\n", include, exclude ,n, v[n], n, w[n] );
    return max(include,exclude);

}

int main(int argc , char ** argv) {
    int value[] = {20, 5, 10, 40, 15, 25};
    int weight[] = {1,  2, 3,  8,  7,  4};
    int capacity = 10;

    int knapsac = 0;

    int items = sizeof(value)/sizeof(value[0]);

    knapsac = find_knapsac(value,weight, items-1, capacity);

    printf("knapsac is %d\n", knapsac);
    

}
