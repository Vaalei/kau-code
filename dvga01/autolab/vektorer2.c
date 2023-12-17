#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int n, i;
    float *ptr, mean, std, sum = 0, sum2 = 0;

    scanf("%d", &n);

    ptr = (float*)malloc(n*sizeof(float));

    for (i = 0; i < n; i++){
        scanf("%f", ptr+i);
        sum +=*(ptr+i);
    }
    mean = sum/n;
    for (i = 0; i < n; i++){
        sum2+=(*(ptr+i)-mean) * (*(ptr+i)-mean);
    }
    printf("%f", sqrt(sum2/(n-1)));
    
    free(ptr);
}