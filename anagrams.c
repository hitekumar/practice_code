/* Print all anagrams of a given string */
/*
 * anagrams of 'abc' are abc acb bac bca cab cba 
 */

#include <stdio.h>
#include <string.h>
void swap(char *str, int l, int r) {
//   printf("%s l %d, r %d\n", str,l,r);
   char tmp = str[l];
   str[l] = str[r];
   str[r] = tmp;
    
}

/*
Try each of the letters in turn as the first letter and then find all the permutations of the remaining letters using a recursive call.
The base case is when the input is an empty string the only permutation is the empty string.
*/

void print_all_anagrams(char * str, int l, int r) {
    int i;
    if (l == r) {
        printf("%s \n", str);
        return;
    }
    for (i = l; i<=r;i++) {
        swap(str,l,i);
//        printf("%c", str[i]);

        print_all_anagrams(str, l+1,r);
        swap(str,l,i); // restore back; backtrack
    }
}


int main(int argc, char ** argv) {
    char str[100] = {0};
    int len =0;
    
    sprintf(str,"%s", "abc");
    len = strlen(str);
    printf("str is %s and len is %d\n", str, len);
    print_all_anagrams(str, 0, len -1 );



}
