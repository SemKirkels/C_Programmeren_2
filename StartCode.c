#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMPINPUT "Test.bmp"

int main(int argc, char* argv[])
{
    FILE *inputBMP = fopen(BMPINPUT, "rb");
    unsigned char header[54] = {0};
    signed int hoogte = 0;
    signed int breedte = 0;
    unsigned char *pixels = NULL;
    int totaalAantalPixels = 0;

    if(inputBMP == NULL)
    {
        printf("%s\n", "Error: Can't open the file");
        return -1;
    }

    fread(header, 1, 54, inputBMP); //Zet de eerste 54 bites van inputBMP in de header.

    breedte = header[21] << 24 | header[20] << 16 | header[19] << 8 | header[18]; // Resultaat: breedte = (8 bits header[21]) (8 bits header[20]) (8 bits header[19]) (8 bits header[18])
    printf("Breedte: %dpx\n", breedte);

    hoogte = header[25] << 24 | header[24] << 16 | header[23] << 8 | header[22];
    printf("Hoogte: %dpx\n", hoogte);

    totaalAantalPixels = breedte * hoogte;
    pixels = (unsigned char *) malloc(totaalAantalPixels * 3);
    if(pixels == NULL)
    {
        printf("Error: Memory allocation failed");
        return -2;
    }

    fread(pixels, 1, totaalAantalPixels * 3, inputBMP);
    printf("INFO: Heap memory allocated %d (bytes)\n", totaalAantalPixels * 3);
    
    

    fclose(inputBMP);
    printf("Info: File %s CLOSED\n", BMPINPUT);

    free(pixels);
    printf("Info: Heap memory freed: %d (bytes)\n", totaalAantalPixels * 3);

    return 0;
}