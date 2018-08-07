#include <stdio.h>

/*
 * Given input a number put each digit into 
 * array, each digit in seperate element.
 * Ex: input a=987654321
 * output arr[0]=1; arr[1]=2;....arr[8]=9
 */
int arr[100];

int in_array(int num, int pos)
{
    int lsb, msb;
    lsb = num % 10;
    msb = num / 10;
    arr[pos++] = lsb;
    if(msb)
        in_array(msb, pos);
    else
    {
        return pos;
    }
}

/* Reverse a number; ex 92 ==> 29 */
int _reverse_number(int num)
{
    int rem; int base = num;
    int rev = 0;
    while (base > 0)
    {
        rem = base % 10;
        base = base /10;
        rev = rev * 10;
        rev = rev + rem;
    }
    return rev;
}

/* 
 * Merge two arrays into one by summing individual elements 
 * each array element shoudl contain one digit 
 */

int merge_array()
{
    int in_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    int in_2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    int j,k, l, sum;
    int size_1 = sizeof(in_1)/sizeof(in_1[0]);
    int size_2 = sizeof(in_2)/sizeof(in_2[0]);
    j =0; k=0; l = 0; sum=0;
    while(( j < size_1) && (k < size_2))
    {
        sum = in_1[j++] + in_2[k++];
        l = in_array(_reverse_number(sum), l);
    }
    if (j < size_1)
    {
        l = in_array(in_1[j], l);
    }
    if (k < size_2)
    {
        l = in_array(in_2[k], l);
    }
    return l;
}

void reverse_array(int item)
{
    int tmp;
    int i;
    printf("Reversing arra elements\n");
    for (i = 0; i < (item/2)+1;i++)
    {
        tmp = arr[i];
        arr[i] = arr[item -1 - i];
        arr[item-1 -i] = tmp;
    }

}

void print_array(int item)
{
    int i;
    for(i = 0; i < item; i++)
    {
        printf(" %d|", arr[i]);
    }
    printf("\n-----------------------\n");
}

main()
{
    int item = 0;
    int a = 987654321;
    int i;
    item = in_array(a, item);
    print_array(item);

    item = merge_array();
    print_array(item);
    reverse_array(item);
    print_array(item);

    


}












