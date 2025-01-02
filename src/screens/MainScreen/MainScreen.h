#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "../Screen.h"

class MainScreen : public Screen {
public:
    void load() override;
    void update() override;
    void handleButtonEvent(const ButtonState& state, const ButtonChange& change) override; // Función unificada
};

#endif