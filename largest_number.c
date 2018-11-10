/* Find largest number possible from set of given numbers
 * Input = {10, 68, 75, 7, 21, 12 }
 * Output = 77568211210
 * Compile with gcc file.c -o out -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void print_array(unsigned int *a, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%u ", a[i]);
    }
    printf("\n");
}

// Retrun a number by placing input numbers one after another
// in:72 and 9
// out: 729
unsigned long get_compibend_val(unsigned int x, unsigned int y)
{
    int x_digit=0;
    unsigned int tmp;
    int y_digit = 0;
    unsigned long ret=0;
    tmp = y;
    while (tmp)
    {
        tmp = tmp/10;
        y_digit++;
//        printf("tmp=%d, y_digit=%d\n",tmp, y_digit);
    }
    ret = (unsigned long)(x*(pow(10,y_digit)) + y);
//    printf("x=%u, y=%u, xy = %lu\n", x,y,ret);
    return ret;
}


int my_bubble_sort(unsigned int *a, int size)
{
    int i,j;
    unsigned int tmp;
    unsigned long xy, yx;
    for(j=0; j<size;j++)
    {
        for(i=0;i<size-1;i++)
        {
//            printf("a[%d]=%u, a[%d]=%u\n", i,a[i],i+1,a[i+1]);
            // Given two number x and y compare xy with yx 
            // and put greater number at the top.
            xy = get_compibend_val(a[i], a[i+1]); 
            yx = get_compibend_val(a[i+1], a[i]); 
//            printf("xy = %lu\n", xy);
//            printf("yx = %lu\n", yx);
            if(xy > yx)
//            if (a[i] > a[i+1])
            {
                tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
            }
        }
    }
}


int main(int argc, char** argv)
{
    unsigned int in[] = {10, 68, 75, 7, 21, 12};
    unsigned long out = 0;
    int size = sizeof(in)/sizeof(in[0]);
    int i;
    // Print unsorted array
    print_array(in,size);
    my_bubble_sort(in,size);
    print_array(in,size);

    // Print largest number by traversing from a[size-1]
    for (i=size-1;i>=0;i--)
    {
        printf("%u", in[i]);
    }
    printf("\n");
}

