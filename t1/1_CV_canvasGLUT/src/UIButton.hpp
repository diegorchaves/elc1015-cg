#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <functional>

// Classe base abstrata para botões
class UIButton {
public:
    virtual void draw() const = 0;
    virtual void handleMouseEvent(int button, int state, int x, int y) = 0;
    virtual ~UIButton() {}
};

// Botão normal: desenha um retângulo
class NormalButton : public UIButton {
private:
    int x1, y1, x2, y2;
    std::function<void()> onClick;
public:
    NormalButton(int x1, int y1, int x2, int y2, std::function<void()> onClick);
    void draw() const override;
    void handleMouseEvent(int button, int state, int x, int y) override;
};

// Botão checkbox: retângulo com “X” quando marcado
class CheckboxButton : public UIButton {
private:
    int x1, y1, x2, y2;
    bool checked;
    std::function<void(bool)> onToggle; // callback com o novo estado
public:
    CheckboxButton(int x1, int y1, int x2, int y2, std::function<void(bool)> onToggle);
    void draw() const override;
    void handleMouseEvent(int button, int state, int x, int y) override;
    bool isChecked() const;
};

// Botão slider: desenha um círculo e atualiza um valor com base no movimento
class SliderButton : public UIButton {
private:
    int centerX, centerY;
    int radius;
    int value; // valor atual (ex: de 0 a 100)
    std::function<void(int)> onSlide; // callback com o novo valor
    bool dragging;
public:
    SliderButton(int centerX, int centerY, int radius, std::function<void(int)> onSlide);
    void draw() const override;
    void handleMouseEvent(int button, int state, int x, int y) override;
    int getValue() const;
};

#endif // UIBUTTON_HPP

