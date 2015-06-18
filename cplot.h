/*################################################################################################################
# Original Name: "Dustin-Plot" changed to C_Plot																 #
# A Programm by Dustin Hebecker																					 #
# This rudimentary version of a plot library may be used for any private purposes as well as distributed for such#
# Only condition is that this header says the way it is.														 #
# For the unexpeted case you want to use this library commercially contact me on dustin.hebecker@gmail.com 		 #
# Have FUN ;) 																									 #
################################################################################################################*/


#ifndef _CPLOT_H_
#define _CPLOT_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bmp.h"
//#include "../matrix.h"

typedef struct{int width;int height; double* elemente;}MATRIX_;

int dplot(char*,double* , double*, int,char *,char *, char *,char *,char *, int ,struct pixel type_colour,struct pixel,struct pixel);
int dplot_waerme(char* dateiname,MATRIX_ waermebild,char *title_line,struct pixel bg_colour,struct pixel txt_colour);
int multi_dplot(char* dateiname,double** arrayy, double** arrayx, int* n,int m,char *title_line, char *x_text,char *x,char *y, int type,struct pixel* type_colour,struct pixel bg_colour,struct pixel txt_colour);



struct pixel* farblegende(MATRIX_ waermebild,struct pixel txt_colour,struct pixel bg_colour);
struct pixel* W_plotter(MATRIX_ waermebild);
struct pixel farbverlauf(double value,double max, double min);
struct pixel* multi_plotter(double **arrayy2,double **arrayx2,int *n2,int m,int linetype,struct pixel *linecolour2);
struct pixel* bottom_legend_multi(char *bottom_line,struct pixel colour,struct pixel bg_colour, struct pixel* punkte);
double find_max_multi(double **array,int *n,int m);
double find_min_multi(double **array,int *n,int m);
double element(MATRIX_ matrix,int i,int j);
double find_max_nonzero(double *array,int n);
double find_min_nonzero(double *array,int n);
struct pixel* xnumber_multi(double **,int*,int,struct pixel);
struct pixel* ynumber_multi(double **,int*,int,struct pixel);

struct pixel* plotter(double *,double *,int,int/*linetype*/,struct pixel);
struct pixel* titlewrite(char *,struct pixel,struct pixel);
struct pixel* sidewrite(char *,struct pixel,struct pixel);
struct pixel* bottomwrite(char *,struct pixel,struct pixel);
struct pixel* achsenwrite(char *,struct pixel,struct pixel);
struct pixel* xnumber(double *,int,struct pixel);
struct pixel* ynumber(double *,int,struct pixel);
struct pixel* achsewrite(char *,struct pixel,struct pixel);

void set_pixel(struct pixel *, int,struct pixel ,int,int, int, int);
void put_cross(struct pixel *,int, int, int, int, struct pixel);
void put_letters(struct pixel *, int ,struct pixel ,int *,int *, char);
void fillin(struct pixel *,int,int,struct pixel *,int,int,int,int);
void draw_line(int,int, int,int,struct pixel* box,int width,struct pixel linecolour,int linetype, int linesize);




double find_max(double*,int );
double find_min(double*,int );




#endif
