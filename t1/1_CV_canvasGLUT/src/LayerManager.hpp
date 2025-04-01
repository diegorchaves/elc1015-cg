#ifndef LAYERMANAGER_HPP
#define LAYERMANAGER_HPP

#include <vector>
#include "Layer.hpp"

class LayerManager {
private:
    std::vector<Layer> layers;
    int activeLayer;

public:
    LayerManager();

    void addLayer(Bmp* img);
    void moveLayerUp(int index);
    void moveLayerDown(int index);
    void toggleLayerVisibility(int index);
    void setActiveLayer(int index);
    void drawLayers();
};

#endif

