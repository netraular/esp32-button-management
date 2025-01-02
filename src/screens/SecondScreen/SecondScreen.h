#ifndef SECONDSCREEN_H
#define SECONDSCREEN_H

#include "../Screen.h"

class SecondScreen : public Screen {
public:
    void load() override;
    void update() override;
    void handleButtonEvent(const ButtonState& state, const ButtonChange& change) override; // Función unificada
};

#endif