#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Functies.h"

#define BMPINPUT "Test.bmp" //Bestandsnaam

void startScherm()
{
    printf("Startscherm\n");
}

FILE *openBMP() //Functie opent de afbeelding
{
    FILE *inputBMP = fopen(BMPINPUT, "rb");

    if(inputBMP == NULL)
    {
        printf("%s\n", "Error: Unable to open the file!\n");
        exit(-1);
    }

    return inputBMP;
}

void readHeader(FILE *inputBMP, unsigned char *header)
{
    fread(header, 1, 54, inputBMP); //Zet de eerste 54 bites van inputBMP in de header.
}

void calcHeight(unsigned char *header, signed int *hoogte) //Functie berekend de hoogte van de afbeelding
{
    *hoogte = header[25] << 24 | header[24] << 16 | header[23] << 8 | header[22]; //Resultaat: hoogte = (8 bits header[21]) (8 bits header[20]) (8 bits header[19]) (8 bits header[18])
    printf("Hoogte: %dpx\n", *hoogte);
}

void calcWidth(unsigned char *header, signed int *breedte) //Functie berekend de breedte van de afbeelding
{
    *breedte = header[21] << 24 | header[20] << 16 | header[19] << 8 | header[18]; //Resultaat: breedte = (8 bits header[21]) (8 bits header[20]) (8 bits header[19]) (8 bits header[18])
    printf("Breedte: %dpx\n", *breedte);
}

void calcPixels(signed int *hoogte, signed int *breedte, signed int *pixels)
{
    *pixels = *hoogte * *breedte;

    printf("Totaal aantal pixels: %dpx\n", *pixels);
}

void cleanup(unsigned char *header, signed int *hoogte, signed int *breedte, signed int *pixels)
{
    free(header);
    free(hoogte);
    free(breedte);
    free(pixels);
}