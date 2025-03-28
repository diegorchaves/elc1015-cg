/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         02/2025
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.1
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "Bmp.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 500, screenHeight = 500;

int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

Bmp *img1;
Bmp *img2;
unsigned char *d;

int primeira = 1;
int movendo1 = 0;
int movendo2 = 0;

int pintando = 0;

void desenhaFundo()
{
    for(int y = 0; y < screenHeight; y+= 5)
    {
        for(int x = 0; x < screenWidth; x+= 5)
        {
            if((x+y) % 2 == 0)
            {
                CV::color(0);
            }
            else
            {
                CV::color(1);
            }

            CV::rectFill(x, y, x+5, y+5);
        }
    }
}

void desenhaImg1()
{
    int x, y, pos;
    int bytesPerLine = (3 * (img1->getWidth() + 1) / 4) * 4;

    CV::translate(0, 0);
    d = img1->getImage();
    if(pintando)
    {
        for(y = mouseY; y < mouseY+10; y++)
        {
            for(x = mouseX; x < mouseX+10; x++)
            {
                pos = y*bytesPerLine + x * 3;
                d[pos] = 255.0;
                d[pos+1] = 0;
                d[pos+2] = 0;
            }
        }
    }


    for(y = 0; y < img1->getHeight(); y++)
    for(x = 0; x < img1->getWidth(); x++)
    {
        pos =  (y * bytesPerLine) + (x * 3);
        CV::color(d[pos]/255.0, d[pos+1]/255.0, d[pos+2]/255.0);
        CV::point(x, y);
    }
}


void desenhaImg2()
{
    CV::translate(100, 100);
    d = img2->getImage();

    int bytesPerLine = (3 * (img2->getWidth() + 1) / 4) * 4;
    for(int y = 0; y < img2->getHeight(); y++)
    for(int x = 0; x < img2->getWidth(); x++)
    {
        int pos =  (y * bytesPerLine) + (x * 3);
        CV::color(d[pos]/255.0, d[pos+1]/255.0, d[pos+2]/255.0);
        CV::point(x, y);
    }
}
//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
    desenhaFundo();

    if(primeira == 1)
    {
        desenhaImg1();
        desenhaImg2();
    }
    else
    {
        desenhaImg2();
        desenhaImg1();
    }


    //CV::translate(0, 0);

   Sleep(10); //nao eh controle de FPS. Somente um limitador de FPS.
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   //printf("\nTecla: %d" , key);
   if(key == 32)
   {
       primeira = 2;
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   //printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   if(state == 0)
    {
        pintando = 1;
    }
    if(state == 1)
    {
        pintando = 0;
    }
   //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    // o botao direito eh o button 2
}

int main(void)
{
   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   img1 = new Bmp(".\\1_CV_canvasGLUT\\images\\img1.bmp");
   img1->convertBGRtoRGB();
   //img1->data = img1->getImage();
   img2 = new Bmp(".\\1_CV_canvasGLUT\\images\\normal_1.bmp");
   img2->convertBGRtoRGB();

   CV::run();
}
