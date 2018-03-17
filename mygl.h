#ifndef _MYGL_H_
#define _MYGL_H_
#include <stdio.h>
#include <math.h>

#include "definitions.h"

//******************************************************************************
    //estrutura das coordenadas do pixel
    typedef struct{
        unsigned int X;
        unsigned int Y;
    }tCoordenadas;
    //estrutura do pixel e suas respectivas características
    typedef struct{
        tCoordenadas coordenadas;
        unsigned int R;
        unsigned int G;
        unsigned int B;
        unsigned int A;
    }tPixel;

//******************************************************************************

//*****************************************************************************
// Defina aqui as suas funções gráficas


    void pintaTela (){
        for (unsigned int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT ; i++){
            FBptr[i*4]   = 255; //R
            FBptr[i*4+1] = 255; //G
            FBptr[i*4+2] = 255; //B
            FBptr[i*4+3] = 255; //A
        }
    }

    void putPixel(tPixel pixel){
        int offset;
        if (pixel.coordenadas.X >= 0 && pixel.coordenadas.X <=IMAGE_WIDTH
            &&pixel.coordenadas.Y >=0 && pixel.coordenadas.Y <= IMAGE_HEIGHT){

            offset = (IMAGE_WIDTH*pixel.coordenadas.Y + pixel.coordenadas.X)*4;

            FBptr[offset]   = pixel.R;
            FBptr[offset+1] = pixel.B;
            FBptr[offset+2] = pixel.G;
            FBptr[offset+3] = pixel.A;

            }
        else{
            printf("Tente um valor entre %d e %d", IMAGE_WIDTH, IMAGE_HEIGHT);
        }
    }

    void drawLine(tPixel primeiro, tPixel ultimo){
        int d;
        int incrementaLeste;
        int incrementaNordeste;
        int incrementaX=0;
        int incrementaY=0;
        int deltaX = ultimo.coordenadas.X - primeiro.coordenadas.X;
        int deltaY = ultimo.coordenadas.Y - primeiro.coordenadas.Y;

        //se o delta for negativo decrementa
        // o valor de incrementaX é 1, caso contrário é -1
        if (deltaX>0){
            incrementaX=1;
        }else{
            incrementaX=-1;
            //módulo de deltaX
            deltaX=abs(deltaX); 
        }
        if(deltaY>0){
            incrementaY=1;
        }else{
            incrementaY=-1;
            //módulo de deltaY
            deltaY=abs(deltaY); 
        }

        //coordenadas e características do pixel 
        tPixel atual;
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        atual.R = ultimo.R;
        atual.G = ultimo.G;
        atual.B = ultimo.B;
        atual.A = ultimo.A;

        //se delta X for igual a zero, temos uma coluna
        //se delta X for diferente de zero e 
        //delta Y for igual a zero temos uma linha
        if (deltaX == 0){
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){
                putPixel(atual);
            }
        }else{
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){
                    putPixel(atual);
                }
            }else{ //nem � uma linha nem uma coluna
                if (abs(deltaX)>=abs(deltaY)){
                    d=2*deltaY-deltaX;
                    incrementaLeste=2*deltaY;
                    incrementaNordeste=2*(deltaY-deltaX);
                    while(atual.coordenadas.X!=ultimo.coordenadas.X){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.X+=incrementaX;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.X+=incrementaX;
                            atual.coordenadas.Y+=incrementaY;
                        }
                        putPixel(atual);
                    }

                }else {
                    d=2*deltaX-deltaY;
                    incrementaLeste=2*deltaX;
                    incrementaNordeste=2*(deltaX-deltaY);
                    while(atual.coordenadas.Y!=ultimo.coordenadas.Y){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.Y+=incrementaY;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.Y+=incrementaY;
                            atual.coordenadas.X+=incrementaX;
                        }
                        putPixel(atual);
                    }

                }
            }
        }

    }

    void interpolar(tPixel primeiro,tPixel ultimo,tPixel *atual){
        float deltaX = (float)(ultimo.coordenadas.X - primeiro.coordenadas.X);
        float deltaY = (float)(ultimo.coordenadas.Y - primeiro.coordenadas.Y);

        int incA, incB, incR, incG;

        if (abs(deltaX) >= abs(deltaY) ){
            incR = (ultimo.R - primeiro.R)/deltaX;
            incG = (ultimo.G - primeiro.G)/deltaX;
            incB = (ultimo.B - primeiro.B)/deltaX;
            incA = (ultimo.A - primeiro.A)/deltaX;
        }
        else{
            incR = (ultimo.R - primeiro.R)/deltaY;
            incG = (ultimo.G - primeiro.G)/deltaY;
            incB = (ultimo.B - primeiro.B)/deltaY;
            incA = (ultimo.A - primeiro.A)/deltaY;
        }

        atual->A+=incA;
        atual->R+=incR;
        atual->G+=incG;
        atual->B+=incB;

        putPixel(*atual);
    }


    void drawLineInterpolado (tPixel primeiro, tPixel ultimo){

        int deltaX = ultimo.coordenadas.X - primeiro.coordenadas.X;
        int deltaY = ultimo.coordenadas.Y - primeiro.coordenadas.Y;
        int d;
        int incrementaLeste;
        int incrementaNordeste;
        int incrementaX=0;
        int incrementaY=0;

       //se o delta for negativo decrementa, se for positivo, incrementa
        if (deltaX>0){
            incrementaX=1;
        }else if (deltaX < 0){
            incrementaX=-1;
            deltaX=abs(deltaX); //trabalhar com m�dulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else if (deltaY<0){
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com m�dulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do primeiro pixel
        atual.R = primeiro.R;
        atual.G = primeiro.G;
        atual.B = primeiro.B;
        atual.A = primeiro.A;

        if (deltaX == 0){ //� uma coluna
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){
                interpolar(primeiro, ultimo, &atual);

            }
        }else{ //deltaX !=0
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){
                    interpolar(primeiro, ultimo, &atual);

                }
            }else{ //nem � uma linha nem uma coluna
                if (abs(deltaX)>=abs(deltaY)){
                    d=2*deltaY-deltaX;
                    incrementaLeste=2*deltaY;
                    incrementaNordeste=2*(deltaY-deltaX);
                    while(atual.coordenadas.X!=ultimo.coordenadas.X){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.X+=incrementaX;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.X+=incrementaX;
                            atual.coordenadas.Y+=incrementaY;
                        }
                        interpolar(primeiro, ultimo, &atual);

                    }

                }else {
                    d=2*deltaX-deltaY;
                    incrementaLeste=2*deltaX;
                    incrementaNordeste=2*(deltaX-deltaY);
                    while(atual.coordenadas.Y!=ultimo.coordenadas.Y){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.Y+=incrementaY;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.Y+=incrementaY;
                            atual.coordenadas.X+=incrementaX;
                        }
                        interpolar(primeiro, ultimo, &atual);

                    }

                }
            }
        }

    }
    void drawTriangleInterpolado (tPixel p1, tPixel p2, tPixel p3 ){
        drawLineInterpolado(p2,p1);
        drawLineInterpolado(p3,p2);
        drawLineInterpolado(p1,p3);
    }

    void drawTriangle(tPixel p1, tPixel p2, tPixel p3 ){
        drawLine(p2, p1);
        drawLine(p3,p2);
        drawLine(p1,p3);
    }

    void drawTriangleFull (tPixel primeiro, tPixel ultimo, tPixel p3 ){
        int deltaX = ultimo.coordenadas.X - primeiro.coordenadas.X;
        int deltaY = ultimo.coordenadas.Y - primeiro.coordenadas.Y;
        int d;
        int incrementaLeste;
        int incrementaNordeste;
        int incrementaX=0;
        int incrementaY=0;

        //se o delta for negativo decrementa, se for positivo, incrementa
        if (deltaX>0){
            incrementaX=1;
        }else{
            incrementaX=-1;
            deltaX=abs(deltaX); //trabalhar com m�dulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else{
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com m�dulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do primeiro pixel
        atual.R = primeiro.R;
        atual.G = primeiro.G;
        atual.B = primeiro.B;
        atual.A = primeiro.A;

        //incrementar cores aos poucos
        int comprimento = sqrt(deltaX*deltaX+deltaY*deltaY);
        int incR = (ultimo.R - primeiro.R)/comprimento;
        int incG = (ultimo.G - primeiro.G)/comprimento;
        int incB = (ultimo.B - primeiro.B)/comprimento;
        int incA = (ultimo.A - primeiro.A)/comprimento;

        if (deltaX == 0){ //� uma coluna
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){

                drawLine(atual,p3);
            }
        }else{ //deltaX !=0
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){
                    drawLine(atual,p3);
                }
            }else{ //nem � uma linha nem uma coluna
                if (abs(deltaX)>=abs(deltaY)){
                    d=2*deltaY-deltaX;
                    incrementaLeste=2*deltaY;
                    incrementaNordeste=2*(deltaY-deltaX);
                    while(atual.coordenadas.X!=ultimo.coordenadas.X){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.X+=incrementaX;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.X+=incrementaX;
                            atual.coordenadas.Y+=incrementaY;
                        }
                        drawLine(atual,p3);
                    }

                }else {
                    d=2*deltaX-deltaY;
                    incrementaLeste=2*deltaX;
                    incrementaNordeste=2*(deltaX-deltaY);
                    while(atual.coordenadas.Y!=ultimo.coordenadas.Y){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.Y+=incrementaY;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.Y+=incrementaY;
                            atual.coordenadas.X+=incrementaX;
                        }
                        drawLine(atual,p3);
                    }

                }
            }
        }
    }

    //teste fazer um triangulo pintado internamente
    void drawTriangleFullInterpolado (tPixel primeiro, tPixel ultimo, tPixel p3){
        int deltaX = ultimo.coordenadas.X - primeiro.coordenadas.X;
        int deltaY = ultimo.coordenadas.Y - primeiro.coordenadas.Y;
        int d;
        int incrementaLeste;
        int incrementaNordeste;
        int incrementaX=0;
        int incrementaY=0;

        //se o delta for negativo decrementa, se for positivo, incrementa
        if (deltaX>0){
            incrementaX=1;
        }else{
            incrementaX=-1;
            deltaX=abs(deltaX); //trabalhar com m�dulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else{
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com m�dulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do primeiro pixel
        atual.R = primeiro.R;
        atual.G = primeiro.G;
        atual.B = primeiro.B;
        atual.A = primeiro.A;

        //incrementar cores aos poucos
        int comprimento = sqrt(deltaX*deltaX+deltaY*deltaY);
        int incR = (ultimo.R - primeiro.R)/comprimento;
        int incG = (ultimo.G - primeiro.G)/comprimento;
        int incB = (ultimo.B - primeiro.B)/comprimento;
        int incA = (ultimo.A - primeiro.A)/comprimento;

        if (deltaX == 0){ //� uma coluna
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){

                interpolar(primeiro, ultimo, &atual);
                drawLineInterpolado(atual,p3);
            }
        }else{ //deltaX !=0
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){

                    interpolar(primeiro, ultimo, &atual);
                    drawLineInterpolado(atual,p3);
                }
            }else{ //nem � uma linha nem uma coluna
                if (abs(deltaX)>=abs(deltaY)){
                    d=2*deltaY-deltaX;
                    incrementaLeste=2*deltaY;
                    incrementaNordeste=2*(deltaY-deltaX);
                    while(atual.coordenadas.X!=ultimo.coordenadas.X){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.X+=incrementaX;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.X+=incrementaX;
                            atual.coordenadas.Y+=incrementaY;
                        }
                        interpolar(primeiro, ultimo, &atual);
                        drawLineInterpolado(atual,p3);
                    }

                }else {
                    d=2*deltaX-deltaY;
                    incrementaLeste=2*deltaX;
                    incrementaNordeste=2*(deltaX-deltaY);
                    while(atual.coordenadas.Y!=ultimo.coordenadas.Y){
                        if(d<=0){
                            d+=incrementaLeste;
                            atual.coordenadas.Y+=incrementaY;
                        }else{
                            d+=incrementaNordeste;
                            atual.coordenadas.Y+=incrementaY;
                            atual.coordenadas.X+=incrementaX;
                        }
                        interpolar(primeiro, ultimo, &atual);
                        drawLineInterpolado(atual,p3);
                    }

                }
            }
        }

    }




//*****************************************************************************



#endif // _MYGL_H_


