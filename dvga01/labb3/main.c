#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funktioner.h"


#define MAX_INPUT 80


int main(){
    char input[MAX_INPUT];
    int choice;
    int i;

    while(1)
    {
        puts("");
        puts("1. Add Vehicle");
        puts("2. Remove Vehicle");
        puts("3. Sort");
        puts("4. Show Vehicle");
        puts("5. Show Registry");
        puts("0. Quit");


        fgets(input, MAX_INPUT, stdin);
        choice = atoi(input);

        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;

        case 4:
            break;
        case 5:
            break;
        
        case 0:
            puts("Exitted program");
            return 0;
        }

    }
}
