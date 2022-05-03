#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Functies.h"

int main(int argc, char *argv[])
{
    /////////////////////
    //Memory allocation//
    /////////////////////
    unsigned char *header = malloc(54*sizeof(unsigned char));
    signed int *hoogte = malloc(sizeof(signed int));
    signed int *breedte = malloc(sizeof(signed int));
    signed int *pixels = malloc(sizeof(signed int));

    ////////////
    //Functies//
    ////////////
    system("cls");
    startScherm();
    FILE *inputBMP = openBMP(); //Opent BMP file
    readHeader(inputBMP, header); //Leest de header
    calcHeight(header, hoogte); //Berekend hoogte BMP file
    calcWidth(header, breedte); //Berekend breedte BMP file
    calcPixels(hoogte, breedte, pixels);

    return 0;
}