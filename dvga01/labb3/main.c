#include <stdio.h>
#include <stdlib.h>
#include "funktioner.h"


int main(){
    char input[MAX_INPUT];
    int choice;
    int i;

    struct Vehicle_t vehicles[MAX_VEHICLES];

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
            addVehicle();
            break;
        case 2:
            removeVehicle();
            break;
        case 3:
            sort();
            break;
        case 4:
            showOneVehicle();
            break;
        case 5:
            showAllVehicles();
            break;
        case 0:
            puts("Exitted program");
            return 0;
        }

    }
}
