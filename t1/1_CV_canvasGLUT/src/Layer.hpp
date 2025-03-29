#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <algorithm>
#include "Bmp.h"  // Supondo que sua classe Bmp esteja separada

class Layer {
public:
    Bmp* image;
    bool visible;
    int offsetX, offsetY;

    Layer(Bmp* img, int x = 0, int y = 0);
    void setVisibility(bool v);
    void draw();
    void setOffset(int x, int y);
};

// Gerenciador de camadas
extern std::vector<Layer> layers;

void desenhaImagens();
void moveLayerUp(int index);
void moveLayerDown(int index);
void toggleVisibility(int index);
void setupLayers();

#endif
