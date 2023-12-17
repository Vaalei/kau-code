#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, inp, temp, *ptr1, *ptr2;

    scanf("%d", &n);

    ptr1 = (int*)malloc(n*sizeof(int));
    ptr2 = (int*)malloc(n*sizeof(int));

    for (i = 0; i < n; i++){
        scanf("%d", ptr1+i);
    }
    for (i = 0; i < n; i++){
        scanf("%d", ptr2+i);
    }
    for (i = 0; i < n; i++){
        printf("%d", *(ptr1+i) + *(ptr2+i));
        if (i + 1 != n) printf("\n");
    }
    free(ptr1); free(ptr2);
}