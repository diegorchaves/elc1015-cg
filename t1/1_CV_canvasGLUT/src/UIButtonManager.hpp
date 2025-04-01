#ifndef UIBUTTONMANAGER_HPP
#define UIBUTTONMANAGER_HPP

#include "UIButton.hpp"
#include <vector>
#include <memory>

class UIButtonManager {
private:
    std::vector<std::unique_ptr<UIButton>> buttons;
public:
    void addButton(std::unique_ptr<UIButton> btn);
    void drawButtons() const;
    void handleMouseEvent(int button, int state, int x, int y);
};

#endif // UIBUTTONMANAGER_HPP

