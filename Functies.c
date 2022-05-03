#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMPINPUT "Test.bmp"

FILE *openBMP();
unsigned char readHeader(FILE *inputBMP);
int calcHeight(unsigned char header[54]);
int calcWidth(unsigned char header[54]);

FILE *openBMP()
{
    FILE *inputBMP = fopen(BMPINPUT, "rb");

    if(inputBMP == NULL)
    {
        printf("%s\n", "Error: Can't open the file!\n");
        //Programma moet stoppen
    }

    return inputBMP;
}

unsigned char readHeader(FILE *inputBMP)
{
    unsigned char header[54] = {0};
    fread(header, 1, 54, inputBMP); //Zet de eerste 54 bites van inputBMP in de header.

    return header[54];
}

int calcHeight(unsigned char header[54])
{
    signed int hoogte = 0;

    hoogte = header[25] << 24 | header[24] << 16 | header[23] << 8 | header[22]; //Resultaat: hoogte = (8 bits header[21]) (8 bits header[20]) (8 bits header[19]) (8 bits header[18])
    printf("Hoogte: %dpx\n", hoogte);

    return hoogte;
}

int calcWidth(unsigned char header[54])
{
    signed int breedte = 0;

    breedte = header[21] << 24 | header[20] << 16 | header[19] << 8 | header[18]; //Resultaat: breedte = (8 bits header[21]) (8 bits header[20]) (8 bits header[19]) (8 bits header[18])
    printf("Breedte: %dpx\n", breedte);

    return breedte;
}