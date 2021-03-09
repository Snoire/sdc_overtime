# include <stdio.h>

int main()
{
    printf("awk '$1 ~ /ipv4/ {printf(\"%%s(%%s) -> %%s(%%s)\\n\",$6,$8,$7,$9)}' ~/ipv.txt | sed 's/src=\\|dst=\\|sport=\\|dport=//g'\n");

}
