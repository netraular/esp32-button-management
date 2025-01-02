#include <Arduino.h>
#include "config.h"
#include "MainScreen.h"
#include "../ScreenManager.h"

extern ScreenManager screenManager;

void MainScreen::load() {
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Main Screen");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    Serial.println("MainScreen cargada.");
}

void MainScreen::update() {
    // Lógica de actualización de la pantalla principal
}

void MainScreen::handleButtonEvent(const ButtonState& state, const ButtonChange& change) {
    // Detectar combinaciones de botones
    if (state.button1Pressed && state.button2Pressed && state.button3Pressed) {
        Serial.println("Botones 1, 2 y 3 pulsados juntos.");
    } else if (state.button1Pressed && state.button2Pressed) {
        Serial.println("Botones 1 y 2 pulsados juntos.");
    } else if (state.button2Pressed && state.button3Pressed) {
        Serial.println("Botones 2 y 3 pulsados juntos.");
    } else if (state.button1Pressed && state.button3Pressed) {
        Serial.println("Botones 1 y 3 pulsados juntos.");
    } else {
        // Detectar pulsaciones individuales
        if (change.button1Changed) {
            if (state.button1Pressed) {
                Serial.println("Botón 1 presionado.");
            } else {
                Serial.println("Botón 1 liberado.");
            }
        }
        if (change.button2Changed) {
            if (state.button2Pressed) {
                Serial.println("Botón 2 presionado.");
            } else {
                Serial.println("Botón 2 liberado.");
            }
        }
        if (change.button3Changed) {
            if (state.button3Pressed) {
                Serial.println("Botón 3 presionado.");
            } else {
                Serial.println("Botón 3 liberado.");
            }
        }
    }
}