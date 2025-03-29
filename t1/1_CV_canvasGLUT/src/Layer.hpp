#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <algorithm>
#include "Bmp.h"  // Supondo que sua classe Bmp esteja separada

class Layer {
public:
    Bmp* image;
    bool visible;

    Layer(Bmp* img);
    void setVisibility(bool v);
    void draw();
};

// Gerenciador de camadas
extern std::vector<Layer> layers;

void desenhaImagens();
void moveLayerUp(int index);
void moveLayerDown(int index);
void toggleVisibility(int index);
void setupLayers();

#endif
