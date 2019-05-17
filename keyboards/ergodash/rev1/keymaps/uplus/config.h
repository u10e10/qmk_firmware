/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// place overrides here

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS


#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 24
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17



#define ONESHOT_TAP_TOGGLE 5 // 固定キーロック
#define ONESHOT_TIMEOUT 3000 // Time (in ms) before the one shot key is released

#define TAPPING_TOGGLE  1
#undef TAPPING_TERM
#define TAPPING_TERM    120
// #define RETRO_TAPPING   // 時間内にキー入力がなければTap扱い DYN系との相性が悪い
#define PERMISSIVE_HOLD // 時間経過前に他のキーを押すとHold扱い
// #define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

#define AUTO_SHIFT_TIMEOUT 100
#define NO_AUTO_SHIFT_ALPHA
// #define NO_AUTO_SHIFT_SPECIAL
// #define NO_AUTO_SHIFT_NUMERIC

#define DYNAMIC_MACRO_SIZE 128

// https://beta.docs.qmk.fm/features/feature_mouse_keys
// アクセルを向こうにして3段階にする
// #define MK_3_SPEED

// アクセルモードでもACL0~2は使えるけど0が早い
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_INTERVAL       10
#define MOUSEKEY_MAX_SPEED      10
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 60


// 無効だとタップしてモード切替になる
#define MK_MOMENTARY_ACCEL

#define MK_C_INTERVAL_UNMOD 5
#define MK_C_INTERVAL_0     5
#define MK_C_INTERVAL_1     5
#define MK_C_INTERVAL_2     5

#define MK_C_OFFSET_UNMOD   12
#define MK_C_OFFSET_0       2
#define MK_C_OFFSET_1       16
#define MK_C_OFFSET_2       32

#define MK_W_C_INTERVAL_UNMOD 16
#define MK_W_C_OFFSET_UNMOD   10
