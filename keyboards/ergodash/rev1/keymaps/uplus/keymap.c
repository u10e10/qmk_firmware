#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#include "action_layer.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define __XXX__ KC_TRNS // 明示的透過

#undef C
#undef A
#undef G

#define O(key) OSM(MOD_##key)
#define C(key) RCTL(KC_##key)
#define A(key) RALT(KC_##key)
#define G(key) RGUI(KC_##key)
#define C_T(key) RCTL_T(KC_##key)
#define A_T(key) RALT_T(KC_##key)
#define G_T(key) RGUI_T(KC_##key)

#define LO_S OSL(_SUB)
#define LO_M OSL(_MISC)
#define LO_A OSL(_ADVANCE)
#define L_S(key) LT(_SUB, KC_##key)
#define L_M(key) LT(_MISC, KC_##key)
#define L_A(key) LT(_ADVANCE, KC_##key)

// QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI
#define H(key)  HYPR(KC_##key)
#define CA(key) RCTL(RALT(KC_##key))
#define GA(key) RGUI(RALT(KC_##key))
#define GC(key) RGUI(RCTL(KC_##key))

#define DYN_REC1 DYN_REC_START1
#define DYN_PLY1 DYN_MACRO_PLAY1
#define DYN_REC2 DYN_REC_START2
#define DYN_PLY2 DYN_MACRO_PLAY2
#define DYN_STOP DYN_REC_STOP

#define _QWERTY  0
#define _SUB     1
#define _MISC    2
#define _ADVANCE 3

enum custom_keycodes {
    QWERTY = SAFE_RANGE, // 使用可能なキーコード
    SUB,
    MISC,
    ADVANCE,

    DYNAMIC_MACRO_RANGE, // このコード以降にダイナミックマクロのキーが割り当てられる
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer
    [_QWERTY] = LAYOUT(
            KC_APP,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,                   XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    DYN_STOP,
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_TAB,                    KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
            C_T(ENT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                   KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L_M(QUOT),
            L_M(ESC),KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,                   XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, L_A(BSLS),
            KC_MPLY, KC_LGUI, KC_LALT, KC_GRV,           KC_ESC,  O(LSFT), KC_LCTL, LO_S,    KC_SPC,  LO_S,             KC_EQL,  KC_LALT, KC_RGUI, KC_ENT
            // tty切替に使うためにRALT -> LALT
            ),

    // F1~F12, Backspace, Delete, Cursor keys, Lang keys, Symbols
    [_SUB] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,                   XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
            _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                   _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F11,
            __XXX__, KC_BSPC, KC_DEL,  KC_LBRC, KC_RBRC, KC_TILD, KC_LPRN,                   KC_RPRN, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LANG2,KC_DQT,
            _______, KC_EQL,  KC_PLUS, KC_LCBR, KC_RCBR, KC_GRV,  XXXXXXX,                   XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LANG1,KC_PIPE,
            _______, __XXX__, __XXX__, _______,          __XXX__, __XXX__, __XXX__, _______, __XXX__, __XXX__,          _______, __XXX__, __XXX__, _______
            ),

    // Mouse keys, Window control shortcuts
    [_MISC] = LAYOUT(
            XXXXXXX, KC_FN1,  KC_FN2,  KC_FN3,  KC_FN4,  KC_FN5,  _______,                   _______, KC_FN6,  KC_FN7,  KC_FN8,  KC_FN9,  KC_FN10, KC_FN12,
            _______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(R),    _______,                   _______, GC(Y),   GC(U),   GC(I),   GC(O),   XXXXXXX, KC_FN11,
            __XXX__, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______,                   _______, GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),XXXXXXX, __XXX__,
            __XXX__, KC_BTN2, KC_WH_L, G(M),    KC_WH_R, KC_WH_D, _______,                   _______, G(LEFT), G(DOWN), G(UP),   G(RGHT), XXXXXXX, __XXX__,
            _______, __XXX__, __XXX__, _______,          __XXX__, __XXX__, __XXX__, KC_ACL0, KC_ACL2, KC_ACL1,          _______, __XXX__, __XXX__, _______
            ),

    // Media keys, Media control shortcuts, Dynamic macro keys, Sleep, etc...
    [_ADVANCE] =  LAYOUT(
            RESET,   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, KC_SLEP,
            DEBUG,   XXXXXXX, DYN_PLY1,DYN_PLY2,KC_PSCR, XXXXXXX, _______,                   _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
            __XXX__, C(ENT),  DYN_REC1,DYN_REC2,CA(T),   XXXXXXX, _______,                   _______, H(A),    H(B),    H(C),    H(D),    H(G),    __XXX__,
            TERM_ON, CA(S),   DYN_STOP,CA(D),   CA(Y),   CA(B),   _______,                   _______, H(E),    KC_MPRV, KC_MPLY, KC_MNXT, H(F),    __XXX__,
            TERM_OFF,__XXX__, __XXX__, _______,          __XXX__, __XXX__, __XXX__, _______, __XXX__, __XXX__,          _______, __XXX__, __XXX__, _______
            )
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case SUB:
            if (record->event.pressed) {
                layer_on(_SUB);
                update_tri_layer(_SUB, _MISC, _ADVANCE);
            } else {
                layer_off(_SUB);
                update_tri_layer(_SUB, _MISC, _ADVANCE);
            }
            return false;
            break;
        case MISC:
            if (record->event.pressed) {
                layer_on(_MISC);
                update_tri_layer(_SUB, _MISC, _ADVANCE);
            } else {
                layer_off(_MISC);
                update_tri_layer(_SUB, _MISC, _ADVANCE);
            }
            return false;
            break;
        case ADVANCE:
            if (record->event.pressed) {
                layer_on(_ADVANCE);
            } else {
                layer_off(_ADVANCE);
            }
            return false;
            break;
    }
    return true;
}
