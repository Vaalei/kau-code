#include "file.h"


/**
 * @brief Request a string input with an input message.
 *
 * Request a string from the user using a message that will be prompted to the user before their input. 
 * Returns the users response without an end of line character.
 */
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


/**
 * @brief Request an integer input using an input message.
 *
 * Request an integer from the user using a message that will be prompted to the user before their input. 
 * Returns the users response without any excess characters.
 * 
 * Example: lk2asjkdj2uasd -> 22
 */
int readInt(char message[])
{
    puts("");
    puts(message);
    char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);
    int number = atoi(input);
    return number;
}

/**
 * @brief Check if file exists, creates new file if it does not exist
 */
void checkForFile(char filename[])
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        f = fopen(filename, "w");
    }
    fclose(f);
}

/**
 * @brief Create a new vehicle
 *
 * Creates a new vehicle by modifying an empty Vehicle_t struct
 * Usage:
 * @code{.c}
 * struct Vehicle_t vehicle;
 * createVehicle(vehicle);
 * @endcode
 */
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

/**
 * @brief Loads all vehicles from the register, returns length of array
 * 
 * Loads all vehicles by modifying and empty array of Vehicle_t structs with data from the save file
 * Usage:
 * @code{.c}
 * struct Vehicle_t vehicles[];
 * length = loadAllVehicles(vehicles);
 * @endcode
 */
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

/**
 * @brief Prints the entire register to the user
 *
 * Shows Vehicle- type, brand and register number. 
 */
void showAllVehicles(void)
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    int i;
    for (i = 0; i <length; i++)
    {
        printf("%d.\tType: %s\tBrand: %s\tReg Num: %s\n", i+1, vehicles[i].type, vehicles[i].brand, vehicles[i].register_number);
    }
}

/**
 * @brief Prints the info of one car in the register to the user
 *
 * Shows Vehicle- type, brand, register number, owner- name and age  
 */
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
/**
 * @brief Saves all vehicles to the file
 *
 * Saves Vehicle- type, brand, register number, owner- name and age in a file with formatting
 * type brand "register number" "owner name" "owner age"
 */
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

/**
 * @brief Saves one vehicle to the file
 *
 * Saves Vehicle- type, brand, register number, owner- name and age in a file with formatting
 * type brand "register number" "owner name" "owner age"
 */
void saveVehicle(struct Vehicle_t vehicle)
{
    struct Vehicle_t vehicles[MAX_VEHICLES];
    int length = loadAllVehicles(vehicles);
    vehicles[length] = vehicle;
    
    save(vehicles, length+1);

}
/**
 * @brief Deletes one vehicle based on position from the the file
 */
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

/**
 * @brief Prompts the user to create a new vehicle
 */
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

/**
 * @brief Prompts the user to deleta an existing vehicle
 */
void removeVehicle()
{
    int index = readInt("Index of the vehicle to be removed: ");
    deleteVehicle(index);

}

/**
 * @brief Swaps the memory addresses of two pointers
 */
void swap(struct Vehicle_t* ap, struct Vehicle_t* bp){
    struct Vehicle_t temp = *ap;
    *ap = *bp;
    *bp = temp;
}

/**
 * @brief Sorts the savefile based on the name of the cars brand
 */
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
