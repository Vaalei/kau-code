#include "funktioner.h"

const char* readStr(char message[])
{
    puts("");
    puts(message);
    static char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);
    if (strchr(input,'\n') == NULL) /* no occurence of the newline character in the buffer */
        while (getchar() != '\n');
    strtok(input, "\n");
    return input;
}

int readInt(char message[])
{
    puts("");
    puts(message);
    char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);
    int number = atoi(input);
    return number;
}

void checkForFile(char filename[])
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        f = fopen(filename, "w");
    }
    fclose(f);
}

void createVehicle(struct Vehicle_t *vehicle)
{
    struct Person_t person;

    strcpy(vehicle -> type, readStr("Type of vehicle: "));
    strcpy(vehicle -> brand, readStr("Vehicle brand: "));
    strcpy(vehicle -> register_number, readStr("Registration number: "));
    strcpy(person.name, readStr("Owner name: "));
    person.age = readInt("Owner age: ");

    vehicle -> person = person;
}


int loadAllVehicles(struct Vehicle_t *vehicles)
{
    checkForFile(FILENAME);
    FILE *f = fopen(FILENAME, "r");

    int i = 0;
    while(fscanf(f, "%s %s %s %s %d\n", vehicles[i].type, vehicles[i].brand, vehicles[i].register_number, vehicles[i].person.name, &vehicles[i].person.age) != EOF)
    {
        i++;
    }
    fclose(f);
    return i;
}

void showAllVehicles(void)
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    int i;
    for (i = 0; i <length; i++)
    {
        printf("%d.\tType: %s\tBrand: %s\tReg Num: %s\tOwners name: %s\tOwners age: %d\n", i+1, vehicles[i].type, vehicles[i].brand, vehicles[i].register_number, vehicles[i].person.name, vehicles[i].person.age);
    }
}

void showOneVehicle()
{
    int position = readInt("Index of vehicle: ");
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    if ((position > length) || (position < 1))
    {
        puts("Requested vehicle does not exist");
        return;
    }
    int i = position - 1;
    printf("Type: %s\tBrand: %s\tReg Num: %s\tOwners name: %s\tOwners age: %d\n", vehicles[i].type, vehicles[i].brand, vehicles[i].register_number, vehicles[i].person.name, vehicles[i].person.age);
}

void save(struct Vehicle_t vehicles[], int length)
{
    printf("%s\n", vehicles[length].type);
    FILE *f = fopen(FILENAME, "w");
    int i;
    for (i = 0; i <length; i++)
    {
        fprintf(f, "%s %s %s %s %d\n", vehicles[i].type, vehicles[i].brand, vehicles[i].register_number, vehicles[i].person.name, vehicles[i].person.age);
    }
    fclose(f);
}

void saveVehicle(struct Vehicle_t vehicle)
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    vehicles[length] = vehicle;
    
    save(vehicles, length+1);

}

void deleteVehicle(int position)
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    if ((position > length) || (position < 1))
    {
        puts("Requested vehicle does not exist");
        return;
    }
    int i;
    for (i = position - 1; i < length - 1; i++)
        vehicles[i] = vehicles[i+1];
    save(vehicles, length-1);
}

void addVehicle()
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    if (length >= MAX_VEHICLES){
        puts("Error: Maximum amount of cars has been exceeded");
        return;
    }
    struct Vehicle_t vehicle;
    createVehicle(&vehicle);
    if (vehicle.person.age == 0){
        puts("Error: Invalid age, age must be a positive integer");
        return;
    }
    saveVehicle(vehicle);
}

void removeVehicle()
{
    int index = readInt("Index of the vehicle to be removed: ");
    deleteVehicle(index);

}
void swap(struct Vehicle_t* ap, struct Vehicle_t* bp){
    struct Vehicle_t temp = *ap;
    *ap = *bp;
    *bp = temp;
}
void sort()
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    int i, j, tmp;
    int max = length -1;
    struct Vehicle_t temp;

    for (i = 0; i < max; i++)
    {
        for (j = 0; j < max - i; j++)
        {
            if (strcmp(vehicles[j].brand, vehicles[j + 1].brand) > 0)
            {
                swap(&vehicles[j], &vehicles[j+1]);
            }
        }
    }
    save(vehicles, length);
}
