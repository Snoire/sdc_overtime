#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int * initnew(char * str, int len)
{
    int * new = NULL;
    new = (int *)malloc(len * sizeof(int));

    new[0] = -1;

    for( int i=1; i<len; i++)
    {
        int j = new[i-1];

        while( str[j+1]!=str[i] && (j>=0) )
            j = new[j];

        if(str[j+1]==str[i])
            new[i] = j+1;
        else
            new[i] = -1;
    }

    return new;
}

int kmp(char *str1, char *str2)
{
    int i=0, j=0;
    int *p = NULL, len1, len2;

    len1 = strlen(str1);
    len2 = strlen(str2);

    p = initnew(str2, len2);
    
#if 0
    for(int i=0; i<len2; i++)
        printf("p[%d]=%d ",i,p[i]);
    printf("\n");
#endif

    while( i<len1 && j<len2 )
    {
        if(j == -1 || str1[i] == str2[j])
        {
            i++;
            j++;
        }
        else
            j = p[j];
    }

    free(p);

    if ( j == len2 )
        return i-j;
    else
        return -1;


}

