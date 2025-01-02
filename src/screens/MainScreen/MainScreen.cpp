#include <Arduino.h>
#include "config.h"
#include "MainScreen.h"
#include "../ScreenManager.h"

extern ScreenManager screenManager;

void MainScreen::load() {
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Main Screen");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    Serial.println("MainScreen cargada.");
}

void MainScreen::update() {
    // Lógica de actualización de la pantalla principal
}

void MainScreen::handleButtonEvent(const ButtonState& state, const ButtonChange& change) {
    noTone(BUZZER_PIN); // Detener cualquier sonido anterior

    // Detectar combinaciones de botones
    if (state.button1Pressed && state.button2Pressed && state.button3Pressed) {
        // Botones 1, 2 y 3 presionados
        tone(BUZZER_PIN, 500, 1000);
        screenManager.setScreen("SecondScreen"); // Cambiar a SecondScreen
    } else if (state.button1Pressed && state.button2Pressed) {
        // Botones 1 y 2 presionados
        tone(BUZZER_PIN, 800, 500);
    } else if (state.button1Pressed && state.button3Pressed) {
        // Botones 1 y 3 presionados
        tone(BUZZER_PIN, 900, 500);
    } else if (state.button2Pressed && state.button3Pressed) {
        // Botones 2 y 3 presionados
        tone(BUZZER_PIN, 600, 500);
    } else {
        // Detectar pulsaciones individuales
        if (change.button1Changed && state.button1Pressed) {
            // Botón 1 presionado
            tone(BUZZER_PIN, 1000, 200);
        }
        if (change.button2Changed && state.button2Pressed) {
            // Botón 2 presionado
            tone(BUZZER_PIN, 1200, 200);
        }
        if (change.button3Changed && state.button3Pressed) {
            // Botón 3 presionado
            tone(BUZZER_PIN, 1400, 200);
        }
    }
}