#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "Functies.h"

#define BMPINPUT "Test.bmp" //Bestandsnaam

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

void chooseFilter()
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
            zwartWitFilter();
        }
        else if(keuze == 2)
        {
            zwartWitFilter();
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
            //Doe niets
        }
    }
}

void blurFilter()
{
    printf("Blur filter\n");
}

void zwartWitFilter()
{
    printf("Zwart wit filter\n");
}

void cleanup(unsigned char *header, signed int *hoogte, signed int *breedte, signed int *aantalPixels, unsigned char *pixels)
{
    free(header);
    free(hoogte);
    free(breedte);
    free(aantalPixels);
    free(pixels);
}