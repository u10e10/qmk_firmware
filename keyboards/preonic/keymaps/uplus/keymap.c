// vim: cursorcolumn

// noexpandtab tabstop=8 shiftwidth=8 softtabstop=8

/* Copyright 2015-2017 Jack Humbert
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

#include "preonic.h"
#include "action_layer.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define __XXX__ KC_TRNS // 明示的透過

#undef A
#undef G
#undef C

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



// process_record_userでpreonic_layersとpreonic_keycodesを紐付けてる
// update_tri_layerを使うのには必要なのかも
enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _SUB,
  _MISC,
  _ADVANCE,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE, // 使用可能なキーコード
  COLEMAK,
  DVORAK,
  SUB,
  MISC,
  ADVANCE,
  DYNAMIC_MACRO_RANGE, // このコード以降にダイナミックマクロのキーが割り当てられる
};

#include "dynamic_macro.h"

/* 理想のキーマップに向けて

   右下のAlt,Guiは必ず他のキーと使うからTapHoldにしてもいいのでは

   ESC 3回でLANG1
   L_S(ESC)もいいかも

   CTR(ENTER)便利なんだけどそれらを同時に押せない

   Need _ADVANCE toggle key

   _QWERTY:
    左右斜めしたのLANGは試用中 思いの外使いやすい
    ESCにしたほうがいいのでは
   _SUB:
    左手薬指のTILD GRVは試用中
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Main layer
[_QWERTY] = {
  {KC_APP,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    DYN_STOP},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS},
  {C_T(ENT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L_M(QUOT)},
  {KC_ESC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, L_A(BSLS)},
  {KC_MPLY, KC_LGUI, KC_LALT, KC_GRV,  O(LSFT), KC_LCTL,        LO_S,  KC_SPC,    KC_EQL,  KC_LALT, KC_RGUI, KC_ENT}
  // tty切替に使うためにRALT -> LALT
},

// F1~F12, Backspace, Delete, Cursor keys, Lang keys, Symbols
[_SUB] = {
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12},
  {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F11},
  {__XXX__, KC_BSPC, KC_DEL,  KC_LBRC, KC_RBRC, KC_TILD,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LANG2,KC_DQT},
  {_______, KC_EQL,  KC_PLUS, KC_LCBR, KC_RCBR, KC_GRV,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LANG1,KC_PIPE},
  {_______, __XXX__, __XXX__, _______, __XXX__, __XXX__,        __XXX__, __XXX__, _______, __XXX__, __XXX__, _______}
},

// Mouse keys, Window control shortcuts
[_MISC] = {
  {XXXXXXX, KC_FN1,  KC_FN2,  KC_FN3,  KC_FN4,  KC_FN5,         KC_FN6,  KC_FN7,  KC_FN8,  KC_FN9,  KC_FN10, KC_FN12},
  {_______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(R),           GC(Y),   GC(U),   GC(I),   GC(O),   G(W),    KC_FN11},
  {__XXX__, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,        GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),XXXXXXX, __XXX__},
  {__XXX__, KC_BTN2, KC_WH_L, G(M),    KC_WH_R, KC_WH_D,        G(LEFT), G(DOWN), G(UP),   G(RGHT), XXXXXXX, __XXX__},
  {_______, __XXX__, __XXX__, _______, __XXX__, __XXX__,        G(S),    G(F),    _______, __XXX__, __XXX__, _______},
},

// Media keys, Media control shortcuts, Dynamic macro keys, Sleep, etc...
[_ADVANCE] = {
  {RESET,   DYN_REC1,DYN_REC1,QWERTY,  COLEMAK, DVORAK,         _______, _______, _______, _______, KC_BRK,  KC_SLEP},
  {DEBUG,   DYN_PLY1,DYN_PLY2,XXXXXXX, KC_PSCR, A(F4),          XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX},
  {__XXX__, DYN_STOP,CA(S),   CA(D),   CA(T),   XXXXXXX,        H(A),    H(B),    H(C),    H(D),    H(G),    __XXX__},
  {TERM_ON, XXXXXXX, XXXXXXX, XXXXXXX, CA(Y),   CA(B),          H(E),    KC_MPRV, KC_MPLY, KC_MNXT, H(F),    __XXX__},
  {TERM_OFF,__XXX__, __XXX__, _______, __XXX__, __XXX__,        __XXX__, __XXX__, _______, __XXX__, __XXX__, _______}
},


[_COLEMAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,           KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    L_M(QUOT)},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, L_A(ENT) },
  {XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, LO_M,    KC_SPC,         KC_SPC,  LO_S,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_DVORAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL},
  {KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    L_M(SLSH)},
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    L_A(ENT) },
  {XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, LO_M,    KC_SPC,         KC_SPC,  LO_S,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
};

void send_key(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
      return false;
  }

  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case KC_ESC:
          if (record->event.pressed) {
              register_code(KC_ESC);
              register_code(KC_LANG2);
          } else {
              unregister_code(KC_ESC);
              unregister_code(KC_LANG2);
          }
          return false;
          break;
  }

  // ここに入れると、マウス操作とかのキー入力が途切れる
  // update_tri_layer(_SUB, _MISC, _ADVANCE);

  return true;
};
