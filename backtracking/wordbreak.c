/*
Given a valid sentence without any spaces between the words 
and a dictionary of valid English words, find all possible 
ways to break the sentence in individual dictionary words.

EXAMPLE
Consider the following dictionary
{ i, like, sam, sung, samsung, mobile, ice,
  and, cream, icecream, man, go, mango}

Input: "ilikesamsungmobile"
Output: i like sam sung mobile
        i like samsung mobile

Input: "ilikeicecreamandmango"
Output: i like ice cream and man go
        i like ice cream and mango
        i like icecream and man go
        i like icecream and mango
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dict[] = {"mobile", "samsung", "sam", "sung", "man", "mango",
                "icecream", "ice", "cream", "and", "go", "i", "love"};
                

int is_word_in_dict(char * word) {
    int dict_size = sizeof(dict)/sizeof(dict[0]);
    int i;
    for (i = 0; i < dict_size; i++) {
        if (strcmp(word,dict[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void wordbreak(char *str) {
    int i;
    int str_size = strlen(str);
    if (str_size == 0) {
        printf("\n");
        return;
    }

    char *buf = malloc(str_size +1);
//    printf("str received is \"%s\"\n", str);
    for (i = 0; i < str_size; i++) {
        buf[i] = str[i];
        buf[i+1] = '\0';
        if (is_word_in_dict(buf)) {
            printf("%s ", buf);
            wordbreak(str+i+1);
        }
    }
}


int main(int argc, char ** argv) {
    char *str1 = "iloveicecreamandmango";
    char *str2 = "ilovesamsungmobile";
    printf("wordbreak for %s\n", str1);
    wordbreak(str1);
    printf("wordbreak for %s\n", str2);
    wordbreak(str2);
}
