#pragma once
//#ifndef HEADER_H
//#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define MAX_INPUT 20
#define FILENAME "register.txt"
#define MAX_VEHICLES 10

struct Person_t{
    char name[MAX_INPUT];
    int age;
};


struct Vehicle_t{
    char type[MAX_INPUT];
    char brand[MAX_INPUT];
    char register_number[MAX_INPUT];
    struct Person_t person;
};

void addVehicle(void);
void removeVehicle(void);
void sort(void);
void showOneVehicle(void);
void showAllVehicles(void);
//#endif