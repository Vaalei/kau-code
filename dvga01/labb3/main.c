#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "file.h"

#define ADD_VEHICLCE 1
#define REMOVE_VEHICLE 2
#define SORT 3
#define SHOW_VEHICLE 4
#define SHOW_REGISTRY 5
#define QUIT 0

int main(){
    char input[MAX_INPUT];
    char *eptr;
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
        choice = strtol(input, &eptr, 0);
        if (input == eptr) choice = -1; // Check if input is jibberish

        switch (choice)
        {
        case ADD_VEHICLCE:
            addVehicle();
            break;
        case REMOVE_VEHICLE:
            removeVehicle();
            break;
        case SORT:
            sort();
            break;
        case SHOW_VEHICLE:
            showOneVehicle();
            break;
        case SHOW_REGISTRY:
            showAllVehicles();
            break;
        case QUIT:
            puts("Exitted program");
            return 0;
        default:
            puts("That option does not exist");
            break;

        }

    }
}
