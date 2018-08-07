// Count number bit required to invert in second number to make 2 number equal

#include <stdio.h>

unsigned int mask_sign_bit( int a)
{
    unsigned int mask = ~(1 << ((8*sizeof(int)) -1));
    return (mask & a);
}

int count_bit(int a)
{
    int count = 0;
    if (a < 0)
    {
        a = mask_sign_bit(a);
        count++;
    }
    while (a > 0)
    {
        if ((a & 0x1) == 1) 
        {
            count++;
            printf("found bit set in 0x%x\n", a);
        }
        a = a >> 1;
    }
    return count;
}


int compare_bit(int a, int b)
{
    int count = 0;
    int xor = a^b;
    printf("0x%x^0x%x = 0x%x\n", a, b, xor);
    return count_bit(xor);
     
}


int main()
{
    int a = 5;  // 101
    int b = 2;  // 010
    int count = 0;
    count = compare_bit(a, b);
    printf("Count = %d\n", count);

}
