#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int i;
    char *p;

    p = malloc(sizeof(char)*100);

    fgets(p, 100, stdin);
    strtok(p, "\n");
    for (i = 0; i < strlen(p); i++){
        printf("%c", p[i]-3);
    }
}