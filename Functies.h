#ifndef Functies_H
#define Functies_H

/*
*Print het startscherm.
*@param: Geen
*@return: Geen
*/
void startScherm();


/*
*Opent de BMP afbeelding.
*@param: char BMPINPUT[100] (Hier wordt de bestandsnaam van het te openen bestand in opgeslagen)
*@return: FILE *inputBMP
*/
FILE *openBMP();


/*
*Functie opent de targetBMP
*@param: char BMPOUTPUT[100] (Hier wordt de bestandsnaam van het doel bestand in opgeslagen)
*@return: FILE *inputBMP
*/
FILE *openTargetBMP();


/*
*Leest de eerste 54 bytes in van de BMP afbeelding.
*@param: FILE *inputBMP 
*@param: unsigned char *header (In de header worden de eerste 54 bytes van de afbeelding opgeslagen.)
*@return: Geen
*/
void readHeader(FILE *inputBMP, unsigned char *header, FILE *targetBMP);


/*
*Haalt de hoogte uit de header.
*@param: unsigned char *header (Uit deze header worden de eerste 54 bytes van de afbeelding gehaald. Hiermee wordt de hoogte berekend.)
*@param: signed int *hoogte (Hier wordt de hoogte van de afbeelding in opgeslagen.)
*@return: Geen
*/
void calcHeight(unsigned char *header, signed int *hoogte);


/*
*Haalt de breedte uit de header.
*@param: unsigned char *header (Uit deze header worden de eerste 54 bytes van de afbeelding gehaald. Hiermee wordt de breedte berekend.)
*@param: signed int *breedte (Hier wordt de breedte van de afbeelding in opgeslagen.)
*@return: Geen
*/
void calcWidth(unsigned char *header, signed int *breedte);


/*
*Berekend het totaal aantal pixels van de afbeelding.
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *pixels (Hier wordt het totaal aantal pixels in opgeslagen.)
*@return: Geen
*/
void calcPixels(signed int *hoogte, signed int *breedte, signed int *aantalPixels);


/*
*Leest de pixels van de bestaande afbeelding in en plaatst deze in een array.
*@param: FILE *inputBMP
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *aantalPixels
*@param: unsiged char *pixels
*@return: Geen
*/
void readImage(FILE *inputBMP, signed int *hoogte, signed int *breedte, signed int *aantalPixels, unsigned char *pixels);


/*
*Laat de gebruiker een filter kiezen.
*@param: int keuze (Hier in wordt de keuze van de gebruiker in opgeslagen en het bijbehorende programma uitgevoerd)
*@param: char confirmExit (Hierin wordt de bevestiging van de gebruiker opgeslagen)
*@param: unsigned char *pixels
*@param: unsigned char *filterPixels (hier worden de nieuwe pixels in opgeslagen)
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *aantalPixels
*@param: FILE *targetBMP
*@return: Geen
*/
void chooseFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP);


/*
*Filtert de afbeelding door het gemiddelde van de elke pixel en zijn omliggende pixels te berekenen
*@param: unsigned char *pixels
*@param: unsigned char *filterPixels
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *aantalPixels
*@param: FILE *targetBMP
*@param: unsigned char newPixel     (Hier in wordt de herberekende waarde van de pixel opgeslagen)
*@param: unsigned char targetPixel  (Hier in wordt de huidige waarde de geselecteerde pixel opgeslagen)
*@param: unsigned char tempPixelTL  (Waarde van de pixel links boven targetPixel)
*@param: unsigned char tempPixelT   (Waarde van de pixel boven targetPixel)
*@param: unsigned char tempPixelTR  (Waarde van de pixel rechts boven targetPixel)
*@param: unsigned char tempPixelL   (Waarde van de pixel links van targetPixel)
*@param: unsigned char tempPixelR   (Waarde van de pixel rechts van targetPixel)
*@param: unsigned char tempPixelBL  (Waarde van de pixel links onder targetPixel)
*@param: unsigned char tempPixelB   (Waarde van de pixel onder targetPixel)
*@param: unsigned char tempPixelBR  (Waarde van de pixel rechts onder targetPixel)
*@param: int counter    (De counter houdt bij op welke plaats in het array "filterPixels" de nieuwe pixel wordt weggeschreven)
*@param: int offset     (De offset zorgt er voor dat de header van de bmpfile niet wordt overschreven)
*@return: Geen
*/
void blurFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP);


/*
*Telt de waarde van elke kleur in elke pixel op en deelt deze door 3. Deze waarde wordt opgeslagen in de 3 kleurcomponenten per pixel. De afbeelding wordt zwartwit.
*@param: unsigned char *pixels
*@param: unsigned char *filterPixels
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *aantalPixels
*@param: FILE *targetBMP
*@param: unsigned char targetPixelB (blauwe kleurcomponent van targetpixel)
*@param: unsigned char targetPixelG (groene kleurcomponent van targetpixel)
*@param: unsigned char targetPixelR (rode kleurcomponent van targetpixel)
*@param: int blauw                  (offset voor de blauwe kleurcomponent)
*@param: int groen                  (offset voor de groene kleurcomponent)
*@param: int rood                   (offset voor de rode kleurcomponent)
*@param: int counter    (De counter houd bij op welke plaats in het array "filterPixels" de niewe pixel wordt weggeschreven)
*@param: int offset     (De offset zorgt er voor dat de header van de bmpfile neit wordt overschreven)
*@return: Geen
*/
void zwartWitFilter(unsigned char *pixels, unsigned char *filterPixels, signed int *hoogte, signed int *breedte, signed int *aantalPixels, FILE *targetBMP);


/*
*Maakt maakt het geheugen dat eerder gealloceerd is vrij en sluit de afbeeldingen.
*@param: unsigned char *header
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *aantalPixels
*@param: unsigned char *pixels
*@param: unsigned char *filterPixels
*@param: FILE *inputBMP
*@param: FILE *targetBMP
*@return: geen
*/
void cleanup(unsigned char *header, signed int *hoogte, signed int *breedte, signed int *aantalPixels, unsigned char *pixels, unsigned char *filterPixels, FILE *inputBMP, FILE *targetBMP);

#endif