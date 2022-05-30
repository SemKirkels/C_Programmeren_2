#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "Functies.h"

/*
#define BMPINPUT "Input/Test7.bmp" //Bestandsnaam
#define BMPOUTPUT "Output/FilterBMP.bmp" //Bestandsnaam Target File
*/

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
    char BMPINPUT[255]="";

    printf("Kies een bestand: ");
    scanf("%s", BMPINPUT);
    
    FILE *inputBMP = fopen(BMPINPUT, "rb");

    if(inputBMP == NULL)
    {
        printf("%s\n", "Error: Unable to open the file!\n");
        sleep(1);
        exit(-1);
    }

    return inputBMP;
}

FILE *openTargetBMP() //Functie opent de target afbeelding
{
    char BMPOUTPUT[255]="";

    printf("Naam ouput file: ");
    scanf("%s", BMPOUTPUT);
    
    FILE *targetBMP = fopen(BMPOUTPUT, "wb");

    if(targetBMP == NULL)
    {
        printf("%s\n", "Error: Unable to create the file!\n");
        sleep(1);
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
    printf("\nHoogte: %dpx\n", *hoogte);
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
    /*
    for(int i = 0; i < kleurComponenten; i++)
    {
        printf("%d: %x ", i, pixels[i]);
        if(i % 3 == 0)
        {
            printf("\n");
        }
    }
    */
}

void chooseFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP, FILE *inputBMP, unsigned char *header)
{
    int keuze = 0;
    char confirmExit;

    /*
    Er wordt eerst gecontrolleerd of dat de afbeelding de juiste resolutie heeft.
    Als de lengte of breedte van de afbeelding niet deelbaar is door 4 wordt gebruiker gevraagd of dat de lege doel afbeelding verwijderd moet worden.
    */

    if((*breedte % 4) != 0 || (*hoogte % 4) != 0 )
    {
        char *fileName = (char *) malloc(sizeof(char));
        char confirmDelete;

        printf("\n");
        printf("De afbeelding wordt niet ondersteunt!\n");
        printf("Het opruimen wordt gestart\n");
        cleanup(header, hoogte, breedte, aantalPixels, pixels, filterPixels, inputBMP, targetBMP);
        
        while(1)
        {
            printf("\n");
            printf("Het doelbestand kan beschadigd of leeg zijn.\n");
            printf("Wilt u het doelbestand verwijderen [y/n]?\n");
            scanf(" %c", &confirmDelete);
            if(confirmDelete == 'y' || confirmDelete == 'Y')
            {
                printf("Geef de bestandsnaam van het te verwijderen bestand op: ");
                scanf("%s", fileName);
                remove(fileName);
                break;
            }
            else if(confirmDelete == 'n' || confirmDelete == 'N')
            {
                break;
            }
            else
            {
                printf("Ongeldige invoer!\n");
            }
        }
        exit(-2);
    }

    /*
    *While loop fungeert als een FSM
    *De loop wacht op input en keert terug als het programma is doorlopen.
    */

    while(1) 
    {
        /*
        De gebruiker wordt gevraagd welke filter hij wil gebruiken.
        Daarna wordt de functie van de bijbehorende filter gestart
        */
       
        printf("\n");
        printf("1. Blur filter.\n");
        printf("2. Zwart-wit filter.\n");
        printf("3. Negatief filter\n");
        printf("4. Exit\n");
        printf("Kies een filter: ");
        scanf("%d", &keuze);

        if(keuze == 1)
        {
            printf("Blur filter\n");
            blurFilter(pixels, filterPixels, hoogte, breedte, aantalPixels, targetBMP);
            closersmoother();
        }
        else if(keuze == 2)
        {
            printf("Zwart wit filter\n");
            zwartWitFilter(pixels, filterPixels, hoogte, breedte, aantalPixels, targetBMP);
            zwartwitcloser();
        }
        else if(keuze == 3)
        {
            printf("Negatief filter\n");
            negatieffilter(pixels, filterPixels, hoogte, breedte, aantalPixels, targetBMP);
        }
        else if(keuze == 4)
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
    unsigned char newPixel;
    unsigned char targetPixel;  //      Target pixel           (y * (*breedte) * 3) + (x)
    unsigned char tempPixelTL;  //TL    top left               (y * (*breedte) * 3) + (x) + ((3 * (*breedte)) - 3)
    unsigned char tempPixelT;   //T     top                    (y * (*breedte) * 3) + (x) + (3 * (*breedte))
    unsigned char tempPixelTR;  //TR    top right              (y * (*breedte) * 3) + (x) + ((3 * (*breedte)) + 3)
    unsigned char tempPixelL;   //L     left                   (y * (*breedte) * 3) + (x) - 3
    unsigned char tempPixelR;   //R     right                  (y * (*breedte) * 3) + (x) + 3
    unsigned char tempPixelBL;  //BL    bottom left            (y * (*breedte) * 3) + (x) - ((3 * (*breedte)) - 3)
    unsigned char tempPixelB;   //B     bottom                 (y * (*breedte) * 3) + (x) - (3 * (*breedte))
    unsigned char tempPixelBR;  //BR    bottom right           (y * (*breedte) * 3) + (x) - ((3 * (*breedte)) + 3)
    int counter = 0;  //Telt waar de cursor in de target bmp is
    int offset = 54;  //Offset voor het schrijven in de target bmp
 
    /////////////
    //Execution//
    /////////////
    /*
    for(int x = 0; x < (3 * (*aantalPixels)); x++)
    {
        printf("%d ", pixels[x]);
        if(x % (3 * (*breedte)) == 0 && x != 0)
        {
            printf("\n");
        }
    }
    */

    printf("\n");

    for(int y = 0; y < *hoogte; y++)
    {
        //printf("Pixel offset = %d\t y = %d\n", (y * ((*breedte) * 3)), y);
        
        for(int x = 0; x < (3 * (*breedte)); x++)
        {
            if((x - 3) < 0)                                 //pixel linkerzijkant
            {
                if((y - 1) < 0)                             //pixel links onder
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = pixels[(y * ((*breedte) * 3)) + (x) + (3 * (*breedte))];
                    tempPixelB  = 0;
                    tempPixelTL = 0;
                    tempPixelL  = 0;
                    tempPixelBL = 0;
                    tempPixelTR = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) + 3)];
                    tempPixelR  = pixels[(y * ((*breedte) * 3)) + (x) + 3];
                    tempPixelBR = 0;
                }
                else if((y + 1) >= (*hoogte))               //pixel links boven
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = 0;
                    tempPixelB  = pixels[(y * ((*breedte) * 3)) + (x) - (3 * (*breedte))];
                    tempPixelTL = 0;
                    tempPixelL  = 0;
                    tempPixelBL = 0;
                    tempPixelTR = 0;
                    tempPixelR  = pixels[(y * ((*breedte) * 3)) + (x) + 3];
                    tempPixelBR = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) + 3)];
                }
                else                                        //pixel linkerzijkant
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = pixels[(y * ((*breedte) * 3)) + (x) + (3 * (*breedte))];
                    tempPixelB  = pixels[(y * ((*breedte) * 3)) + (x) - (3 * (*breedte))];
                    tempPixelTL = 0;
                    tempPixelL  = 0;
                    tempPixelBL = 0;
                    tempPixelTR = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) + 3)];
                    tempPixelR  = pixels[(y * ((*breedte) * 3)) + (x) + 3];
                    tempPixelBR = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) + 3)];
                }
            }
            else if((x + 3) > ((3 * (*breedte)) - 1))               //pixel rechterzijkant
            {
                if((y - 1) < 0)                             //pixel rechts onder
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = pixels[(y * ((*breedte) * 3)) + (x) + (3 * (*breedte))];
                    tempPixelB  = 0;
                    tempPixelTL = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) - 3)];
                    tempPixelL  = pixels[(y * ((*breedte) * 3)) + (x) - 3];
                    tempPixelBL = 0;
                    tempPixelTR = 0;
                    tempPixelR  = 0;
                    tempPixelBR = 0;
                }
                else if((y + 1) >= (*hoogte))                //pixel rechts boven
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = 0;
                    tempPixelB  = pixels[(y * ((*breedte) * 3)) + (x) - (3 * (*breedte))];
                    tempPixelTL = 0;
                    tempPixelL  = pixels[(y * ((*breedte) * 3)) + (x) - 3];
                    tempPixelBL = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) - 3)];
                    tempPixelTR = 0;
                    tempPixelR  = 0;
                    tempPixelBR = 0;
                }
                else                                        //pixel rechterzijkant
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = pixels[(y * ((*breedte) * 3)) + (x) + (3 * (*breedte))];
                    tempPixelB  = pixels[(y * ((*breedte) * 3)) + (x) - (3 * (*breedte))];
                    tempPixelTL = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) - 3)];
                    tempPixelL  = pixels[(y * ((*breedte) * 3)) + (x) - 3];
                    tempPixelBL = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) - 3)];
                    tempPixelTR = 0;
                    tempPixelR  = 0;
                    tempPixelBR = 0;
                }
            }
            else            
            {
                if((y - 1) < 0)                             //Pixel onderkant
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = pixels[(y * ((*breedte) * 3)) + (x) + (3 * (*breedte))];
                    tempPixelB  = 0;
                    tempPixelTL = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) - 3)];
                    tempPixelL  = pixels[(y * ((*breedte) * 3)) + (x) - 3];
                    tempPixelBL = 0;
                    tempPixelTR = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) + 3)];
                    tempPixelR  = pixels[(y * ((*breedte) * 3)) + (x) + 3];
                    tempPixelBR = 0;
                }
                else if((y + 1) >= (*hoogte))               //Pixel bovenkant
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = 0;
                    tempPixelB  = pixels[(y * ((*breedte) * 3)) + (x) - (3 * (*breedte))];
                    tempPixelTL = 0;
                    tempPixelL  = pixels[(y * ((*breedte) * 3)) + (x) - 3];
                    tempPixelBL = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) - 3)];
                    tempPixelTR = 0;
                    tempPixelR  = pixels[(y * ((*breedte) * 3)) + (x) + 3];
                    tempPixelBR = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) + 3)];
                }
                else
                {
                    targetPixel = pixels[(y * ((*breedte) * 3)) + (x)];
                    tempPixelT  = pixels[(y * ((*breedte) * 3)) + (x) + (3 * (*breedte))];
                    tempPixelB  = pixels[(y * ((*breedte) * 3)) + (x) - (3 * (*breedte))];
                    tempPixelTL = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) - 3)];
                    tempPixelL  = pixels[(y * ((*breedte) * 3)) + (x) - 3];
                    tempPixelBL = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) - 3)];
                    tempPixelTR = pixels[(y * ((*breedte) * 3)) + (x) + ((3 * (*breedte)) + 3)];
                    tempPixelR  = pixels[(y * ((*breedte) * 3)) + (x) + 3];
                    tempPixelBR = pixels[(y * ((*breedte) * 3)) + (x) - ((3 * (*breedte)) + 3)];
                }
            }
            newPixel = (targetPixel + tempPixelTL + tempPixelT + tempPixelTR + tempPixelL + tempPixelR + tempPixelBL + tempPixelB + tempPixelBR) / 9;
            filterPixels[counter] = newPixel;
            counter++;
        }
    }
    /*
    for(int x = 0; x < (3 * (*aantalPixels)); x++)
    {
        printf("%d ", filterPixels[x]);
        if(x % (3 * (*breedte)) == 0 && x != 0)
        {
            printf("\n");
        }
    }
    */

    fseek(targetBMP, (offset), SEEK_SET);
    fwrite(filterPixels, 1, (3 * (*aantalPixels)), targetBMP);
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

   unsigned char newPixel;
   unsigned char targetPixelB;  //Target pixel blauw (y * (*breedte) * 3) + (x + blauw)
   unsigned char targetPixelG;  //Target pixel groen (y * (*breedte) * 3) + (x + groen)
   unsigned char targetPixelR;  //Target pixel rood (y * (*breedte) * 3) + (x + rood)
   int blauw = 0;
   int groen = 1;
   int rood = 2;
   int counter = 0;             //Telt waar de cursor in de target bmp is.
   int offset = 54;             //Offset voor het schrijven in target bmp. (voorkomt overschrijven van de header)

   /////////////
   //Execution//
   /////////////
   /*
   for(int x = 0; x < (3 * (*aantalPixel)); x++)
   {
       printf("%d ", pixels[x]);
       if(x % (3 * (*breedte)) == 0 && x != 0)
       {
           printf("\n");
       }
   }
   */

    printf("\n");

    for(int y = 0; y < *hoogte; y++)
    {
        //printf("Pixel offset = %d\t y = %d\n", (y * ((*breedte) * 3)), y);
        
        for(int x = 0; x < (3 * (*breedte)); x += 3)
        {
            targetPixelB = pixels[(y * ((*breedte) * 3)) + (x + blauw)];
            targetPixelG = pixels[(y * ((*breedte) * 3)) + (x + groen)];
            targetPixelR = pixels[(y * ((*breedte) * 3)) + (x + rood)];
            newPixel = (targetPixelB + targetPixelG + targetPixelR) / 3;
            filterPixels[counter + blauw] = newPixel;
            filterPixels[counter + groen] = newPixel;
            filterPixels[counter + rood] = newPixel;
            counter += 3;
        }
    }
    /*
    for(int x = 0; x < (3 * (*aantalPixels)); x++)
    {
        printf("%d ", filterPixels[x]);
        if(x % (3 * (*breedte)) == 0 && x != 0)
        {
            printf("\n");
        }
    }
    */

   fseek(targetBMP, (offset), SEEK_SET);
   fwrite(filterPixels, 1, (3 * (*aantalPixels)), targetBMP);
}

void negatieffilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP)
{
    unsigned char newPixel;
    unsigned char pixel;
    int counter = 0;
    int offset =54;

    printf("\n");

    for(int y = 0; y < *hoogte; y++)
    {
        for(int x = 0; x <(3 * (*breedte)); x ++)
        {
           pixel = pixels[(y * ((*breedte) * 3)) + (x)];
           newPixel = 255-pixel;
           filterPixels[counter] =newPixel;
           counter++; 

        }
    }
    fseek(targetBMP, (offset), SEEK_SET);
    fwrite(filterPixels,1, (3 * (*aantalPixels)), targetBMP);
}

void closersmoother()
{
printf("\t   ______          _             _    _                                 _        _                       \n");       
printf("\t   | ___ \\        | |           | |  | |                               | |      (_)                           \n");  
printf("\t   | |_/ / ___  __| | __ _ _ __ | | _| |_  __   _____   ___  _ __    __| | ___   _ _ __ ___   __ _  __ _  ___ \n");  
printf("\t   | ___ \\/ _ \\/ _` |/ _` | '_ \\| |/ / __| \\ \\ / / _ \\ / _ \\| '__|  / _` |/ _ \\ | | '_ ` _ \\ / _` |/ _` |/ _ \\   ");  
printf("\t   | |_/ /  __/ (_| | (_| | | | |   <| |_   \\ V / (_) | (_) | |    | (_| |  __/ | | | | | | | (_| | (_| |  __/\n");  
printf("\t   \\____/ \\___|\\__,_|\\__,_|_| |_|_|\\_\\__|    \\_/ \\___/ \\___/|_|     \\__,_|\\___| |_|_| |_| |_|\\__,_|\\__, |\\___|   ");  
printf("\t                                                                                                    __/ |     \n");  
printf("\t                                                                                                   |___/      \n");  
printf("\t                              _   _                  _                    _                _ _                \n");  
printf("\t                             | | | |                | |                  | |              (_) |               \n");  
printf("\t    ___ _ __ ___   ___   ___ | |_| |__   ___ _ __   | |_ ___    __ _  ___| |__  _ __ _   _ _| | _____ _ __    \n");  
printf("\t   / __| '_ ` _ \\ / _ \\ / _ \\| __| '_ \\ / _ \\ '__|  | __/ _ \\  / _` |/ _ \\ '_ \\| '__| | | | | |/ / _ \\ '_ \\   \n");  
printf("\t   \\__ \\ | | | | | (_) | (_) | |_| | | |  __/ |     | ||  __/ | (_| |  __/ |_) | |  | |_| | |   <  __/ | | |  \n");  
printf("\t   |___/_| |_| |_|\\___/ \\___/ \\__|_| |_|\\___|_|      \\__\\___|  \\__, |\\___|_.__/|_|   \\__,_|_|_|\\_\\___|_| |_|  \n");  
printf("\t                                                                __/ |                                         \n");  
printf("\t                                                               |___/                                          \n");  
}

void zwartwitcloser()
{
printf("\t______          _             _    _                                 _                                _                       _ _   \n");
printf("\t| ___ \\        | |           | |  | |                               | |                              | |                     (_) |  \n");
printf("\t| |_/ / ___  __| | __ _ _ __ | | _| |_  __   _____   ___  _ __    __| | ___   ______      ____ _ _ __| |_   ______  __      ___| |_ \n");
printf("\t| ___ \\/ _ \\/ _` |/ _` | '_ \\| |/ / __| \\ \\ / / _ \\ / _ \\| '__|  / _` |/ _ \\ |_  /\\ \\ /\\ / / _` | '__| __| |______| \\ \\ /\\ / / | __| \n");
printf("\t| |_/ /  __/ (_| | (_| | | | |   <| |_   \\ V / (_) | (_) | |    | (_| |  __/  / /  \\ V  V / (_| | |  | |_            \\ V  V /| | |_  \n");
printf("\t\\____/ \\___|\\__,_|\\__,_|_| |_|_| \\_\\__|   \\_/ \\___/ \\___/|_|     \\__,_|\\___| /___|  \\_/\\_/ \\__,_|_|   \\__|            \\_/\\_/ |_|\\__| \n");
                                                                                                                                    
                                                                                                                                    
printf("\t   __ _ _ _              _                    _                _ _                      \n");                                            
printf("\t  / _(_) | |            | |                  | |              (_) |            \n");                                                     
printf("\t | |_ _| | |_ ___ _ __  | |_ ___    __ _  ___| |__  _ __ _   _ _| | _____ _ __      \n");                                                
printf("\t |  _| | | __/ _ \\ '__| | __/ _ \\  / _` |/ _ \\ '_ \\| '__| | | | | |/ / _ \\ '_ \\       \n");                                              
printf("\t | | | | | ||  __/ |    | ||  __/ | (_| |  __/ |_) | |  | |_| | |   <  __/ | | |  \n");                                                  
printf("\t |_| |_|_|\\__\\___|_|     \\__\\___|  \\__, |\\___|_.__/|_|   \\__,_|_|_|\\_\\___|_| |_|        \n");                                            
printf("\t                                    __/ |                                                                   \n");                        
printf("\t                                   |___/                                                                           \n");                 
    
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