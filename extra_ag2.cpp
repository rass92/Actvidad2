//extra_ag.cpp
/*
 Coleccion de funciones extras utiles en la implementacion de algoritmos geneticos con 'clase_ag'
 - Codificar y Decodificar 8/16 bits Binario <-> float
 - Codificar y Decodificar Gray <-> Binario
*/

#ifndef __EXTRA_AG2_H
#define __EXTRA_AG2_H

#include <stdio.h>
#include <stdlib.h>

//funcion que convierte de binario a gray (1 byte)
unsigned char exBinarioGray(unsigned char);
//funcion que convierte de gray a binario (1 byte)
unsigned char exGrayBinario(unsigned char);

//funcion que recibe dos bytes (16 bits) y lo decodifica a float (binario-lineal)
float crDecodificar16(unsigned char *ap, float min, float max);
//funcion que recibe un byte (8 bits) y lo decodifica a float (binario-lineal)
float crDecodificar8(unsigned char ap, float min, float max);

//************************************************
//funcion que convierte de binario a gray (1 byte)
unsigned char exBinarioGray(unsigned char bin)
{
        return bin^(bin>>1); //BIN XOR (BIN>>1)
}

//************************************************
//funcion que convierte de gray a binario (1 byte)
unsigned char exGrayBinario(unsigned char gray)
{
    unsigned char bin=gray^(gray>>1);
    for(register int k=2;k<8;k++) bin=bin^(gray>>k);
    return bin;
}

//****************************************************************
//devuelve el valor asociado a un segmento de cromosoma de 16 bits
float crDecodificar16(unsigned char *ap, float min, float max)
{
	float a;
   unsigned short int b;
   b = *(unsigned short int*) ap;
   a = (b*(max-min)/65536)+min;
   return a;
}

//****************************************************************
//devuelve el valor asociado a un segmento de cromosoma de 16 bits
float crDecodificar8(unsigned char ap, float min, float max)
{
	float a, b;
   b = (float)ap;
   a = (b*(max-min)/256)+min;
   return a;
}

//****************************************************************
//Función que recibe un string de caracteres, y devuelve el bit 'i' de dicho string
bool leerBit (char *string, unsigned int i)
{
	//determino en cual byte se encuentra el bit 'i' dividiendo (entero) entre 8 (es lo mismo que desplazar a la derecha 3 veces)
	int nbyte = (int) i / 8;
	//determino en bit 'i' calculando el residuo con 8
	int nbit = i % 8;
	char c = string[nbyte];
	char mask = 0x01;
	mask = mask << nbit;
	//obtengo y devuelvo el de ese bit haciendo AND & con la máscara
	bool bit = c & mask;
	return (bit);
}

//****************************************************************
//Función que permite leer los datos de un archivo separado por tabuladores.
// Cada fila es una nueva entrada de datos, y cada columna es una variable nueva
// Ejemplo:
//	X0	Y0
//	X1	Y1
//	X2	Y2
//	......
//	XN	YN
bool importTabFile (FILE *apArchivo, int *x, int casillas)
{
	//chequeo si el apuntador al archivo provisto es nulo. salgo
	if (apArchivo==NULL)	return false;
	// si el numero de datos solicitados es menor o igual a cero, salgo.
	if (casillas <=0) return false;

	int fx[20];
	for (int i=0; i<casillas; i++)
	{
		fscanf(apArchivo,"%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f", &fx[0], &fy[1], &fx[2], &fx[3], &fx[4], &fx[5], &fx[6], &fx[7], &fx[8], &fx[9], &fx[10], &fx[11], &fx[12], &fx[13], &fx[14], &fx[15], &fx[16], &fx[17], &fx[18], &fx[19]);	//leo una fila, dos datos de una vez
		for (int j=0; j<casillas; j++)
		{
		x[i][j]=fx[j];
		}
		
	}
	return true;
}

#endif
