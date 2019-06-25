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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

#define ONESHOT_TAP_TOGGLE 5 // 固定キーロック
#define ONESHOT_TIMEOUT 3000 // Time (in ms) before the one shot key is released

#define TAPPING_TOGGLE  1
#undef TAPPING_TERM
#define TAPPING_TERM    150
// #define RETRO_TAPPING   // 時間内にキー入力がなければTap扱い DYN系との相性が悪い
#define PERMISSIVE_HOLD // 時間経過前に他のキーを押すとHold扱い
// #define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

#define AUTO_SHIFT_TIMEOUT 100
#define NO_AUTO_SHIFT_ALPHA
// #define NO_AUTO_SHIFT_SPECIAL
// #define NO_AUTO_SHIFT_NUMERIC

#define MOUSEKEY_DELAY          0
#define MOUSEKEY_INTERVAL       10
#define MOUSEKEY_MAX_SPEED      10
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 60

#define DYNAMIC_MACRO_SIZE 128

#endif /* CONFIG_USER_H */
