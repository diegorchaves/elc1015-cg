#include "Layer.hpp"
#include "gl_canvas2d.h"

// Inicializa o vetor global de camadas
std::vector<Layer> layers;

Layer::Layer(Bmp* img, int x, int y) : image(img), visible(true), offsetX(x), offsetY(y)
{
    img->convertBGRtoRGB();
}

void Layer::setVisibility(bool v)
{
    visible = v;
}

void Layer::setOffset(int x, int y)
{
    offsetX = x; offsetY = y;
}

void Layer::draw() {
    if (visible) {
        //CV::translate(offsetX, offsetY);
        uchar* d = image->getImage();
        int bytesPerLine = (3 * (image->getWidth() + 1) / 4) * 4;

        for (int y = 0; y < image->getHeight(); y++)
        for (int x = 0; x < image->getWidth(); x++) {
            int pos = (y * bytesPerLine) + (x * 3);
            CV::color(d[pos] / 255.0, d[pos + 1] / 255.0, d[pos + 2] / 255.0);
            CV::point(x, y);
        }
    }
}

void desenhaImagens() {
    for (Layer& layer : layers) {
        layer.draw();
    }
}

void moveLayerUp(int index) {
    if (index < layers.size() - 1) {
        std::swap(layers[index], layers[index + 1]);
    }
}

void moveLayerDown(int index) {
    if (index > 0) {
        std::swap(layers[index], layers[index - 1]);
    }
}

void toggleVisibility(int index) {
    if (index >= 0 && index < layers.size()) {
        layers[index].setVisibility(!layers[index].visible);
    }
}

void setupLayers() {
    Bmp* img1 = new Bmp(".\\1_CV_canvasGLUT\\images\\normal_1.bmp");
    Bmp* img2 = new Bmp(".\\1_CV_canvasGLUT\\images\\img1.bmp");
    Bmp* img3 = new Bmp(".\\1_CV_canvasGLUT\\images\\img3.bmp");

    //layers.push_back(Layer(img1), 0, 0);
    //layers.push_back(Layer(img2), 20, 20);
    //layers.push_back(Layer(img3), 60, 60);

    layers.emplace_back(img1, 0, 0);
    layers.emplace_back(img2, 40, 40);
    layers.emplace_back(img3, 80, 80);

    // movendo a img 1 duas posicoes para cima, deixando-a em primeiro plano
    moveLayerUp(0);
    moveLayerUp(1);

    // movendo a img 1 uma posicao para baixo, deixando-a em segundo plano
    moveLayerDown(2);

    toggleVisibility(1);
    toggleVisibility(1);
}
