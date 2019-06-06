#ifndef CONFIG_USER_H
#define CONFIG_USER_H
// https://docs.qmk.fm/config_options.html

#include "config_common.h"

#define ONESHOT_TAP_TOGGLE 5 // 固定キーロック
#define ONESHOT_TIMEOUT 3000 // Time (in ms) before the one shot key is released

#define TAPPING_TOGGLE  1
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

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND) }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

#endif
