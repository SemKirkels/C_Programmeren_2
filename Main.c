#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "Functies.h"

int main(int argc, char *argv[])
{
    /////////////////////
    //Memory allocation//
    /////////////////////
    unsigned char *header = (unsigned char *) malloc(54 * sizeof(unsigned char));
    signed int *hoogte = (signed int *) malloc(sizeof(signed int));
    signed int *breedte = (signed int *) malloc(sizeof(signed int));
    signed int *aantalPixels = (signed int *) malloc(sizeof(signed int));
    unsigned char *pixels = (unsigned char *) malloc(sizeof(char) * (*aantalPixels) * 3);
    unsigned char *filterPixels = (unsigned char *) malloc(sizeof(char) * (*aantalPixels) * 3);

    ///////////////
    //Preparation//
    ///////////////
    //system("cls");
    //startScherm();
    FILE *inputBMP = openBMP(); //Opent BMP file
    FILE *targetBMP = openTargetBMP(); //Opent de BMP Target file
    readHeader(inputBMP, header, targetBMP); //Leest de header
    calcHeight(header, hoogte); //Berekend hoogte BMP file
    calcWidth(header, breedte); //Berekend breedte BMP file
    calcPixels(hoogte, breedte, aantalPixels); //Berekend het totaal aantal pixels
    readImage(inputBMP, hoogte, breedte, aantalPixels, pixels); //Leest de kleurcomponenten in

    /////////////
    //Execution//
    /////////////
    chooseFilter(pixels, filterPixels, hoogte, breedte, aantalPixels, targetBMP);

    ///////////
    //Cleanup//
    ///////////
    cleanup(header, hoogte, breedte, aantalPixels, pixels, filterPixels, inputBMP, targetBMP);

    return 0;
}