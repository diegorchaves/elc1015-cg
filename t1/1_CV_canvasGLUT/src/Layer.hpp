#ifndef LAYER_HPP
#define LAYER_HPP

#include "Bmp.h"
#include <vector>

class Layer {
private:
    Bmp* image;
    bool visible;
    int index;

public:
    Layer(Bmp* img, int idx);

    void draw();
    void toggleVisibility();
    void setIndex(int idx);
    int getIndex() const;
    bool isVisible() const;
    Bmp* getImage();
};

class LayerManager {
private:
    std::vector<Layer> layers;
    int activeLayerIndex;

public:
    LayerManager();
    void addLayer(Bmp* img);
    void removeLayer(int idx);
    void moveLayerUp(int idx);
    void moveLayerDown(int idx);
    void toggleLayerVisibility(int idx);
    void setActiveLayer(int idx);
    Layer* getActiveLayer();
    void drawLayers();
};

#endif // LAYER_HPP
