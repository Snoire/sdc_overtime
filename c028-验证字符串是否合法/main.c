#include <stdio.h>

int validkey(char * key)
{
    char * p;
    for( p=key; *p!='\0'; p++)
    {
        //valid char: "small letter" and "numeric(0-9)"
        //prohibited characters are:  "l" "i" "q" "o" "u"
        if( (*p >= 97 && *p <= 122 ||  *p >= 48 && *p <=57)   && *p!='l' && *p!='i' && *p!='q' && *p!='o' && *p!='u'    )
            printf("%c\n",*p);
    }
    return 0;
}

int main()
{
    char key[16] = "ISEOsJOWFfsljef";
    validkey(key);

    return 0;
}

