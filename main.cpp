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

    tPixel pixel = {200,200, 255,255,0,0};

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

