#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

// for dynamic macro
enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // 使用可能なキーコードの範囲
    EPRM,
    VRSN,
    RGB_SLD,
    DYNAMIC_MACRO_RANGE, // このコード以降にダイナミックマクロのキーが割り当てられる
};

#include "dynamic_macro.h"

// 押下時間で処理を分ける http://qiita.com/teri_yakichan/items/db54589b67ba9330faed
// http://qiita.com/ReSTARTR/items/970354940f49c67fb9fd
// https://github.com/jackhumbert/qmk_firmware/blob/master/quantum/keymap.h
// /quantum/keymap.h

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define MISC 3 // left hand layer

#define M_HW 0
#define M_AMA 1
#define M_DKV 2
#define M_YRH 3

#define BREAK RCTL(KC_PAUSE)
#define LOCK RGUI(KC_L)
#define LT_2(key) LT(MDIA, KC_##key)
#define LT_3(key) LT(MISC, KC_##key)
#define H(key)  HYPR(KC_##key)
#define G(key)  RGUI(KC_##key)
#define CA(key) RCTL(RALT(KC_##key))
#define GA(key) RGUI(RALT(KC_##key))
#define M_S(key) D(LSFT), T(key), U(LSFT)

#define DYN_REC1 DYN_REC_START1
#define DYN_PLY1 DYN_MACRO_PLAY1
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// TxBolt Codes
#define GRPMASK 0b11000000

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
     * ,--------------------------------------------------.     ,--------------------------------------------------.
     * |   L3   |   1  |   2  |   3  |   4  |   5  |DYN_P1|     |DYN_R1|   6  |   7  |   8  |   9  |   0  |DYN_STOP|
     * |--------+------+------+------+------+------+------|     |------+------+------+------+------+------+--------|
     * |   `    |   Q  |   W  |   E  |   R  |   T  | TAB  |     |  -   |   Y  |   U  |   I  |   O  |   P  |   -    |
     * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
     * | Enter  |   A  |   S  |   D  |   F  |   G  |------|     |------|   H  |   J  |   K  |   L  |   ;  |  '/L2  |
     * |--------+------+------+------+------+------|  `   |     |  =   |------+------+------+------+------+--------|
     * |  Esc   |   Z  |   X  |   C  |   V  |   B  |      |     |      |   N  |   M  |   ,  |   .  |   /  |   \    |
     * |--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------|
     * |        | Gui  | Alt  | ESC  |  L3  |                                 |   [  |   ]  | Alt  | Gui  | Enter  |
     * `------------------------------------'                                 `------------------------------------'
     *                                     .--------------.     .--------------.
     *                                     |  Eng  | Play |     |  App |  Jpn  |
     *                              ,------|-------|------|     |------|-------|-------.
     *                              |      |       | Eng  |     |  Jpn |       |       |
     *                              | Ctrl | Shift |------|     |------|  L1   | Space |
     *                              |      |       | Eng  |     |  Jpn |       |       |
     *                              `---------------------'     `----------------------'
     */
    // If it accepts an argument (i.e, is a function), it doesn't need KC_.
    // Otherwise, it needs KC_*
    [BASE] = KEYMAP(  // layer 0 : default
            MO(MISC),   KC_1,     KC_2,    KC_3,    KC_4,    KC_5,     DYN_PLY1,
            KC_GRV,     KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,     KC_TAB,
            KC_ENT,     KC_A,     KC_S,    KC_D,    KC_F,    KC_G,
            KC_ESC,     KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_GRV,
            XXXXXXX,    KC_LGUI,  KC_LALT, KC_ESC,  MO(MISC),
            KC_LANG1,   KC_MPLY,
            KC_LANG1,
            KC_LCTL,    OSM(MOD_LSFT), KC_LANG1,

            DYN_REC1,   KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     DYN_REC_STOP,
            KC_MINS,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_MINS,
            KC_H,       KC_J,     KC_K,    KC_L,    KC_SCLN, LT_2(QUOT),
            KC_EQL,     KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
            KC_LBRC,    KC_RBRC,  KC_LALT, KC_RGUI, KC_ENT,
            KC_APP,     KC_LANG2,
            KC_LANG2,
            KC_LANG2,   MO(SYMB), KC_SPC),


    /* Keymap 1: Symbol layer
     * ,--------------------------------------------------.     ,--------------------------------------------------.
     * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |     |      |  F6  |  F7  |  F8  |  F9  | F10  |  F12   |
     * |--------+------+------+------+------+------+------|     |------+------+------+------+------+------+--------|
     * |        |  !   |  @   |  #   |  $   |  %   |      |     |  _   |  ^   |  &   |  *   |  (   |  )   |  F11   |
     * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
     * |        |  BS  | CA_S | DEL  | CA_T |  ~   |------|     |------| Left | Down |  Up  | Right|  :   |   "    |
     * |--------+------+------+------+------+------|  ~   |     |  +   |------+------+------+------+------+--------|
     * |        | CA_Z |      | CA_D | CA_Y | CA_B |      |     |      | Home | PgDn | PgUp | End  |  ?   |   |    |
     * `--------------------------------------------------'     `--------------------------------------------------'
     */
    [SYMB] = KEYMAP(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   _______,
            _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, _______,
            _______, KC_BSPC, CA(S),   KC_DELT, CA(T),    KC_TILD,
            _______, CA(Z),   XXXXXXX, CA(D),   CA(Y),    CA(B),   KC_TILD,
            _______, _______, _______, _______, _______,
            _______, _______,
            _______,
            _______,  _______, _______,

            _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
            KC_UNDS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, KC_F11,
            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_COLN, KC_DQUO,
            KC_PLUS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_QUES, KC_PIPE,
            KC_LCBR, KC_RCBR, _______, _______,  _______,
            _______, _______,
            _______,
            _______, _______, _______),

    /* Keymap 2: Mouse and Media layer(H_ keys are VLC's shortcuts)
     * ,--------------------------------------------------.     ,--------------------------------------------------.
     * | RESET  |      |      |      |      |      |      |     |Sleep | Lock |Pause |Break |PrtSc |      |        |
     * |--------+------+------+------+------+------+------|     |------+------+------+------+------+------+--------|
     * |        | Mclk |WBack | MUp  | WFwd | G(M) | G(R) |     | H_F  | H_E  |VolDn | Mute |VolUp |      |        |
     * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
     * |        | Lclk |MsLeft|MsDown|MsRght| WhUp |------|     |------| H_A  | H_B  | H_C  | H_D  |  **  |        |
     * |--------+------+------+------+------+------|      |     | H_G  |------+------+------+------+------+--------|
     * |        | Rclk |WhLeft| App  |WhRght|WhDown|      |     |      |      | Prev | Play | Next |      |        |
     * `--------------------------------------------------'     `--------------------------------------------------'
     *                                                          .-------------.
     *                                                          | ACL0 | ACL0 |
     */
    [MDIA] = KEYMAP(
            RESET,   _______, _______, _______, _______, _______, _______,
            _______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(R),    _______,
            _______, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
            _______, KC_BTN2, KC_WH_L, G(M),    KC_WH_R, KC_WH_D, _______,
            _______, _______, _______, _______, _______,
            _______, _______,
            _______,
            _______, _______, _______,

            KC_SLEP, LOCK,    KC_PAUS, BREAK,   KC_PSCR, _______, _______,
            H(F),    H(E),    KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
            H(A),    H(B),    H(C),    H(D),    _______, _______,
            H(G),    XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
            _______, _______, _______, _______, _______,
            _______, _______,
            _______,
            _______, KC_ACL0, KC_ACL1),

    /* Keymap 3: Misc layer(Right hand keys for window control)
     * ,--------------------------------------------------.     ,--------------------------------------------------.
     * |   **   |   1  |   2  |   3  |   4  |   5  |   6  |     |      |M(HW) |M(AMA)|M(DKV)|M(YRH)|      |        |
     * |--------+------+------+------+------+-------------|     |------+------+------+------+------+------+--------|
     * |        |   7  |   8  |   9  |  10  |  11  |  12  |     |      |CA_Lft|CA_Dwn|CA_Up |CA_Rht|      |        |
     * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
     * |        |  BS  | PgUp | Del  |      |      |------|     |------|GA_Lft|GA_Dwn|GA_Up |GA_Rht|      |        |
     * |--------+------+------+------+------+------|AltF4 |     |      |------+------+------+------+------+--------|
     * |        |WBack | PgDw | WFwd |      |      |      |     |      | G_Lft| G_Dwn| G_Up | G_Rht|      |        |
     * `--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------'
     */
    [MISC] = KEYMAP(
            _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
            _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
            _______, KC_BSPC, KC_PGUP, KC_DELT, XXXXXXX, XXXXXXX,
            _______, KC_WBAK, KC_PGDN, KC_WFWD, XXXXXXX, XXXXXXX, LALT(KC_F4),
            _______, _______, _______, _______, _______,
            _______, _______,
            _______,
            _______, _______, _______,

            _______, M(M_HW), M(M_AMA),M(M_DKV),M(M_YRH),_______, _______,
            _______, CA(LEFT),CA(DOWN),CA(UP),  CA(RGHT),_______, _______,
            GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),_______, _______,
            _______, G(LEFT), G(DOWN), G(UP),   G(RGHT), _______, _______,
            _______, _______, _______, _______, _______,
            _______, _______,
            _______,
            _______, _______, _______),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if(!record->event.pressed) {
        return MACRO_NONE;
    }

    switch(id) {
        case M_HW:
            SEND_STRING("Hello World");
            break;
        case M_AMA:
            SEND_STRING("https://amazon.co.jp");
            break;
        case M_DKV:
            SEND_STRING("http://dokidokivisual.com");
            break;
        case M_YRH:
            SEND_STRING("http://www.ichijinsha.co.jp/yurihime/");
            break;
        case 101:
            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            break;
        case 102:
            // For resetting EEPROM
            eeconfig_init();
            break;
    }

    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

    switch (keycode) {
        // dynamically generate these.
        case EPRM:
            if (record->event.pressed) {
                eeconfig_init();
            }
            return false;
            break;
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            return false;
            break;
        case RGB_SLD:
            if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                rgblight_mode(1);
                #endif
            }
            return false;
            break;
        case RESET:
            // finish if return false
            if(record->event.pressed){
                ergodox_led_all_on();
                return true;
            }
        case DYN_REC_START1:
            if(record->event.pressed){
                ergodox_right_led_1_on();
            }
            break;
        case DYN_REC_START2:
            if(record->event.pressed){
                ergodox_right_led_2_on();
            }
            break;
        case DYN_MACRO_PLAY1:
            break;
        case DYN_MACRO_PLAY2:
            break;
        case DYN_REC_STOP:
            // pressedだと反応しない
            ergodox_led_all_off();
            break;
    }

    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
    return state;

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = biton32(state);
    switch (layer) {
        case 0:
            #ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
            #else
            rgblight_init();
            #endif
            break;
        case 1:
            ergodox_right_led_1_on();
            #ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
            #endif
            break;
        case 2:
            ergodox_right_led_2_on();
            #ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
            #endif
            break;
        case 3:
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
            #endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            #ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
            #endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
            #endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
            #endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            #ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
            #endif
            break;
        default:
            break;
    }

    return state;
};
