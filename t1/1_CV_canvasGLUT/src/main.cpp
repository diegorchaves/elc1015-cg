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
#include "UIButton.hpp"
#include "UIButtonManager.hpp"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1200, screenHeight = 900;
int tamanhoMenuLateral = 350;
int alturaMenuUm = 100;
int alturaMenuInferior = 80;

Bmp *img1 = new Bmp(".\\1_CV_canvasGLUT\\images\\img1.bmp");

UIButtonManager uiManager;

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

void desenhaInterface()
{
    CV::color(0);
    CV::rectFill(0, 0, tamanhoMenuLateral, screenHeight);
    CV::rectFill(tamanhoMenuLateral, 0, screenWidth, alturaMenuInferior);

    CV::color(1);
    CV::line(0, screenHeight - alturaMenuUm, tamanhoMenuLateral, screenHeight - alturaMenuUm);
    CV::line(0, screenHeight - 2*alturaMenuUm, tamanhoMenuLateral, screenHeight - 2*alturaMenuUm);
    CV::line(0, screenHeight - 5*alturaMenuUm, tamanhoMenuLateral, screenHeight - 5*alturaMenuUm);
    CV::line(0, screenHeight - 6*alturaMenuUm, tamanhoMenuLateral, screenHeight - 6*alturaMenuUm);
    CV::line(0, screenHeight - 7*alturaMenuUm, tamanhoMenuLateral, screenHeight - 7*alturaMenuUm);
    CV::line(0, screenHeight - 8*alturaMenuUm, tamanhoMenuLateral, screenHeight - 8*alturaMenuUm);

}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
    desenhaFundo();
    desenhaInterface();
    uiManager.drawButtons();

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
   printf("state: %d button: %d\n", state, button);
   uiManager.handleMouseEvent(button, state, x, y);
}


void acaoBotao1() {
    printf("botao clicado!\n");

}

int main(void)
{
    //setupLayers(img1);
    CV::translate(0, 0);
    // Botão normal:
    uiManager.addButton(std::make_unique<NormalButton>(
        50, 50, 150, 100,
        [](){ std::cout << "Botão normal clicado!" << std::endl; }
    ));

// Checkbox:
uiManager.addButton(std::make_unique<CheckboxButton>(
    200, 50, 250, 100,
    [](bool state){ std::cout << "Checkbox agora está " << (state ? "ativo" : "inativo") << std::endl; }
));

// Slider:
uiManager.addButton(std::make_unique<SliderButton>(
    350, 75, 25,
    [](int value){ std::cout << "Slider valor: " << value << std::endl; }
));
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");

    CV::run();
}
