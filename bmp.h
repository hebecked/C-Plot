/*###############################################################################################################
# BMP-creator																									#
# A library by Dustin Hebecker																					#
# A testversion																									#
################################################################################################################*/


#ifndef _BMP_H_
#define _BMP_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

struct bmp_header{
	//Dateikopf	
	short BM; //Dateityp 19778='BM'
	int Size; //Größe der Datei in byte
	unsigned int Reserved; //=0
	int OffBits; //Offset der bilddateien von begin der datei an
	
	//Bild Eigenschaften
	int Size2; //Größe der "Bildeigenscahften" (40 byte)
	int Width; //Breite des Bildes in Pixel
	int Height; //Höhe des Bildes in Pixel (+ => unten nach oben, - => oben nach unten)
	short Planes; //=1 (anzahl der Farbebenen in BMP immer 1)
	short BitCount; //Farbtiefe (24 empfohlen 8 byte pro farbe) 
	int Compression; //Kompremierung (=0)
	int SizeImmage; //0 oder größe der Bilddateien in Byte
	int XPelsPerMeter; //Horrizontale auflösung (pixel/meter) kann auf 0 gesetzt werden
	int YPelsPerMeter; //Vertikale auflösung (pixel/meter) kann auf 0 gesetzt werden
	int ClrUsed; //Anzahl der einträge in Farbtabelle (0°=2^BitCount) bzw. 0=max.-Anzahl
	int ClrImportant; //Anzahl der der im Bild verwendeten farben (=0 <=alle)
};

struct pixel{
	unsigned char B; //Blau
	unsigned char G; //Grün
	unsigned char R; //Rot
};


struct bmp_header createbmpheader(int height, int width);
struct pixel* init_Bild(int height, int width, struct pixel Backgroundcolour);
int create_bmp(struct pixel* Bild, int width, int height, char* dateiname);

#endif

