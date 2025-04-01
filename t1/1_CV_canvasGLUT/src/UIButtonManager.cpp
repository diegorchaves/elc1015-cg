#include "UIButtonManager.hpp"

void UIButtonManager::addButton(std::unique_ptr<UIButton> btn) {
    buttons.push_back(std::move(btn));
}

void UIButtonManager::drawButtons() const {
    for (const auto& btn : buttons) {
        btn->draw();
    }
}

void UIButtonManager::handleMouseEvent(int button, int state, int x, int y) {
    for (auto& btn : buttons) {
        btn->handleMouseEvent(button, state, x, y);
    }
}

