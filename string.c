#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define lower_a 97

void print_dup_chars(char * string)
{
    unsigned char freq[26] = {0};
    int i, j;
    int len = strlen(string);
    char c;
    for(i = 0; i < len; i++)
    {
        c = tolower (string[i]);
        j = c - lower_a;
        if (j >= 0 && j <= 26)
        {
            freq[j]++;
        }
        else
        {
            printf("Not supported \"%c\"\n", c);
        }
    }
    printf("Duplicate chars\n");
    for (i = 0; i < 26; i++)
    {
        if (freq[i] > 1)
            printf("%c ", i+lower_a);
    }
    printf("\n");

}



int main()
{
    print_dup_chars("Hitesh Kumar Singh");
}
