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

#define O(key) OSM(MOD_##key)
#define C(key) RCTL(KC_##key)
#define A(key) RALT(KC_##key)
#define G(key) RGUI(KC_##key)
#define C_T(key) RCTL_T(KC_##key)
#define A_T(key) RALT_T(KC_##key)
#define G_T(key) RGUI_T(KC_##key)

#define L_S MO(_SUB)
#define L_M MO(_MISC)
#define L_A MO(_ADVANCE)
#define LT_S(key) LT(_SUB, KC_##key)
#define LT_M(key) LT(_MISC, KC_##key)
#define LT_A(key) LT(_ADVANCE, KC_##key)

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
  _ADVANCE
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE, // 使用可能なキーコード
  COLEMAK,
  DVORAK,
  SUB,
  MISC,
  DYNAMIC_MACRO_RANGE, // このコード以降にダイナミックマクロのキーが割り当てられる
};

#include "dynamic_macro.h"

/* 理想のキーマップに向けて

   右下のAlt,Guiは必ず他のキーと使うからTapHoldにしてもいいのでは

   ESC 3回でLANG1
   LT_S(ESC)もいいかも

   CTR(ENTER)便利なんだけどそれらを同時に押せない

   Need _ADVANCE toggle key

   _QWERTY:
    左右斜めしたのLANGは試用中 思いの外使いやすい
    ESCにしたほうがいいのでは
   _SUB:
    左手薬指のTILD GRVは試用中
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |C(Ent)|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | '/M  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Esc  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl |      |      |Shift |    Space    | Sub  |      | ALT  | GUI  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_APP,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    C_T(MINUS)},
  {C_T(ENT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT_M(QUOT)},
  {KC_ESC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LT_A(BSLS)},
  {KC_LANG1,KC_LGUI, KC_LALT, XXXXXXX, O(LSFT), KC_SPC,         KC_SPC,  L_S,     KC_EQL,  KC_LALT, KC_RGUI, KC_LANG2}
},

/* Sub
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_SUB] = {
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12},
  {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F11},
  {__XXX__, KC_BSPC, KC_DEL,  KC_LBRC, KC_RBRC, KC_TILD,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LANG1,__XXX__},
  {_______, KC_EQL,  KC_PLUS, KC_LCBR, KC_RCBR, KC_GRV,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LANG2,_______},
  {_______, __XXX__, _______, _______, __XXX__, _______,        _______, __XXX__, _______, _______, _______, _______}
},

/* Misc(Mouse key & Window controll)
 * ,-----------------------------------------------------------------------------------.
 * |RESET |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_MISC] = {
  {RESET,   KC_FN1,  KC_FN2,  KC_FN3,  KC_FN4,  KC_FN5,         KC_FN6,  KC_FN7,  KC_FN8,  KC_FN9,  KC_FN10, KC_FN12},
  {_______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(R),           GC(LEFT),GC(DOWN),GC(UP),  GC(RGHT),XXXXXXX, KC_FN11},
  {__XXX__, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,        GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),XXXXXXX, __XXX__},
  {_______, KC_BTN2, KC_WH_L, G(M),    KC_WH_R, KC_WH_D,        G(LEFT), G(DOWN), G(UP),   G(RGHT), XXXXXXX, __XXX__},
  {_______, __XXX__, _______, _______, __XXX__, _______,        _______, __XXX__, _______, _______, _______, _______},
},

/* Advance
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADVANCE] = {
  {RESET,   _______, _______, QWERTY,  COLEMAK, DVORAK,         _______, _______, _______, _______, _______, _______},
  {DEBUG,   _______, DYN_PLY1,DYN_PLY2,_______, _______,        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______},
  {__XXX__, C(ENT),  DYN_REC1,DYN_REC2,CA(T),   A(F4),          H(A),    H(B),    H(C),    H(D),    H(F),    __XXX__},
  {TERM_ON, CA(S),   DYN_STOP,CA(D),   CA(Y),   CA(B),          H(E),    KC_MPRV, KC_MPLY, KC_MNXT, H(G),    __XXX__},
  {TERM_OFF,__XXX__, _______, _______, __XXX__, _______,        _______, __XXX__, _______, _______, _______, _______}
},



/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,           KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    LT_M(QUOT)},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LT_A(ENT) },
  {XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, L_M,     KC_SPC,         KC_SPC,  L_S,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL},
  {KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    LT_M(SLSH)},
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    LT_A(ENT) },
  {XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, L_M,     KC_SPC,         KC_SPC,  L_S,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
};

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
  }

  // ここに入れると、マウス操作とかのキー入力が途切れる
  // update_tri_layer(_SUB, _MISC, _ADVANCE);

  return true;
};
