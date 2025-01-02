#include <Arduino.h>
#include "config.h"
#include "MainScreen.h"
#include "../ScreenManager.h"

extern ScreenManager screenManager;

// Variables para almacenar los objetos de los círculos
lv_obj_t* circle1;
lv_obj_t* circle2;
lv_obj_t* circle3;

// Variables para rastrear el momento en que se presionan los botones
unsigned long button1PressTime = 0;
unsigned long button2PressTime = 0;
unsigned long button3PressTime = 0;

// Margen de tiempo para considerar que los botones se presionaron "a la vez" (en milisegundos)
const unsigned long PRESS_TIME_MARGIN = 50;

// Estados de los botones (definidos en MainScreen.h)
ButtonStateEnum button1State = STATE_NONE;
ButtonStateEnum button2State = STATE_NONE;
ButtonStateEnum button3State = STATE_NONE;

// Variables para la animación de colores
uint8_t animationStep = 0; // Paso de la animación
const uint8_t ANIMATION_STEPS = 100; // Número de pasos para la animación

void MainScreen::load() {
    // Crear los círculos
    circle1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(circle1, 30, 30); // Tamaño del círculo reducido
    lv_obj_set_style_radius(circle1, LV_RADIUS_CIRCLE, 0); // Hacerlo circular
    lv_obj_set_style_bg_color(circle1, lv_color_hex(0x808080), 0); // Color gris
    lv_obj_align(circle1, LV_ALIGN_CENTER, -40, 0); // Posicionar el primer círculo

    circle2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(circle2, 30, 30); // Tamaño del círculo reducido
    lv_obj_set_style_radius(circle2, LV_RADIUS_CIRCLE, 0); // Hacerlo circular
    lv_obj_set_style_bg_color(circle2, lv_color_hex(0x808080), 0); // Color gris
    lv_obj_align(circle2, LV_ALIGN_CENTER, 0, 0); // Posicionar el segundo círculo

    circle3 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(circle3, 30, 30); // Tamaño del círculo reducido
    lv_obj_set_style_radius(circle3, LV_RADIUS_CIRCLE, 0); // Hacerlo circular
    lv_obj_set_style_bg_color(circle3, lv_color_hex(0x808080), 0); // Color gris
    lv_obj_align(circle3, LV_ALIGN_CENTER, 40, 0); // Posicionar el tercer círculo

    Serial.println("MainScreen cargada.");
}

void MainScreen::update() {
    // Incrementar el paso de la animación
    animationStep = (animationStep + 1) % ANIMATION_STEPS;

    // Calcular el valor de la animación (0 a 255)
    uint8_t animationValue = (uint8_t)(255 * (sin(2 * PI * animationStep / ANIMATION_STEPS) + 1) / 2);

    // Actualizar el color de los círculos según su estado y la animación
    updateCircleColor(circle1, button1State, animationValue);
    updateCircleColor(circle2, button2State, animationValue);
    updateCircleColor(circle3, button3State, animationValue);
}

void MainScreen::updateCircleColor(lv_obj_t* circle, ButtonStateEnum state, uint8_t animationValue) {
    lv_color_t baseColor, targetColor;

    switch (state) {
        case STATE_NONE:
            baseColor = lv_color_hex(0x808080); // Gris
            targetColor = lv_color_hex(0x000000); // Negro
            break;
        case STATE_PRESSED:
            baseColor = lv_color_hex(0x00FF00); // Verde
            targetColor = lv_color_hex(0x0000FF); // Azul
            break;
        case STATE_COMBO:
            baseColor = lv_color_hex(0xFF0000); // Rojo
            targetColor = lv_color_hex(0xFFFF00); // Amarillo
            break;
    }

    // Interpolar entre el color base y el color objetivo según el valor de la animación
    lv_color_t interpolatedColor = lv_color_mix(targetColor, baseColor, animationValue);
    lv_obj_set_style_bg_color(circle, interpolatedColor, 0);
}

void MainScreen::handleButtonEvent(const ButtonState& state, const ButtonChange& change) {
    // Obtener el tiempo actual
    unsigned long currentTime = millis();


    // Actualizar el tiempo de presión de los botones si se presionan
    if (change.button1Changed && state.button1Pressed) {
        button1PressTime = currentTime;
    }
    if (change.button2Changed && state.button2Pressed) {
        button2PressTime = currentTime;
    }
    if (change.button3Changed && state.button3Pressed) {
        button3PressTime = currentTime;
    }

    // Verificar si los botones se presionaron "a la vez"
    bool buttonsPressedTogether = false;
    if (state.button1Pressed && state.button2Pressed && state.button3Pressed) {
        if (abs((long)(button1PressTime - button2PressTime)) <= PRESS_TIME_MARGIN &&
            abs((long)(button1PressTime - button3PressTime)) <= PRESS_TIME_MARGIN) {
            buttonsPressedTogether = true;
        }
    } else if (state.button1Pressed && state.button2Pressed) {
        if (abs((long)(button1PressTime - button2PressTime)) <= PRESS_TIME_MARGIN) {
            buttonsPressedTogether = true;
        }
    } else if (state.button2Pressed && state.button3Pressed) {
        if (abs((long)(button2PressTime - button3PressTime)) <= PRESS_TIME_MARGIN) {
            buttonsPressedTogether = true;
        }
    } else if (state.button1Pressed && state.button3Pressed) {
        if (abs((long)(button1PressTime - button3PressTime)) <= PRESS_TIME_MARGIN) {
            buttonsPressedTogether = true;
        }
    }

    // Actualizar el estado de los botones
    if (buttonsPressedTogether) {
        // Si los botones se presionaron a la vez, poner los botones presionados en estado COMBO
        if (state.button1Pressed) button1State = STATE_COMBO;
        if (state.button2Pressed) button2State = STATE_COMBO;
        if (state.button3Pressed) button3State = STATE_COMBO;
    } else {
        // Si no se presionaron a la vez, actualizar el estado de cada botón individualmente
        if (change.button1Changed) {
            button1State = state.button1Pressed ? STATE_PRESSED : STATE_NONE;
        }
        if (change.button2Changed) {
            button2State = state.button2Pressed ? STATE_PRESSED : STATE_NONE;
        }
        if (change.button3Changed) {
            button3State = state.button3Pressed ? STATE_PRESSED : STATE_NONE;
        }
    }

    // Si un botón no está pulsado, su estado debe ser STATE_NONE, independientemente de su estado anterior
    if (!state.button1Pressed) {
        button1State = STATE_NONE;
    }
    if (!state.button2Pressed) {
        button2State = STATE_NONE;
    }
    if (!state.button3Pressed) {
        button3State = STATE_NONE;
    }
}