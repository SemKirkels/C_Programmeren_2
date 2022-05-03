#ifndef Functies_H
#define Functies_H

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
unsigned char readHeader(FILE *inputBMP);

/*
*Uitleg
*@param:
*@return:
*/
int calcHeight(unsigned char header[54]);

/*
*Uitleg
*@param:
*@return:
*/
int calcWidth(unsigned char header[54]);

#endif