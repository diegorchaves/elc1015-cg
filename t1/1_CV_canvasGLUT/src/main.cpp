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
#include <iostream>
#include "gl_canvas2d.h"
#include "Bmp.h"
#include "Layer.hpp"
#include "Button.hpp"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 500, screenHeight = 500;

ButtonManager buttonManager;

int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

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

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
    desenhaFundo();
    desenhaImagens();
    buttonManager.renderButtons();

   Sleep(10); //nao eh controle de FPS. Somente um limitador de FPS.
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
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
   buttonManager.handleMouseEvent(button, state, mouseX, mouseY);
   printf("state: %d button: %d\n", state, button);
}


void acaoBotao1() {
    printf("botao clicado!\n");
}

void setupBotoes() {
    // Adicionar um botão na posição (50, 50) até (150, 100)
    buttonManager.addButton(200, 200, 350, 300, acaoBotao1);
}

int main(void)
{
    setupLayers();
    CV::translate(0, 0);
    setupBotoes();
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");

    CV::run();
}
