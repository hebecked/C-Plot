/*###############################################################################################################
# BMP-creator																									#
# A library by Dustin Hebecker																					#
# A testversion																									#
################################################################################################################*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bmp.h"



struct bmp_header createbmpheader(int height, int width){
	struct bmp_header header;

	//Dateikopf	
	header.BM=19778;
	header.Size=54+3*height*width;
	header.Reserved=0;
	header.OffBits=54;
	
	//Bild Eigenschaften
	header.Size2=40;
	header.Width=width;
	header.Height=height;
	header.Planes=1;
	header.BitCount=24; 
	header.Compression=0;
	header.SizeImmage=0;
	header.XPelsPerMeter=0;
	header.YPelsPerMeter=0;
	header.ClrUsed=0;
	header.ClrImportant=0;

	return header;
}

struct pixel* init_Bild(int height, int width, struct pixel Backgroundcolour){
	int i;
/*	int j=0;
	int k;
	struct pixel clear=0,0,0;*/
	struct pixel *Bild=NULL;
/*	for(j=0;width%4==0;j++){
		width++;
	}*/
	Bild=malloc(height*width*sizeof(struct pixel));
	if(Bild==NULL) return NULL;
	for(i=0;i<height*width;i++){
		Bild[i]=Backgroundcolour;
	}
/*	if(j!=0){
		for(i=0;i<height;i++){
			for(k=0;k<j;k++){
				struct bild[i*width-k]=struct clear;
			}
		}
	}*/
	return Bild;
}

int create_bmp_old(struct pixel* Bild, int width, int height, char* dateiname){
	FILE* datei=NULL;
	struct bmp_header header=createbmpheader(height,width);
	datei=fopen(dateiname,"wb");
	if(datei==NULL) return -1;
	fwrite(&header,54,1,datei);
	fwrite(Bild,sizeof(struct pixel),width*height ,datei);
	return 0;
}


int create_bmp(struct pixel* Bild, int width, int height, char* dateiname){
	FILE* datei=NULL;
	struct bmp_header header=createbmpheader(height,width);
	datei=fopen(dateiname,"wb");
	if(datei==NULL) return -1;

	fwrite(&header.BM,2,1,datei);
	fwrite(&header.Size,4,1,datei);
	fwrite(&header.Reserved,4,1,datei);
	fwrite(&header.OffBits,4,1,datei);

	fwrite(&header.Size2,4,1,datei);
	fwrite(&header.Width,4,1,datei);
	fwrite(&header.Height,4,1,datei);
	fwrite(&header.Planes,2,1,datei);
	fwrite(&header.BitCount,2,1,datei);
	fwrite(&header.Compression,4,1,datei);
	fwrite(&header.SizeImmage,4,1,datei);
	fwrite(&header.XPelsPerMeter,4,1,datei);
	fwrite(&header.YPelsPerMeter,4,1,datei);
	fwrite(&header.ClrUsed,4,1,datei);
	fwrite(&header.ClrImportant,4,1,datei);

	fwrite(Bild,sizeof(struct pixel),width*height ,datei);
	return 0;
}



