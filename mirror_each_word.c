#include <stdio.h>
#include <string.h>

char string[] = "Hi my name is Hitesh Kumar";

int mirror(int s, int e)
{
    char tmp;
    while (e>=s)
    {
        tmp = string[e];
        string[e] = string[s];
        string[s] = tmp;
        s++; e--;
    }
}



int mirror_words()
{
    int len = strlen(string);
    int s = 0; int e = 0; int i;

    for(i = 0; i < len; i++)
    {
        if (string[i] == ' ')
        {
            e = i-1;
            mirror(s,e);
            s = i+1;
            e = i+1;
        }
        if( i == len - 1)
        {
            e = i;
            mirror(s,e);
        }
    }
}

int main()
{
    printf("Original: %s\n", string);
    mirror_words();
    printf("Mirrored: %s\n", string);
}

