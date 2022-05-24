#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "Functies.h"

#define BMPINPUT "Test.bmp" //Bestandsnaam
#define BMPOUTPUT "FilterBMP.bmp"

void startScherm()
{
    printf("\t _              _                                   _              _____\n" );                                                                                                               
    printf("\t| |            | |                                 | |            / __  \\ \n");                                                                                                              
    printf("\t| |_ __ _  __ _| | __  ___  ___ _ __ ___   ___  ___| |_ ___ _ __  `' / /'\n");                                                                                                               
    printf("\t| __/ _` |/ _` | |/ / / __|/ _ \\ '_ ` _ \\ / _ \\// __| __/ _ \\ '__|   / /\n");                                                                                                                 
    printf("\t| || (_| | (_| |   <  \\__ \\  __/ | | | | |  __/\\__ \\ ||  __/ |    ./ /___\n");                                                                                                               
    printf(" \t\\__ \\__,_|\\__,_|_|\\_\\ |___/\\___|_| |_| |_|\\___||___/\\__\\___|_|    \\_____/ \n");      

    sleep(2);
    system("cls");
                                                                                                                                                                                        
    printf("\t                                   _    _         _          \n");             
    printf("\t                                  | |  | |       | |\n");
    printf("\t   __ _  ___ _ __ ___   __ _  __ _| | _| |_    __| | ___   ___  _ __\n");      
    printf("\t  / _` |/ _ \\ '_ ` _ \\ / _` |/ _` | |/ / __|  / _` |/ _ \\ / _ \\| '__| \n");     
    printf("\t | (_| |  __/ | | | | | (_| | (_| |   <| |_  | (_| | (_) | (_) | |       \n ");
    printf("\t  \\__, |\\___|_| |_| |_|\\__,_|\\__,_|_| \\_\\__|  \\__,_|\\___/ \\___/|_| \n   ");    
    printf("\t   __/ |  \n  ");                                                              
    printf("\t  |___/       \n   ");  

    sleep(2);
    system("cls");

    printf("\t _____                  _   ___      _        _    \n");                       
    printf("\t/  ___|                | | / (_)    | |      | |     \n");
    printf("\t\\ `--.  ___ _ __ ___   | |/ / _ _ __| | _____| |___      \n");                
    printf("\t `--. \\/ _ \\ '_ ` _ \\  |    \\| | '__| |/ / _ \\ / __|       \n");              
    printf("\t/\\__/ /  __/ | | | | | | |\\  \\ | |  |   <  __/ \\__ \\     \n");               
    printf("\t\\____/ \\___|_| |_| |_| \\_| \\_/_|_|  |_|\\_\\___|_|___/  \n");                   
                                                                         
    sleep(2);
    system("cls");                                                                     
                                                                                                                                   
    printf("\t  ___ _ __ \n");                                                              
    printf("\t / _ \\ '_ \\ \n");                                                             
    printf("\t|  __/ | | | \n");                                                            
    printf("\t \\___|_| |_| \n");    

    sleep(2);
    system("cls");
                                                                                                                           
    printf("\t   _      _ _ \n");                                                           
    printf("\t  (_)    | | | \n");                                                          
    printf("\t   _  ___| | | ___    ___   ___ _   _  ___ _ __  \n");                        
    printf("\t  | |/ _ \\ | |/ _ \\  / _ \\ / _ \\ | | |/ _ \\ '_ \\  \n");                       
    printf("\t  | |  __/ | |  __/ | (_) |  __/ |_| |  __/ | | |  \n");                      
    printf("\t  | |\\___|_|_|\\___|  \\___/ \\___|\\__, |\\___|_| |_|  \n");                      
    printf("\t _/ |                            __/ |             \n");                       
    printf("\t|__/                            |___/   \n ");               
    
    sleep(2);
    system("cls");
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

FILE *openTargetBMP() //Functie opent de target afbeelding
{
    FILE *targetBMP = fopen(BMPOUTPUT, "w");

    if(targetBMP == NULL)
    {
        printf("%s\n", "Error: Unable to create the file!\n");
        exit(-1);
    }
    return targetBMP;
}

void readHeader(FILE *inputBMP, unsigned char *header, FILE *targetBMP)
{
    fread(header, 1, 54, inputBMP); //Zet de eerste 54 bites van inputBMP in de header.

    fwrite(header, 1, 54, targetBMP); //Schrijft de header weg in targetBMP
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

void calcPixels(signed int *hoogte, signed int *breedte, signed int *aantalPixels)
{
    *aantalPixels = *hoogte * *breedte;
    printf("Totaal aantal pixels: %dpx\n", *aantalPixels);
}

void readImage(FILE *inputBMP, signed int *hoogte, signed int *breedte, signed int *aantalPixels, unsigned char *pixels)
{
    int kleurComponenten = 3 * (*aantalPixels);

    fread(pixels, 1, kleurComponenten, inputBMP); //3 * *pixels -> elke pixel bestaat uit 3 kleur componenten
    for(int i = 0; i < kleurComponenten; i++)
    {
        printf("%d: %x ", i, pixels[i]);
        if(i % 3 == 0)
        {
            printf("\n");
        }
    }
}

void chooseFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP)
{
    int keuze = 0;
    char confirmExit;

    /*
    *While loop fungeert als een FSM
    *De loop wacht op input en keert terug als het programma is doorlopen.
    */

    while(1) 
    {
        printf("\n");
        printf("1. Blur filter.\n");
        printf("2. Zwart-wit filter.\n");
        printf("3. Exit\n");
        printf("Kies een filter: ");
        scanf("%d", &keuze);

        if(keuze == 1)
        {
            printf("Blur filter\n");
            blurFilter(pixels, filterPixels, hoogte, breedte, aantalPixels, targetBMP);
        }
        else if(keuze == 2)
        {
            printf("Zwart wit filter\n");
            zwartWitFilter(pixels, filterPixels, hoogte, breedte, aantalPixels, targetBMP);
        }
        else if(keuze == 3)
        {
            printf("Weet u zeker dat u het programma wil verlaten [y/n]? ");
            scanf(" %c", &confirmExit);

            if(confirmExit == 'y' || confirmExit == 'Y')
            {
                exit(0);
            }
            else if(confirmExit == 'n' || confirmExit == 'N')
            {
                //Doe niets
            }
            else
            {
                printf("Ongeldige input!\n");
                //Doe niets
            }
        }
        else
        {
            printf("Ongeldige input\n");
            //Doe niets
        }
    }
}

void blurFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP)
{
     /*
    *Controle: Zijn de variabele goed doorgegeven?
    printf("%x \t", pixels[0]);
    printf("%x \t", filterPixels[0]);
    printf("%d \t", *hoogte);
    printf("%d \t", *breedte);
    printf("%d \t", *aantalPixels);
    printf("\n");
    */
    
    /* 
    | tempPixelTL | tempPixelT  | tempPixelTR |
    | tempPixelL  | targetPixel | tempPixelR  |
    | tempPixelBL | tempPixelB  | tempPixelBR |
    */
    int newPixel;
    int targetPixel;  //      Target pixel           (y * (*breedte) * 3) + (3 * x)
    int tempPixelTL;  //TL    top left               (y * (*breedte) * 3) + (3 * x) + (*breedte - 3)
    int tempPixelT;   //T     top                    (y * (*breedte) * 3) + (3 * x) + (*breedte)
    int tempPixelTR;  //TR    top right              (y * (*breedte) * 3) + (3 * x) + (*breedte + 3)
    int tempPixelL;   //L     left                   (y * (*breedte) * 3) + (3 * x) - 3
    int tempPixelR;   //R     right                  (y * (*breedte) * 3) + (3 * x) + 3
    int tempPixelBL;  //BL    bottom left            (y * (*breedte) * 3) + (3 * x) - (*breedte - 3)
    int tempPixelB;   //B     bottom                 (y * (*breedte) * 3) + (3 * x) - *breedte
    int tempPixelBR;  //BR    bottom right           (y * (*breedte) * 3) + (3 * x) - (*breedte + 3)
    int counter = 0;  //Telt waar de cursor in de target bmp is
    int offset = 54;  //Offset voor het schrijven in de target bmp
 
    /////////////
    //Execution//
    /////////////
    for(int y = 0; y < *hoogte; y++)
    {
        for(int x = 0; x < 3 * (*breedte); x++)
        {
            if((x - 3) < 0)                                 //pixel linkerzijkant
            {
                if((y - 1) < 0)                             //pixel links onder
                {
                    targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                    tempPixelT  = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte)];
                    tempPixelB  = 0;
                    tempPixelTL = 0;
                    tempPixelL  = 0;
                    tempPixelBL = 0;
                    tempPixelTR = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte + 3)];
                    tempPixelR  = pixels[(y * (*breedte) * 3) + (3 * x) + 3];
                    tempPixelBR = 0;
                }
                else if((y + 1) > *breedte)                 //pixel links boven
                {
                    targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                    tempPixelT  = 0;
                    tempPixelB  = pixels[(y * (*breedte) * 3) + (3 * x) - *breedte];
                    tempPixelTL = 0;
                    tempPixelL  = 0;
                    tempPixelBL = 0;
                    tempPixelTR = 0;
                    tempPixelR  = pixels[(y * (*breedte) * 3) + (3 * x) + 3];
                    tempPixelBR = pixels[(y * (*breedte) * 3) + (3 * x) - (*breedte + 3)];
                }
                else                                        //pixel linkerzijkant
                {
                    targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                    tempPixelT  = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte)];
                    tempPixelB  = pixels[(y * (*breedte) * 3) + (3 * x) - *breedte];
                    tempPixelTL = 0;
                    tempPixelL  = 0;
                    tempPixelBL = 0;
                    tempPixelTR = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte + 3)];
                    tempPixelR  = pixels[(y * (*breedte) * 3) + (3 * x) + 3];
                    tempPixelBR = pixels[(y * (*breedte) * 3) + (3 * x) - (*breedte + 3)];
                }
            }
            else if((x - 3) > *breedte)                     //pixel rechterzijkant
            {
                if((y - 1) < 0)                             //pixel rechts onder
                {
                    targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                    tempPixelT  = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte)];
                    tempPixelB  = 0;
                    tempPixelTL = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte - 3)];
                    tempPixelL  = pixels[(y * (*breedte) * 3) + (3 * x) - 3];
                    tempPixelBL = 0;
                    tempPixelTR = 0;
                    tempPixelR  = 0;
                    tempPixelBR = 0;
                }
                else if((y + 1) > *breedte)                //pixel rechts boven
                {
                    targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                    tempPixelT  = 0;
                    tempPixelB  = pixels[(y * (*breedte) * 3) + (3 * x) - *breedte];
                    tempPixelTL = 0;
                    tempPixelL  = pixels[(y * (*breedte) * 3) + (3 * x) - 3];
                    tempPixelBL = pixels[(y * (*breedte) * 3) + (3 * x) - (*breedte - 3)];
                    tempPixelTR = 0;
                    tempPixelR  = 0;
                    tempPixelBR = 0;
                }
                else                                        //pixel rechterzijkant
                {
                    targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                    tempPixelT  = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte)];
                    tempPixelB  = pixels[(y * (*breedte) * 3) + (3 * x) - *breedte];
                    tempPixelTL = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte - 3)];
                    tempPixelL  = pixels[(y * (*breedte) * 3) + (3 * x) - 3];
                    tempPixelBL = pixels[(y * (*breedte) * 3) + (3 * x) - (*breedte - 3)];
                    tempPixelTR = 0;
                    tempPixelR  = 0;
                    tempPixelBR = 0;
                }
            }
            else            
            {
                targetPixel = pixels[(y * (*breedte) * 3) + (3 * x)];
                tempPixelT  = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte)];
                tempPixelB  = pixels[(y * (*breedte) * 3) + (3 * x) - *breedte];
                tempPixelTL = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte - 3)];
                tempPixelL  = pixels[(y * (*breedte) * 3) + (3 * x) - 3];
                tempPixelBL = pixels[(y * (*breedte) * 3) + (3 * x) - (*breedte - 3)];
                tempPixelTR = pixels[(y * (*breedte) * 3) + (3 * x) + (*breedte + 3)];
                tempPixelR  = pixels[(y * (*breedte) * 3) + (3 * x) + 3];
                tempPixelBR = pixels[(y * (*breedte) * 3) + (3 * x) - (*breedte + 3)];
            }
            newPixel = (targetPixel + tempPixelTL + tempPixelT + tempPixelTR + tempPixelL + tempPixelR + tempPixelBL + tempPixelB + tempPixelBR) / 9;
            printf("%x\n", newPixel); //Test
            filterPixels[counter] = newPixel;
            printf("%x\n", filterPixels[counter]); //Test
            counter++;
        }
    }
    fseek(targetBMP, (offset), SEEK_SET);
    fwrite(filterPixels, 1, 3 * (*aantalPixels), targetBMP);
}

void zwartWitFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP)
{
    /*
    *Controle: Zijn de variabele goed doorgegeven?
    printf("%x \t", pixels[0]);
    printf("%x \t", filterPixels[0]);
    printf("%d \t", *hoogte);
    printf("%d \t", *breedte);
    printf("%d \t", *aantalPixels);
    printf("\n");
    */
}

void cleanup(unsigned char *header, signed int *hoogte, signed int *breedte, signed int *aantalPixels, unsigned char *pixels, unsigned char *filterPixels, FILE *inputBMP, FILE *targetBMP)
{
    free(header);
    free(hoogte);
    free(breedte);
    free(aantalPixels);
    free(pixels);
    free(filterPixels);

    fclose(inputBMP);
    fclose(targetBMP);
}