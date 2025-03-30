// Button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <vector>

// Estrutura global para coordenadas do mouse
extern int mouseX, mouseY;

class Button {
private:
    int x1, y1, x2, y2;
    std::function<void()> onClick;

public:
    Button(int x1, int y1, int x2, int y2, std::function<void()> onClick);
    void draw() const;
    bool isHovered(int x, int y) const;
    void checkClick(int button, int state, int x, int y);
};

class ButtonManager {
private:
    std::vector<Button> buttons;

public:
    void addButton(int x1, int y1, int x2, int y2, std::function<void()> onClick);
    void renderButtons() const;
    void handleMouseEvent(int button, int state, int x, int y);
};

#endif // BUTTON_HPP
