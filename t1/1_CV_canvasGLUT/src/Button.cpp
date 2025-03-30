// Button.cpp
#include "Button.hpp"
#include "gl_canvas2d.h" // Supondo que esta seja a API para desenhar
#include <iostream>

Button::Button(int x1, int y1, int x2, int y2, std::function<void()> onClick)
    : x1(x1), y1(y1), x2(x2), y2(y2), onClick(onClick) {}

void Button::draw() const {
    CV::color(0.8, 0.8, 0.8); // Cor cinza claro
    CV::rect(x1, y1, x2, y2);
}

bool Button::isHovered(int x, int y) const {
    std::cout << "Mouse Pos: (" << x << ", " << y << ") | "
              << "Botão: (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << ")"
              << std::endl;

    bool inside = x >= x1 && x <= x2 && y >= y1 && y <= y2;
    std::cout << "isHovered(" << x << ", " << y << ") -> " << inside << std::endl;
    return inside;
}

void Button::checkClick(int button, int state, int x, int y) {
    if (button == 0 && state == 0 && isHovered(x, y)) { // Botão esquerdo pressionado
        onClick();
    }
}

void ButtonManager::addButton(int x1, int y1, int x2, int y2, std::function<void()> onClick) {
    buttons.emplace_back(x1, y1, x2, y2, onClick);
}

void ButtonManager::renderButtons() const {
    for (const auto& button : buttons) {
        button.draw();
    }
}

void ButtonManager::handleMouseEvent(int button, int state, int x, int y) {
    for (auto& btn : buttons) { // Renomeia a variável interna para evitar conflito
        btn.checkClick(button, state, x, y);
    }
}
