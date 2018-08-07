#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return a > b ? a:b;
}

// X[0...m-1], Y[0....n-1]
// O(2^n) exponential
int get_lcs_rec(char *X, char *Y, int m, int n)
{
    if(m ==0 || n ==0 )
        return 0;
    if (X[m-1] == Y[n-1])
        return (1 + get_lcs_rec(X,Y,m-1,n-1));
    else
        return max(get_lcs_rec(X,Y,m-1,n), get_lcs_rec(X,Y,m,n-1));        
}
// Better O(n^2)
int get_lcs(char * X, char *Y, int m, int n)
{
    int L[m+1][n+1];   // Matrix to hold lcs
    int i,j;
    printf("Common sequence:\n");    
    for (i =0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
            if (i == 0 || j == 0) // Make first row and first col = 0
            {
                L[i][j] = 0;
            }
            else if (X[i] == Y[j])
            {
                L[i][j] = 1 + max(L[i-1][j], L[i][j-1]);
            }
            else
            {
                L[i][j] = max(L[i-1][j], L[i][j-1]);
            }
            if (X[i]==Y[j])
                printf("%c", X[i]);
                  
            //printf("L[%d][%d] = %d\n", i,j,L[i][j]);
        }
    }
    printf("\n");
    return L[i-1][j-1];
}

int main()
{
    char X[] = "ABCDEFG";
    char Y[] = "ACD";
    int m = strlen(X);
    int n = strlen(Y);
    
    int length_lcs = 0;

    length_lcs = get_lcs_rec(X,Y,m,n);
    printf("Longest length is through recursive approach  %d\n", length_lcs);
    
    length_lcs = get_lcs(X,Y,m,n);
    printf("Longest length is through matrix approach  %d\n", length_lcs);
}
