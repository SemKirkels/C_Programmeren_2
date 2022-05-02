#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functies.h"

int main(int argc, char *argv[])
{
    FILE *inputBMP = openBMP(); //Opent BMP file
    unsigned char header = readHeader(inputBMP);
    calcHeight(header); //Berekend hoogte BMP file
    calcWidth(header); //Berekend breedte BMP file

    return 0;
}