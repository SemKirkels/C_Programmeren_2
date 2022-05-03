#ifndef Functies_H
#define Functies_H

/*
*Uitleg
*@param:
*@return:
*/
void startScherm();

/*
*Uitleg
*@param:
*@return:
*/
FILE *openBMP();

/*
*Uitleg
*@param:
*@return:
*/
void readHeader(FILE *inputBMP, unsigned char *header);

/*
*Uitleg
*@param:
*@return:
*/
void calcHeight(unsigned char *header, signed int *hoogte);

/*
*Uitleg
*@param:
*@return:
*/
void calcWidth(unsigned char *header, signed int *breedte);

/*
*Uitleg
*@param:
*@return:
*/
void calcPixels(signed int *hoogte, signed int *breedte, signed int *pixels);

#endif