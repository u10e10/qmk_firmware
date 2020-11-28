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

#pragma once

#define ORYX_CONFIGURATOR

#define ONESHOT_TAP_TOGGLE 5 // 固定キーロック
#define ONESHOT_TIMEOUT 3000 // Time (in ms) before the one shot key is released

#define TAPPING_TOGGLE  1
#define TAPPING_TERM    130
#define PERMISSIVE_HOLD // 時間経過前に他のキーを押すとHold扱い
// #define RETRO_TAPPING   // 時間内にキー入力がなければTap扱い DYN系との相性が悪い
// #define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

#define AUTO_SHIFT_TIMEOUT 100
#define NO_AUTO_SHIFT_ALPHA
// #define NO_AUTO_SHIFT_SPECIAL
// #define NO_AUTO_SHIFT_NUMERIC

#define DYNAMIC_MACRO_NO_NESTING
#define DYNAMIC_MACRO_SIZE 128

// 時間は多分100ms単位
#define MOUSEKEY_DELAY             0
#define MOUSEKEY_INTERVAL          16
#define MOUSEKEY_MAX_SPEED         16
#define MOUSEKEY_TIME_TO_MAX       50
#define MOUSEKEY_WHEEL_DELAY       0
#define MOUSEKEY_WHEEL_INTERVAL    10
#define MOUSEKEY_WHEEL_MAX_SPEED   10
#define MOUSEKEY_WHEEL_TIME_TO_MAX 80

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
