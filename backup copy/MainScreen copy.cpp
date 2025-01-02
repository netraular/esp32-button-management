#include <Arduino.h>
#include "config.h"
#include "MainScreen.h"
#include "../ScreenManager.h"

extern ScreenManager screenManager;

// Variables para almacenar los objetos de los círculos
lv_obj_t* circle1;
lv_obj_t* circle2;
lv_obj_t* circle3;

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
    // Lógica de actualización de la pantalla principal (no necesaria en este caso)
}

void MainScreen::handleButtonEvent(const ButtonState& state, const ButtonChange& change) {
    // Cambiar el color de los círculos según el estado de los botones
    if (change.button1Changed) {
        if (state.button1Pressed) {
            lv_obj_set_style_bg_color(circle1, lv_color_hex(0x00FF00), 0); // Verde
        } else {
            lv_obj_set_style_bg_color(circle1, lv_color_hex(0x808080), 0); // Gris
        }
    }
    if (change.button2Changed) {
        if (state.button2Pressed) {
            lv_obj_set_style_bg_color(circle2, lv_color_hex(0x00FF00), 0); // Verde
        } else {
            lv_obj_set_style_bg_color(circle2, lv_color_hex(0x808080), 0); // Gris
        }
    }
    if (change.button3Changed) {
        if (state.button3Pressed) {
            lv_obj_set_style_bg_color(circle3, lv_color_hex(0x00FF00), 0); // Verde
        } else {
            lv_obj_set_style_bg_color(circle3, lv_color_hex(0x808080), 0); // Gris
        }
    }
}