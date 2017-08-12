#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "sendchar.h"
#include "virtser.h"

void backlight_toggle(void){
  // static int flag=0;
  // if(!flag) ergodox_led_all_on();
  // else ergodox_led_all_off();
  // flag = !flag;
}

// for dynamic macro
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,
};

#define _DYN 3
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

#define LOCK RGUI(KC_L)
#define LT_2(key) LT(MDIA, KC_##key)
#define LT_3(key) LT(MISC, KC_##key)
#define H(key)  HYPR(KC_##key)
#define G(key)  RGUI(KC_##key)
#define CA(key) RCTL(RALT(KC_##key))
#define GA(key) RGUI(RALT(KC_##key))

#define DYN_REC1 DYN_REC_START1
#define DYN_PLY1 DYN_MACRO_PLAY1
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// TxBolt Codes
#define GRPMASK 0b11000000

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * |   L3   |   1  |   2  |   3  |   4  |   5  |DYN_R1|     |      |   6  |   7  |   8  |   9  |   0  | DYN_P1 |
 * |--------+------+------+------+------+------+------|     |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  | TAB  |     |  -   |   Y  |   U  |   I  |   O  |   P  |   -    |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * | Enter  |   A  |   S  |   D  |   F  |   G  |------|     |------|   H  |   J  |   K  |   L  |   ;  |  '/L2  |
 * |--------+------+------+------+------+------|  `   |     |  =   |------+------+------+------+------+--------|
 * |  Esc   |   Z  |   X  |   C  |   V  |   B  |      |     |      |   N  |   M  |   ,  |   .  |   /  |   \    |
 * |--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------|
 * |        | Gui  | Alt  | ESC  |  L3  |                                 |   [  |   ]  | Alt  | Gui  |        |
 * `------------------------------------'                                 `------------------------------------'
 *                                     .--------------.     .--------------.
 *                                     |  Eng  | Play |     |  App |  Jpn  |
 *                              ,------|-------|------|     |------|-------|-------.
 *                              |      |       | Eng  |     |  Jpn |       |       |
 *                              | Ctrl | Shift |------|     |------|  L2   | Space |
 *                              |      |       | Eng  |     |  Jpn |       |       |
 *                              `---------------------'     `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [BASE] = KEYMAP(  // layer 0 : default
      MO(MISC),       KC_1,     KC_2,    KC_3,    KC_4,   KC_5,  DYN_REC1,
      XXXXXXX,        KC_Q,     KC_W,    KC_E,    KC_R,   KC_T,  KC_TAB,
      KC_ENT,         KC_A,     KC_S,    KC_D,    KC_F,   KC_G,
      KC_ESC,         KC_Z,     KC_X,    KC_C,    KC_V,   KC_B,  KC_GRV,
      XXXXXXX,        KC_LGUI,  KC_LALT, KC_ESC,  MO(MISC),
               KC_LANG1,      KC_MPLY,
                              KC_LANG1,
      KC_LCTL, OSM(MOD_LSFT), KC_LANG1,

      XXXXXXX,     KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     DYN_PLY1,
      KC_MINS,     KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_MINS,
                   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  LT_2(QUOT),
      KC_EQL,      KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
                           KC_LBRC, KC_RBRC, KC_RALT, KC_RGUI,  XXXXXXX,
      KC_APP,      KC_LANG2,
      KC_LANG2,
      KC_LANG2,    MO(SYMB), KC_SPC
      ),


/* Keymap 1: Symbol layer
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |     |      |  F6  |  F7  |  F8  |  F9  | F10  |  F12   |
 * |--------+------+------+------+------+------+------|     |------+------+------+------+------+------+--------|
 * |        |  !   |  @   |  #   |  $   |  %   |      |     |  _   |  ^   |  &   |  *   |  (   |  )   |  F11   |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        |  BS  |      | DEL  | CA_T |  ~   |------|     |------| Left | Down |  Up  | Right|  :   |   "    |
 * |--------+------+------+------+------+------|  ~   |     |  +   |------+------+------+------+------+--------|
 * |        | CA_Z |      | CA_D | CA_Y | CA_F |      |     |      | Home | PgDn | PgUp | End  |  ?   |   |    |
 * `--------------------------------------------------'     `--------------------------------------------------'
 */
  [SYMB] = KEYMAP(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   _______,
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, _______,
      _______, KC_BSPC, XXXXXXX, KC_DELT, CA(T),    KC_TILD,
      _______, CA(Z),   XXXXXXX, CA(D),   CA(Y),    CA(F),   KC_TILD,
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
      _______, _______, _______
      ),

/* Keymap 2: Mouse and Media layer(H_ keys are VLC's shortcuts)
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |     |Sleep | Lock |      |      |PrtSc |      |        |
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
      _______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(M),    G(R),
      _______, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
      _______, KC_BTN2, KC_WH_L, KC_APP,  KC_WH_R, KC_WH_D, _______,
      _______, _______, _______, _______, _______,
      _______, _______,
      _______,
      _______, _______, _______,

      KC_SLEP, LOCK,    _______, _______, KC_PSCR, _______, _______,
      H(F),    H(E),    KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
               H(A),    H(B),    H(C),    H(D),    _______, _______,
      H(G),    XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                        _______, _______, _______, _______, _______,
               _______, _______,
                        _______,
      _______, KC_ACL0, KC_ACL1
      ),


/* Keymap 3: Misc layer(Right hand keys for window control)
 * ,--------------------------------------------------.     ,--------------------------------------------------.
 * |   **   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |     |      |M(HW) |M(AMA)|M(DKV)|      |      |        |
 * |--------+------+------+------+------+-------------|     |------+------+------+------+------+------+--------|
 * |        |  F7  |  F8  |  F9  | F10  | F11  | F12  |     |      |CA_Lft|CA_Dwn|CA_Up |CA_Rht|      |        |
 * |--------+------+------+------+------+------|      |     |      |------+------+------+------+------+--------|
 * |        |  BS  | PgUp | Del  |      |      |------|     |------|GA_Lft|GA_Dwn|GA_Up |GA_Rht|      |        |
 * |--------+------+------+------+------+------|AltF4 |     |      |------+------+------+------+------+--------|
 * |        |WBack | PgDw | WFwd |      |      |      |     |      |G_Lft |G_Dwn | G_Up |G_Rht |      |        |
 * `--------+------+------+------+------+-------------'     `-------------+------+------+------+------+--------'
 */
  [MISC] = KEYMAP(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      _______, KC_BSPC, KC_PGUP, KC_DELT, XXXXXXX, XXXXXXX,
      _______, KC_WBAK, KC_PGDN, KC_WFWD, XXXXXXX, XXXXXXX, LALT(KC_F4),
      _______, _______, _______, _______, _______,
      _______, _______,
      _______,
      _______, _______, _______,

      _______, M(M_HW), M(M_AMA),M(M_DKV),_______, _______, _______,
      _______, CA(LEFT),CA(DOWN),CA(UP),  CA(RGHT),_______, _______,
               GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),_______, _______,
      _______, G(LEFT), G(DOWN), G(UP),   G(RGHT), _______, _______,
                        _______, _______, _______, _______, _______,
               _______, _______,
                        _______,
      _______, _______, _______
      ),
};

enum {
  TD_ESC_LANG1 = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for LANG1
  // Other declarations would go here, separated by commas, if you have them
  [TD_ESC_LANG1] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_LANG1),
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
  if(!process_record_dynamic_macro(keycode, record))
    return false;

  // We need to track keypresses in all modes, in case the user
  // changes mode whilst pressing other keys.
  if(record->event.pressed)
    pressed_count++;
  else
    pressed_count--;

  // finish if return false
  if(record->event.pressed){
    switch(keycode){
      case RESET:
        ergodox_led_all_on();
        return true;
    }
  }

  return true;
}

#define M_S(key) D(LSFT), T(key), U(LSFT)
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  if(record->event.pressed){
    uint8_t grp = (id & GRPMASK) >> 6;
    chord[grp] |= id;

    switch(id){
      case M_HW:
        SEND_STRING("Hello World");
        break;
      case M_AMA:
        SEND_STRING("https://amazon.co.jp");
        break;
      case M_DKV:
        SEND_STRING("http://dokidokivisual.com");
        break;
    }
  } else {
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
};
