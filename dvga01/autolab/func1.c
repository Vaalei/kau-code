#include <stdio.h>
void calc(float param1, float param2, int operator){
    float sum = 0;
    int i;

    switch (operator)
    {
        case 43: // +
            printf("%0.f", param1 + param2);
            break;
        case 45: // -
            printf("%0.f", param1 - param2);
            break;
        case 42: // *
            printf("%0.f", param1 * param2);
            break;
        case 47: // /
            if (param2 == 0) {
                printf("NaN");
                break;
            }
            else {
                printf("%f", param1 / param2);
                break;
            }
        case 94: // ^
            for (i = 0; i < param2; i++){
                if (i == 0){
                    sum = param1;
                }
                else {
                    sum = sum * param1;
                }
            }
            printf("%0.f", sum);
            break;
    }
}

int main()
{
    char p;
    char operator;
    int param1, param2;


    scanf("%d %c %d", &param1, &operator, &param2);
    calc(param1, param2, operator);
    
}


