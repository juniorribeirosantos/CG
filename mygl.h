#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <iostream>
using namespace std; 

//*****************************************************************************
// Defina aqui as suas fun√ß√µes gr·ficas
//*****************************************************************************  
typedef struct{
	unsigned int X;
	unsigned int Y;
	unsigned int R;
	unsigned int G;
	unsigned int B;
	unsigned int A;
}tPixel;

int interpolar (int inicio, int fim, int passo, int final_passo) {

	int delta = (fim-inicio)*passo / (final_passo + inicio);
	if (delta!=0)
		return delta; 
	else 
		return inicio;
}


void linha (){
	
	for (unsigned int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT ; i++){
            FBptr[i*4]   = 255; //R
            FBptr[i*4+1] = 255; //G
            FBptr[i*4+2] = 0; //B
            FBptr[i*4+3] = 0; //A
        }
    }

    void putPixel(tPixel pixel){
    	int pos = 0;

    	if (pixel.X >= 0 && pixel.X <=IMAGE_WIDTH &&pixel.Y >=0 && pixel.Y <= IMAGE_HEIGHT){

    		pos = (IMAGE_WIDTH*pixel.Y + pixel.X)*4;
    		FBptr[pos]   = pixel.R;
    		FBptr[pos+1] = pixel.B;
    		FBptr[pos+2] = pixel.G;
    		FBptr[pos+3] = pixel.A;
    		
    	}else{
    		
    		cout<<"Valor n„o suportado pelo tamanho de tela. Use um valor entre 512x512";
    		
    	}
    }

    void drawLine(tPixel inicial, tPixel final) {

    	int dx = final.X - inicial.X; 
    	int dy = final.Y - final.Y; 
    	int d; 
    	int incrementaLeste; 
    	int incrementaNordeste; 
    	int incrementaX = 0; 
    	int incrementaY = 0;
    	tPixel pixel; //pixel que ser· manipulado


    	//trata o caso para todos os octantes
    	if (dx > 0) {
    		incrementaX = 1;
    	}else{
    		incrementaX = -1; 
    		dx = abs(dx); 
    	}if (dy>0){
    		incrementaY = 1;
    	} else{
    		incrementaY = -1;
    		dy = abs(dy);
   		}

    //passando valores que ser„o impressos
		pixel.X = inicial.X; 
		pixel.Y = inicial.Y; 
		pixel.R = final.R;
		pixel.G = final.G;
		pixel.B = final.B;
		pixel.A = final.A;

		//caso linha horizontal
		if (dx == 0) {

			for (pixel.X; pixel.X!=final.X; pixel.X+incrementaX) {
				putPixel(pixel);
			}
		}else {
			if (abs(dx)>abs(dy)){
				d=2*dy-dx;
				incrementaLeste=2*dy;
				incrementaNordeste = 2*(dy-dx);
				while (pixel.X!=final.X) {
					if (d<=0){
						d+=incrementaLeste;
						pixel.X+=incrementaX;
					}else {
						d+=incrementaNordeste;
						pixel.X=incrementaX;
						pixel.Y=incrementaY;
					}
				}

			}
		}
}



#endif // _MYGL_H_

