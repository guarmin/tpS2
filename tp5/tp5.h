#ifndef tp5_h
#define tp5_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char name[50];
    int code;
    char date_peremption[20];
    char date_fabrication[20];
    float price;
    int quantity;
    int stock;
} Medicament;

#endif