/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,
    SUB,
    MISC,
    ADVANCE
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
    DYNAMIC_MACRO_RANGE, // このコード以降にダイナミックマクロのキーが割り当てられる
};

#define _______ KC_TRNS
#define __XXX__ KC_TRNS // 明示的透過
#define XXXXXXX KC_NO

#define O(key) OSM(MOD_##key)

#undef C
#undef A
#undef G
#define C(key) RCTL(KC_##key)
#define A(key) RALT(KC_##key)
#define G(key) RGUI(KC_##key)

#define C_T(key) RCTL_T(KC_##key)
#define A_T(key) RALT_T(KC_##key)
#define G_T(key) RGUI_T(KC_##key)

#define LO_S OSL(SUB)
#define LO_M OSL(MISC)
#define LO_A OSL(ADVANCE)
#define L_S(key) LT(SUB, KC_##key)
#define L_M(key) LT(MISC, KC_##key)
#define L_A(key) LT(ADVANCE, KC_##key)

// QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI
#define H(key)  HYPR(KC_##key)
#define CA(key) RCTL(RALT(KC_##key))
#define GA(key) RGUI(RALT(KC_##key))
#define GC(key) RGUI(RCTL(KC_##key))

// TG(SYMB) WEBUSB_PAIR MO(SYMB) TOGGLE_LAYER_COLOR VRSN
// KC_AMPR KC_PERC KC_DLR KC_CIRC
// EEP_RST, RGB_VAI, RGB_HUD, RGB_VAD, RGB_HUI
// LED_LEVEL,RESET,EEP_RST
// TERM_ON
// TERM_OFF


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// align
//      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,

    // Main layer
    [BASE] = LAYOUT_moonlander(
        KC_APP,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,          XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    DM_RSTP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_TAB,           XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
        C_T(ENT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,          KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L_M(QUOT),
        KC_TAB,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, L_A(BSLS),
        KC_MPLY, KC_LGUI, KC_LALT, KC_GRV,  KC_ESC,           KC_ESC,           KC_ESC,           KC_MINUS,KC_EQL,  KC_LALT, KC_RGUI, KC_ENT,
                                            O(LSFT), KC_LCTL, KC_LCTL,          LO_S,    LO_S,  KC_SPC
    ),

    // F1~F12, Backspace, Delete, Cursor keys, Lang keys, Symbols
    [SUB] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LANG5,KC_F11,
        __XXX__, KC_BSPC, KC_DEL,  XXXXXXX, XXXXXXX, KC_TILD, _______,          _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LANG2,XXXXXXX,
        __XXX__, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,                             KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LANG1,XXXXXXX,
        _______, __XXX__, __XXX__, _______, __XXX__,          _______,          _______,          _______, _______, __XXX__, __XXX__, _______,
                                            __XXX__, __XXX__, __XXX__,          __XXX__, __XXX__, __XXX__
    ),

    // Mouse keys, Window control shortcuts
    [MISC] = LAYOUT_moonlander(
        XXXXXXX, KC_FN1,  KC_FN2,  KC_FN3,  KC_FN4,  KC_FN5,  _______,          _______, KC_FN6,  KC_FN7,  KC_FN8,  KC_FN9,  KC_FN10, KC_FN12,
        _______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(R),    _______,          _______, GC(Y),   GC(U),   GC(I),   GC(O),   XXXXXXX, KC_FN11,
        __XXX__, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______,          _______, GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),XXXXXXX, __XXX__,
        __XXX__, KC_BTN2, KC_WH_L, G(M),    KC_WH_R, KC_WH_D,                            G(LEFT), G(DOWN), G(UP),   G(RGHT), XXXXXXX, __XXX__,
        _______, __XXX__, __XXX__, _______, __XXX__,          _______,          _______,          _______, _______, __XXX__, __XXX__, _______,
                                            __XXX__, __XXX__, __XXX__,          KC_ACL1, KC_ACL2, KC_ACL0
    ),

    // Media keys, Media control shortcuts, Dynamic macro keys, Sleep, etc...
    [ADVANCE] = LAYOUT_moonlander(
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP,
        DEBUG,   DM_RSTP, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, _______,          _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        __XXX__, DM_REC1, DM_PLY1, XXXXXXX, CA(T),   XXXXXXX, _______,          _______, H(A),    H(B),    H(C),    H(D),    H(G),    __XXX__,
        __XXX__, DM_REC2, DM_PLY1, CA(D),   CA(Y),   CA(B),                              H(E),    KC_MPRV, KC_MPLY, KC_MNXT, H(F),    __XXX__,
        _______, __XXX__, __XXX__, _______, __XXX__,          _______,          _______,          _______, _______, __XXX__, __XXX__, _______,
                                            __XXX__, __XXX__, __XXX__,          __XXX__, __XXX__, __XXX__
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    return state;
}
