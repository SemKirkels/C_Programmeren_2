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
*@param: Geen
*@return: FILE *inputBMP
*/
FILE *openBMP();


/*
*Leest de eerste 54 bytes in van de BMP afbeelding.
*@param: FILE *inputBMP 
*@param: unsigned char *header (In de header worden de eerste 54 bytes van de afbeelding opgeslagen.)
*@return: Geen
*/
void readHeader(FILE *inputBMP, unsigned char *header);


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
void calcPixels(signed int *hoogte, signed int *breedte, signed int *pixels);


/*
*Uitleg
*@param:
*@return
*/
void readImage(FILE *inputBMP, signed int *hoogte, signed int *breedte, signed int *pixels);


/*
*Maakt maakt het geheugen dat eerder gealloceerd is vrij.
*@param: unsigned char *header
*@param: signed int *hoogte
*@param: signed int *breedte
*@param: signed int *pixels
*@return: geen
*/
void cleanup(unsigned char *header, signed int *hoogte, signed int *breedte, signed int *pixels);

#endif