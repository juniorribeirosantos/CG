#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

	//linha();
	//DesenhaLinha();
    //DesenhaPixels();

    tPixel pixel1 = {256, 256, 0, 255, 0, 255};
    tPixel pixel2 = {384, 128, 0, 0, 255, 255};
   	tPixel pixel3 = {128, 128, 255, 0, 0, 255};
    drawTriangleFullInterpolado(pixel1, pixel2, pixel3);

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();


	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;
	// Framebuffer scan loop.
 
	glutMainLoop();


	return 0;
}

