/*################################################################################################################
# Original Name: "Dustin-Plot" changed to C-Plot																 #
# A Programm by Dustin Hebecker																					 #
# This rudimentary version of a plot library may be used for any private purposes as well as distributed for such#
# Only condition is that this header says the way it is.														 #
# For the unexpeted case you want to use this library commercially contact me on dustin.hebecker@gmail.com 		 #
# Have FUN ;) 																									 #
################################################################################################################*/

/*

noch zu ergänzen sind:
if(empy x-y range) print text in plot
wasserzeichen
fit
mehrere plots auf einmal/versch-farben (übergebe pointer auf arrays) und array mit anzahl und anzahl der arrays)
bilder einfügen(einlesen)
sortierung für "with lines"
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bmp.h"
#include "cplot.h"
//#include "./matrix.h"


int dplot(char* dateiname,double* arrayy, double* arrayx, int n,char *title_line,char *y_text, char *x_text,char *x,char *y, int type/* 0=cross,1=lines,2=bottomlines,3=Linear-fit, 4=pixel, 5=lines&crosses*/,struct pixel type_colour,struct pixel bg_colour,struct pixel txt_colour){

	int height=768;
	int width=1024;
	struct pixel *title=NULL;
	struct pixel *side=NULL;
	struct pixel *bottom=NULL;
	struct pixel *x_achse=NULL;
	struct pixel *y_achse=NULL;
	struct pixel *x_numbers=NULL;
	struct pixel *y_numbers=NULL;
	struct pixel *plot=NULL;

	struct pixel *the_great_picture=init_Bild(height,width,bg_colour);

	title=titlewrite(title_line, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,title,60,500,300,698);
	side=sidewrite(y_text, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,side,500,60,10,168);
	bottom=bottomwrite(x_text, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,bottom,60,700,180,38);
	
	x_achse=achsewrite(x, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,x_achse,60,90,915,128);
	y_achse=achsewrite(y, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,y_achse,60,90,190,660);




	x_numbers=xnumber(arrayx,n,bg_colour);
	fillin(the_great_picture,height,width,x_numbers,50,700,206,118);
	y_numbers=ynumber(arrayy,n,bg_colour);
	fillin(the_great_picture,height,width,y_numbers,500,116,90,168);


	plot=plotter(arrayy,arrayx,n,type,type_colour);
	fillin(the_great_picture,height,width,plot,500,700,206,168);


	create_bmp(the_great_picture,width,height, dateiname);

	free(title);
	free(side);
	free(bottom);
	free(x_achse);
	free(y_achse);
	free(x_numbers);
	free(y_numbers);
	free(plot);
	free(the_great_picture);

	return 0;
}


int multi_dplot(char* dateiname,double** arrayy, double** arrayx, int* n,int m,char *title_line, char *x_text,char *x,char *y, int type,struct pixel* type_colour,struct pixel bg_colour,struct pixel txt_colour){
//0=cross,1=lines,2=bottomlines,3=Linear-fit, 4=pixel, 5=lines&crosses
	int height=768;
	int width=1024;
	struct pixel *title=NULL;
	struct pixel *bottom=NULL;
	struct pixel *x_achse=NULL;
	struct pixel *y_achse=NULL;
	struct pixel *x_numbers=NULL;
	struct pixel *y_numbers=NULL;
	struct pixel *plot=NULL;

	struct pixel *the_great_picture=init_Bild(height,width,bg_colour);

	title=titlewrite(title_line, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,title,60,500,300,698);
	bottom=bottom_legend_multi(x_text, txt_colour,bg_colour,type_colour);
	fillin(the_great_picture,height,width,bottom,60,700,180,38);

	x_achse=achsewrite(x, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,x_achse,60,90,915,128);
	y_achse=achsewrite(y, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,y_achse,60,90,190,660);




	x_numbers=xnumber_multi(arrayx,n,m,bg_colour);
	fillin(the_great_picture,height,width,x_numbers,50,700,206,118);
	y_numbers=ynumber_multi(arrayy,n,m,bg_colour);
	fillin(the_great_picture,height,width,y_numbers,500,116,90,168);

	plot=multi_plotter(arrayy,arrayx,n,m,type,type_colour);
	fillin(the_great_picture,height,width,plot,500,700,206,168);

	create_bmp(the_great_picture,width,height, dateiname);

	free(title);
	free(bottom);
	free(x_achse);
	free(y_achse);
	free(x_numbers);
	free(y_numbers);
	free(plot);
	free(the_great_picture);

	return 0;
}


int dplot_waerme(char* dateiname,MATRIX_ waermebild,char *title_line,struct pixel bg_colour,struct pixel txt_colour){

	int height=768;
	int width=1024;
	struct pixel *title=NULL;
	struct pixel *legende=NULL;
	struct pixel *plot=NULL;

	struct pixel *the_great_picture=init_Bild(height,width,bg_colour);


	title=titlewrite(title_line, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,title,60,500,300,698);
	legende=farblegende(waermebild, txt_colour,bg_colour);
	fillin(the_great_picture,height,width,legende,648,160,844,20);

	plot=W_plotter(waermebild);
	fillin(the_great_picture,height,width,plot,648,800,20,20);


	create_bmp(the_great_picture,width,height, dateiname);

	free(title);
	free(legende);
	free(plot);
	free(the_great_picture);

	return 0;
}

void fillin(struct pixel *master,int height_m,int width_m,struct pixel *minor,int height_s,int width_s,int posx,int posy){
	int i;
	int j;
	for(i=0;i<height_s;i++){
		for(j=0;j<width_s;j++){
			set_pixel(master,width_m ,minor[width_s*i+j],posx,posy,j,i);
			/*master[(width_m)*posx*i+j+posy]=minor[width_s*i+j];*/
		}
	}
	return;
}

struct pixel* bottom_legend_multi(char *bottom_line,struct pixel colour,struct pixel bg_colour, struct pixel* punkte){
	int i;
	int j=0;
	int height=60;
	int width=700;
	struct pixel *bottom=NULL;
/*	struct pixel white={255,255,255};*/
	int current_x=0;
	int current_y=40;
	int line=0;
	bottom=malloc(height*width*sizeof(struct pixel));
	if(bottom==NULL) return NULL;
	for(i=0;i<height*width;i++){
		bottom[i]=bg_colour;
	}
	for(i=0;width-current_x>16 || line<(int)(height/16);i++){
		if(bottom_line[i]=='\0')break;
		if(width-current_x<16 || bottom_line[i]=='\n'){ current_x=0; line++; current_y-=16;}
		if(bottom_line[i]=='@'){
			put_cross(bottom,height,width,current_y+6,current_x,punkte[j]);
			j++;
		}
		if(bottom_line[i]!='\n')put_letters(bottom,width ,colour,&current_x,&current_y, bottom_line[i]);
	}

	return bottom;
}

struct pixel* farblegende(MATRIX_ waermebild,struct pixel txt_colour,struct pixel bg_colour){
	double max=find_max_nonzero(waermebild.elemente,waermebild.height*waermebild.width);
	double min=find_min_nonzero(waermebild.elemente,waermebild.height*waermebild.width);
	int i;
	int j;
	int current_x;
	int current_y;
	int width=160;
	int height=648;
	int bc=40;
	char buffer[20];
	char num[50];
	struct pixel black={0,0,0};
	struct pixel* box=NULL;
	struct pixel colour={0,0,0};
	box=malloc(width*height*sizeof(struct pixel));
	if(box==NULL)return NULL;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			box[i*width+j]=bg_colour;
			if((i==0 && j< bc) || (i==height-1 && j< bc) || j==0 || j==bc){
				box[i*width+j]=black;
			}
		}
	}
	for(i=1;i<height-1;i++){
		colour=farbverlauf((double)i,(double)height-2,0);
		for(j=1;j<bc;j++){
			box[i*width+j]=colour;
		}
	}
	for(i=bc;i<bc+8;i++){
		box[i]=black;
		box[width+i]=black;
		box[width*(height-1)+i]=black;
		box[width*(height-2)+i]=black;
		box[width*(height/2)+i]=black;
		box[width*(height/2-1)+i]=black;
		box[width*(height/4-1)+i]=black;
		box[width*(height/4)+i]=black;
		box[width*(height*3/4-1)+i]=black;
		box[width*(height*3/4)+i]=black;
	}
	
	for(i=0;i<5;i++){
		if(i==0)sprintf(buffer,"%e",min);
		if(i==1)sprintf(buffer,"%e",(min+(min+max)/2)/2);
		if(i==2)sprintf(buffer,"%e",(min+max)/2);
		if(i==3)sprintf(buffer,"%e",(max+(min+max)/2)/2);
		if(i==4)sprintf(buffer,"%e",max);	
		num[0+i*8]=buffer[0];
		num[1+i*8]=buffer[1];
		num[2+i*8]=buffer[2];
		num[3+i*8]=buffer[3];
		num[4+i*8]=buffer[8];
		num[5+i*8]=buffer[9];
		num[6+i*8]=buffer[10];
		num[7+i*8]=buffer[11];
	}


	current_x=bc+12;
	current_y=5;
	for(i=0;i<40;i++){
		if(i==8){current_x=bc+12;current_y=156;}
		if(i==16){current_x=bc+12;current_y=318;}
		if(i==24){current_x=bc+12;current_y=481;}
		if(i==32){current_x=bc+12;current_y=633;}
		put_letters(box,width, txt_colour,&current_x,&current_y, num[i]);
	}
	return box;
}

struct pixel farbverlauf(double value,double max, double min){
	int i;
	int colours=510;
	struct pixel colour={0,0,0};
	i=(colours/(1.0*(max-min)))*(value-min);
		if(i<256){
			colour.B=255-i;
			colour.G=i;
		}
		else {
			colour.G=255-i;
			colour.R=i+1;
		}
	return colour;
}

struct pixel* W_plotter(MATRIX_ waermebild){
	double max=find_max_nonzero(waermebild.elemente,waermebild.height*waermebild.width);
	double min=find_min_nonzero(waermebild.elemente,waermebild.height*waermebild.width);
	struct pixel colour;
	int i;
	int j;
	int x;
	int y;
	int width=800;
	int height=650;
	double x_pixel=width/(1.0*waermebild.width);
	double y_pixel=height/(1.0*waermebild.height);
	struct pixel black={0,0,0};
	struct pixel white={255,255,255};
	struct pixel* box=NULL;
	box=malloc(width*height*sizeof(struct pixel));

	if(box==NULL)return NULL;
	
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			box[i*width+j]=white;
			if(i==0 || i==height-1 || j==0 || j==width-1){
				box[i*width+j]=black;
			}
		}
	}
	for(x=0;x<waermebild.width;x++){
		for(y=0;y<waermebild.height;y++){
			if(element(waermebild,y,x)!=0){
				colour=farbverlauf(element(waermebild,y,x),max,min);
			}
			else{
				colour=black;
			}
			for(i=height-y_pixel*(y+1);i<height-y_pixel*y;i++){
				for(j=x_pixel*(x);j<x_pixel*(x+1);j++){
					box[i*width+j]=colour;
				}
			}

		}
	}

	return box;
}

struct pixel* titlewrite(char *title_line,struct pixel colour,struct pixel bg_colour){
	int i;
	int height=60;
	int width=500;
	struct pixel *title=NULL;
	/*struct pixel white={255,255,255};*/
	int current_x=0;
	int current_y=34;
	int line=0;
	title=malloc(height*width*sizeof(struct pixel));
	if(title==NULL) return NULL;
	for(i=0;i<height*width;i++){
		title[i]=bg_colour;
	}
	for(i=0;width-current_x>16 || line<(int)(height/16);i++){
		if(title_line[i]=='\0')break;
		if(width-current_x<16 || title_line[i]=='\n'){ current_x=0; line++; current_y-=16;}
		if(title_line[i]!='\n')put_letters(title,width ,colour,&current_x,&current_y, title_line[i]);
	}

	return title;
}

struct pixel* sidewrite(char *side_line,struct pixel colour,struct pixel bg_colour){
	int i;
	int j;
	int height=60;
	int width=500;
	struct pixel *side=NULL;
	struct pixel *realside=NULL;
/*	struct pixel white={255,255,255};*/
	int current_x=0;
	int current_y=34;
	int line=0;
	side=malloc(height*width*sizeof(struct pixel));
	if(side==NULL) return NULL;
	for(i=0;i<height*width;i++){
		side[i]=bg_colour;
	}
	for(i=0;width-current_x>16 || line<(int)(height/16);i++){
		if(side_line[i]=='\0')break;
		if(width-current_x<16 || side_line[i]=='\n'){ current_x=0; line++; current_y-=16;}
		if(side_line[i]!='\n')put_letters(side,width ,colour,&current_x,&current_y, side_line[i]);
	}

	realside=malloc(height*width*sizeof(struct pixel));
	if(realside==NULL) return NULL;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			realside[height*j-i+(height-1)]=side[width*i+j]; 
		}
	}	
	free(side);
	return realside;
}



struct pixel* bottomwrite(char *bottom_line,struct pixel colour,struct pixel bg_colour){
	int i;
	int height=60;
	int width=700;
	struct pixel *bottom=NULL;
/*	struct pixel white={255,255,255};*/
	int current_x=0;
	int current_y=34;
	int line=0;
	bottom=malloc(height*width*sizeof(struct pixel));
	if(bottom==NULL) return NULL;
	for(i=0;i<height*width;i++){
		bottom[i]=bg_colour;
	}
	for(i=0;width-current_x>16 || line<(int)(height/16);i++){
		if(bottom_line[i]=='\0')break;
		if(width-current_x<16 || bottom_line[i]=='\n'){ current_x=0; line++; current_y-=16;}
		if(bottom_line[i]!='\n')put_letters(bottom,width ,colour,&current_x,&current_y, bottom_line[i]);
	}

	return bottom;
}
	

struct pixel* achsewrite(char *achse_line,struct pixel colour,struct pixel bg_colour){
	int i;
	int height=60;
	int width=90;
	struct pixel *achse=NULL;
/*	struct pixel white={255,255,255};*/
	int current_x=0;
	int current_y=44;
	int line=0;
	achse=malloc(height*width*sizeof(struct pixel));
	if(achse==NULL) return NULL;
	for(i=0;i<height*width;i++){
		achse[i]=bg_colour;
	}
	for(i=0;width-current_x>16 || line<(int)(height/16);i++){
		if(achse_line[i]=='\0')break;
		if(width-current_x<16 || achse_line[i]=='\n'){ current_x=0; line++; current_y-=16;}
		if(achse_line[i]!='\n')put_letters(achse,width ,colour,&current_x,&current_y, achse_line[i]);
	}
	return achse;
}


struct pixel *xnumber(double *arrayx,int n,struct pixel bg_colour){
	int i;
	struct pixel* x_numbers=NULL;
	int width=700;
	int height=50;
	char num[40];
	int current_x;
	int current_y;
	double max=find_max(arrayx,n);
	double min=find_min(arrayx,n);
	char buffer[30];
/*	struct pixel white={255,255,255};*/
	struct pixel black={0,0,0};
	struct pixel colour=black;
	x_numbers=malloc(width*height*sizeof(struct pixel));
	if(x_numbers==NULL) return NULL;
	for(i=0;i<height*width;i++){
		x_numbers[i]=bg_colour;
	}
	for(i=height-9;i<height;i++){
		x_numbers[width*i]=black;
		x_numbers[width*i+width-1]=black;
		x_numbers[width*i+1]=black;
		x_numbers[width*i+width-2]=black;
		x_numbers[width*i+width/2]=black;
		x_numbers[width*i+1+width/2]=black;
		x_numbers[width*i+width*3/4]=black;
		x_numbers[width*i+1+(width+width/2)/2]=black;
		x_numbers[width*i+width/4]=black;
		x_numbers[width*i+1+width/4]=black;
	}

	for(i=0;i<5;i++){
		if(i==0)sprintf(buffer,"%e",min);
		if(i==1)sprintf(buffer,"%e",(min+(min+max)/2)/2);
		if(i==2)sprintf(buffer,"%e",(min+max)/2);
		if(i==3)sprintf(buffer,"%e",(max+(min+max)/2)/2);
		if(i==4)sprintf(buffer,"%e",max);	
		num[0+i*9]=buffer[0];
		num[1+i*9]=buffer[1];
		num[2+i*9]=buffer[2];
		num[3+i*9]=buffer[3];
		num[4+i*9]=buffer[8];
		num[5+i*9]=buffer[9];
		num[6+i*9]=buffer[10];
		num[7+i*9]=buffer[11];
		num[8+i*9]=buffer[12];
	}



	current_x=0;
	current_y=24;
	for(i=0;i<45;i++){
		if(i==9)current_x=140;
		if(i==18)current_x=316;
		if(i==27)current_x=480;
		if(i==36)current_x=608;
		put_letters(x_numbers,width ,colour,&current_x,&current_y, num[i]);
	}


	return x_numbers;
}
struct pixel *ynumber(double *arrayy,int n,struct pixel bg_colour){
	int i;
	struct pixel* y_numbers=NULL;
	int width=116;
	int height=500;
	char num[45];
	int current_x;
	int current_y;
	double max=find_max(arrayy,n);
	double min=find_min(arrayy,n);
	char buffer[30];
/*	struct pixel white={255,255,255};*/
	struct pixel black={0,0,0};
	struct pixel colour=black;
	y_numbers=malloc(width*height*sizeof(struct pixel));
	if(y_numbers==NULL) return NULL;
	for(i=0;i<height*width;i++){
		y_numbers[i]=bg_colour;
	}
	for(i=width-9;i<width;i++){
		y_numbers[i]=black;
		y_numbers[width+i]=black;
		y_numbers[width*(height-1)+i]=black;
		y_numbers[width*(height-2)+i]=black;
		y_numbers[width*(height/2)+i]=black;
		y_numbers[width*(height/2-1)+i]=black;
		y_numbers[width*(height/4-1)+i]=black;
		y_numbers[width*(height/4)+i]=black;
		y_numbers[width*(height*3/4-1)+i]=black;
		y_numbers[width*(height*3/4)+i]=black;
	}
	
	for(i=0;i<5;i++){
		if(i==0)sprintf(buffer,"%e",min);
		if(i==1)sprintf(buffer,"%e",(min+(min+max)/2)/2);
		if(i==2)sprintf(buffer,"%e",(min+max)/2);
		if(i==3)sprintf(buffer,"%e",(max+(min+max)/2)/2);
		if(i==4)sprintf(buffer,"%e",max);	
		num[0+i*9]=buffer[0];
		num[1+i*9]=buffer[1];
		num[2+i*9]=buffer[2];
		num[3+i*9]=buffer[3];
		num[4+i*9]=buffer[8];
		num[5+i*9]=buffer[9];
		num[6+i*9]=buffer[10];
		num[7+i*9]=buffer[11];
	if(buffer[0]=='-')num[8+i*9]=buffer[12];
	else num[8+i*9]=' ';
	}


	current_x=0;
	current_y=10;
	for(i=0;i<45;i++){
		if(i==9){current_x=0;current_y=125;}
		if(i==18){current_x=0;current_y=250;}
		if(i==27){current_x=0;current_y=375;}
		if(i==36){current_x=0;current_y=475;}
		put_letters(y_numbers,width ,colour,&current_x,&current_y, num[i]);
	}
	return y_numbers;
}

struct pixel *xnumber_multi(double **arrayx,int *n,int m,struct pixel bg_colour){
	int i;
	struct pixel* x_numbers=NULL;
	int width=700;
	int height=50;
	char num[40];
	int current_x;
	int current_y;
	double max=find_max_multi(arrayx,n,m);
	double min=find_min_multi(arrayx,n,m);
	char buffer[30];
/*	struct pixel white={255,255,255};*/
	struct pixel black={0,0,0};
	struct pixel colour=black;
	x_numbers=malloc(width*height*sizeof(struct pixel));
	if(x_numbers==NULL) return NULL;
	for(i=0;i<height*width;i++){
		x_numbers[i]=bg_colour;
	}
	for(i=height-9;i<height;i++){
		x_numbers[width*i]=black;
		x_numbers[width*i+width-1]=black;
		x_numbers[width*i+1]=black;
		x_numbers[width*i+width-2]=black;
		x_numbers[width*i+width/2]=black;
		x_numbers[width*i+1+width/2]=black;
		x_numbers[width*i+width*3/4]=black;
		x_numbers[width*i+1+(width+width/2)/2]=black;
		x_numbers[width*i+width/4]=black;
		x_numbers[width*i+1+width/4]=black;
	}

	for(i=0;i<5;i++){
		if(i==0)sprintf(buffer,"%e",min);
		if(i==1)sprintf(buffer,"%e",(min+(min+max)/2)/2);
		if(i==2)sprintf(buffer,"%e",(min+max)/2);
		if(i==3)sprintf(buffer,"%e",(max+(min+max)/2)/2);
		if(i==4)sprintf(buffer,"%e",max);	
		num[0+i*9]=buffer[0];
		num[1+i*9]=buffer[1];
		num[2+i*9]=buffer[2];
		num[3+i*9]=buffer[3];
		num[4+i*9]=buffer[8];
		num[5+i*9]=buffer[9];
		num[6+i*9]=buffer[10];
		num[7+i*9]=buffer[11];
		num[8+i*9]=buffer[12];
	}



	current_x=0;
	current_y=24;
	for(i=0;i<45;i++){
		if(i==9)current_x=140;
		if(i==18)current_x=316;
		if(i==27)current_x=480;
		if(i==36)current_x=608;
		put_letters(x_numbers,width ,colour,&current_x,&current_y, num[i]);
	}


	return x_numbers;
}
struct pixel *ynumber_multi(double **arrayy,int* n,int m,struct pixel bg_colour){
	int i;
	struct pixel* y_numbers=NULL;
	int width=116;
	int height=500;
	char num[45];
	int current_x;
	int current_y;
	double max=find_max_multi(arrayy,n,m);
	double min=find_min_multi(arrayy,n,m);
	char buffer[30];
/*	struct pixel white={255,255,255};*/
	struct pixel black={0,0,0};
	struct pixel colour=black;
	y_numbers=malloc(width*height*sizeof(struct pixel));
	if(y_numbers==NULL) return NULL;
	for(i=0;i<height*width;i++){
		y_numbers[i]=bg_colour;
	}
	for(i=width-9;i<width;i++){
		y_numbers[i]=black;
		y_numbers[width+i]=black;
		y_numbers[width*(height-1)+i]=black;
		y_numbers[width*(height-2)+i]=black;
		y_numbers[width*(height/2)+i]=black;
		y_numbers[width*(height/2-1)+i]=black;
		y_numbers[width*(height/4-1)+i]=black;
		y_numbers[width*(height/4)+i]=black;
		y_numbers[width*(height*3/4-1)+i]=black;
		y_numbers[width*(height*3/4)+i]=black;
	}
	
	for(i=0;i<5;i++){
		if(i==0)sprintf(buffer,"%e",min);
		if(i==1)sprintf(buffer,"%e",(min+(min+max)/2)/2);
		if(i==2)sprintf(buffer,"%e",(min+max)/2);
		if(i==3)sprintf(buffer,"%e",(max+(min+max)/2)/2);
		if(i==4)sprintf(buffer,"%e",max);	
		num[0+i*9]=buffer[0];
		num[1+i*9]=buffer[1];
		num[2+i*9]=buffer[2];
		num[3+i*9]=buffer[3];
		num[4+i*9]=buffer[8];
		num[5+i*9]=buffer[9];
		num[6+i*9]=buffer[10];
		num[7+i*9]=buffer[11];
	if(buffer[0]=='-')num[8+i*9]=buffer[12];
	else num[8+i*9]=' ';
	}


	current_x=0;
	current_y=10;
	for(i=0;i<45;i++){
		if(i==9){current_x=0;current_y=125;}
		if(i==18){current_x=0;current_y=250;}
		if(i==27){current_x=0;current_y=375;}
		if(i==36){current_x=0;current_y=475;}
		put_letters(y_numbers,width ,colour,&current_x,&current_y, num[i]);
	}
	return y_numbers;
}

struct pixel* plotter(double *arrayy,double *arrayx,int n,int linetype/*linetype*/,struct pixel linecolour){
	double x_max=find_max(arrayx,n);
	double x_min=find_min(arrayx,n);
	double y_max=find_max(arrayy,n);
	double y_min=find_min(arrayy,n);
	struct pixel colour2={0,0,255};
	int *x;
	int *y;
	int i;
	int j;
	int x_value;
	int y_value;
	int width=700;
	int height=500;
	struct pixel black={0,0,0};
	struct pixel white={255,255,255};
	struct pixel* box=NULL;
	box=malloc(width*height*sizeof(struct pixel));
	if(box==NULL)return NULL;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			box[i*width+j]=white;
			if(i==0 || i==height-1 || j==0 || j==width-1){
				box[i*width+j]=black;
			}
		}
	}

	switch(linetype){
		case 0:{/*crosses*/
			for(i=0;i<n;i++){
				x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
				y_value=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
				put_cross(box,height,width,y_value,x_value,linecolour);
			}
		}break;
		case 1:{/*lines*/
			x=malloc(n*sizeof(int));
			y=malloc(n*sizeof(int));
			for(i=0;i<n;i++){
				x[i]=((width-10)/(1.0*(x_max-x_min)))*1.0*(arrayx[i]-x_min)+5;
				y[i]=((height-10)/(1.0*(y_max-y_min)))*1.0*(arrayy[i]-y_min)+5;
			}
			for(i=0;i<n-1;i++){
				draw_line(x[i],y[i],x[i+1],y[i+1],box,width,linecolour,0,0);
			}
			free(x);
			free(y);

		}break;
		case 2:{/*bottomlines*/
			for(i=0;i<n;i++){
				x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
				y_value=((height-10)/(1.0*(y_max-y_min)))*(arrayy[i]-y_min)+5;
				for(j=0;j>(-y_value);j--){
					set_pixel(box,width ,linecolour,x_value,y_value, 0, j);
				}			
			}
		}break;
		case 3:{/*linear fit*/
/*steigung m
	startpunk b

*/

		}break;
		case 4:{/*points*/
			for(i=0;i<n;i++){
				x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
				y_value=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
				set_pixel(box,width ,linecolour,x_value,y_value, 0, 0);
			}
		}break;
		case 5:{/*lines & crosses*/
			x=malloc(n*sizeof(int));
			y=malloc(n*sizeof(int));
			for(i=0;i<n;i++){
				x[i]=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
				y[i]=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
			}
			for(i=0;i<n-1;i++){
				draw_line(x[i],y[i],x[i+1],y[i+1],box,width,linecolour,0,0);
			}
			for(i=0;i<n;i++){
				put_cross(box,height,width,y[i],x[i],colour2);
			}
			free(x);
			free(y);
		}break;
		case 6:{
			for(i=0;i<n;i++){
				x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
				y_value=((height-10)/(1.0*(y_max-y_min)))*(arrayy[i]-y_min)+5;
				for(j=0;j>(-y_value);j--){
					set_pixel(box,width ,linecolour,x_value,y_value, 0, j);
				}			
			}
			x=malloc(n*sizeof(int));
			y=malloc(n*sizeof(int));
			for(i=0;i<n;i++){
				x[i]=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
				y[i]=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
			}
			for(i=0;i<n-1;i++){
				draw_line(x[i],y[i],x[i+1],y[i+1],box,width,linecolour,0,0);
			}
			free(x);
			free(y);
		}

	}
	/*create_bmp(box,width,height, "plot_test.bmp");*/
	return box;
}

struct pixel* multi_plotter(double **arrayy2,double **arrayx2,int *n2,int m,int linetype,struct pixel *linecolour2){
	double x_max=find_max_multi(arrayx2,n2,m);
	double x_min=find_min_multi(arrayx2,n2,m);
	double y_max=find_max_multi(arrayy2,n2,m);
	double y_min=find_min_multi(arrayy2,n2,m);
	struct pixel colour2={0,0,255};
	int *x;
	int *y;
	int i;
	int j;
	int k;
	int n;
	int x_value;
	int y_value;
	int width=700;
	int height=500;
	double* arrayy;
	double *arrayx;
	struct pixel black={0,0,0};
	struct pixel white={255,255,255};
	struct pixel* box=NULL;
	struct pixel linecolour;
	box=malloc(width*height*sizeof(struct pixel));
	if(box==NULL)return NULL;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			box[i*width+j]=white;
			if(i==0 || i==height-1 || j==0 || j==width-1){
				box[i*width+j]=black;
			}
		}
	}
	for(k=0;k<m;k++){
		arrayy=arrayy2[k];
		arrayx=arrayx2[k];
		n=n2[k];
		linecolour=linecolour2[k];
		switch(linetype){
			case 0:{//crosses
				for(i=0;i<n;i++){
					x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
					y_value=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
					put_cross(box,height,width,y_value,x_value,linecolour);
				}
			}break;
			case 1:{//lines
				x=malloc(n*sizeof(int));
				y=malloc(n*sizeof(int));
				for(i=0;i<n;i++){
					x[i]=((width-10)/(1.0*(x_max-x_min)))*1.0*(arrayx[i]-x_min)+5;
					y[i]=((height-10)/(1.0*(y_max-y_min)))*1.0*(arrayy[i]-y_min)+5;
				}
				for(i=0;i<n-1;i++){
					draw_line(x[i],y[i],x[i+1],y[i+1],box,width,linecolour,0,0);
				}
				free(x);
				free(y);

			}break;
			case 2:{//bottomlines
				for(i=0;i<n;i++){
					x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
					y_value=((height-10)/(1.0*(y_max-y_min)))*(arrayy[i]-y_min)+5;
					for(j=0;j>(-y_value);j--){
						set_pixel(box,width ,linecolour,x_value,y_value, 0, j);
					}			
				}
			}break;
			case 3:{//linear fit


			}break;
			case 4:{//points
				for(i=0;i<n;i++){
					x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
					y_value=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
					set_pixel(box,width ,linecolour,x_value,y_value, 0, 0);
				}
			}break;
			case 5:{//lines & crosses
				x=malloc(n*sizeof(int));
				y=malloc(n*sizeof(int));
				for(i=0;i<n;i++){
					x[i]=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
					y[i]=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
				}
				for(i=0;i<n-1;i++){
					draw_line(x[i],y[i],x[i+1],y[i+1],box,width,linecolour,0,0);
				}
				for(i=0;i<n;i++){
					put_cross(box,height,width,y[i],x[i],colour2);
				}
				free(x);
				free(y);
			}break;
			case 6:{//???
				for(i=0;i<n;i++){
					x_value=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
					y_value=((height-10)/(1.0*(y_max-y_min)))*(arrayy[i]-y_min)+5;
					for(j=0;j>(-y_value);j--){
						set_pixel(box,width ,linecolour,x_value,y_value, 0, j);
					}			
				}
				x=malloc(n*sizeof(int));
				y=malloc(n*sizeof(int));
				for(i=0;i<n;i++){
					x[i]=((width-10)/(1.0*(x_max-x_min)))*(arrayx[i]-x_min)+5;
					y[i]=((height-10)/(y_max-y_min))*(arrayy[i]-y_min)+5;
				}
				for(i=0;i<n-1;i++){
					draw_line(x[i],y[i],x[i+1],y[i+1],box,width,linecolour,0,0);
				}
				free(x);
				free(y);
			}

		}
	}
	//create_bmp(box,width,height, "plot_test.bmp");
	return box;
}

double find_max(double *array,int n){
	int i;
	int j=0;
	for(i=0;i<n;i++){
		j=(array[j]<array[i])?i:j;
	}
	return array[j];
}


double find_min(double *array,int n){
	int i;
	int j=0;
	for(i=0;i<n;i++){
		j=(array[j]>array[i])?i:j;
	}
	return array[j];
}

double find_max_multi(double **array,int *n,int m){
	int i;
	int j;
	double max=array[0][0];
	for(i=0;i<m;i++){
		for(j=0;j<n[i];j++){
			max=(array[i][j]<max)?max:array[i][j];
		}
	}
	return max;
}

double find_min_multi(double **array,int *n,int m){
	int i;
	int j;
	double min=array[0][0];
	for(i=0;i<m;i++){
		for(j=0;j<n[i];j++){
			min=(array[i][j]>min)?min:array[i][j];
		}
	}
	return min;
}

double find_max_nonzero(double *array,int n){
	int i;
	int j=0;
	for(i=0;i<n;i++){
		if(array[i]!=0)
			j=(array[j]<array[i])?i:j;
	}
	return array[j];
}


double find_min_nonzero(double *array,int n){
	int i;
	int j=0;
	for(i=0;i<n;i++){
		if(array[i]!=0)
			j=(array[j]>array[i])?i:j;
	}
	return array[j];
}


void put_cross(struct pixel *box,int height, int width, int y_value, int x_value, struct pixel linecolour){
	int i;	
	for(i=-4;i<5;i++){	
		box[width*y_value+x_value+i]=linecolour;
		box[width*(y_value-1)+x_value+i]=linecolour;
		box[width*(y_value+1)+x_value+i]=linecolour;
		box[width*(y_value+i)+x_value]=linecolour;
		box[width*(y_value+i)+x_value+1]=linecolour;
		box[width*(y_value+i)+x_value-1]=linecolour;
	}
	return;
}

void set_pixel(struct pixel *textfield, int width ,struct pixel colour,int start_x,int start_y, int plus_x, int plus_y){
	textfield[width*(start_y+plus_y)+(start_x+plus_x)]=colour;
}

void draw_line(int x,int y, int x1,int y1,struct pixel* box,int width,struct pixel linecolour,int linetype, int linesize){
	int i,j;
	double m;
	if(x==x1 && y!=y1){
		for(i=0;abs(i)<abs(y-y1);i-=(y-y1)/abs(y-y1)){
			set_pixel(box,width ,linecolour,x,y,0 ,i );
		}
	}
	else if(x!=x1 && y==y1){
		for(i=0;abs(i)<abs(x-x1);i-=(x-x1)/abs(x-x1)){
			set_pixel(box,width ,linecolour,x,y,i ,0 );
		}
	}
	else if(x==x1 && y==y1){
		set_pixel(box,width ,linecolour,x,y,0 ,0 );
	}
	else{
		m=(double)((y1-y)/(double)(x1-x));
		if(abs(y1-y)<abs(x1-x)){
			for(j=0;abs(j)<=abs(x1-x);j=j+(x1/abs(x1))){
				if(m>0) set_pixel(box,width ,linecolour,x,y, j, m*j);
				else set_pixel(box,width ,linecolour,x1,y1, j, m*j);
			}
		}	
		else{
			for(j=0;abs(j)<=abs(y1-y);j=j+(y1/abs(y1))){
						if(m>0) set_pixel(box,width ,linecolour,x,y, j/m, j);
						else set_pixel(box,width ,linecolour,x1,y1, j/m, j);
			}
		}
	}
	return;
}

void put_letters(struct pixel *textfield, int width ,struct pixel colour,int* start_fin_x,int* start_fin_y, char letter){
	int i;
	int j;
	switch(letter){
		case 'a':
		case 'A':{							/* x,y */
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,12,0);
			j=0;
			for(i=0;i<12;i++){
				if((i+1)%2==0)j++;
					set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,j,i);
			}
			for(;i>0;i--){
				if((i+1)%2==0)j++;
					set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,j,i);
			}
			for(i=3;i<10;i++){
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,5);
			}

			*start_fin_x+=16;
		}break;
		case 'b':
		case 'B':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,0);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,7);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,12);
				
			}
			j=0;
			for(i=0;i<2;i++){
				if(i==1)j=6;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6+j);
				if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6+j);
			}

			*start_fin_x+=12;
		}break;
		case 'c':
		case 'C':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,0+j*i);			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0);
			}

			*start_fin_x+=13;
		}break;
		case 'd':
		case 'D':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
			}	
			for(i=0;i<2;i++){
				j=13;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,0+j*i);			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,7+j*i);j-=2;
			}

			*start_fin_x+=13;
		}break;
		case 'e':
		case 'E':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,0);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,6);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,12);	
			}

			*start_fin_x+=10;
		}break;
		case 'f':
		case 'F':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				if(i!=11)if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,6);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,12);	
			}

			*start_fin_x+=10;
		}break;
		case 'g':
		case 'G':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;
				if(i!=0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,0+j*i);
				if(i!=0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0+j*i);
				if(i!=0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0);
			}			
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,2);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,11,3);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,12,4);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,5);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,6);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,7);
			for(i=0;i<5;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8+i,7);
			}

			*start_fin_x+=16;
		}break;
		case 'h':
		case 'H':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,i);
			}
			for(i=0;i<9;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+1,6);
			}

			*start_fin_x+=14;
		}break;
		case 'i':
		case 'I':{							/* x,y */
			for(i=0;i<6;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,0);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12);
			}
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,i);
			}

			*start_fin_x+=9;
		}break;
		case 'j':
		case 'J':{							/* x,y */
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12);
			}
			for(i=4;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,i);
			}

			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,2);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,3);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,4);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,5);

			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,2);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,3);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,4);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,5);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,5);


			*start_fin_x+=12;
		}break;
		case 'k':
		case 'K':{							/* x,y */
			for(i=0;i<13;i++){			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
			}
			for(i=0;i<7;i++){			
				if(i<5)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7-i,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,i+i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,i+i-1);
			}

			*start_fin_x+=12;
		}break;
		case 'l':
		case 'L':{							/* x,y */
			for(i=0;i<13;i++){			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
			}
			for(i=0;i<8;i++){			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,0);
			}

			*start_fin_x+=12;
		}break;
		case 'm':
		case 'M':{							/* x,y */
			for(i=0;i<13;i++){			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,12,i);
			}
			for(i=0;i<6;i++){			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6-i,i+6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6+i,i+6);
			}

			*start_fin_x+=16;
		}break;
		case 'n':
		case 'N':{							/* x,y */
			for(i=0;i<13;i++){			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,11,i);
				if(i!=12)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12-i);
			}

			*start_fin_x+=15;
		}break;
		case 'o':
		case 'O':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7+j*i);j-=2;
			}
			for(i=0;i<2;i++){
				j=11;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,7+j*i);j-=2;
			}

			*start_fin_x+=14;
		}break;
		case 'p':
		case 'P':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,7);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,12);
			}				
			j=6;
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6+j);


			*start_fin_x+=12;
		}break;
		case 'q':
		case 'Q':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0);
			}
			for(i=0;i<2;i++){
				j=11;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,11,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,12,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,14,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,14,7+j*i);j-=2;
			}
			for(i=0;i<6;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8+i,5-i);
			}

			*start_fin_x+=16;
		}break;
		case 'r':
		case 'R':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,7);
				if((i+1)%2==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2,12);
			}				
			j=6;
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6+j);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6+j);
			for(i=0;i<8;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2+4,7-i);
			}

			*start_fin_x+=12;
		}break;
		case 's':
		case 'S':{							/* x,y */
			j=0;
			for(i=0;i<2;i++){
				if(i==1)j=6;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5-i*3,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6-i*5,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7-i*7,2+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7-i*7,3+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7-i*7,4+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6-i*5,5+j);
				if(i==0)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5-i*4,6+j);
				if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4-i*2,6+j);
				
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,i*12);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,i*12);
			}
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,2);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,3);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,6);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,7);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,12);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,12);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,11);

			*start_fin_x+=11;
		}break;
		case 't':
		case 'T':{							/* x,y */
			for(i=0;i<13;i++){	
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12);
			}

			*start_fin_x+=15;
		}break;
		case 'u':
		case 'U':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,i);
				if(i>5)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i);
			}
			for(i=0;i<2;i++){
				j=13;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,0);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,0);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,1);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,1);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,2);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,3);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,4);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,5);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,0);
			}
			for(i=0;i<2;i++){
				j=11;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,1);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,1);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,2);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,11,3);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,12,4);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,12,5);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,13,7);
			}

			*start_fin_x+=16;
		}break;
		case 'v':
		case 'V':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,(12-i)/2,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2+6,i);
			}


			*start_fin_x+=15;
		}break;
		case 'w':
		case 'W':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,(12-i)/4,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,(12-i)/4,i);
				if(i<7)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,(12-i)/4+6,i);
				if(i<7)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2+3,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2+9,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/2+9,i);
			}

			*start_fin_x+=16;
		}break;
		case 'x':
		case 'X':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,(12-i)/1.5,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/1.5,i);
			}

			*start_fin_x+=12;
		}break;
		case 'y':
		case 'Y':{							/* x,y */
			for(i=0;i<13;i++){
				if(i>6)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,(12-i)/1.5,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/1.5,i);
			}

			*start_fin_x+=12;
		}break;
		case 'z':
		case 'Z':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/1.5,i);
			}
			for(i=0;i<8;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,0);
			}

			*start_fin_x+=12;
		}break;	





		case '(':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,7+j*i);j-=2;
			}

			*start_fin_x+=9;
		}break;
		case ')':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,7+j*i);j-=2;
			}

			*start_fin_x+=9;
		}break;
		case '/':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/1.5,i);
			}

			*start_fin_x+=15;
		}break;
		case '*':{							/* x,y */			
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					if(i==1 || j==1 || i==2 || j==2 || i==3 || j==3) set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,j,i+6);
				}
			}


			*start_fin_x+=10;
		}break;
		case '+':{							/* x,y */
			
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,i+4);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,7);
			}

			*start_fin_x+=10;
		}break;
		case '-':{							/* x,y */			
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,7);
			}

			*start_fin_x+=10;
		}break;



		case '0':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7+j*i);j-=2;
			}
			for(i=0;i<2;i++){
				j=11;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,7+j*i);j-=2;
			}
			for(i=1;i<11;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,((i+2)/4)+4,12-i);
			}

			*start_fin_x+=13;
		}break;
		case '1':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,i);
			}
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+1,0);
			}
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,11);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,10);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,9);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,8);


			*start_fin_x+=13;
		}break;
		case '2':{							/* x,y */
			for(i=0;i<8;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,0);
			}
			for(i=0;i<8;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,i);
			}
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,11);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,12);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,12);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,12);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,11);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,11);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,10);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,9);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,8);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,10);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,9);


			*start_fin_x+=13;
		}break;
		case '3':{							/* x,y */
			j=0;
			for(i=0;i<2;i++){
				if(i==1)j=6;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6+j);
				if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6+j);
			}
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,0);
				if(i>2)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12);
			}

			*start_fin_x+=13;
		}break;
		case '4':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,i);
			}
			for(i=0;i<8;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,5);
			}
			for(i=0;i<6;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,i*1.5+6);
			}

			*start_fin_x+=15;
		}break;
		case '5':{							/* x,y */
			for(i=0;i<6;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,i+7);
			}
			for(i=0;i<8;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,12);
			}
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6);
			if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6);
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,0);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,7);
			}

			*start_fin_x+=13;
		}break;
		case '6':{							/* x,y */
			for(i=0;i<2;i++){
				j=13;			
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,0+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,0+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,1+j*i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,1+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,2+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,3+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,4+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,5+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j*i);j-=2;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7+j*i);j-=2;
			}		
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,1);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,2);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,3);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,10,4);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,5);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,4,6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,3,6);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,5);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,5);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,9,12);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,12);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,13);
			

			*start_fin_x+=13;
		}break;
		case '7':{							/* x,y */
			for(i=0;i<13;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/1.5,i);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i/1.5,12);
			}
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,7);
			}


			*start_fin_x+=13;
		}break;
		case '8':{							/* x,y */
			j=0;
			for(i=0;i<2;i++){
				if(i==1)j=6;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6+j);
				if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6+j);
			}
			j=0;
			for(i=0;i<2;i++){
				if(i==1)j=6;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,2+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,3+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,4+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,5+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,6+j);
				if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,6+j);
			}
			for(i=0;i<3;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+3,0);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+3,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+3,12);
			}

			*start_fin_x+=13;
		}break;
		case '9':{							/* x,y */
			j=0;
			for(i=0;i<2;i++){
				if(i==1)j=6;
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,1+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,2+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,3+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,4+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,8,5+j);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,7,6+j);
				if(i==1)set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,6,6+j);
			}
			for(i=0;i<2;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,8);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,9);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,10);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,11);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,12);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,2,12);
			}
			for(i=0;i<3;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+2,0);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+3,7);
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i+3,12);
			}
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,5,0);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,1,1);
			set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,0,2);

			*start_fin_x+=13;
		}break;
		case ' ':{
			*start_fin_x+=15;
		}break;
		case ',':
		case '.':{			
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					if(i==1 || j==1 || i==2 || j==2 || i==3 || j==3) set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,j,i);
				}
			}


			*start_fin_x+=9;
		}break;
		case ':':{			
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					if(i==1 || j==1 || i==2 || j==2 || i==3 || j==3){ 
						set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,j,i);
						set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,j,i+7);
					}
				}
			}


			*start_fin_x+=9;
		}break;
		case '=':{							/* x,y */			
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,8);
			}
			for(i=0;i<7;i++){
				set_pixel(textfield,width,colour,*start_fin_x,*start_fin_y,i,3);
			}

			*start_fin_x+=10;
		}break;
		default:{
			*start_fin_x+=15;
		}break;
	}
	return;
}

double element(MATRIX_ matrix,int i,int j){
	if (i>=matrix.height){printf("i ist größer als die matrix hoch ist\n"); return 0;}
	if (j>=matrix.width){printf("j ist größer als die matrix breit ist\n"); return 0;}
	return matrix.elemente[matrix.width*i+j];
}



