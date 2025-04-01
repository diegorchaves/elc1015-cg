#include "Layer.hpp"
#include "gl_canvas2d.h"

Layer::Layer(Bmp* img, int idx) : image(img), index(idx), visible(true) {}

void Layer::draw() {
    if (visible && image) {
        image->convertBGRtoRGB();
        unsigned char* d = image->getImage();
        int bytesPerLine = (3 * (image->getWidth() + 1) / 4) * 4;
        for(int y = 0; y < image->getHeight(); y++) {
            for(int x = 0; x < image->getWidth(); x++) {
                int pos = (y * bytesPerLine) + (x * 3);
                CV::color(d[pos]/255.0, d[pos+1]/255.0, d[pos+2]/255.0);
                CV::point(x, y);
            }
        }
    }
}

void Layer::toggleVisibility() {
    visible = !visible;
}

void Layer::setIndex(int idx) {
    index = idx;
}

int Layer::getIndex() const {
    return index;
}

bool Layer::isVisible() const {
    return visible;
}

Bmp* Layer::getImage() {
    return image;
}

LayerManager::LayerManager() : activeLayerIndex(-1) {}

void LayerManager::addLayer(Bmp* img) {
    layers.emplace_back(img, layers.size());
    if (activeLayerIndex == -1) {
        activeLayerIndex = 0;
    }
}

void LayerManager::removeLayer(int idx) {
    if (idx >= 0 && idx < layers.size()) {
        layers.erase(layers.begin() + idx);
        for (int i = 0; i < layers.size(); i++) {
            layers[i].setIndex(i);
        }
        if (activeLayerIndex >= layers.size()) {
            activeLayerIndex = layers.empty() ? -1 : layers.size() - 1;
        }
    }
}

void LayerManager::moveLayerUp(int idx) {
    if (idx > 0 && idx < layers.size()) {
        std::swap(layers[idx], layers[idx - 1]);
        layers[idx].setIndex(idx);
        layers[idx - 1].setIndex(idx - 1);
    }
}

void LayerManager::moveLayerDown(int idx) {
    if (idx >= 0 && idx < layers.size() - 1) {
        std::swap(layers[idx], layers[idx + 1]);
        layers[idx].setIndex(idx);
        layers[idx + 1].setIndex(idx + 1);
    }
}

void LayerManager::toggleLayerVisibility(int idx) {
    if (idx >= 0 && idx < layers.size()) {
        layers[idx].toggleVisibility();
    }
}

void LayerManager::setActiveLayer(int idx) {
    if (idx >= 0 && idx < layers.size()) {
        activeLayerIndex = idx;
    }
}

Layer* LayerManager::getActiveLayer() {
    return (activeLayerIndex >= 0 && activeLayerIndex < layers.size()) ? &layers[activeLayerIndex] : nullptr;
}

void LayerManager::drawLayers() {
    for (auto& layer : layers) {
        layer.draw();
    }
}
