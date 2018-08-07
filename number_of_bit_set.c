#include<stdio.h>

int count_bit_set_naive(unsigned char byte)
{
    int i = 0;
    int count = 0;
    for(i = 0; i < (8*sizeof(unsigned char)); i++)
    {
        if (byte & 0x01) 
        {
            count++;
        }
        byte = byte >> 1;
    }
    return count;
}

// Better approach
int count_bit_set(unsigned char byte)
{
    int count = 0;
    while (byte)
    {
        count++;
        byte = byte & (byte - 1);
    }
    return count;
}

int main()
{
    printf("In number 3 bit set are %d\n",count_bit_set_naive(3));
    printf("In number 4 bit set are %d\n",count_bit_set_naive(4));
    printf("In number 5 bit set are %d\n",count_bit_set_naive(5));
    printf("In number 3 bit set are %d\n",count_bit_set(3));
    printf("In number 4 bit set are %d\n",count_bit_set(4));
    printf("In number 5 bit set are %d\n",count_bit_set(5));
}
