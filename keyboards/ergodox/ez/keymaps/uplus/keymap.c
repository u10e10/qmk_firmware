#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "sendchar.h"
#include "virtser.h"

// http://qiita.com/ReSTARTR/items/970354940f49c67fb9fd
// https://github.com/jackhumbert/qmk_firmware/blob/master/quantum/keymap.h

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define LHND 3 // left hand layer

// TxBolt Codes
#define GRPMASK 0b11000000

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * |   L3   |   1  |   2  |   3  |   4  |   5  |      |     |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|     |------+------+------+------+------+------+--------|
 * |Tab/Hyp |   Q  |   W  |   E  |   R  |   T  | Eng  |     |  -   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|     |------|   H  |   J  |   K  |   L  | ;/ L2| '/Gui  |
 * |--------+------+------+------+------+------|  `   |     |  =   |------+------+------+------+------+--------|
 * |Esc/Gui |   Z  |   X  |   C  |   V  |   B  |      |     |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------'
 * |   L3   |      |   (  |   )  | Eng  |                                 |  Jpn |   [  |   ]  |      |        |
 * `------------------------------------'                                 `------------------------------------'
 *                                     ,--------------.     ,--------------.
 *                                     |   BS  | Eng  |     | Jpn  |ESC/Alt|
 *                              ,------|-------|------|     |------+-------+-------.
 *                              |      |       | Del  |     | App  | Alt/  |Enter/ |
 *                              |Space |LShift |------|     |------| Space |  L1   |
 *                              |      |       | Alt  |     | ESC  |       |       |
 *                              `---------------------'     `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
    MO(LHND),       KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   KC_NO,
    ALL_T(KC_TAB),  KC_Q,      KC_W,   KC_E,   KC_R,   KC_T,   KC_LANG1,
    KC_LCTL,        KC_A,      KC_S,   KC_D,   KC_F,   KC_G,
    GUI_T(KC_ESC),  KC_Z,      KC_X,   KC_C,   KC_V,   KC_B,   KC_GRV,
    MO(LHND),       KC_NO,     KC_LPRN,KC_RPRN,KC_LANG1,
                                               KC_BSPC,        KC_LANG1,
                                                               KC_DELT,
                               KC_SPC,         OSM(MOD_LSFT),  KC_LALT,

    KC_NO,       KC_6,   KC_7,     KC_8,    KC_9,      KC_0,             KC_NO,
    KC_MINS,     KC_Y,   KC_U,     KC_I,    KC_O,      KC_P,             KC_BSLS,
                 KC_H,   KC_J,     KC_K,    KC_L,      LT(MDIA, KC_SCLN),GUI_T(KC_QUOT),
    KC_EQL,      KC_N,   KC_M,     KC_COMM, KC_DOT,    CTL_T(KC_SLSH),   OSM(MOD_RSFT),
                         KC_LANG2, KC_LBRC, KC_RBRC,   KC_NO,            KC_NO,
    KC_LANG2,    ALT_T(KC_ESC),
    KC_APP,
    KC_ESC,      ALT_T(KC_SPC),    LT(SYMB, KC_ENT)
    ),


/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |     |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F12  |
 * |--------+------+------+------+------+-------------|     |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |     |      |   &  |   -  |  =   |  _   |  *   |   F11  |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        |   ^  |   $  |   (  |   )  |   ~  |------|     |------| Left | Down |  Up  | Right|  +   |        |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        |   #  |   %  |   [  |   ]  |   `  |      |     |      | Home | PgDn | PgUp | End  |      |        |
 * `--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                 |      |      |      |      |      |
 *   `----------------------------------'                                 `----------------------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_TRNS,
       KC_TRNS,   KC_EXLM,   KC_AT,     KC_LCBR,   KC_RCBR,   KC_PIPE,   KC_TRNS,
       KC_TRNS,   KC_CIRC,   KC_DLR,    KC_LPRN,   KC_RPRN,   KC_TILD,
       KC_TRNS,   KC_HASH,   KC_PERC,   KC_LBRC,   KC_RBRC,   KC_GRV,    KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                                                              KC_TRNS,   KC_TRNS,
                                                                         KC_TRNS,
                                                     KC_TRNS, KC_TRNS,   KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F12,
       KC_TRNS, KC_AMPR, KC_MINS, KC_EQL,  KC_UNDS,  KC_ASTR,  KC_F11,
                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_PLUS,  KC_TRNS,
       KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS,  KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |     |Sleep |      |      |      |      |PrtSc |        |
 * |--------+------+------+------+------+-------------|     |------+------+------+------+------+------+--------|
 * |        |      |WBack | MsUp | WFwd |      |      |     |      |      |VolDn | Mute |VolUp |      |        |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        | Lclk |MsLeft|MsDown|MsRght| WhUp |------|     |------| Left | Down |  Up  | Right|      |        |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        | Rclk |      |      |      | WhDn |      |     |      |      | Prev | Play | Next |      |        |
 * `--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                 |      |      |      |      |        |
 *   `----------------------------------'                                 `------------------------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK, KC_MS_U, KC_WFWD, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
       KC_TRNS, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS,
                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Left hand layer
 *
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |     |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|     |------+------+------+------+------+------+--------|
 * |        |  F7  |  F8  |  F9  | F10  | F11  | F12  |     |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        |      |      |Enter |BSpace|Delete|------|     |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        |      |      |WBack | PgUp | WFwd |      |     |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------'
 *   |      |      |      |      | PgDn |                                 |      |      |      |      |      |
 *   `----------------------------------'                                 `----------------------------------'
 */
// Left hand layer
[LHND] = KEYMAP(
       // left hand
       KC_TRNS,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,
       KC_TRNS,   KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_ENT,    KC_BSPC,   KC_DELT,
       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_WBAK,   KC_PGUP,   KC_WFWD,   KC_TRNS,
       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_PGDN,
                                                              KC_TRNS,   KC_TRNS,
                                                                         KC_TRNS,
                                                     KC_NO,   KC_NO,     KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
                M(0),    M(1),    M(2),    KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};



const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

uint8_t chord[4] = {0,0,0,0};
uint8_t pressed_count = 0;

void send_chord(void)
{
  for(uint8_t i = 0; i < 4; i++)
  {
    if(chord[i])
      virtser_send(chord[i]);
  }
  virtser_send(0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // We need to track keypresses in all modes, in case the user
  // changes mode whilst pressing other keys.
  if (record->event.pressed)
    pressed_count++;
  else
    pressed_count--;
  return true;
}

#define M_S(key) D(LSFT), T(key), U(LSFT)
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function

    if (record->event.pressed) {
        uint8_t grp = (id & GRPMASK) >> 6;
        chord[grp] |= id;
        switch(id){
            case 0:
                return MACRO(I(0), T(H), T(E), T(L), T(L), T(O), T(SPC), T(W), T(O), T(R), T(L), T(D), END);
                break;
            case 1:
                return MACRO(I(0), T(H), T(T), T(T), T(P), T(S), M_S(SCLN), T(SLSH), T(SLSH), T(A), T(M), T(A), T(Z), T(O), T(N), T(DOT), T(C), T(O), T(DOT), T(J), T(P), END);
                break;
            case 2:
                return MACRO(I(0), T(H), T(T), T(T), T(P), M_S(SCLN), T(SLSH), T(SLSH), T(D), T(O), T(K), T(I), T(D), T(O), T(K), T(I), T(V), T(I), T(S), T(U), T(A), T(L), T(DOT), T(C), T(O), T(M), END);
                break;
        }
  }
  else {
    if (pressed_count == 0) {
      send_chord();
      chord[0] = chord[1] = chord[2] = chord[3] = 0;
    }
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_2_on();
            break;
        case 2:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
