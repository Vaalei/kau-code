#include <stdio.h>
#include <string.h>

int rev(char* string) {
    int length = strlen(string);
    char copy[length];
    strcpy(copy, string);
    for (int i = 0; i <length; i++){
        string[i] = copy[length -i -1];
    }
}

int chop(char* input){
    int length = strlen(input);
    for(int i = 0; i<length; i++){
        if (input[i]!=95){
            rev(input);
            input[length-i] = NULL;
            rev(input);
            break;
        }
    }
}

void main()
{
    char input[200];
    scanf("%s", input);
    chop(input);
    rev(input);
    chop(input);
    rev(input);   
    printf("%s\n", input);

}

/*
__test__test__ -> test__test
____test__test_ -> test__test

*/
