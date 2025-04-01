#include "UIButton.hpp"
#include "gl_canvas2d.h"
#include <algorithm>
#include <iostream>

// ---------- NormalButton ----------

NormalButton::NormalButton(int x1, int y1, int x2, int y2, std::function<void()> onClick)
    : x1(x1), y1(y1), x2(x2), y2(y2), onClick(onClick)
{}

void NormalButton::draw() const {
    CV::rect(x1, y1, x2, y2);
}

void NormalButton::handleMouseEvent(int button, int state, int x, int y) {
    // Supondo que button 0 e state 0 correspondam ao clique pressionado
    if (button == 0 && state == 0 && x >= x1 && x <= x2 && y >= y1 && y <= y2) {
        onClick();
    }
}

// ---------- CheckboxButton ----------

CheckboxButton::CheckboxButton(int x1, int y1, int x2, int y2, std::function<void(bool)> onToggle)
    : x1(x1), y1(y1), x2(x2), y2(y2), checked(false), onToggle(onToggle)
{}

void CheckboxButton::draw() const {
    // Desenha a caixa do checkbox
    CV::rect(x1, y1, x2, y2);
    // Se estiver marcado, desenha um X dentro
    if (checked) {
        CV::line(x1, y1, x2, y2);
        CV::line(x1, y2, x2, y1);
    }
}

void CheckboxButton::handleMouseEvent(int button, int state, int x, int y) {
    if (button == 0 && state == 0 && x >= x1 && x <= x2 && y >= y1 && y <= y2) {
        checked = !checked;
        onToggle(checked);
    }
}

bool CheckboxButton::isChecked() const {
    return checked;
}

// ---------- SliderButton ----------

SliderButton::SliderButton(int centerX, int centerY, int radius, std::function<void(int)> onSlide)
    : centerX(centerX), centerY(centerY), radius(radius), value(0), onSlide(onSlide), dragging(false)
{}

void SliderButton::draw() const {
    // Define a barra do slider
    int barX1 = centerX - radius;
    int barX2 = centerX + radius;
    int barHeight = 10; // espessura da barra
    int barY1 = centerY - barHeight / 2;
    int barY2 = centerY + barHeight / 2;
    CV::rect(barX1, barY1, barX2, barY2);

    // Calcula a posição do knob com base no valor (0 a 100)
    int knobX = centerX - radius + (value * 2 * radius / 100);

    // Desenha o knob como um círculo sobre a barra
    CV::circle(knobX, centerY, this->radius, 30);
}

void SliderButton::handleMouseEvent(int button, int state, int x, int y) {
    // Se o botão esquerdo for pressionado dentro do círculo, inicia o arrasto
    if (button == 0) {
        if (state == 0) { // pressionado
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx*dx + dy*dy <= radius*radius) {
                dragging = true;
            }
        } else { // liberado
            dragging = false;
        }
        if (dragging) {
            // Atualiza o valor com base na posição horizontal do mouse
            // Exemplo: mapeia a posição horizontal dentro de uma faixa (centerX - radius, centerX + radius) para 0-100
            int newValue = std::max(0, std::min(100, (x - (centerX - radius)) * 100 / (2 * radius)));
            if (newValue != value) {
                value = newValue;
                onSlide(value);
            }
        }
    }
}

int SliderButton::getValue() const {
    return value;
}

