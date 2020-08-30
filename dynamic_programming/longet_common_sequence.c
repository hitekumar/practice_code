/* LCS Problem Statement: Given two sequences, find the length of longest 
 * subsequence present in both of them. A subsequence is a sequence that 
 * appears in the same relative order, but not necessarily contiguous. 
 * For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are 
 * subsequences of “abcdefg”.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a:b;
}

static int count = 0;
int lcs_recursive(char *str_a, char *str_b, int pos_a, int pos_b) {
    count++;
	if (str_a[pos_a] == '\0' || str_b[pos_b] == '\0')
		return 0;
    if (str_a[pos_a] == str_b[pos_b]) {
        return (1 + lcs_recursive(str_a, str_b, pos_a+1, pos_b+1));
    }
    else {
        return max( lcs_recursive(str_a, str_b, pos_a+1,pos_b) ,
                lcs_recursive(str_a, str_b, pos_a,  pos_b+1));
    }
 }

int lcs_recursive_memoization (char *str_a, char *str_b, int pos_a, int pos_b, int** lcs_memo) {
    count++;
	if (str_a[pos_a] == '\0' || str_b[pos_b] == '\0') {
        lcs_memo[pos_a][pos_b]  = 0;
		return lcs_memo[pos_a][pos_b];
    }

    if (str_a[pos_a] == str_b[pos_b]) {
        if (lcs_memo[pos_a][pos_b] != -1 ) {
//            printf("from lcs_memo[%d][%d] = %d;%c\n", pos_a,pos_b, lcs_memo[pos_a][pos_b], str_b[pos_b]);
            return lcs_memo[pos_a][pos_b];
        }
        else {
            lcs_memo[pos_a][pos_b] = 1 + lcs_recursive_memoization(str_a, str_b, pos_a+1, pos_b+1, lcs_memo);
//            printf("to lcs_memo[%d][%d] = %d;%c\n", pos_a,pos_b, lcs_memo[pos_a][pos_b], str_b[pos_b]);
            return lcs_memo[pos_a][pos_b];
        }
    }
    else {
        if (lcs_memo[pos_a+1][pos_b] == -1) 
            lcs_memo[pos_a+1][pos_b] = lcs_recursive_memoization(str_a, str_b, pos_a+1,pos_b, lcs_memo);
        if (lcs_memo[pos_a][pos_b+1] == -1)
            lcs_memo[pos_a][pos_b+1] = lcs_recursive_memoization(str_a, str_b, pos_a,pos_b+1, lcs_memo);

        return max( lcs_memo[pos_a+1][pos_b],lcs_memo[pos_a][pos_b+1]);
    }
 }


 void print_arr(int** lcs_mem, int m, int n) {
    int i,j;
    for(i = 0; i<m;i++) {
         for (j = 0; j < n; j++) {
             printf("%2d ", lcs_mem[i][j]);
         }
         printf("\n");
     }
     printf("\n");

 }

 int lcs_dp_bottom_up(char *s1, char *s2) {
     int m = strlen(s1);
     int n = strlen(s2);
     int i,j;
     char * lcs; 
     int tmp = 0;
     // make an array of m x n
    
     int **lcs_dp = malloc(sizeof(int *) * (m+1));
     for (i = 0; i <= m; i++ ) {
         lcs_dp[i] = malloc(sizeof(int) * (n+1));
         // initilize with 0
         memset(lcs_dp[i], 0, sizeof(int) * (n+1));
     }
     print_arr(lcs_dp,m+1,n+1);
     printf("--s1 %s-------\n", s1);
     printf("--s2 %s-------\n", s2);

     for (i = 1; i <= m;i++) {
         for (j = 1; j<=n;j++) {
             if (s1[i-1] == s2[j-1]) {
                lcs_dp[i][j] = 1 + lcs_dp[i-1][j-1];
                printf("%c %c\n", s1[i-1], s2[j-1]);
             }
             else {
                 lcs_dp[i][j] = max( lcs_dp[i][j-1], lcs_dp[i-1][j] );
             }                 
         }
     }
     // trace back to see what is lcs
     i = m; j = n;
     lcs = malloc(lcs_dp[m][n]+1);
     memset(lcs,0,lcs_dp[m][n]+1);
     tmp = lcs_dp[m][n];
     lcs[tmp] = '\0';
     tmp--;
     while (i > 0 && j > 0 &&tmp >=0)  {
         // Move horizontal or vertical
         if (lcs_dp[i][j] == max(lcs_dp[i-1][j], lcs_dp[i][j-1])) {
             if (lcs_dp[i-1][j] > lcs_dp[i][j-1]) {
                 i--;
             }
             else {
                 j--;
             }
         }
         // move diagonal
         else {
             lcs[tmp] = s2[j-1];
             tmp--;
//            printf("lcs_dp[%d][%d] = %d; %c \n", i,j, lcs_dp[i][j], s2[j-1]);
            i--;
            j--;
         }
     }
//     printf("\n");
    printf("lcs is %s\n", lcs);
     print_arr(lcs_dp,m+1,n+1);
     return lcs_dp[m][n];

 }

 int main(int argc, char** argv) {
     char *s1 = "stone";
     char *s2 = "longest";
     int lcs = 0;
     int i;
     // memoiazation table m x n
     int m = strlen(s1);
     int n = strlen(s2);

     printf("s1=%s, size=%d\n", s1, m);
     printf("s2=%s, size=%d\n", s2, n);

     int **lcs_memo = malloc(sizeof(int *) * (m+1));
     for (i = 0; i <= m; i++ ) {
         lcs_memo[i] = malloc(sizeof(int) * (n+1));
         memset(lcs_memo[i], -1, sizeof(int) * (n+1));
     }
     print_arr(lcs_memo, m+1,n+1); 

     count = 0;
     printf("Recurssion \n");
     lcs = lcs_recursive(s1,s2,0,0);
     printf("lcs recursive of s1=%s, s2=%s is %d; count=%d\n", s1, s2,lcs, count);

     count = 0;

     printf("Recurssion with memoization\n");
     lcs = lcs_recursive_memoization(s1,s2,0,0,lcs_memo);
     printf("lcs recursive memoization of s1=%s, s2=%s is %d; count=%d\n", s1, s2,lcs, count);
     print_arr(lcs_memo, m+1,n+1); 
    
     printf("Dynamic programming bottom up\n");
     lcs = lcs_dp_bottom_up(s1,s2);
     printf("lcs recursive memoization of s1=%s, s2=%s is %d;\n", s1, s2,lcs);



 }
