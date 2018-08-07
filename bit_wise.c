#include <stdio.h>

void shift_by2(char a)
{    
    char b = a >> 2;
    char c = a << 2;
    char d = a >> 8;
    printf("%s --> a = 0x%x; b = 0x%x; c = 0x%x d = 0x%x\n", __func__, a, b, c, d);
    
}


void is_power_of_2(int a)
{
    int f = ( a & (a -1));
    printf("%s --> a = 0x%x f = 0x%x\n", __func__, a, f);
}


int main()
{
    shift_by2(4);
    shift_by2(-127);
    is_power_of_2(5);
    is_power_of_2(1);
    is_power_of_2(8);
    is_power_of_2(6);
}
