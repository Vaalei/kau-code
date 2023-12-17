#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int tot = 0;
    char *p = malloc(sizeof(char) * 100);
    fgets(p, 100, stdin);
    while ((p = strstr(p, "ab")) != NULL){
        p++;
        tot++;
    }
    printf("%d", tot);
}