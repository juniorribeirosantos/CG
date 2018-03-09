#ifndef _MYGL_H_
#define _MYGL_H_
#include <stdio.h>
#include <math.h>

#include "definitions.h"

//******************************************************************************
//estruturas para facilitar as chamadas nas funções
    typedef struct{
        unsigned int X;
        unsigned int Y;
    }tCoordenadas;

    typedef struct{
        tCoordenadas coordenadas;
        unsigned int valorR;
        unsigned int valorG;
        unsigned int valorB;
        unsigned int valorA;
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

            offset = 4*(IMAGE_WIDTH*pixel.coordenadas.Y + pixel.coordenadas.X);

            FBptr[offset]   = pixel.valorR;
            FBptr[offset+1] = pixel.valorB;
            FBptr[offset+2] = pixel.valorG;
            FBptr[offset+3] = pixel.valorA;

            }
        else{
            printf("pixel fora do intervalo\n");
        }
    }

    void drawLine(tPixel primeiro, tPixel ultimo){
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
            deltaX=abs(deltaX); //trabalhar com módulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else{
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com módulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do ultimo pixel
        atual.valorR = ultimo.valorR;
        atual.valorG = ultimo.valorG;
        atual.valorB = ultimo.valorB;
        atual.valorA = ultimo.valorA;

        if (deltaX == 0){ //é uma coluna
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){
                putPixel(atual);
            }
        }else{ //deltaX !=0
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){
                    putPixel(atual);
                }
            }else{ //nem é uma linha nem uma coluna
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
            incR = (ultimo.valorR - primeiro.valorR)/deltaX;
            incG = (ultimo.valorG - primeiro.valorG)/deltaX;
            incB = (ultimo.valorB - primeiro.valorB)/deltaX;
            incA = (ultimo.valorA - primeiro.valorA)/deltaX;
        }
        else{
            incR = (ultimo.valorR - primeiro.valorR)/deltaY;
            incG = (ultimo.valorG - primeiro.valorG)/deltaY;
            incB = (ultimo.valorB - primeiro.valorB)/deltaY;
            incA = (ultimo.valorA - primeiro.valorA)/deltaY;
        }

        /*
            float comprimento = sqrt(deltaX*deltaX+deltaY*deltaY);
            float incR = (float)(ultimo.valorR - primeiro.valorR)/comprimento;
            float incG = (float)(ultimo.valorG - primeiro.valorG)/comprimento;
            float incB = (float)(ultimo.valorB - primeiro.valorB)/comprimento;
            //static int incA = (ultimo.valorA - primeiro.valorA)/comprimento;
        */

        atual->valorA+=incA;
        atual->valorR+=incR;
        atual->valorG+=incG;
        atual->valorB+=incB;

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
            deltaX=abs(deltaX); //trabalhar com módulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else if (deltaY<0){
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com módulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do primeiro pixel
        atual.valorR = primeiro.valorR;
        atual.valorG = primeiro.valorG;
        atual.valorB = primeiro.valorB;
        atual.valorA = primeiro.valorA;

        if (deltaX == 0){ //é uma coluna
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){
                interpolar(primeiro, ultimo, &atual);

            }
        }else{ //deltaX !=0
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){
                    interpolar(primeiro, ultimo, &atual);

                }
            }else{ //nem é uma linha nem uma coluna
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
            deltaX=abs(deltaX); //trabalhar com módulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else{
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com módulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do primeiro pixel
        atual.valorR = primeiro.valorR;
        atual.valorG = primeiro.valorG;
        atual.valorB = primeiro.valorB;
        atual.valorA = primeiro.valorA;

        //incrementar cores aos poucos
        int comprimento = sqrt(deltaX*deltaX+deltaY*deltaY);
        int incR = (ultimo.valorR - primeiro.valorR)/comprimento;
        int incG = (ultimo.valorG - primeiro.valorG)/comprimento;
        int incB = (ultimo.valorB - primeiro.valorB)/comprimento;
        int incA = (ultimo.valorA - primeiro.valorA)/comprimento;

        if (deltaX == 0){ //é uma coluna
            for (atual.coordenadas.Y ; atual.coordenadas.Y != ultimo.coordenadas.Y; atual.coordenadas.Y+=incrementaY){

                drawLine(atual,p3);
            }
        }else{ //deltaX !=0
            if (deltaY == 0){ //linha horizontal
                for (atual.coordenadas.X; atual.coordenadas.X!=ultimo.coordenadas.X; atual.coordenadas.X+=incrementaX){
                    drawLine(atual,p3);
                }
            }else{ //nem é uma linha nem uma coluna
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
            deltaX=abs(deltaX); //trabalhar com módulo (valor positivo)
        }
        if(deltaY>0){
            incrementaY=1;
        }else{
            incrementaY=-1;
            deltaY=abs(deltaY); //trabalhar com módulo (valor positivo)
        }

        tPixel atual;
        //ter as coordenadas inciais do primeiro pixel
        atual.coordenadas.X = primeiro.coordenadas.X;
        atual.coordenadas.Y = primeiro.coordenadas.Y;
        //ter as cores do primeiro pixel
        atual.valorR = primeiro.valorR;
        atual.valorG = primeiro.valorG;
        atual.valorB = primeiro.valorB;
        atual.valorA = primeiro.valorA;

        //incrementar cores aos poucos
        int comprimento = sqrt(deltaX*deltaX+deltaY*deltaY);
        int incR = (ultimo.valorR - primeiro.valorR)/comprimento;
        int incG = (ultimo.valorG - primeiro.valorG)/comprimento;
        int incB = (ultimo.valorB - primeiro.valorB)/comprimento;
        int incA = (ultimo.valorA - primeiro.valorA)/comprimento;

        if (deltaX == 0){ //é uma coluna
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
            }else{ //nem é uma linha nem uma coluna
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


